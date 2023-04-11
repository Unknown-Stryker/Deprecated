#ifndef _PARALLEL_DYNAMIC_ARRAY_HXX_
#define _PARALLEL_DYNAMIC_ARRAY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "parallel.memory_block_allocator.hxx"
#include "../include/public/FE.parallel.mutex.hpp"
#include <optional>


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class padding_size = FE::memory::align_64bit_cache_line>
class constructible_array_iterator
{
	var::ATOMIC_BYTE_PTR m_content_iterator_ptr;
	var::ATOMIC_BYTE_PTR m_flag_iterator_ptr;

	var::ATOMIC_BYTE_PTR m_end_ptr;

public_static_variables:
	static size_t s_size_of_an_element;

public_constructors:
	constructible_array_iterator(var::ATOMIC_BYTE_PTR begin_ptr_p) noexcept : m_content_iterator_ptr(begin_ptr_p + 1), m_flag_iterator_ptr(begin_ptr_p) {}
	constructible_array_iterator(var::ATOMIC_BYTE_PTR begin_ptr_p, var::ATOMIC_BYTE_PTR end_ptr_p) noexcept : m_content_iterator_ptr(begin_ptr_p + 1), m_flag_iterator_ptr(begin_ptr_p), m_end_ptr(end_ptr_p + 1) {}

public_destructor:
	~constructible_array_iterator() noexcept = default;

public_operators:
	constructible_array_iterator& operator++() noexcept
	{
		this->m_content_iterator_ptr += constructible_array_iterator::s_size_of_an_element;
		this->m_flag_iterator_ptr += constructible_array_iterator::s_size_of_an_element;

		while (this->m_flag_iterator_ptr->load(std::memory_order_acquire) == false && this->m_content_iterator_ptr < this->m_end_ptr)
		{
			this->m_content_iterator_ptr += constructible_array_iterator::s_size_of_an_element;
			this->m_flag_iterator_ptr += constructible_array_iterator::s_size_of_an_element;
		}
		return *this;
	}
	T& operator*() noexcept { return reinterpret_cast<FE::memory::object<T, padding_size>*>(this->m_content_iterator_ptr)->_content; }
	boolean operator!=(constructible_array_iterator& other_ref_p) noexcept { return this->m_content_iterator_ptr < other_ref_p.m_content_iterator_ptr; }
};


/*template class array is a dynamically scalable thread-safe array.*/
template <typename T, typename max_array_length = var::uint64, class padding_size = FE::memory::align_64bit_cache_line,
	class allocator = block_allocator<T, padding_size>, class iterator = constructible_array_iterator<T, padding_size>, class pointer = block_ptr<T, padding_size>>
class array final
{
	static_assert(std::is_integral<max_array_length>::value, "max_array_length is not a valid numeric type");
	static_assert(padding_size::s_size == 0 || padding_size::s_size >= sizeof(T), "padding_size::s_size is invalid. padding_size::s_size must be greater than sizeof(T)");
	static_assert(std::is_class<allocator>::value, "the template argument of FE::array 'allocator' must be a class type");
	static_assert(std::is_class<iterator>::value, "the template argument of FE::array 'iterator' must be a class type");
	static_assert(std::is_class<pointer>::value, "the template argument of FE::array 'pointer' must be a class type");

private_member_variables:
	std::atomic<max_array_length> m_atomic_array_length;
	pointer m_array_ptr;
	std::atomic<max_array_length> m_atomic_total_array_length;
	FE::parallel::mutex m_lock;

private_static_variables:
	static T s_null;

public_static_variables:
	static std::atomic< max_array_length> s_reserve_length;

public_constructors:
	_FORCE_INLINE_ array(FE::memory::initial_reservation&& reserve_p) noexcept;
	_FORCE_INLINE_ array(std::initializer_list<T>&& arraylist_ref_p) noexcept;

public_copy_constructor:
	_FORCE_INLINE_ array(array<T, max_array_length, padding_size, allocator, iterator, pointer>& object_ref_p) noexcept;

public_copy_assignment_operator:
	_FORCE_INLINE_ array<T, max_array_length, padding_size, allocator, iterator, pointer>& operator=(array<T, max_array_length, padding_size, allocator, iterator, pointer>& object_ref_p) noexcept;

public_move_constructor:
	_FORCE_INLINE_ array(array<T, max_array_length, padding_size, allocator, iterator, pointer>&& move_p) noexcept;

public_move_assignment_operator:
	_FORCE_INLINE_ array<T, max_array_length, padding_size, allocator, iterator, pointer>& operator=(array<T, max_array_length, padding_size, allocator, iterator, pointer>&& move_p) noexcept;

public_destructor:
	_FORCE_INLINE_ ~array() noexcept;

public_operators:
	_FORCE_INLINE_ T& operator[](max_array_length index_p) noexcept; 

public_methods:
	_FORCE_INLINE_ std::optional<T> try_pop_at(max_array_length index_p) noexcept; // Lock-free operation

