// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../heap_utilization.hpp"


std::atomic_size_t FE::heap_memory_tracker::s_global_total_bytes = 0;

thread_local FE::var::size_t FE::heap_memory_tracker::tl_s_thread_local_total_bytes = 0;


void ::FE::memset_s(void* const dst_ptrc_p, int32 value_p, length_t count_p, size_t bytes_p) noexcept
{
	memset(dst_ptrc_p, value_p, bytes_p * count_p);
}

void ::FE::memcpy_s(void* const dst_memblock_ptrc_p, void* const src_memblock_ptrc_p, length_t dst_length_p, size_t dst_bytes_p, length_t src_length_p, size_t src_bytes_p) noexcept
{
	size_t l_src_size = src_bytes_p * src_length_p;
	size_t l_dst_size = dst_bytes_p * dst_length_p;

	if (l_src_size >= l_dst_size)
	{
		::memcpy(dst_memblock_ptrc_p, src_memblock_ptrc_p, l_dst_size);
	}
	else
	{
		::memcpy(dst_memblock_ptrc_p, src_memblock_ptrc_p, l_src_size);
	}
}