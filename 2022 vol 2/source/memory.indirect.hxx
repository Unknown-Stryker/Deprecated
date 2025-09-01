#ifndef _INDIRECT_HXX_
#define _INDIRECT_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if  _HAS_CXX17 == 1
#include "memory.unique.hxx"




BEGIN_NAMESPACE(FE)



BEGIN_NAMESPACE(memory)



/*template class FE::memory::indirect is a smart pointer that promises null safety.If the indirection target(unique) is null, indirect will never access the invalid address.
Indirect has nothing to do with object lifecycle management.
Avoid sharing the same reference of a unique instance across your thread pool.There are possible false sharing issues when multiple threads access the same indirection list container.
set the _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ macro flag to 1 or 2 if null object is occupying too much space. Singleton type instances are not supported.
allocator interface info:
static T* allocate(size_t count_p);
static void deallocate(T* ptr_p, size_t count_p);
e.g. when invoked: allocator::allocate(...); */
template <typename T, class allocator = t_allocator<T> >
class indirect final
{
	template <typename T, class allocator >
	friend class unique;

member_variables:
	std::atomic<FE::memory::unique<T, allocator>*> m_ptr;
	
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	static T s_null; // null object can be expansive if the size of T type is enormous. T must not be a singleton type.
#endif

constructors:
	_FORCE_INLINE_ indirect() noexcept;
	_FORCE_INLINE_ indirect(unique<T, allocator>& unique_ref_p) noexcept;
	

destructor:
	_FORCE_INLINE_ ~indirect() noexcept;

copy_constructor:
	_FORCE_INLINE_ indirect(const indirect<T, allocator>& copy_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ indirect(indirect<T, allocator>&& rvalue_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ indirect<T, allocator>& operator=(const indirect<T, allocator>& copy_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ indirect<T, allocator>& operator=(indirect<T, allocator>&& rvalue_p) noexcept;

assignment_operator:
	_FORCE_INLINE_ indirect<T, allocator>& operator=(unique<T, allocator>& unique_ref_p) noexcept;

operators:
	_FORCE_INLINE_ T& operator[](uint64 index_p) noexcept;
	_FORCE_INLINE_ T& operator*() noexcept;
	_FORCE_INLINE_ T* operator->() noexcept;

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >(const indirect<T, allocator>& left_p, const indirect<T, allocator>& right_p) noexcept
	{
		if ( left_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }
		if ( right_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }

		if ( *(left_p.m_ptr) > *(right_p.m_ptr) )
		{
			return true;
		}
		return false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator >=(const indirect<T, allocator>& left_p, const indirect<T, allocator>& right_p) noexcept
	{
		if ( left_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }
		if ( right_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }

		if ( *(left_p.m_ptr) >= *(right_p.m_ptr) )
		{
			return true;
		}
		return false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <(const indirect<T, allocator>& left_p, const indirect<T, allocator>& right_p) noexcept
	{
		if ( left_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }
		if ( right_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }

		if ( *(left_p.m_ptr) < *(right_p.m_ptr) )
		{
			return true;
		}
		return false;
	}

	// evaluates the location of memory address
	_FORCE_INLINE_ friend boolean operator <=(const indirect<T, allocator>& left_p, const indirect<T, allocator>& right_p) noexcept
	{
		if ( left_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }
		if ( right_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return false; }

		if ( *(left_p.m_ptr) <= *(right_p.m_ptr) )
		{
			return true;
		}
		return false;
	}

static_methods:
	_FORCE_INLINE_ static void swap(indirect<T, allocator>& A_ref_p, indirect<T, allocator>& B_ref_p) noexcept;

	_FORCE_INLINE_ void indirection_list_reservation_size(uint32 next_reservation_size_p) noexcept;
	_FORCE_INLINE_ uint32 indirection_list_reservation_size() noexcept;
};

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
template <typename T, class allocator >
T indirect<T, allocator>::s_null; // null object is can be expansive if the size of T type is enormous. T must not be a singleton type.
#endif

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>::indirect() noexcept : m_ptr() {}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>::indirect(unique<T, allocator>& unique_ref_p) noexcept
{
	if ( unique_ref_p.m_indirection_list.size() < unique_ref_p.m_indirection_list.capacity() )
	{
		unique_ref_p.m_indirection_list.emplace_back(this);
		this->m_ptr.store(&unique_ref_p, std::memory_order_release);
		return;
	}

	for ( var::uint64 idx = 0; idx < unique_ref_p.m_indirection_list.size(); ++idx)
	{
		if ( unique_ref_p.m_indirection_list[idx] == nullptr )
		{
			unique_ref_p.m_indirection_list[idx] = this;
			this->m_ptr.store(&unique_ref_p, std::memory_order_release);
			return;
		}
	}

	unique_ref_p.m_indirection_list.reserve(this->indirection_list_reservation_size());
	unique_ref_p.m_indirection_list.emplace_back(this);
	this->m_ptr.store(&unique_ref_p, std::memory_order_release);
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>::~indirect() noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	var::uint64 l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();
	for ( var::uint64 idx = 0; idx < l_size; ++idx )
	{
		if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return; }
		l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();

		if ( this->m_ptr.load(std::memory_order_acquire) != nullptr && 
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == this )
		{
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = nullptr;
			this->m_ptr.store(nullptr, std::memory_order_release);
			return;
		}
	}
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>::indirect(const indirect<T, allocator>& copy_ref_p) noexcept
{
	if ( copy_ref_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	this->m_ptr.store(copy_ref_p.m_ptr, std::memory_order_release);

	if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size() < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.capacity() )
	{
		this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
		return;
	}

	for ( var::uint64 idx = 0; idx < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size(); ++idx )
	{
		if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == nullptr )
		{
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = this;
			return;
		}
	}

	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.reserve(this->indirection_list_reservation_size());
	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>::indirect(indirect<T, allocator>&& rvalue_p) noexcept : m_ptr()
{
	if ( rvalue_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return; }

	this->m_ptr.store(rvalue_p.m_ptr, std::memory_order_release);

	if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size() < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.capacity() )
	{
		this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
		return;
	}

	for ( var::uint64 idx = 0; idx < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size(); ++idx )
	{
		if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == nullptr )
		{
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = this;
			return;
		}
	}

	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.reserve(this->indirection_list_reservation_size());
	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>& indirect<T, allocator>::operator=(const indirect<T, allocator>& copy_ref_p) noexcept
{
	if ( copy_ref_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return *this; }

	this->m_ptr.store(copy_ref_p.m_ptr, std::memory_order_release);

	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr )
	{
		var::uint64 l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();
		for ( var::uint64 idx = 0; idx < l_size; ++idx )
		{
			if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return *this; }
			l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();

			if ( this->m_ptr.load(std::memory_order_acquire) != nullptr &&
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == this )
			{
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = nullptr;
				this->m_ptr.store(nullptr, std::memory_order_release);
			}
		}
	}


	if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size() < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.capacity() )
	{
		this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
		return *this;
	}

	for ( var::uint64 idx = 0; idx < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size(); ++idx )
	{
		if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == nullptr )
		{
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = this;
			return *this;
		}
	}

	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.reserve(this->indirection_list_reservation_size());
	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
	return *this;
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>& indirect<T, allocator>::operator=(indirect<T, allocator>&& rvalue_p) noexcept
{
	if ( rvalue_p.m_ptr.load(std::memory_order_acquire) == nullptr ) { return *this; }

	this->m_ptr.store(rvalue_p.m_ptr, std::memory_order_release);

	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr )
	{
		var::uint64 l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();
		for ( var::uint64 idx = 0; idx < l_size; ++idx )
		{
			if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return *this; }
			l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();

			if ( this->m_ptr.load(std::memory_order_acquire) != nullptr &&
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == this )
			{
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = nullptr;
				this->m_ptr.store(nullptr, std::memory_order_release);
			}
		}
	}


	if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size() < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.capacity() )
	{
		this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
		return *this;
	}

	for ( var::uint64 idx = 0; idx < this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size(); ++idx )
	{
		if ( this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == nullptr )
		{
			this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = this;
			return *this;
		}
	}

	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.reserve(this->indirection_list_reservation_size());
	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.emplace_back(this);
	return *this;
}

