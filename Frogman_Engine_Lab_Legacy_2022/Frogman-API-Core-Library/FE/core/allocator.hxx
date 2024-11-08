#ifndef _FE_CORE_ALLOCATOR_HXX_
#define _FE_CORE_ALLOCATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <oneapi/tbb/cache_aligned_allocator.h>
#include <oneapi/tbb/scalable_allocator.h>
#include "prerequisite_symbols.h"
#include "runtime_exception.hpp"
#include "heap_utilization.hpp"
#include "private/memory.hxx"


BEGIN_NAMESPACE(FE)


template <typename T>
class new_delete_allocator final
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef var::size_t size_type;


	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p) noexcept
	{
		// must invoke delete[] when returning memory to the system. Calling delete without index operator [] will abort() the application.
		switch (count_p)
		{
		case 0:
			::FE::exception::handle_exceptions(true, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.", _EXCEPTION_ORIGIN_);
			break;

		case 1:
#if _ENABLE_MEMORY_TRACKER_ == 1
			::FE::heap_utilization<T>::add(sizeof(T));
#endif
			return new T;

		default:
			break;
		}

#if _ENABLE_MEMORY_TRACKER_ == 1
		::FE::heap_utilization<T>::add(sizeof(T) * count_p);
#endif
		return new T[count_p];
	}

	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, size_t prev_count_p, size_t new_count_p) noexcept
	{
		switch (new_count_p)
		{
		case 0:
			::FE::exception::handle_exceptions(true, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: queried reallocation size is zero.", _EXCEPTION_ORIGIN_);
			break;

		default:
			break;
		}

		return ::FE::trackable_realloc(ptrc_p, prev_count_p, sizeof(T), new_count_p, sizeof(T));
	}

	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, size_t count_p) noexcept
	{
		::FE::exception::handle_exceptions(ptrc_p == nullptr, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr.", _EXCEPTION_ORIGIN_);

		switch (count_p)
		{
		case 0:
			::FE::exception::handle_exceptions(true, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: attempted to delete zero byte.", _EXCEPTION_ORIGIN_);
			break;
		case 1:
#if _ENABLE_MEMORY_TRACKER_ == 1
			::FE::heap_utilization<T>::sub(sizeof(T));
#endif
			delete ptrc_p;
			break;

		default:
			break;
		}

#if _ENABLE_MEMORY_TRACKER_ == 1
		::FE::heap_utilization<T>::sub(sizeof(T) * count_p);
#endif 
		delete[] ptrc_p;
	}
};


template <typename T>
class c_style_allocator final
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef var::size_t size_type;

	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p) noexcept
	{
		switch(count_p)
		{
		case 0:
			::FE::exception::handle_exceptions(true, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.", _EXCEPTION_ORIGIN_);
			break;

		default:
			break;
		}

		return ::FE::trackable_calloc<T>(count_p, sizeof(T));
	}

	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, size_t prev_count_p, size_t new_count_p) noexcept
	{
		switch (new_count_p)
		{
		case 0:
			::FE::exception::handle_exceptions(true, FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: queried reallocation size is zero.", _EXCEPTION_ORIGIN_);
			break;

		default:
			break;
		}

		return ::FE::trackable_realloc(ptrc_p, prev_count_p, sizeof(T), new_count_p, sizeof(T));
	}

	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, size_t count_p) noexcept
	{
		::FE::exception::handle_exceptions((ptrc_p == nullptr) || (count_p == 0), FE::_ABORT_IMMEDIATELY_, "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr or the size input value is zero.", _EXCEPTION_ORIGIN_);
		
		::FE::trackable_free(ptrc_p, count_p, sizeof(T));
	}
};


END_NAMESPACE
#endif