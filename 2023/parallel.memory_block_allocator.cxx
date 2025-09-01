#ifndef _PARALLEL_MEMORY_BLOCK_ALLOCATOR_CXX_
#define _PARALLEL_MEMORY_BLOCK_ALLOCATOR_CXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "parallel.memory_block_allocator.hxx"
#include "../include/public/FE.runtime exception.hpp"
#include "memory.cstring.cxx"


BEGIN_NAMESPACE(FE::parallel)


template<typename T, class padding_size>
_NODISCARD_ _FORCE_INLINE_ var::ATOMIC_BYTE_PTR block_allocator<T, padding_size>::allocate(length_t count_p) noexcept
{
	exception::handle_exceptions(IF(count_p == 0), FE::_ABORT_IMMEDIATELY, "Critical Error!: size_t count_p is an invalid size.", _EXCEPTION_ORIGIN_);

	ATOMIC_BYTE_PTR l_result_buffer_ptr = FE::memory::calloc_s<std::atomic_bool>(count_p, block_ptr<T, padding_size>::s_size_of_an_element);
	construct_atomic_bitfield(block_ptr<T, padding_size>::s_size_of_an_element, l_result_buffer_ptr, l_result_buffer_ptr + (block_ptr<T, padding_size>::s_size_of_an_element * count_p) );
	return l_result_buffer_ptr;

}

template<typename T, class padding_size>
_FORCE_INLINE_ void block_allocator<T, padding_size>::deallocate(var::ATOMIC_BYTE_PTR ptr_p, _MAYBE_UNUSED_ length_t count_p) noexcept
{
	exception::handle_exceptions(IF(ptr_p == nullptr || count_p == 0), FE::_ABORT_IMMEDIATELY, "Critical Error!: invalid arguments! Parameters are null", _EXCEPTION_ORIGIN_);

	if (padding_size::s_size == 0 || sizeof(T) == padding_size::s_size)
	{
		FE::memory::free_s( ptr_p, count_p, block_ptr<T, padding_size>::s_size_of_an_element);
		return;
	}
	FE::memory::free_s( ptr_p, count_p, block_ptr<T, padding_size>::s_size_of_an_element);
}

template<typename T, class padding_size>
var::ATOMIC_BYTE_PTR block_allocator<T, padding_size>::reallocate(var::ATOMIC_BYTE_PTR memblock_ptr_p, length_t prev_count_p, length_t new_count_p) noexcept
{
	ATOMIC_BYTE_PTR l_result_buffer_ptr = FE::memory::realloc_s<std::atomic_bool>(memblock_ptr_p, prev_count_p, block_ptr<T, padding_size>::s_size_of_an_element, new_count_p, block_ptr<T, padding_size>::s_size_of_an_element);
	construct_atomic_bitfield(block_ptr<T, padding_size>::s_size_of_an_element, l_result_buffer_ptr + (block_ptr<T, padding_size>::s_size_of_an_element * prev_count_p), l_result_buffer_ptr + (block_ptr<T, padding_size>::s_size_of_an_element * new_count_p));
	return l_result_buffer_ptr;
}

template<typename T, class padding_size>
void block_allocator<T, padding_size>::construct_atomic_bitfield(size_t size_of_an_element_p, ATOMIC_BYTE_PTR begin_ptr_p, ATOMIC_BYTE_PTR end_ptr_p) noexcept
{
	for (var::ATOMIC_BYTE_PTR iter_ptr = begin_ptr_p; iter_ptr != end_ptr_p; iter_ptr = iter_ptr + size_of_an_element_p)
	{
		new(iter_ptr) std::atomic_bool();
	}
}

template <typename T, class padding_size>
size_t block_ptr<T, padding_size>::s_size_of_an_element = block_ptr<T, padding_size>::calculate_size_of_an_element();

END_NAMESPACE
#endif