#ifndef _PARALLEL_DYNAMIC_ARRAY_CXX_
#define _PARALLEL_DYNAMIC_ARRAY_CXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "parallel.array.hxx"
#include "parallel.memory_block_allocator.cxx"


BEGIN_NAMESPACE(FE::parallel)


template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
T array<T, max_array_length, padding_size, allocator, iterator, pointer>::s_null = T();

template <typename T, class padding_size>
size_t constructible_array_iterator<T, padding_size>::s_size_of_an_element = block_ptr<T, padding_size>::calculate_size_of_an_element();

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
std::atomic< max_array_length> array<T, max_array_length, padding_size, allocator, iterator, pointer>::s_reserve_length = 0;

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
_FORCE_INLINE_ array<T, max_array_length, padding_size, allocator, iterator, pointer>::array(FE::memory::initial_reservation&& reserve_p) noexcept : m_lock()
{
	FE::exception::handle_exceptions(IF(reserve_p._length == 0), FE::_LOG_EXCEPTION_HISTORY, "invalid length: reserve_p._size is zero.", _EXCEPTION_ORIGIN_);
	
	this->m_array_ptr = allocator::allocate(reserve_p._length);
	this->m_atomic_total_array_length.store(reserve_p._length, std::memory_order_relaxed);
	this->m_atomic_array_length.store(0, std::memory_order_relaxed);
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
array<T, max_array_length, padding_size, allocator, iterator, pointer>::array(std::initializer_list<T>&& arraylist_ref_p) noexcept : m_lock()
{
	FE::exception::handle_exceptions(IF(arraylist_ref_p.size() == 0), FE::_LOG_EXCEPTION_HISTORY, "invalid length: arraylist_ref_p is zero.", _EXCEPTION_ORIGIN_);

	this->m_array_ptr = allocator::allocate(arraylist_ref_p.size());
	this->m_atomic_total_array_length.store(arraylist_ref_p.size(), std::memory_order_relaxed);
	this->m_atomic_array_length.store(arraylist_ref_p.size(), std::memory_order_relaxed);
	
	var::index_t l_index = 0;
	for (auto& value_ref : arraylist_ref_p)
	{
		this->m_array_ptr.construct_at(l_index, value_ref);
		++l_index;
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
array<T, max_array_length, padding_size, allocator, iterator, pointer>::array(array<T, max_array_length, padding_size, allocator, iterator, pointer>& object_ref_p) noexcept : m_lock()
{
	FE::exception::handle_exceptions(IF(object_ref_p.m_atomic_array_length.load(std::memory_order_acquire) == 0), FE::_LOG_EXCEPTION_HISTORY, "invalid length: object_ref_p.m_atomic_array_length.load(std::memory_order_acquire) is zero.", _EXCEPTION_ORIGIN_);

	this->m_atomic_total_array_length.store(object_ref_p.m_atomic_total_array_length.load(std::memory_order_acquire), std::memory_order_relaxed);
	this->m_atomic_array_length.store(object_ref_p.m_atomic_array_length.load(std::memory_order_acquire), std::memory_order_relaxed);
	this->m_array_ptr = allocator::allocate(this->m_atomic_total_array_length.load(std::memory_order_acquire));
	
	var::index_t l_object_idx = 0;
	for (var::index_t i = 0; i < object_ref_p.m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == true)
		{
			this->m_array_ptr.construct_at(i, object_ref_p[l_object_idx]);
			++l_object_idx;
		}
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
array<T, max_array_length, padding_size, allocator, iterator, pointer>& array<T, max_array_length, padding_size, allocator, iterator, pointer>::operator=(array<T, max_array_length, padding_size, allocator, iterator, pointer>& object_ref_p) noexcept
{
	FE::exception::handle_exceptions(IF(object_ref_p.m_atomic_array_length.load(std::memory_order_acquire) == 0), FE::_LOG_EXCEPTION_HISTORY, "invalid length: object_ref_p.m_atomic_array_length.load(std::memory_order_acquire) is zero.", _EXCEPTION_ORIGIN_);
	
	if (this->m_atomic_total_array_length.load(std::memory_order_acquire) < object_ref_p.m_atomic_array_length.load(std::memory_order_acquire))
	{
		this->m_array_ptr = allocator::reallocate(this->m_array_ptr.get_ptr(), this->m_atomic_total_array_length.load(std::memory_order_acquire), object_ref_p.m_atomic_array_length.load(std::memory_order_acquire));
		this->m_atomic_array_length.store(object_ref_p.m_atomic_array_length.load(std::memory_order_acquire), std::memory_order_release);
		this->m_atomic_total_array_length.store(object_ref_p.m_atomic_array_length.load(std::memory_order_acquire), std::memory_order_release);
	}
	else if (object_ref_p.m_array_ptr.get_ptr() == nullptr) { return *this; }


	var::index_t l_object_idx = 0;
	for (var::index_t i = 0; i < object_ref_p.m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == true)
		{
			this->m_array_ptr[i] = object_ref_p[l_object_idx];
			++l_object_idx;
		}
		else
		{
			this->m_array_ptr.construct_at(i, object_ref_p[l_object_idx]);
			++l_object_idx;
		}
	}
	return *this;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
array<T, max_array_length, padding_size, allocator, iterator, pointer>::array(array<T, max_array_length, padding_size, allocator, iterator, pointer>&& move_p) noexcept : m_lock()
{
	this->m_array_ptr = std::move(move_p.m_array_ptr);
	this->m_atomic_array_length = move_p.m_atomic_array_length.exchange(0, std::memory_order_relaxed);
	this->m_atomic_total_array_length = move_p.m_atomic_total_array_length.exchange(0, std::memory_order_relaxed);
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
array<T, max_array_length, padding_size, allocator, iterator, pointer>& array<T, max_array_length, padding_size, allocator, iterator, pointer>::operator=(array<T, max_array_length, padding_size, allocator, iterator, pointer>&& move_p) noexcept
{
	if (this->m_array_ptr.get_ptr() != nullptr)
	{
		for (var::index_t i = 0; i < this->m_atomic_array_length.load(std::memory_order_relaxed); ++i)
		{
			if (this->m_array_ptr.is_valid(i) == true)
			{
				this->m_array_ptr.destruct_at(i);
			}
		}
		allocator::deallocate(this->m_array_ptr.get_ptr(), this->m_atomic_total_array_length.load(std::memory_order_relaxed));
	}

	this->m_array_ptr = std::move(move_p.m_array_ptr);
	this->m_atomic_array_length = move_p.m_atomic_array_length.exchange(0, std::memory_order_relaxed);
	this->m_atomic_total_array_length = move_p.m_atomic_total_array_length.exchange(0, std::memory_order_relaxed);
	return *this;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
_FORCE_INLINE_ array<T, max_array_length, padding_size, allocator, iterator, pointer>::~array() noexcept
{
	if (this->m_array_ptr.get_ptr() == nullptr) { return; }

	for (var::index_t idx = 0; idx < this->m_atomic_array_length.load(std::memory_order_relaxed); ++idx)
	{
		if (this->m_array_ptr.is_valid(idx) == true)
		{
			this->m_array_ptr.destruct_at(idx);
		}
	}
	allocator::deallocate( this->m_array_ptr.get_ptr(), this->m_atomic_total_array_length.load(std::memory_order_relaxed));
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
T& array<T, max_array_length, padding_size, allocator, iterator, pointer>::operator[](max_array_length index_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.is_valid(index_p) == false || this->m_array_ptr.get_ptr() == nullptr || this->m_atomic_array_length.load(std::memory_order_acquire) <= index_p), FE::_ABORT_IMMEDIATELY, "Critical Error: index_p is outside of the range or the pointer was nullptr", _EXCEPTION_ORIGIN_);


	return this->m_array_ptr[index_p];
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
std::optional<T> array<T, max_array_length, padding_size, allocator, iterator, pointer>::try_pop_at(max_array_length index_p) noexcept
{
	if (FE::exception::handle_exceptions(IF(this->m_array_ptr.is_valid(index_p) == false || this->m_array_ptr.get_ptr() == nullptr || this->m_atomic_array_length.load(std::memory_order_acquire) <= index_p), FE::_ABORT_IMMEDIATELY, "Warning: index_p is outside of the index range or the pointer was nullptr. Returning std::nullopt", _EXCEPTION_ORIGIN_))	
	{
		return std::nullopt;
	}

	std::optional<T> l_rbuffer = std::move( this->m_array_ptr[index_p] );
	this->m_array_ptr.destruct_at(index_p);
	return std::move(l_rbuffer);
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
max_array_length array<T, max_array_length, padding_size, allocator, iterator, pointer>::push_back(T& value_ref_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if (this->size >= this->capacity())
	{
		this->reserve(s_reserve_length);
	}

	this->m_array_ptr.construct_at(this->m_atomic_array_length.load(std::memory_order_acquire), value_ref_p);
	this->m_atomic_array_length.fetch_add(1);
	return this->m_atomic_array_length.load(std::memory_order_relaxed) - 1;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
max_array_length array<T, max_array_length, padding_size, allocator, iterator, pointer>::emplace_back(const T& value_cref_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if (this->size >= this->capacity())
	{
		this->reserve(s_reserve_length);
	}

	this->m_array_ptr.construct_at(this->m_atomic_array_length.load(std::memory_order_acquire), value_cref_p);
	this->m_atomic_array_length.fetch_add(1);
	return this->m_atomic_array_length.load(std::memory_order_relaxed) - 1;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
max_array_length array<T, max_array_length, padding_size, allocator, iterator, pointer>::emplace_back(T&& move_value_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if (this->size() >= this->capacity())
	{
		this->reserve(s_reserve_length);
	}

	this->m_array_ptr.construct_at(this->m_atomic_array_length.load(std::memory_order_acquire), move_value_p);
	this->m_atomic_array_length.fetch_add(1);
	return this->m_atomic_array_length.load(std::memory_order_relaxed) - 1;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
std::optional<T> array<T, max_array_length, padding_size, allocator, iterator, pointer>::try_pop_back() noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	while (this->m_atomic_array_length.load(std::memory_order_acquire) > 0)
	{
		index_t l_index = --this->m_atomic_array_length;
		if (this->m_array_ptr.is_valid(l_index) == true)
		{
			std::optional<T> l_rbuffer = std::move(this->m_array_ptr[l_index]);
			this->m_array_ptr.destruct_at(l_index);
			return std::move(l_rbuffer);
		}
	}

	FE::exception::handle_exceptions(true, FE::_LOG_EXCEPTION_HISTORY, "Warning: the FE::array container was empty. Returning std::nullopt instead.", _EXCEPTION_ORIGIN_);
	return std::nullopt;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
var::boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::construct_at(max_array_length index_p, const T& copy_cref_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if( this->m_array_ptr.is_valid(index_p) == true || index_p >= this->m_atomic_array_length.load(std::memory_order_acquire) )
	{
		return false;
	}

	this->m_array_ptr.construct_at(index_p, copy_cref_p);
	return true;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
var::boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::construct_at(max_array_length index_p, T&& move_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if (this->m_array_ptr.is_valid(index_p) == true || index_p >= this->m_atomic_array_length.load(std::memory_order_acquire))
	{
		return false;
	}

	this->m_array_ptr.construct_at(index_p, move_p);
	return true;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
var::boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::destruct_at(max_array_length index_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	if (this->m_array_ptr.is_valid(index_p) == false || index_p >= this->m_atomic_array_length.load(std::memory_order_acquire))
	{
		return false;
	}

	this->m_array_ptr.destruct_at(index_p);
	return true;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
void array<T, max_array_length, padding_size, allocator, iterator, pointer>::construct_all(const T& copy_cref_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	for (var::index_t i = 0; i < this->m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == false)
		{
			this->m_array_ptr.construct_at(i, copy_cref_p);
		}
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
void array<T, max_array_length, padding_size, allocator, iterator, pointer>::construct_all(T&& move_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	for (var::index_t i = 0; i < this->m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == false)
		{
			this->m_array_ptr.construct_at(i, move_p);
		}
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
void array<T, max_array_length, padding_size, allocator, iterator, pointer>::destruct_all() noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);

	for (var::index_t i = 0; i < this->m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == true)
		{
			this->m_array_ptr.destruct_at(i);
		}
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::is_valid(max_array_length index_p) noexcept
{
	FE::exception::handle_exceptions(IF(this->m_array_ptr.get_ptr() == nullptr), FE::_ABORT_IMMEDIATELY, "Critical Error: this->m_array_ptr.get_ptr() is nullptr.", _EXCEPTION_ORIGIN_);
	
	if (FE::exception::handle_exceptions(IF(this->m_atomic_array_length.load(std::memory_order_acquire) <= index_p), FE::_LOG_EXCEPTION_HISTORY, "Warning: Fail to search the target element validity and index_p is out of the index range. It will always return 'false'.", _EXCEPTION_ORIGIN_)) { return false; }

	return this->m_array_ptr.is_valid(index_p);
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
T* array<T, max_array_length, padding_size, allocator, iterator, pointer>::copy_raw_pointer_array() noexcept
{
	T* l_buffer_ptr = new T[this->m_atomic_array_length.load(std::memory_order_acquire)];

	var::index_t l_index = 0;
	for (var::index_t i = 0; i <this->m_atomic_array_length.load(std::memory_order_acquire); ++i)
	{
		if (this->m_array_ptr.is_valid(i) == true)
		{
			l_buffer_ptr[l_index] = this->m_array_ptr[i];
			++l_index;
		}
	}

	return l_buffer_ptr;
}

template <typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
_FORCE_INLINE_ max_array_length array<T, max_array_length, padding_size, allocator, iterator, pointer>::max_length() const noexcept
{
	switch ( FE::typename_hash_code(max_array_length{}) )
	{
	case _UINT8_HASH_CODE_:
		return _UINT8_MAX_;

	case _INT8_HASH_CODE_:
		return _INT8_MAX_;


	case _UINT16_HASH_CODE_:
		return _UINT16_MAX_;

	case _INT16_HASH_CODE_:
		return _INT16_MAX_;


	case _UINT32_HASH_CODE_:
		return _UINT32_MAX_;

	case _INT32_HASH_CODE_:
		return _INT32_MAX_;


	case _UINT64_HASH_CODE_:
		return _UINT64_MAX_;

	case _INT64_HASH_CODE_:
		return _INT64_MAX_;


	default:
		return 0;
	}
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::reserve(max_array_length length_p) noexcept
{
	this->m_array_ptr = allocator::reallocate(	this->m_array_ptr.get_ptr(),
												this->m_atomic_total_array_length.load(std::memory_order_relaxed),
												this->m_atomic_total_array_length.load(std::memory_order_relaxed) + length_p
												);
	this->m_atomic_total_array_length.store(this->m_atomic_total_array_length.load(std::memory_order_relaxed) + length_p, std::memory_order_release);
	return false;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
boolean array<T, max_array_length, padding_size, allocator, iterator, pointer>::shrink_to_fit() noexcept
{
	return false;
}

template<typename T, typename max_array_length, class padding_size, class allocator, class iterator, class pointer>
void array<T, max_array_length, padding_size, allocator, iterator, pointer>::swap(array<T, max_array_length, padding_size, allocator, iterator, pointer>& A_ref_p, array<T, max_array_length, padding_size, allocator, iterator, pointer>& B_ref_p) noexcept
{
	array<T, max_array_length, padding_size, allocator, iterator, pointer> l_buffer_array = std::move(A_ref_p);
	A_ref_p = std::move(B_ref_p);
	B_ref_p = std::move(l_buffer_array);
}


END_NAMESPACE
#endif