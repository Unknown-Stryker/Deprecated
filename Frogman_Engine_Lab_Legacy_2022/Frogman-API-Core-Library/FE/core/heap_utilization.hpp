#ifndef _FE_CORE_HEAP_UTILIZATION_HPP_
#define _FE_CORE_HEAP_UTILIZATION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "memory_metrics.h"
#include "private/memory.hxx"


BEGIN_NAMESPACE(FE)


template<typename T>
class heap_utilization;

template<typename T>
class new_delete_allocator;

template <typename T>
class c_style_allocator;


void memset_s(void* const dst_ptrc_p, int32 value_p, length_t count_p, size_t bytes_p) noexcept;

void memcpy_s(void* const dst_memblock_ptrc_p, void* const src_memblock_ptrc_p, length_t dst_length_p, size_t dst_bytes_p, length_t src_length_p, size_t src_bytes_p) noexcept;


class heap_memory_tracker
{
protected:
	static std::atomic_size_t s_global_total_bytes;
	thread_local static var::size_t tl_s_thread_local_total_bytes;
};


template<typename T1>
class heap_utilization final : public heap_memory_tracker
{
	friend class new_delete_allocator<T1>;
	friend class c_style_allocator<T1>;

private:
	static std::atomic_size_t s_global_total_bytes_by_type;
	thread_local static var::size_t tl_s_thread_local_total_bytes_by_type;

private:
	static void add(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker::s_global_total_bytes.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes += size_bytes_p;

		heap_utilization<T1>::s_global_total_bytes_by_type.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_utilization<T1>::tl_s_thread_local_total_bytes_by_type += size_bytes_p;
	}

	static void sub(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker::s_global_total_bytes.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes -= size_bytes_p;

		heap_utilization<T1>::s_global_total_bytes_by_type.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_utilization<T1>::tl_s_thread_local_total_bytes_by_type -= size_bytes_p;
	}

public:
	typedef T1 memory_type;

	static total_memory_utilization_data query_all_data() noexcept 
	{
#if _ENABLE_MEMORY_TRACKER_ == 1
		total_memory_utilization_data l_data
		{
			heap_memory_tracker::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes,
			heap_utilization<T1>::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_utilization<T1>::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
		return 0;
#endif
	}
	
	static global_memory_utilization query_global_data() noexcept
	{
#if _ENABLE_MEMORY_TRACKER_ == 1
		global_memory_utilization l_data
		{
			heap_memory_tracker::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes
		};
		return l_data;
#else
		return 0;
#endif
	}

	static type_memory_utilization query_type_data() noexcept
	{
#if _ENABLE_MEMORY_TRACKER_ == 1
		type_memory_utilization l_data
		{
			heap_utilization<T1>::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_utilization<T1>::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
	return 0;
#endif
	}

public:
	template<typename T>
	friend _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept;

	template<typename T>
	friend _FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, length_t count_p, size_t bytes_p) noexcept;

	template<typename T>
	friend _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept;
};


template<typename T>
std::atomic_size_t FE::heap_utilization<T>::s_global_total_bytes_by_type = 0;

template<typename T>
thread_local var::size_t FE::heap_utilization<T>::tl_s_thread_local_total_bytes_by_type = 0;


template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == 1
	::FE::heap_utilization<T>::add(count_p * bytes_p);
#endif
	return (T*)::calloc(count_p, bytes_p);
}


template<typename T>
_FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, length_t count_p, size_t bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == 1
	::FE::heap_utilization<T>::sub(count_p * bytes_p);
#endif 
	::free(memblock_ptrc_p);
}


template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == 1
	::FE::heap_utilization<T>::s_global_total_bytes_by_type::sub(prev_length_p * prev_bytes_p);
	::FE::heap_utilization<T>::s_global_total_bytes_by_type::add(new_length_p * new_bytes_p);
#endif

	T* l_realloc_result_ptr = static_cast<T*>(::std::realloc(memblock_ptrc_p, new_bytes_p * new_length_p));

	if (l_realloc_result_ptr == nullptr)
#if _HAS_CXX20_
		_UNLIKELY_
#endif
	{
		l_realloc_result_ptr = ::FE::trackable_calloc<T>(new_length_p, new_bytes_p);

		if (l_realloc_result_ptr == nullptr)
#if _HAS_CXX20_
			_UNLIKELY_
#endif
		{
			::abort();
		}

		::FE::memcpy_s(l_realloc_result_ptr, memblock_ptrc_p, new_length_p, new_bytes_p, prev_length_p, prev_bytes_p);
		::FE::trackable_free(memblock_ptrc_p, prev_length_p, prev_bytes_p);
	}

	return l_realloc_result_ptr;
}


END_NAMESPACE
#endif 
