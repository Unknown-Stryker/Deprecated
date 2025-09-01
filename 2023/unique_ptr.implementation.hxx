#ifndef _FE_CORE_PARALLEL_UNIQUE_PTR_IMPLEMENTATION_HXX_
#define _FE_CORE_PARALLEL_UNIQUE_PTR_IMPLEMENTATION_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "unique_ptr.interface.hxx"
#include "../../memory/allocator/allocator.implementation.hxx"
#include "../../macros/attributes.h"


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class allocator>
std::atomic<var::uint64> unique_ptr<T, allocator>::s_indirection_list_reservation_size = 1048576; //8 mb

template <typename T, class allocator>
proxy_table<T, allocator> unique_ptr<T, allocator>::s_indirection_list;

template <typename T, class allocator>
T unique_ptr<T, allocator>::s_null; // null object can be expensive if the size of T type is enormous. T must not be a singleton type.


template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::unique_ptr() noexcept : m_was_previous_access_violation(false), m_unique_ptr()
{
	if (unique_ptr<T, allocator>::s_indirection_list.size() >= unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		unique_ptr<T, allocator>::s_indirection_list.reserve(unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_relaxed));
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::unique_ptr(const T& value_ref_p) noexcept : m_was_previous_access_violation(false), m_unique_ptr(allocator::allocate(1))
{
	*(this->m_unique_ptr.load(std::memory_order_relaxed)) = value_ref_p;
	if (unique_ptr<T, allocator>::s_indirection_list.size() >= unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		unique_ptr<T, allocator>::s_indirection_list.reserve(unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_relaxed));
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::unique_ptr(T&& rvalue_p) noexcept : m_was_previous_access_violation(false), m_unique_ptr(allocator::allocate(1))
{
	*(this->m_unique_ptr.load(std::memory_order_relaxed)) = rvalue_p;
	if (unique_ptr<T, allocator>::s_indirection_list.size() >= unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		unique_ptr<T, allocator>::s_indirection_list.reserve(unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_relaxed));
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::~unique_ptr() noexcept
{
	T* l_subject_to_delete_ptr = this->m_unique_ptr.exchange(nullptr);

	if (l_subject_to_delete_ptr == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == l_subject_to_delete_ptr)
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(nullptr);
		}
	}

	allocator::deallocate(l_subject_to_delete_ptr, 1);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::unique_ptr(unique_ptr<T, allocator>& copy_ref_p) noexcept : m_was_previous_access_violation(false)
{
	this->m_unique_ptr = copy_ref_p.m_unique_ptr.exchange(nullptr);

	if (this->m_unique_ptr.load(std::memory_order_relaxed) == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == this->m_unique_ptr.load(std::memory_order_relaxed))
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(this);
		}
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>::unique_ptr(unique_ptr<T, allocator>&& move_p) noexcept : m_was_previous_access_violation(false)
{
	this->m_unique_ptr = move_p.m_unique_ptr.exchange(nullptr);

	if (this->m_unique_ptr.load(std::memory_order_relaxed) == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == this->m_unique_ptr.load(std::memory_order_relaxed))
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(this);
		}
	}
}

template<typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>& unique_ptr<T, allocator>::operator=(unique_ptr<T, allocator>& copy_ref_p) noexcept
{
	this->m_unique_ptr = copy_ref_p.m_unique_ptr.exchange(nullptr);

	if (this->m_unique_ptr.load(std::memory_order_relaxed) == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == this->m_unique_ptr.load(std::memory_order_relaxed))
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(this);
		}
	}

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>& unique_ptr<T, allocator>::operator=(unique_ptr<T, allocator>&& move_p) noexcept
{
	this->m_unique_ptr = move_p.m_unique_ptr.exchange(nullptr);

	if (this->m_unique_ptr.load(std::memory_order_relaxed) == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == this->m_unique_ptr.load(std::memory_order_relaxed))
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(this);
		}
	}

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>& unique_ptr<T, allocator>::operator=(const T& value_ref_p) noexcept
{
	if (this->m_unique_ptr.load(std::memory_order_relaxed) != nullptr)
	{
		*(this->m_unique_ptr.load(std::memory_order_relaxed)) = value_ref_p;
	}
	else
	{
		this->m_unique_ptr.store(allocator::allocate(1));
		*(this->m_unique_ptr.load(std::memory_order_relaxed)) = value_ref_p;
	}

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique_ptr<T, allocator>& unique_ptr<T, allocator>::operator=(T&& rvalue_p) noexcept
{
	if (this->m_unique_ptr.load(std::memory_order_relaxed) != nullptr)
	{
		*(this->m_unique_ptr.load(std::memory_order_relaxed)) = rvalue_p;
	}
	else
	{
		this->m_unique_ptr.store(allocator::allocate(1));
		*(this->m_unique_ptr.load(std::memory_order_relaxed)) = rvalue_p;
	}

	return *this;
}

template <typename T, class allocator>
_FORCE_INLINE_ T& unique_ptr<T, allocator>::operator*() noexcept
{
	if (this->m_unique_ptr.load(std::memory_order_relaxed) != nullptr)
#if _HAS_CXX20_
		_LIKELY_
#endif
	{
		this->m_was_previous_access_violation.store(false);
		return *(this->m_unique_ptr.load(std::memory_order_relaxed));
	}

	this->m_was_previous_access_violation.store(true);
	return unique_ptr<T, allocator>::s_null;
}

template <typename T, class allocator>
_FORCE_INLINE_ T* unique_ptr<T, allocator>::operator->() noexcept
{
	if (this->m_unique_ptr.load(std::memory_order_relaxed) != nullptr)
#if _HAS_CXX20_
		_LIKELY_
#endif
	{
		this->m_was_previous_access_violation.store(false);
		return this->m_unique_ptr.load(std::memory_order_relaxed);
	}

	this->m_was_previous_access_violation.store(true);
	return &(unique_ptr<T, allocator>::s_null);
}

template <typename T, class allocator >
_FORCE_INLINE_ void unique_ptr<T, allocator>::swap(unique_ptr<T, allocator>& A_ref_p, unique_ptr<T, allocator>& B_ref_p) noexcept
{
	unique_ptr<T, allocator> l_tmp = A_ref_p;
	A_ref_p = B_ref_p;
	B_ref_p = l_tmp;
}

template <typename T, class allocator>
_FORCE_INLINE_ void unique_ptr<T, allocator>::discard() noexcept
{
	T* l_subject_to_delete_ptr = this->m_unique_ptr.exchange(nullptr);

	if (l_subject_to_delete_ptr == nullptr) { return; }

	// notify all...
	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load() != nullptr &&
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.load() == l_subject_to_delete_ptr)
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].load()->m_proxy_ptr.store(nullptr);
		}
	}

	allocator::deallocate(l_subject_to_delete_ptr, 1);
}

template <typename T, class allocator >
_FORCE_INLINE_ boolean unique_ptr<T, allocator>::is_valid() const noexcept
{
	return (this->m_unique_ptr.load(std::memory_order_relaxed) != nullptr) ? true : false;
}

template<typename T, class allocator>
_FORCE_INLINE_ void unique_ptr<T, allocator>::shrink_to_fit_indirection_list() noexcept
{
	unique_ptr<T, allocator>::shrink_to_fit_indirection_list();
}

template<typename T, class allocator>
_FORCE_INLINE_ void unique_ptr<T, allocator>::sort_indirection_list() const noexcept
{
	unique_ptr<T, allocator>::s_indirection_list.sort();
}


END_NAMESPACE
#endif