template <typename T, class allocator>
_FORCE_INLINE_ indirect<T, allocator>& indirect<T, allocator>::operator=(unique<T, allocator>& unique_ref_p) noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr )
	{
		var::uint64 l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();
		for ( var::uint64 idx = 0; idx < l_size; ++idx )
		{
			if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return *this; }
			l_size = this->m_ptr.load(std::memory_order_acquire)->m_indirection_list.size();

			if ( this->m_ptr.load(std::memory_order_acquire) != nullptr &&
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] == this )
			{
				this->m_ptr.load(std::memory_order_acquire)->m_indirection_list[idx] = nullptr;
				this->m_ptr.store(nullptr, std::memory_order_release);
			}
		}
	}


	if ( unique_ref_p.m_indirection_list.size() < unique_ref_p.m_indirection_list.capacity() )
	{
		unique_ref_p.m_indirection_list.emplace_back(this);
		this->m_ptr.store(&unique_ref_p, std::memory_order_release);
		return *this;
	}

	for ( var::uint64 idx = 0; idx < unique_ref_p.m_indirection_list.size(); ++idx )
	{
		if ( unique_ref_p.m_indirection_list[idx] == nullptr )
		{
			unique_ref_p.m_indirection_list[idx] = this;
			this->m_ptr.store(&unique_ref_p, std::memory_order_release);
			return *this;
		}
	}

	unique_ref_p.m_indirection_list.reserve(this->indirection_list_reservation_size());
	unique_ref_p.m_indirection_list.emplace_back(this);
	this->m_ptr.store(&unique_ref_p, std::memory_order_release);
	return *this;
}

