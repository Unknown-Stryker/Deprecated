#ifndef _FE_CORE_PARALLEL_PROXY_TABLE_INTERFACE_HXX_
#define _FE_CORE_PARALLEL_PROXY_TABLE_INTERFACE_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "../allocator/allocator.interface.hxx"
#include "../private/memory.hxx"
#include "../heap_utilization.hpp"


// this class will be replaced with concurrent_hash_map


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class allocator>
class unique_ptr;

template <typename T, class allocator>
class proxy_ptr;

// update hash codes of indirects immediately right after the unsafe_end of reserve() / sort() / shrink_to_fit()
template <typename T, class allocator = FE::new_delete_allocator<T>>
class proxy_table final
{
	friend class unique_ptr<T, allocator>;
	friend class proxy_ptr<T, allocator>;
private_member_variables:
	std::atomic<var::boolean> m_is_quick_access_ptr_on_update;
	std::atomic<var::uint64> m_element_count;
	std::atomic<var::uint64> m_array_total_length;
	std::atomic< std::atomic<volatile proxy_ptr<T, allocator>*>* > m_pointer_array_ptr;
	std::mutex m_lock;

private_static_variables:
	static std::atomic< volatile proxy_ptr<T, allocator>* > s_null;

public_constructors:
	_FORCE_INLINE_ proxy_table() noexcept
		: m_is_quick_access_ptr_on_update(false), m_element_count(0), m_array_total_length(0), m_pointer_array_ptr(nullptr) {}

	_FORCE_INLINE_ proxy_table(FE::initial_reservation&& initial_reservation_size_p) noexcept
		: m_is_quick_access_ptr_on_update(false), m_element_count(0), m_array_total_length(initial_reservation_size_p._length), m_pointer_array_ptr(FE::trackable_calloc<std::atomic< volatile proxy_ptr<T, allocator>* >>(initial_reservation_size_p._length, sizeof(volatile proxy_ptr<T, allocator>*))) {}

public_destructor:
	_FORCE_INLINE_ ~proxy_table() noexcept = default;

public_copy_constructor:
	_FORCE_INLINE_ proxy_table(const proxy_table<T, allocator>& other_ref_p) noexcept = delete;

public_move_constructor:
	_FORCE_INLINE_ proxy_table(proxy_table<T, allocator>&& move_p) noexcept = delete;

public_copy_assignment_operator:
	_FORCE_INLINE_ proxy_table<T, allocator>& operator=(const proxy_table<T, allocator>& other_ref_p) noexcept = delete;

public_move_assignment_operator:
	_FORCE_INLINE_ proxy_table<T, allocator>& operator=(proxy_table<T, allocator>&& move_p) noexcept = delete;

public_operators:
	_FORCE_INLINE_ std::atomic< volatile proxy_ptr<T, allocator>* >& operator[](index_t idx_p) noexcept;

public_methods:
	_FORCE_INLINE_ std::atomic< volatile proxy_ptr<T, allocator>* >* emplace_back(proxy_ptr<T, allocator>* const indirect_ptrc_p) noexcept;
	_FORCE_INLINE_ void reserve(uint64 new_size_p) noexcept;
	_FORCE_INLINE_ void sort() const noexcept;
	_FORCE_INLINE_ void shrink_to_fit() noexcept;

	_FORCE_INLINE_ uint64 max_length() const noexcept { return _UINT64_MAX_; }
	_FORCE_INLINE_ uint64 size() const noexcept { return this->m_element_count.load(std::memory_order_acquire); }
	_FORCE_INLINE_ uint64 capacity() const noexcept { return this->m_array_total_length.load(std::memory_order_acquire); }
};


END_NAMESPACE


#endif