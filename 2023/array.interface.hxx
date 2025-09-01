#ifndef _FE_CORE_PARALLEL_ARRAY_INTERFACE_HXX_
#define _FE_CORE_PARALLEL_ARRAY_INTERFACE_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "../../memory/allocator/allocator.interface.hxx"
#include "../mutex.hpp"
#include <optional>


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class padding_size = FE::memory::align_64bytes>
class array_iterator
{
	/*FE::parallel::memory_block<T, padding_size>* m_array_iterator_ptr;
public_constructors:
	array_iterator(FE::parallel::memory_block<T, padding_size>* const address_cptr_p) noexcept : m_array_iterator_ptr(address_cptr_p) {};

public_destructor:
	~array_iterator() noexcept = default;

public_operators:
	array_iterator& operator++() noexcept { ++this->m_array_iterator_ptr; return *this; }

	T& operator*() noexcept { return *this->m_array_iterator_ptr; }

	boolean operator!=(array_iterator& other_ref_p) noexcept { return (other_ref_p.m_array_iterator_ptr != this->m_array_iterator_ptr) ? true : false; }*/
};

/*
* try and log if fail / try and abort if fail
*/

/*template class array is a dynamically scalable thread-safe array.*/
template <typename T, typename max_length_type = var::uint64, class padding_size = FE::memory::align_64bytes,
	class allocator = FE::memory::c_style_allocator<T, padding_size>, class iterator = array_iterator<T, padding_size>>
class array final
{
	static_assert(std::is_integral<max_length_type>::value, "max_length_type is not a valid numeric type");
	static_assert(padding_size::s_size == 0 || padding_size::s_size >= sizeof(T), "padding_size::s_size is invalid. padding_size::s_size must be greater than sizeof(T)");
	static_assert(std::is_class<allocator>::value, "the template argument of FE::array 'allocator' must be a class type");
	static_assert(std::is_class<iterator>::value, "the template argument of FE::array 'iterator' must be a class type");

public:
	typedef allocator allocator_type;
	typedef iterator iterator_type;
	typedef T value_type;
	typedef max_length_type length_type;
	typedef padding_size padding_size_type;

private_member_variables:
	std::atomic<max_length_type> m_atomic_array_length;
	std::atomic<max_length_type> m_atomic_total_array_length;
	//std::atomic<FE::parallel::memory_block<T, padding_size>*> m_array_ptr;
	FE::parallel::mutex m_lock;

private_static_variables:
	static T s_null;

public_static_variables:
	static std::atomic< max_length_type> s_reserve_length;

public_constructors:
	_FORCE_INLINE_ array(FE::memory::initial_reservation&& reserve_p) noexcept;
	_FORCE_INLINE_ array(std::initializer_list<T>&& arraylist_ref_p) noexcept;

public_copy_constructor:
	_FORCE_INLINE_ array(array<T, max_length_type, padding_size, allocator, iterator>& object_ref_p) noexcept;

public_copy_assignment_operator:
	_FORCE_INLINE_ array<T, max_length_type, padding_size, allocator, iterator>& operator=(array<T, max_length_type, padding_size, allocator, iterator>& object_ref_p) noexcept;

public_move_constructor:
	_FORCE_INLINE_ array(array<T, max_length_type, padding_size, allocator, iterator>&& move_p) noexcept;

public_move_assignment_operator:
	_FORCE_INLINE_ array<T, max_length_type, padding_size, allocator, iterator>& operator=(array<T, max_length_type, padding_size, allocator, iterator>&& move_p) noexcept;

public_destructor:
	_FORCE_INLINE_ ~array() noexcept;

public_operators:
	_FORCE_INLINE_ T& operator[](max_length_type index_p) noexcept; // + try_access(index_t idx_p) noexcept;

public_methods:
	_FORCE_INLINE_ std::optional<T> try_pop_at(max_length_type index_p) noexcept; // Lock-free operation

	_FORCE_INLINE_ max_length_type push_back(T& value_ref_p) noexcept; // Lock-free operation
	_FORCE_INLINE_ max_length_type emplace_back(const T& value_cref_p) noexcept; // Lock-free operation
	_FORCE_INLINE_ max_length_type emplace_back(T&& move_value_p) noexcept; // Lock-free operation

	_FORCE_INLINE_ std::optional<T> try_pop_back() noexcept; // Lock-free operation

	// DO NOT use ranged-for loop and size-related functions like reserve() and shrink_to_fit() at the same time.
	_FORCE_INLINE_ iterator unsafe_begin() noexcept { return iterator(this->m_array_ptr.load(std::memory_order_acquire) ); }
	_FORCE_INLINE_ iterator unsafe_end() noexcept { return iterator( this->m_array_ptr.load(std::memory_order_acquire) + this->m_atomic_array_length.load(std::memory_order_acquire) ); }

	_FORCE_INLINE_ T& front() noexcept { return this->m_array_ptr[0]; }
	_FORCE_INLINE_ T& back() noexcept { return this->m_array_ptr[this->m_atomic_array_length.load(std::memory_order_acquire) - 1]; }

	_FORCE_INLINE_ var::boolean construct_at(max_length_type index_p, const T& copy_cref_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ var::boolean construct_at(max_length_type index_p, T&& move_p) noexcept;  // Lock-free operation

	_FORCE_INLINE_ var::boolean destruct_at(max_length_type index_p) noexcept;  // Lock-free operation

	_FORCE_INLINE_ void construct_all(const T& copy_cref_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ void construct_all(T&& move_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ void destruct_all() noexcept;  // Lock-free operation

	_FORCE_INLINE_ boolean is_valid(max_length_type index_p) noexcept;  // Lock-free operation

	_NODISCARD_ _FORCE_INLINE_ T* copy_raw_pointer_array() noexcept;

	_FORCE_INLINE_ max_length_type size() const noexcept { return this->m_atomic_array_length.load(std::memory_order_acquire); }  // Lock-free operation
	_FORCE_INLINE_ max_length_type capacity() const noexcept { return this->m_atomic_total_array_length.load(std::memory_order_acquire); }  // Lock-free operation
	_FORCE_INLINE_ max_length_type max_length() const noexcept; 

	_FORCE_INLINE_ boolean reserve(max_length_type length_p) noexcept; // invoke it with caution!
	_FORCE_INLINE_ boolean shrink_to_fit() noexcept; // invoke it with caution!

public_static_methods:
	_FORCE_INLINE_ void swap(array<T, max_length_type, padding_size, allocator, iterator>& A_ref_p, array<T, max_length_type, padding_size, allocator, iterator>& B_ref_p) noexcept; // invoke it with caution!
};


END_NAMESPACE
#endif