	_FORCE_INLINE_ max_array_length push_back(T& value_ref_p) noexcept; // Lock-free operation
	_FORCE_INLINE_ max_array_length emplace_back(const T& value_cref_p) noexcept; // Lock-free operation
	_FORCE_INLINE_ max_array_length emplace_back(T&& move_value_p) noexcept; // Lock-free operation

	_FORCE_INLINE_ std::optional<T> try_pop_back() noexcept; // Lock-free operation

	// DO NOT use ranged-for loop and size-related functions like reserve() and shrink_to_fit() at the same time.
	_FORCE_INLINE_ iterator begin() noexcept { return iterator( this->m_array_ptr.get_ptr(), this->m_array_ptr.get_ptr() + this->m_atomic_array_length.load(std::memory_order_acquire) * iterator::s_size_of_an_element ); }
	_FORCE_INLINE_ iterator end() noexcept { return iterator( this->m_array_ptr.get_ptr() + this->m_atomic_array_length.load(std::memory_order_acquire) * iterator::s_size_of_an_element ); }

	_FORCE_INLINE_ T& front() noexcept { return this->m_array_ptr[0]; }
	_FORCE_INLINE_ T& back() noexcept { return this->m_array_ptr[this->m_atomic_array_length.load(std::memory_order_acquire) - 1]; }

	_FORCE_INLINE_ var::boolean construct_at(max_array_length index_p, const T& copy_cref_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ var::boolean construct_at(max_array_length index_p, T&& move_p) noexcept;  // Lock-free operation

	_FORCE_INLINE_ var::boolean destruct_at(max_array_length index_p) noexcept;  // Lock-free operation

	_FORCE_INLINE_ void construct_all(const T& copy_cref_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ void construct_all(T&& move_p) noexcept;  // Lock-free operation
	_FORCE_INLINE_ void destruct_all() noexcept;  // Lock-free operation

	_FORCE_INLINE_ boolean is_valid(max_array_length index_p) noexcept;  // Lock-free operation

	_NODISCARD_ _FORCE_INLINE_ T* copy_raw_pointer_array() noexcept;

	_FORCE_INLINE_ max_array_length size() const noexcept { return this->m_atomic_array_length.load(std::memory_order_acquire); }  // Lock-free operation
	_FORCE_INLINE_ max_array_length capacity() const noexcept { return this->m_atomic_total_array_length.load(std::memory_order_acquire); }  // Lock-free operation
	_FORCE_INLINE_ max_array_length max_length() const noexcept; 

	_FORCE_INLINE_ boolean reserve(max_array_length length_p) noexcept; // invoke it with caution!
	_FORCE_INLINE_ boolean shrink_to_fit() noexcept; // invoke it with caution!

public_static_methods:
	_FORCE_INLINE_ void swap(array<T, max_array_length, padding_size, allocator, iterator, pointer>& A_ref_p, array<T, max_array_length, padding_size, allocator, iterator, pointer>& B_ref_p) noexcept; // invoke it with caution!
};


END_NAMESPACE
#endif