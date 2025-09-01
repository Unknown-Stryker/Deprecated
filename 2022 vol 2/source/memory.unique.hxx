#ifndef _UNIQUE_HXX_
#define _UNIQUE_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "memory.allocator.hxx"
#include "memory.indirect.hxx"
#include <cstdlib>
#include <atomic>



BEGIN_NAMESPACE(FE)



BEGIN_NAMESPACE(memory)


template <typename T, class allocator = t_allocator<T>>
class indirection_list 
{
member_variables:
	std::atomic<var::uint32> m_element_count;
	std::atomic<var::uint32> m_array_total_length;
	std::atomic<indirect<T, allocator>**> m_pointer_array_ptr;

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	static indirect<T, allocator>* s_null;
#endif

constructors:
	_FORCE_INLINE_ indirection_list() noexcept : m_element_count(0), m_array_total_length(0), m_pointer_array_ptr(nullptr) {};
	_FORCE_INLINE_ indirection_list(initial_reservation&& initial_reservation_size_p) noexcept;

destructor:
	_FORCE_INLINE_ ~indirection_list() noexcept;

copy_constructor:
	_FORCE_INLINE_ indirection_list(const indirection_list<T, allocator>& other_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ indirection_list(indirection_list<T, allocator>&& move_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ indirection_list<T, allocator>& operator=(const indirection_list<T, allocator>& other_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ indirection_list<T, allocator>& operator=(indirection_list<T, allocator>&& move_p) noexcept;

operators:
	_FORCE_INLINE_ indirect<T, allocator>*& operator[](uint64 idx_p) noexcept;

methods:
	_FORCE_INLINE_ void emplace_back(indirect<T, allocator>* indirect_ptr_p);
	_FORCE_INLINE_ void reserve(uint32 new_size_p);
	_FORCE_INLINE_ void shrink_to_fit();

	_FORCE_INLINE_ indirect<T, allocator>** begin() noexcept { return this->m_pointer_array_ptr.load(std::memory_order_acquire); }
	_FORCE_INLINE_ indirect<T, allocator>** end() noexcept { return ( this->m_pointer_array_ptr.load(std::memory_order_acquire) ) + (this->m_element_count.load(std::memory_order_acquire)); }

	_FORCE_INLINE_ uint32 max_length() noexcept { return _UINT32_MAX_; }
	_FORCE_INLINE_ uint32 size() noexcept { return this->m_element_count.load(std::memory_order_acquire); }
	_FORCE_INLINE_ uint32 capacity() noexcept { return this->m_array_total_length.load(std::memory_order_acquire); }
};

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
template<typename T, class allocator>
indirect<T, allocator>* indirection_list<T, allocator>::s_null;
#endif

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>::indirection_list(initial_reservation&& initial_reservation_size_p) noexcept : m_element_count(), m_array_total_length(), m_pointer_array_ptr()
{
	this->m_pointer_array_ptr.store(new indirect<T, allocator>*[initial_reservation_size_p._size] {nullptr}, std::memory_order_release);
	this->m_array_total_length.store(static_cast<var::uint32>(initial_reservation_size_p._size), std::memory_order_release);
}

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>::~indirection_list() noexcept
{
	if ( this->m_pointer_array_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	delete[] this->m_pointer_array_ptr.load(std::memory_order_acquire);
}

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>::indirection_list(const indirection_list<T, allocator>& other_ref_p) noexcept
	: m_element_count(other_ref_p.m_element_count.load(std::memory_order_acquire)), m_array_total_length(other_ref_p.m_array_total_length.load(std::memory_order_acquire))
{
	if ( other_ref_p.m_pointer_array_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	this->m_pointer_array_ptr.store(new std::atomic< indirect<T, allocator>* >[this->m_array_total_length.load(std::memory_order_acquire)] {nullptr}, std::memory_order_release);

	memcpy(this->m_pointer_array_ptr.load(std::memory_order_acquire), other_ref_p.m_pointer_array_ptr.load(std::memory_order_acquire), sizeof(indirect<T, allocator>*) * (this->m_array_total_length.load(std::memory_order_acquire)) );
}

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>::indirection_list(indirection_list<T, allocator>&& move_p) noexcept
	: m_element_count( std::move(move_p.m_element_count.load(std::memory_order_acquire)) ), m_array_total_length( std::move(move_p.m_array_total_length.load(std::memory_order_acquire)) ), m_pointer_array_ptr( std::move(move_p.m_pointer_array_ptr) ) 
{
	move_p.m_pointer_array_ptr.store(nullptr, std::memory_order_release);
	move_p.m_element_count.store(0, std::memory_order_release);
	move_p.m_array_total_length.store(0, std::memory_order_release);
}

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>&  indirection_list<T, allocator>::operator=(const indirection_list<T, allocator>& other_ref_p) noexcept
{
	if ( other_ref_p.m_pointer_array_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	this->m_element_count.store(other_ref_p.m_element_count, std::memory_order_release);
	this->m_array_total_length.store(other_ref_p.m_array_total_length, std::memory_order_release);

	this->m_pointer_array_ptr.store( new std::atomic< indirect<T, allocator>* >[this->m_array_total_length.load(std::memory_order_acquire)] {nullptr}, std::memory_order_acquire);

	memcpy(this->m_pointer_array_ptr.load(std::memory_order_acquire), other_ref_p.m_pointer_array_ptr.load(std::memory_order_acquire), sizeof(indirect<T, allocator>*) * (this->m_array_total_length.load(std::memory_order_acquire)) );

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ indirection_list<T, allocator>& indirection_list<T, allocator>::operator=(indirection_list<T, allocator>&& move_p) noexcept
{
	this->m_pointer_array_ptr.store(std::move(move_p.m_pointer_array_ptr), std::memory_order_release);
	move_p.m_pointer_array_ptr.store(nullptr, std::memory_order_release);

	this->m_element_count.store(std::move(move_p.m_element_count.load(std::memory_order_acquire)), std::memory_order_release);
	this->m_array_total_length.store(std::move(move_p.m_array_total_length.load(std::memory_order_acquire)), std::memory_order_release);

	move_p.m_element_count.store(0, std::memory_order_release);
	move_p.m_array_total_length.store(0, std::memory_order_release);

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>*& indirection_list<T, allocator>::operator[](uint64 idx_p) noexcept
{
	if ( this->m_array_total_length.load(std::memory_order_acquire) < idx_p ) _UNLIKELY_
	{
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return indirection_list<T, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
	}

	return this->m_pointer_array_ptr[idx_p];
}

template<typename T, class allocator>
_FORCE_INLINE_ void indirection_list<T, allocator>::emplace_back(indirect<T, allocator>* indirect_ptr_p)
{
	if ( this->m_element_count.load() < this->m_array_total_length.load() ) _LIKELY_
	{
		this->m_pointer_array_ptr.load(std::memory_order_acquire)[this->m_element_count] = indirect_ptr_p;
		++this->m_element_count;
	}
}

template<typename T, class allocator>
_FORCE_INLINE_ void indirection_list<T, allocator>::reserve(uint32 new_size_p)
{
	indirect<T, allocator>** l_ptr = this->m_pointer_array_ptr.load(std::memory_order_acquire);
	l_ptr = static_cast<indirect<T, allocator>**>( std::realloc( l_ptr, 
																static_cast< var::size_t>( sizeof(T) ) * static_cast<var::size_t>(this->m_array_total_length.load(std::memory_order_acquire) + new_size_p) 
																) 
												  );
	
	if ( l_ptr == nullptr )
	{
		l_ptr = new indirect<T, allocator>* [this->m_array_total_length.load(std::memory_order_acquire) + new_size_p] {nullptr};

		memcpy(l_ptr, this->m_pointer_array_ptr.load(std::memory_order_acquire), sizeof(indirect<T, allocator>*) * (this->m_array_total_length.load(std::memory_order_acquire)) );

		delete[] this->m_pointer_array_ptr.load(std::memory_order_acquire);
	}

	this->m_pointer_array_ptr.store(l_ptr, std::memory_order_release);
	this->m_array_total_length.store(this->m_array_total_length.load(std::memory_order_acquire) + new_size_p, std::memory_order_release);
}

template<typename T, class allocator>
_FORCE_INLINE_ void indirection_list<T, allocator>::shrink_to_fit()
{
	auto l_ptr = new indirect<T, allocator>*[this->m_array_total_length.load(std::memory_order_acquire)] {nullptr};

	var::uint32 l_index = 0;
	for ( auto it = this->begin(); it != this->end(); ++it )
	{
		if ( *it != nullptr )
		{
			l_ptr[l_index] = *it;
			++l_index;
		}
	}

	delete[] this->m_pointer_array_ptr.load(std::memory_order_acquire);
	this->m_pointer_array_ptr.store(l_ptr, std::memory_order_release);
	this->m_element_count.store(l_index, std::memory_order_release);
}





/* template class FE::memory::unique is a smart pointer that manages the lifecycle of a pointed object with a unique ownership policy. The object being pointed will be de-allocated when unique gets popped from the block scope.
Unique is null when anything has not been assigned. The memory will automatically be allocated when assigning value to it.
Avoid sharing the same reference of a unique instance across your thread pool. There are possible false sharing issues when multiple threads access the same indirection list container.
set the _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ macro flag to 1 or 2 if null object is occupying too much space. Singleton type instances are not supported.
allocator interface info:
static T* allocate(size_t count_p);
static void deallocate(T* ptr_p, size_t count_p);
e.g. when invoked: allocator::allocate(...); */
template <typename T, class allocator = t_allocator<T> >
class unique final
{
	template <typename T, class allocator >
	friend class indirect;

member_variables:
	indirection_list<T, allocator> m_indirection_list;
	std::atomic<T*> m_unique_ptr;
	var::uint32 m_indirection_list_reservation_size;
	std::atomic<var::uint32> m_size;
	
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	static T s_null; // null object can be expansive if the size of T type is enormous. T must not be a singleton type.
#endif

constructors:
	_FORCE_INLINE_ unique() noexcept;
	_FORCE_INLINE_ unique(std::initializer_list<T>&& arraylist_p) noexcept;
	_FORCE_INLINE_ unique(const T& value_ref_p) noexcept;
	_FORCE_INLINE_ unique(T&& rvalue_p) noexcept;

destructor:
	_FORCE_INLINE_ ~unique() noexcept;

copy_constructor:
	_FORCE_INLINE_ unique(unique<T, allocator>& copy_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ unique(unique<T, allocator>&& move_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ unique<T, allocator>& operator=(unique<T, allocator>& copy_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ unique<T, allocator>& operator=(unique<T, allocator>&& move_p) noexcept;

assignment_operator:
	_FORCE_INLINE_ unique<T, allocator>& operator=(std::initializer_list<T>&& arraylist_p) noexcept;
	_FORCE_INLINE_ unique<T, allocator>& operator=(const T& value_ref_p) noexcept;
	_FORCE_INLINE_ unique<T, allocator>& operator=(T&& rvalue_p) noexcept;

operators:
	_FORCE_INLINE_ T& operator[](uint64 index_p);
	_FORCE_INLINE_ T& operator*() noexcept;
	_FORCE_INLINE_ T* operator->() noexcept;

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >(const unique<T, allocator>& left_p, const unique<T, allocator>& right_p) noexcept
	{
		return left_p.m_unique_ptr > right_p.m_unique_ptr ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >=(const unique<T, allocator>& left_p, const unique<T, allocator>& right_p) noexcept
	{
		return left_p.m_unique_ptr >= right_p.m_unique_ptr ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <(const unique<T, allocator>& left_p, const unique<T, allocator>& right_p) noexcept
	{
		return left_p.m_unique_ptr < right_p.m_unique_ptr ? true : false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <=(const unique<T, allocator>& left_p, const unique<T, allocator>& right_p) noexcept
	{
		return left_p.m_unique_ptr <= right_p.m_unique_ptr ? true : false;
	}

static_methods:
	_FORCE_INLINE_ static void swap(unique<T, allocator>& A_ref_p, unique<T, allocator>& B_ref_p) noexcept;

methods:
	_FORCE_INLINE_ void discard() noexcept;
	_FORCE_INLINE_ boolean is_valid() noexcept;
	_FORCE_INLINE_ uint64 max_array_length() noexcept { return _UINT32_MAX_; }

	_FORCE_INLINE_ void indirection_list_reservation_size(uint32 next_reservation_size_p) noexcept { this->m_indirection_list_reservation_size = next_reservation_size_p; }
	_FORCE_INLINE_ uint32 indirection_list_reservation_size() noexcept { return this->m_indirection_list_reservation_size; }
};

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
template <typename T, class allocator >
T unique<T, allocator>::s_null; // null object is can be expansive if the size of T type is enormous. T must not be a singleton type.
#endif

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique() noexcept : m_unique_ptr(), m_size(), m_indirection_list_reservation_size(100)
{
	this->m_indirection_list.reserve(this->m_indirection_list_reservation_size);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique(std::initializer_list<T>&& arraylist_p) noexcept : m_indirection_list_reservation_size(100)
{
	this->m_unique_ptr.store( allocator::allocate(arraylist_p.size()), std::memory_order_release );

	var::uint16 l_idx = 0;
	for ( auto& ref : arraylist_p )
	{
		this->m_unique_ptr.load(std::memory_order_acquire)[l_idx] = std::move(ref);
		++l_idx;
	}
	this->m_size.store( arraylist_p.size(), std::memory_order_release );
	this->m_indirection_list.reserve(this->m_indirection_list_reservation_size);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique(const T& value_ref_p) noexcept : m_indirection_list_reservation_size(100)
{
	this->m_unique_ptr.store( allocator::allocate(1), std::memory_order_release );
	*(this->m_unique_ptr.load(std::memory_order_acquire)) = value_ref_p;
	this->m_size.store(1, std::memory_order_release);
	this->m_indirection_list.reserve(this->m_indirection_list_reservation_size);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique(T&& rvalue_p) noexcept : m_indirection_list_reservation_size(100)
{
	this->m_unique_ptr.store(allocator::allocate(1), std::memory_order_release);
	*(this->m_unique_ptr.load(std::memory_order_acquire)) = rvalue_p;
	this->m_size.store(1, std::memory_order_release);
	this->m_indirection_list.reserve(this->m_indirection_list_reservation_size);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::~unique() noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	// notify all...
	for ( std::atomic< indirect<T, allocator>* > ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr.store(nullptr, std::memory_order_release);
		}
	}
	allocator::deallocate(this->m_unique_ptr.load(std::memory_order_acquire), this->m_size.load(std::memory_order_acquire));
	this->m_unique_ptr.store(nullptr, std::memory_order_release);
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique(unique& copy_ref_p) noexcept : m_indirection_list_reservation_size(copy_ref_p.m_indirection_list_reservation_size)
{
	this->m_unique_ptr.store(std::move(copy_ref_p.m_unique_ptr), std::memory_order_release);
	copy_ref_p.m_unique_ptr.store(nullptr, std::memory_order_release);

	this->m_indirection_list = std::move(copy_ref_p.m_indirection_list);
	this->m_size.store(std::move(copy_ref_p.m_size), std::memory_order_release);

	// notify all... 
	for ( std::atomic<indirect<T, allocator>*> ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr.store(nullptr, std::memory_order_release);
		}
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>::unique(unique<T, allocator>&& move_p) noexcept : m_indirection_list_reservation_size(move_p.m_indirection_list_reservation_size)
{
	this->m_unique_ptr.store(std::move(move_p.m_unique_ptr), std::memory_order_release);
	move_p.m_unique_ptr.store(nullptr, std::memory_order_release);

	this->m_indirection_list = std::move(move_p.m_indirection_list);
	this->m_size.store(std::move(move_p.m_size), std::memory_order_release);

	// notify all...
	for ( std::atomic<indirect<T, allocator>*> ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr.store(nullptr, std::memory_order_release);
		}
	}
}

template<typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>& unique<T, allocator>::operator=(unique<T, allocator>& copy_ref_p) noexcept
{
	this->m_unique_ptr.store(std::move(copy_ref_p.m_unique_ptr), std::memory_order_release);
	copy_ref_p.m_unique_ptr.store(nullptr, std::memory_order_release);

	this->m_indirection_list = std::move(copy_ref_p.m_indirection_list);
	this->m_size.store(std::move(copy_ref_p.m_size), std::memory_order_release);
	this->m_indirection_list_reservation_size = copy_ref_p.m_indirection_list_reservation_size;

	// notify all... 
	for ( std::atomic<indirect<T, allocator>*> ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr.store(nullptr, std::memory_order_release);
		}
	}

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>& unique<T, allocator>::operator=(unique<T, allocator>&& move_p) noexcept
{
	this->m_unique_ptr.store(std::move(move_p.m_unique_ptr), std::memory_order_release);
	move_p.m_unique_ptr.store(nullptr, std::memory_order_release);

	this->m_indirection_list = std::move(move_p.m_indirection_list);
	this->m_size.store(std::move(move_p.m_size), std::memory_order_release);
	this->m_indirection_list_reservation_size = move_p.m_indirection_list_reservation_size;

	// notify all...
	for ( std::atomic<indirect<T, allocator>*> ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr.store(nullptr, std::memory_order_release);
		}
	}
	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>& unique<T, allocator>::operator=(std::initializer_list<T>&& arraylist_p) noexcept
{
	if ( this->m_size.load(std::memory_order_acquire) == arraylist_p.size() && this->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		var::uint16 l_idx = 0;
		for ( auto& ref : arraylist_p )
		{
			this->m_unique_ptr.load(std::memory_order_acquire)[l_idx] = std::move(ref);
			++l_idx;
		}
		return *this;
	}

	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		allocator::deallocate(this->m_unique_ptr.load(std::memory_order_acquire), this->m_size.load(std::memory_order_acquire));
	}

	this->m_unique_ptr,store( allocator::allocate(arraylist_p.size()), std::memory_order_release);
	this->m_size.store( arraylist_p.size(), std::memory_order_release );

	var::uint16 l_idx = 0;
	for ( auto& ref : arraylist_p )
	{
		this->m_unique_ptr.load(std::memory_order_acquire)[l_idx] = std::move(ref);
		++l_idx;
	}
	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>& unique<T, allocator>::operator=(const T& value_ref_p) noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		*(this->m_unique_ptr.load(std::memory_order_acquire)) = value_ref_p;
		this->m_size.store(1, std::memory_order_release);
	}
	else
	{
		this->m_unique_ptr.store( allocator::allocate(1), std::memory_order_release);
		this->m_size.store(1, std::memory_order_release);
		*(this->m_unique_ptr.load(std::memory_order_acquire)) = value_ref_p;
	}

	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ unique<T, allocator>& unique<T, allocator>::operator=(T&& rvalue_p) noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		*(this->m_unique_ptr.load(std::memory_order_acquire)) = rvalue_p;
		this->m_size.store(1, std::memory_order_release);
	}
	else
	{
		this->m_unique_ptr.store(allocator::allocate(1), std::memory_order_release);
		this->m_size.store(1, std::memory_order_release);
		*(this->m_unique_ptr.load(std::memory_order_acquire)) = rvalue_p;
	}

	return *this;
}

template <typename T, class allocator>
_FORCE_INLINE_ T& unique<T, allocator>::operator[](uint64 index_p)
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr ) _LIKELY_
	{
		return this->m_unique_ptr.load(std::memory_order_acquire)[index_p];
	}
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return unique<T, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template <typename T, class allocator>
_FORCE_INLINE_ T& unique<T, allocator>::operator*() noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr ) _LIKELY_
	{
		return *(this->m_unique_ptr.load(std::memory_order_acquire));
	}
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return unique<T, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template <typename T, class allocator>
_FORCE_INLINE_ T* unique<T, allocator>::operator->() noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		return this->m_unique_ptr.load(std::memory_order_acquire);
	}

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return &(unique<T, allocator>::s_null);
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template <typename T, class allocator>
_FORCE_INLINE_ void unique<T, allocator>::swap(unique<T, allocator>& A_ref_p, unique<T, allocator>& B_ref_p) noexcept
{
	unique<T, allocator> l_tmp = A_ref_p;
	A_ref_p = B_ref_p;
	B_ref_p = l_tmp;
}

template <typename T, class allocator>
_FORCE_INLINE_ void unique<T, allocator>::discard() noexcept
{
	if ( this->m_unique_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	// notify all...
	for ( std::atomic<indirect<T, allocator>*> ptr : this->m_indirection_list )
	{
		if ( ptr.load(std::memory_order_acquire) != nullptr )
		{
			ptr.load(std::memory_order_acquire)->m_ptr = nullptr;
		}
	}

	allocator::deallocate(this->m_unique_ptr.load(std::memory_order_acquire), this->m_size.load(std::memory_order_acquire));
	this->m_unique_ptr.store(nullptr, std::memory_order_release);
}

template <typename T, class allocator>
_FORCE_INLINE_ boolean unique<T, allocator>::is_valid() noexcept
{
	return this->m_unique_ptr.load(std::memory_order_acquire) != nullptr ? true : false;
}


END_NAMESPACE


template<typename T>
using unique_ptr = memory::unique<T>;


END_FE

#endif
#endif