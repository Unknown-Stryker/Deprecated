#ifndef _PARALLEL_MEMORY_BLOCK_ALLOCATOR_HXX_
#define _PARALLEL_MEMORY_BLOCK_ALLOCATOR_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "../include/internal-headers/memory.hxx"
#include "../include/internal-headers/core.access specifier.h"
#include "../include/internal-headers/core.debug.h"
#include "memory.cstring.hxx"


BEGIN_NAMESPACE(FE::parallel)


template <typename T, class padding_size = FE::memory::align_64bit_cache_line>
class block_allocator
{
public_static_methods:
	_NODISCARD_ _FORCE_INLINE_ static var::ATOMIC_BYTE_PTR allocate(length_t count_p) noexcept;
	_FORCE_INLINE_ static void deallocate(var::ATOMIC_BYTE_PTR ptr_p, _MAYBE_UNUSED_ length_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ static var::ATOMIC_BYTE_PTR reallocate(var::ATOMIC_BYTE_PTR memblock_ptr_p, length_t prev_count_p, length_t new_count_p) noexcept;

protected_static_methods:
	_FORCE_INLINE_ static void construct_atomic_bitfield(size_t size_of_an_element_p, var::ATOMIC_BYTE_PTR begin_ptr_p, var::ATOMIC_BYTE_PTR end_ptr_p) noexcept;
};




// it is not a smart pointer class nor related to FE::memory::memory_block<T, padding_size>
template <typename T, class padding_size = FE::memory::align_null>
class block_ptr
{
private_member_variables:
	std::atomic<std::atomic_bool*> m_object_ptr;
	std::atomic<std::atomic_bool*> m_flag_ptr;


public_static_variables:
	static size_t s_size_of_an_element;


public_constructors:
	_FORCE_INLINE_ block_ptr() noexcept : m_object_ptr(), m_flag_ptr() {}
	_FORCE_INLINE_ block_ptr(ATOMIC_BYTE_PTR ptr_p) noexcept : m_object_ptr(ptr_p + 1), m_flag_ptr(ptr_p) {}


public_destructor:
	_FORCE_INLINE_ ~block_ptr() noexcept = default;


public_copy_constructor:
	_FORCE_INLINE_ block_ptr(const block_ptr<T, padding_size>& other_ref_p) noexcept = delete;


public_move_constructor:
	_FORCE_INLINE_ block_ptr(block_ptr<T, padding_size>&& rvalue_p) noexcept
	{
		this->m_object_ptr = rvalue_p.m_object_ptr.exchange(nullptr);
		this->m_flag_ptr = rvalue_p.m_flag_ptr.exchange(nullptr);
	}


public_assignment_operator:
	_FORCE_INLINE_ block_ptr<T, padding_size>& operator=(ATOMIC_BYTE_PTR ptr_p) noexcept
	{
		this->m_object_ptr.store(	ptr_p + 1,
									std::memory_order_release
									);
		this->m_flag_ptr.store(ptr_p, std::memory_order_release);
		return *this;
	}


public_copy_assignment_operator:
	_FORCE_INLINE_ block_ptr<T, padding_size>& operator=(const block_ptr<T, padding_size>& other_ref_p) noexcept = delete;


public_move_assignment_operator:
	_FORCE_INLINE_ block_ptr<T, padding_size>& operator=(block_ptr<T, padding_size>&& rvalue_p) noexcept
	{
		this->m_object_ptr = rvalue_p.m_object_ptr.exchange(nullptr);
		this->m_flag_ptr = rvalue_p.m_flag_ptr.exchange(nullptr);
		return *this;
	}


public_operators:
	_FORCE_INLINE_ T& operator[](index_t idx_p) noexcept
	{
		return reinterpret_cast<FE::memory::object<T, padding_size>*>(this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element))->_content;
	}


private_methods:
	_FORCE_INLINE_ std::atomic_bool& get_flag(index_t idx_p) noexcept
	{
		return *(this->m_flag_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element));
	}


public_methods:
	_FORCE_INLINE_ boolean is_valid(index_t idx_p) noexcept
	{
		return (this->m_flag_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element))->load(std::memory_order_acquire);
	}

	_FORCE_INLINE_ var::ATOMIC_BYTE_PTR get_ptr() noexcept
	{
		return this->m_flag_ptr.load(std::memory_order_acquire);
	}

	_FORCE_INLINE_ void construct_at(index_t idx_p) noexcept
	{
		if (this->is_valid(idx_p) == false)
		{
			this->get_flag(idx_p).store(true, std::memory_order_release);
			new( this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element) ) FE::memory::object<T, padding_size>();
		}
	}

	_FORCE_INLINE_ void construct_at(index_t idx_p, T&& rvalue_p) noexcept
	{
		if (this->is_valid(idx_p) == false)
		{
			this->get_flag(idx_p).store(true, std::memory_order_release);
			new( this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element) ) FE::memory::object<T, padding_size>(rvalue_p);
		}
	}

	_FORCE_INLINE_ void construct_at(index_t idx_p, T& other_ref_p) noexcept
	{
		if (this->is_valid(idx_p) == false)
		{
			this->get_flag(idx_p).store(true, std::memory_order_release);
			new(this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element)) FE::memory::object<T, padding_size>(other_ref_p);
		}
	}

	_FORCE_INLINE_ void construct_at(index_t idx_p, const T& other_cref_p) noexcept
	{
		if (this->is_valid(idx_p) == false)
		{
			this->get_flag(idx_p).store(true, std::memory_order_release);
			new( this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element) ) FE::memory::object<T, padding_size>(other_cref_p);
		}
	}

	_FORCE_INLINE_ void destruct_at(index_t idx_p) noexcept
	{
		if (this->is_valid(idx_p) == true)
		{
			this->get_flag(idx_p).store(false, std::memory_order_release);
			reinterpret_cast<FE::memory::object<T, padding_size>*>(this->m_object_ptr.load(std::memory_order_acquire) + (idx_p * s_size_of_an_element))->~object<T, padding_size>();
		}
	}


public_static_methods:
	static constexpr var::size_t calculate_size_of_an_element()
	{
		if (padding_size::s_size == 0 || sizeof(T) == padding_size::s_size)
		{
			return sizeof(T) + 1;
		}

		return sizeof(FE::memory::object<T, padding_size>);
	}
};


END_NAMESPACE
#endif