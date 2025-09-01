#ifndef _DYNAMIC_ARRAY_HXX_
#define _DYNAMIC_ARRAY_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1

#include "core.debug.h"
#include "core.types.h"
#include "memory.allocator.hxx"




BEGIN_NAMESPACE(FE)



BEGIN_NAMESPACE(memory)


// 	https://en.cppreference.com/w/cpp/container/vector
/*
	_FORCE_INLINE_ _NODISCARD_ T* allocate(size_t count_p) noexcept;
	_FORCE_INLINE_ _NODISCARD_ T* allocate(size_t count_p, const T& initial_value_p) noexcept;
	_FORCE_INLINE_ _NODISCARD_ T* allocate(size_t count_p, T&& initial_rvalue_p) noexcept;
	_FORCE_INLINE_ void deallocate(T* ptr_p, size_t count_p) noexcept;
	_FORCE_INLINE_ _NODISCARD_ T* reallocate(T* src_ptr_p, size_t new_count_p) noexcept;

template class dynamic_array is a dynamically resizeale lock free array which provides anti-false sharing feature.*/
template <typename T, typename max_array_length = var::uint64, 
	class padding_size = align_null, class allocator = block_allocator<T, padding_size> >
class dynamic_array
{
	typedef max_array_length uint_t;
member_variables:
	allocator m_allocator;
	uint_t m_array_length;
	uint_t m_array_total_length;

	T* m_array_ptr;

	typedef const max_array_length uint;
constructors:
	dynamic_array(initial_reservation&& reserve_p) noexcept;
	dynamic_array(std::initializer_list<T>&& arraylist_ref_p) noexcept;

copy_constructor:
	dynamic_array(const dynamic_array<T, max_array_length, size_p, allocator>& object_ref_p) noexcept;

copy_assignment_operator:
	dynamic_array<T, max_array_length, size_p, allocator>& operator=(const dynamic_array<T, max_array_length, size_p, allocator>& object_ref_p) noexcept;

move_constructor:
	dynamic_array(dynamic_array<T, max_array_length, size_p, allocator>&& move_p) noexcept;

move_assignment_operator:
	dynamic_array<T, max_array_length, size_p, allocator>& operator=(dynamic_array<T, max_array_length, size_p, allocator>&& move_p) noexcept;

destructor:
	~dynamic_array() noexcept;

operators:
	T& operator[](uint index_p) noexcept;

methods:
	T pop_at(uint index_p) noexcept;

	uint emplace_back(const T& value_ref_p) noexcept;
	T pop_back() noexcept;

	T* begin() const noexcept { return this->m_array_ptr; }
	T* end() const noexcept { return &(this->m_array_ptr[this->m_array_length]); }

	T& front() noexcept { return this->m_array_ptr[0]; }
	T& back() noexcept { return this->m_array_ptr[this->m_array_length]; }

	void construct_at(uint index_p) noexcept;
	void destruct_at(uint index_p) noexcept;
	void destruct_all() noexcept;

	boolean is_valid(uint index_p) noexcept;

	_NODISCARD_ T* copy_raw_pointer_array() noexcept;

	uint array_length() const noexcept { return this->m_array_length; }
	uint array_total_length() const noexcept { return this->m_array_total_length; }
	uint spare_elements() const noexcept { return this->m_array_total_length - this->m_array_length; }
	uint max_length() const noexcept;

	void resize(uint length_p) noexcept;
	void reserve(uint length_p) noexcept;
	void shrink_to_fit() noexcept;

static_methods:
	static void swap(dynamic_array<T, max_array_length, size_p, allocator>& A_ref_p, dynamic_array<T, max_array_length, size_p, allocator>& B_ref_p) noexcept;
};

template <typename T, typename max_array_length, class padding_size, class allocator>
dynamic_array<T, max_array_length, padding_size, allocator>::uint  dynamic_array<T, max_array_length, padding_size, allocator>::max_length() const noexcept
{
	switch ( typename_hash_code(typeid( uint ).name()) )
	{
	case 0:
		return _UINT8_HASH_CODE_;
		break;

	case 1:
		return _UINT16_HASH_CODE_;
		break;

	case 2:
		return _UINT32_HASH_CODE_;
		break;

	case 3:
		return _UINT64_HASH_CODE_;
		break;
	}
}


END_NAMESPACE


END_FE

#endif
#endif // !_DYNAMIC_ARRAY_HXX_