template<typename T, class allocator>
_FORCE_INLINE_ T& indirect<T, allocator>::operator[](uint64 index_p) noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr &&
		this->m_ptr.load(std::memory_order_acquire)->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		return this->m_ptr.load(std::memory_order_acquire)-> m_unique_ptr.load(std::memory_order_acquire)[index_p];
	}
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return indirect<T, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template<typename T, class allocator>
_FORCE_INLINE_ T& indirect<T, allocator>::operator*() noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr &&
		this->m_ptr.load(std::memory_order_acquire)->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		return *(this->m_ptr.load(std::memory_order_acquire)->m_unique_ptr.load(std::memory_order_acquire));
	}
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return indirect<T, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template<typename T, class allocator>
_FORCE_INLINE_ T* indirect<T, allocator>::operator->() noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) != nullptr && 
		this->m_ptr.load(std::memory_order_acquire)->m_unique_ptr.load(std::memory_order_acquire) != nullptr )
	{
		return this->m_ptr.load(std::memory_order_acquire)->m_unique_ptr.load(std::memory_order_acquire);
	}
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
	return &( indirect<T, allocator>::s_null );
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
	exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
}

template<typename T, class allocator>
_FORCE_INLINE_ void indirect<T, allocator>::swap(indirect<T, allocator>& A_ref_p, indirect<T, allocator>& B_ref_p) noexcept
{
	indirect<T, allocator> l_tmp = A_ref_p;
	A_ref_p = B_ref_p;
	B_ref_p = l_tmp;
}

template<typename T, class allocator>
_FORCE_INLINE_ void indirect<T, allocator>::indirection_list_reservation_size(uint32 next_reservation_size_p) noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return; }
	this->m_ptr.load(std::memory_order_acquire)->m_indirection_list_reservation_size = next_reservation_size_p;
}

template<typename T, class allocator>
_FORCE_INLINE_ uint32 indirect<T, allocator>::indirection_list_reservation_size() noexcept
{
	if ( this->m_ptr.load(std::memory_order_acquire) == nullptr ) { return 0; }
	return this->m_ptr.load(std::memory_order_acquire)->m_indirection_list_reservation_size;
}


END_NAMESPACE


template<typename T>
using indirect_ptr = memory::indirect<T>;


END_FE

#endif
#endif