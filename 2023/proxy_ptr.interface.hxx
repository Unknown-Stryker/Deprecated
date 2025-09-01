#ifndef _FE_CORE_PARALLEL_PROXY_PTR_INTERFACE_HXX_
#define _FE_CORE_PARALLEL_PROXY_PTR_INTERFACE_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#pragma warning(disable : 4302)
#pragma warning(disable : 4311)
#include "../../memory/allocator/allocator.interface.hxx"


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class allocator>
class unique_ptr;

template <typename T, class allocator>
class proxy_table;


/*template class FE::memory::proxy_ptr is a smart pointer that promises null safety. If the pointer to the object(unique_ptr) is nullptr, proxy_ptr will avoid the invalid address.
proxy_ptr<T> does not manage the lifecycle of its indirection target, which is very similar to std::weak_ptr<T>.
allocator interface info:
static T* allocate(size_t count_p);
static void deallocate(T* ptr_p, size_t count_p);
e.g. when invoked: allocator::allocate(...); */
template <typename T, class allocator = FE::memory::new_delete_allocator<T>>
class proxy_ptr final
{
	friend class unique_ptr<T, allocator>;
	friend class proxy_table<T, allocator>;
private_member_variables:
	std::atomic<var::boolean> m_was_previous_access_violation;
	std::atomic< std::atomic< volatile proxy_ptr<T, allocator>* >* > m_quick_access_ptr;
	std::atomic<T*> m_proxy_ptr;

private_static_variables:
	static T s_null; // null object can be expensive if the size of T type is enormous. T must not be a singleton type.

public_constructors:
	_FORCE_INLINE_ proxy_ptr() noexcept : m_proxy_ptr() {}
	_FORCE_INLINE_ proxy_ptr(unique_ptr<T, allocator>& unique_ref_p) noexcept
	{
		if (unique_ref_p.m_unique_ptr.load() == nullptr) { return; }

		if ( unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity() )
		{
			this->m_quick_access_ptr.store(	unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed );
			this->m_proxy_ptr.store( unique_ref_p.m_unique_ptr.load() );
			return;
		}

		unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
		this->m_quick_access_ptr.store(	unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed );
		this->m_proxy_ptr.store( unique_ref_p.m_unique_ptr.load() );
	}


public_destructor:
	_FORCE_INLINE_ ~proxy_ptr() noexcept;

public_copy_constructor:
	_FORCE_INLINE_ proxy_ptr(const proxy_ptr<T, allocator>& copy_ref_p) noexcept;

public_move_constructor:
	_FORCE_INLINE_ proxy_ptr(proxy_ptr<T, allocator>&& rvalue_p) noexcept;

public_copy_assignment_operator:
	_FORCE_INLINE_ proxy_ptr<T, allocator>& operator=(const proxy_ptr<T, allocator>& copy_ref_p) noexcept;

public_move_assignment_operator:
	_FORCE_INLINE_ proxy_ptr<T, allocator>& operator=(proxy_ptr<T, allocator>&& rvalue_p) noexcept;

public_assignment_operator:
	_FORCE_INLINE_ proxy_ptr<T, allocator>& operator=(unique_ptr<T, allocator>& unique_ref_p) noexcept
	{
		if (unique_ref_p.m_unique_ptr.load() == nullptr) { return *this; }

		if (unique_ptr<T, allocator>::s_indirection_list.m_is_quick_access_ptr_on_update.load() == false &&
			this->m_quick_access_ptr.load(std::memory_order_relaxed) != nullptr &&
			this->m_quick_access_ptr.load(std::memory_order_relaxed)->load() == this)
		{
			this->m_proxy_ptr.store( unique_ref_p.m_unique_ptr.load() );
			return *this;
		}

		if (unique_ptr<T, allocator>::s_indirection_list.size() < unique_ptr<T, allocator>::s_indirection_list.capacity())
		{
			this->m_quick_access_ptr.store(	unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed );
			this->m_proxy_ptr.store( unique_ref_p.m_unique_ptr.load() );
			return *this;
		}

		unique_ptr<T, allocator>::s_indirection_list.reserve( unique_ptr<T, allocator>::s_indirection_list_reservation_size.load(std::memory_order_acquire) );
		this->m_quick_access_ptr.store(	unique_ptr<T, allocator>::s_indirection_list.emplace_back(this), std::memory_order_relaxed );
		this->m_proxy_ptr.store( unique_ref_p.m_unique_ptr.load() );
		return *this;
	}

public_operators:
	_FORCE_INLINE_ T& operator*() noexcept;
	_FORCE_INLINE_ T* operator->() noexcept;

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >(const proxy_ptr<T, allocator>& left_p, const proxy_ptr<T, allocator>& right_p) noexcept
	{
		return (left_p.m_proxy_ptr > right_p.m_proxy_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >=(const proxy_ptr<T, allocator>& left_p, const proxy_ptr<T, allocator>& right_p) noexcept
	{
		return (left_p.m_proxy_ptr >= right_p.m_proxy_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <(const proxy_ptr<T, allocator>& left_p, const proxy_ptr<T, allocator>& right_p) noexcept
	{
		return (left_p.m_proxy_ptr < right_p.m_proxy_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <=(const proxy_ptr<T, allocator>& left_p, const proxy_ptr<T, allocator>& right_p) noexcept
	{
		return (left_p.m_proxy_ptr <= right_p.m_proxy_ptr) ? true : false;
	}

public_static_methods:
	_FORCE_INLINE_ static void swap(proxy_ptr<T, allocator>& A_ref_p, proxy_ptr<T, allocator>& B_ref_p) noexcept;

	_FORCE_INLINE_ boolean was_it_access_violation() const noexcept { return this->m_was_previous_access_violation.load(std::memory_order_relaxed); }
};


END_NAMESPACE
#endif