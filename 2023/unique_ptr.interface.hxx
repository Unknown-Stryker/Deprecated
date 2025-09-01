#ifndef _FE_CORE_PARALLEL_UNIQUE_PTR_INTERFACE_HXX_
#define _FE_CORE_PARALLEL_UNIQUE_PTR_INTERFACE_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "../../memory/allocator/allocator.interface.hxx"


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class allocator>
class proxy_ptr;


template <typename T, class allocator>
class proxy_table;


/* template class FE::memory::unique_ptr is a smart pointer that manages the lifecycle of its pointed object withh a unique_ptr ownership policy. The object being pointed will be automatically de-allocated at the unsafe_end of its owner's lifecycle.
unique_ptr<T> is nullptr when anything has not been assigned. Its allocation and deletion algorithm can be modified by passing a custom template allocator class compatible with the interface of FE::memory::new_delete_allocator<T> via its template argument “allocator”.
allocator interface info:
static _NODISCARD_ T* allocate(size_t count_p) noexcept;
static void deallocate(T* ptr_p, size_t count_p) noexcept;
e.g. when invoked: allocator::allocate(...); */
template <typename T, class allocator = FE::memory::new_delete_allocator<T>>
class unique_ptr final
{
	friend class proxy_ptr<T, allocator>;

private_member_variables:
	std::atomic<var::boolean> m_was_previous_access_violation;
	std::atomic<T*> m_unique_ptr;

private_static_variables:
	static proxy_table<T, allocator> s_indirection_list;
	static T s_null; // null object can be expensive if the size of T type is enormous. T must not be a singleton type.

public_static_variables:
	static std::atomic<var::uint64> s_indirection_list_reservation_size;

public_constructors:
	_FORCE_INLINE_ unique_ptr() noexcept;
	_FORCE_INLINE_ unique_ptr(const T& value_ref_p) noexcept;
	_FORCE_INLINE_ unique_ptr(T&& rvalue_p) noexcept;

public_destructor:
	_FORCE_INLINE_ ~unique_ptr() noexcept;

public_copy_constructor:
	_FORCE_INLINE_ unique_ptr(unique_ptr<T, allocator>& copy_ref_p) noexcept;

public_move_constructor:
	_FORCE_INLINE_ unique_ptr(unique_ptr<T, allocator>&& move_p) noexcept;

public_copy_assignment_operator:
	_FORCE_INLINE_ unique_ptr<T, allocator>& operator=(unique_ptr<T, allocator>& copy_ref_p) noexcept;

public_move_assignment_operator:
	_FORCE_INLINE_ unique_ptr<T, allocator>& operator=(unique_ptr<T, allocator>&& move_p) noexcept;

public_assignment_operator:
	_FORCE_INLINE_ unique_ptr<T, allocator>& operator=(const T& value_ref_p) noexcept;
	_FORCE_INLINE_ unique_ptr<T, allocator>& operator=(T&& rvalue_p) noexcept;

public_operators:
	_FORCE_INLINE_ T& operator*() noexcept;
	_FORCE_INLINE_ T* operator->() noexcept;

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >(const unique_ptr<T, allocator>& left_ref_p, const unique_ptr<T, allocator>& right_ref_p) noexcept
	{
		return (left_ref_p.m_unique_ptr > right_ref_p.m_unique_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >=(const unique_ptr<T, allocator>& left_ref_p, const unique_ptr<T, allocator>& right_ref_p) noexcept
	{
		return (left_ref_p.m_unique_ptr >= right_ref_p.m_unique_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <(const unique_ptr<T, allocator>& left_ref_p, const unique_ptr<T, allocator>& right_ref_p) noexcept
	{
		return (left_ref_p.m_unique_ptr < right_ref_p.m_unique_ptr) ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <=(const unique_ptr<T, allocator>& left_ref_p, const unique_ptr<T, allocator>& right_ref_p) noexcept
	{
		return (left_ref_p.m_unique_ptr <= right_ref_p.m_unique_ptr) ? true : false;
	}

public_static_methods:
	_FORCE_INLINE_ static void swap(unique_ptr<T, allocator>& A_ref_p, unique_ptr<T, allocator>& B_ref_p) noexcept;

public_methods:
	_FORCE_INLINE_ void discard() noexcept;
	_FORCE_INLINE_ boolean is_valid() const noexcept;
	_FORCE_INLINE_ boolean was_it_access_violation() const noexcept { return this->m_was_previous_access_violation.load(std::memory_order_relaxed); }
	_FORCE_INLINE_ uint32 max_unique_array_length() const noexcept { return _UINT32_MAX_; }

	_FORCE_INLINE_ void shrink_to_fit_indirection_list() noexcept;
	_FORCE_INLINE_ void sort_indirection_list() const noexcept;
};


END_NAMESPACE
#endif