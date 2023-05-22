#ifndef _FE_CORE_PARALLEL_PROXY_PTR_IMPLEMENTATION_HXX_
#define _FE_CORE_PARALLEL_PROXY_PTR_IMPLEMENTATION_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#pragma warning(disable : 4302)
#pragma warning(disable : 4311)
#include "proxy_ptr.interface.hxx"
#include "../../memory/allocator/allocator.implementation.hxx"


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class allocator >
T proxy_ptr<T, allocator>::s_null; // null object is can be expensive if the size of T type is enormous. T must not be a singleton type.


template <typename T, class allocator>
_FORCE_INLINE_ proxy_ptr<T, allocator>::~proxy_ptr() noexcept
{
	if (unique_ptr<T, allocator>::s_indirection_list.m_is_quick_access_ptr_on_update.load() == false)
	{
		this->m_quick_access_ptr.load(std::memory_order_relaxed)->store(nullptr);
		return;
	}

	for (var::uint64 idx = 0; idx < unique_ptr<T, allocator>::s_indirection_list.size(); ++idx)
	{
		if (unique_ptr<T, allocator>::s_indirection_list[idx].load(std::memory_order_acquire) == this)
		{
			unique_ptr<T, allocator>::s_indirection_list[idx].store(nullptr);
			return;
		}
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ proxy_ptr<T, allocator>::proxy_ptr(const proxy_ptr<T, allocator>& copy_ref_p) _FE_EXCEPT_
{
	if (exception::handle_exceptions( IF(copy_ref_p.m_proxy_ptr.load() == nullptr), FE::_LOG_EXCEPTION_HISTORY_, "const proxy_ptr<T, allocator>& copy_ref_p is nullptr.", _EXCEPTION_ORIGIN_ )) 
	{
		return;
	}

	this->m_proxy_ptr.store(copy_ref_p.m_proxy_ptr.load());

	if (unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
		return;
	}

	unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
	this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
}

template <typename T, class allocator>
_FORCE_INLINE_ proxy_ptr<T, allocator>::proxy_ptr(proxy_ptr<T, allocator>&& rvalue_p) _FE_EXCEPT_ : m_proxy_ptr()
{
	if (exception::handle_exceptions(	IF(rvalue_p.m_proxy_ptr.load() == nullptr),
										FE::_LOG_EXCEPTION_HISTORY_,
										"const proxy_ptr<T, allocator>& copy_ref_p is nullptr.",
										_EXCEPTION_ORIGIN_
										)
		) 
	{
		return;
	}

	this->m_proxy_ptr.store(rvalue_p.m_proxy_ptr.load());

	if (unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
		return;
	}

	unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
	this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
}

template <typename T, class allocator>
_FORCE_INLINE_ proxy_ptr<T, allocator>& proxy_ptr<T, allocator>::operator=(const proxy_ptr<T, allocator>& copy_ref_p) _FE_EXCEPT_
{
	if (exception::handle_exceptions(	IF(copy_ref_p.m_proxy_ptr.load() == nullptr),
										FE::_LOG_EXCEPTION_HISTORY_,
										"const proxy_ptr<T, allocator>& copy_ref_p is nullptr.",
										_EXCEPTION_ORIGIN_
										)
		) 
	{
		return *this;
	}

	this->m_proxy_ptr.store(copy_ref_p.m_proxy_ptr.load());

	if (unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
		return *this;
	}

	unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
	this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
	return *this;
}

template <typename T, class allocator>
_FORCE_INLINE_ proxy_ptr<T, allocator>& proxy_ptr<T, allocator>::operator=(proxy_ptr<T, allocator>&& rvalue_p) _FE_EXCEPT_
{
	if (exception::handle_exceptions(	IF(rvalue_p.m_proxy_ptr.load() == nullptr),
										FE::_LOG_EXCEPTION_HISTORY_,
										"const proxy_ptr<T, allocator>& copy_ref_p is nullptr.",
										_EXCEPTION_ORIGIN_
										)
		) 
	{
		return *this;
	}

	this->m_proxy_ptr.store(rvalue_p.m_proxy_ptr.load());

	if (unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity())
	{
		this->m_quick_access_ptr.store(unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
		return *this;
	}

	unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
	this->m_quick_access_ptr.store(	unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed);
	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ T& proxy_ptr<T, allocator>::operator*() noexcept
{
	if (this->m_proxy_ptr.load() != nullptr)
	{
		this->m_was_previous_access_violation.store(false);
		return *( this->m_proxy_ptr.load() );
	}

	this->m_was_previous_access_violation.store(true);
	return proxy_ptr<T, allocator>::s_null;
}

template<typename T, class allocator>
_FORCE_INLINE_ T* proxy_ptr<T, allocator>::operator->() noexcept
{
	if (this->m_proxy_ptr.load() != nullptr)
	{
		this->m_was_previous_access_violation.store(false);
		return this->m_proxy_ptr.load();
	}

	this->m_was_previous_access_violation.store(true);
	return &(proxy_ptr<T, allocator>::s_null);
}

template<typename T, class allocator>
_FORCE_INLINE_ void proxy_ptr<T, allocator>::swap(proxy_ptr<T, allocator>& A_ref_p, proxy_ptr<T, allocator>& B_ref_p) noexcept
{
	proxy_ptr<T, allocator> l_tmp = A_ref_p;
	A_ref_p = B_ref_p;
	B_ref_p = l_tmp;
}


END_NAMESPACE


#endif