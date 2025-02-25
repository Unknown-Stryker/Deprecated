﻿#ifndef _FE_CORE_PRIVATE_ALLOCATOR_BASE_HPP_
#define _FE_CORE_PRIVATE_ALLOCATOR_BASE_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/memory_metrics.h>
#include <FE/core/memory.hxx>
#include <FE/core/thread.hpp>
#include <cstdlib>



#ifdef _WINDOWS_X86_64_
#define ALIGNED_ALLOC(size_p, alignment_p) ::_aligned_malloc(size_p, alignment_p)
#define ALIGNED_FREE(ptr_to_memory_p) ::_aligned_free(ptr_to_memory_p)
#define ALIGNED_REALLOC(ptr_to_memory_p, new_size_p, alignment_p) ::_aligned_realloc(ptr_to_memory_p, new_size_p, alignment_p)

#elif defined(_LINUX_X86_64_)
#define ALIGNED_ALLOC(size_p, alignment_p) ::aligned_alloc(size_p, alignment_p)
#define ALIGNED_FREE(ptr_to_memory_p) ::free(ptr_to_memory_p)
#define ALIGNED_REALLOC(ptr_to_memory_p, new_size_p, alignment_p) ::realloc(ptr_to_memory_p, new_size_p)
#endif




BEGIN_NAMESPACE(FE)


class allocator_base
{
protected:
	static std::atomic_int64_t s_total_memory_util;
	thread_local static var::int64 tl_s_thread_local_memory_util;

	_FORCE_INLINE_ static void add(int64 size_bytes_p) noexcept
	{
		s_total_memory_util.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		tl_s_thread_local_memory_util += size_bytes_p;
	}

	_FORCE_INLINE_ static void sub(int64 size_bytes_p) noexcept
	{
		s_total_memory_util.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		tl_s_thread_local_memory_util -= size_bytes_p;
	}

#if defined(_ENABLE_MEMORY_TRACKER_)
	_FORCE_INLINE_ static void __log_heap_memory_allocation(uint64 size_in_bytes_to_allocate_p, const char* const allocator_name_p, U* const allocated_address_p, const char* const allocated_type_name_p) noexcept
	{
		uint64 l_this_thread_id = FE::thread::this_thread_id();

		memory_utilization l_prev_heap_mem_usage_in_bytes = query_all_data();
		add(size_in_bytes_to_allocate_p);
		FE_LOG("\n\n The previous total heap memory used by this application was ${%lu@0} bytes. \n The previous total heap memory used by this thread[id:${%lu@1}] was ${%lu@2} bytes.\n Allocated ${%lu@3} bytes of heap memory from ${%s@4}. \n The memory address is aligned by ${%d@5} bytes. \n The allocated memory data type is ${%s@6}.\n The allocated memory address is 0x${%p@7} \n", &(l_prev_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_prev_heap_mem_usage_in_bytes._thread_local_bytes), &size_in_bytes_to_allocate_p, allocator_name_p, &SourceAddressAlignment::size, allocated_type_name_p, allocated_address_p);

		memory_utilization l_new_heap_mem_usage_in_bytes = query_all_data();
		FE_LOG("\n\n New total heap memory used by this application is now ${%lu@0} bytes. \n New total heap memory used by this thread[id:${%lu@1}] is now ${%lu@2} bytes.\n", &(l_new_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_new_heap_mem_usage_in_bytes._thread_local_bytes));
	}

	_FORCE_INLINE_ static void __log_heap_memory_reallocation(uint64 prev_size_in_bytes_p, uint64 new_size_in_bytes_to_allocate_p, const char* const allocator_name_p, U* const allocated_address_p, const char* const allocated_type_name_p) noexcept
	{
		uint64 l_this_thread_id = FE::thread::this_thread_id();

		memory_utilization l_prev_heap_mem_usage_in_bytes = query_all_data();
		sub(prev_size_in_bytes_p);
		add(new_size_in_bytes_to_allocate_p);
		FE_LOG("\n\n The previous total heap memory used by this application was ${%lu@0} bytes. \n The previous total heap memory used by this thread[id:${%lu@1}] was ${%lu@2} bytes.\n Re-allocated ${%lu@3} bytes of heap memory from ${%s@4}. \n The memory address is aligned by ${%d@5} bytes. \n The allocated memory data type is ${%s@6}.\n The allocated memory address is 0x${%p@7} \n", &(l_prev_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_prev_heap_mem_usage_in_bytes._thread_local_bytes), &new_size_in_bytes_to_allocate_p, allocator_name_p, &SourceAddressAlignment::size, allocated_type_name_p, allocated_address_p);

		memory_utilization l_new_heap_mem_usage_in_bytes = query_all_data();
		FE_LOG("\n\n New total heap memory used by this application is now ${%lu@0} bytes. \n New total heap memory used by this thread[id:${%lu@1}] is now ${%lu@2} bytes.\n", &(l_new_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_new_heap_mem_usage_in_bytes._thread_local_bytes));
	}

	_FORCE_INLINE_ static void __log_heap_memory_deallocation(uint64 size_in_bytes_to_deallocate_p, const char* const allocator_name_p, U* const allocated_address_p, const char* const allocated_type_name_p) noexcept
	{
		uint64 l_this_thread_id = FE::thread::this_thread_id();

		memory_utilization l_prev_heap_mem_usage_in_bytes = query_all_data();
		sub(size_in_bytes_to_deallocate_p);
		FE_LOG("\n\n The previous total heap memory used by this application was ${%lu@0} bytes. \n The previous total heap memory used by this thread[id:${%lu@1}] was ${%lu@2} bytes.\n De-allocated ${%lu@3} bytes of heap memory via ${%s@4}. \n The memory address is aligned by ${%d@5} bytes. \n The de-allocated memory data type is ${%s@6}.\n The de-allocated memory address is 0x${%p@7} \n", &(l_prev_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_prev_heap_mem_usage_in_bytes._thread_local_bytes), &size_in_bytes_to_deallocate_p, allocator_name_p, &SourceAddressAlignment::size, allocated_type_name_p, allocated_address_p);

		memory_utilization l_new_heap_mem_usage_in_bytes = query_all_data();
		FE_LOG("\n\n New total heap memory used by this application is now ${%lu@0} bytes. \n New total heap memory used by this thread[id:${%lu@1}] is now ${%lu@2} bytes.\n", &(l_new_heap_mem_usage_in_bytes._global_bytes), &l_this_thread_id, &(l_new_heap_mem_usage_in_bytes._thread_local_bytes));
	}
#endif

public:
	_FORCE_INLINE_ static memory_utilization query_all_data() noexcept
	{
#if defined(_ENABLE_MEMORY_TRACKER_)
		memory_utilization l_data
		{
			s_total_memory_util.load(std::memory_order_relaxed), tl_s_thread_local_memory_util
		};
		return l_data;
#else
		memory_utilization l_null{ _NULL_ };
		return l_null;
#endif
	}

	template<typename T, class Alignment = typename FE::SIMD_auto_alignment>
	_FORCE_INLINE_ T* trackable_alloc(size_t bytes_p) noexcept
	{
		T* const l_result = (T*)ALIGNED_ALLOC(bytes_p, Alignment::size);
#if !defined(_RELEASE_)
		ALIGNED_MEMSET(l_result, _NULL_, bytes_p);
#endif

		FE_ASSERT(l_result == nullptr, "${%s@0}: Failed to allocate memory from scalable_aligned_malloc()", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
		FE_ASSERT((reinterpret_cast<uintptr_t>(l_result) % Alignment::size) != 0, "${%s@0}: The allocated heap memory address not aligned by ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_ILLEGAL_ADDRESS_ALIGNMENT), &Alignment::size);

#if defined(_ENABLE_MEMORY_TRACKER_)
		allocator_base::__log_heap_memory_allocation(bytes_p, TO_STRING(trackable_alloc), l_result, typeid(T).name());
#endif

		return l_result;
	}

	template<typename T, class Alignment = typename FE::SIMD_auto_alignment>
	_FORCE_INLINE_ void trackable_free(T* const ptr_to_memory_p, _MAYBE_UNUSED_ size_t bytes_p) noexcept
	{
		FE_ASSERT((reinterpret_cast<uintptr_t>(ptr_to_memory_p) % Alignment::size) != 0, "${%s@0}: The allocated heap memory address not aligned by ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_ILLEGAL_ADDRESS_ALIGNMENT), &Alignment::size);

		ALIGNED_FREE(ptr_to_memory_p);

#if defined(_ENABLE_MEMORY_TRACKER_)
		allocator_base::__log_heap_memory_deallocation(bytes_p, TO_STRING(trackable_free), ptr_to_memory_p, typeid(T).name());
#endif 
	}

	template<typename T, class Alignment = typename FE::SIMD_auto_alignment>
	_FORCE_INLINE_ T* trackable_realloc(T* const ptr_to_memory_p, size_t prev_bytes_p, size_t new_bytes_p) noexcept
	{
		T* l_realloc_result = (T*)ALIGNED_REALLOC(ptr_to_memory_p, new_bytes_p, Alignment::size);

		if (l_realloc_result == nullptr) _UNLIKELY_
		{
			l_realloc_result = (T*)ALIGNED_ALLOC(new_bytes_p, Alignment::size);
	#if !defined(_RELEASE_)
			ALIGNED_MEMSET(l_realloc_result, _NULL_, new_bytes_p);
	#endif
			FE_ASSERT(l_realloc_result == nullptr, "${%s@0}: Failed to re-allocate memory from scalable_aligned_malloc()", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

			FE::memcpy<ADDRESS::_ALIGNED, ADDRESS::_ALIGNED>(l_realloc_result, new_bytes_p, ptr_to_memory_p, prev_bytes_p);

			if (l_realloc_result != ptr_to_memory_p) _LIKELY_
			{
				ALIGNED_FREE(ptr_to_memory_p);
			}
		}

		FE_ASSERT((reinterpret_cast<uintptr_t>(l_realloc_result) % Alignment::size) != 0, "${%s@0}: The allocated heap memory address not aligned by ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_ILLEGAL_ADDRESS_ALIGNMENT), &Alignment::size);

#if defined(_ENABLE_MEMORY_TRACKER_)
		allocator_base::__log_heap_memory_reallocation(prev_bytes_p, new_bytes_p, TO_STRING(trackable_realloc), l_realloc_result, typeid(T).name());
#endif

		return l_realloc_result;
	}
};


END_NAMESPACE
#endif 
