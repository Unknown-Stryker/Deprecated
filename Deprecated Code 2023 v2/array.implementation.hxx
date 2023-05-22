#ifndef _FE_CORE_PARALLEL_ARRAY_IMPLEMENTATION_HXX_
#define _FE_CORE_PARALLEL_ARRAY_IMPLEMENTATION_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "array.interface.hxx"
#include "../../memory/allocator/allocator.implementation.hxx"


#if _MSVCPP_ == 1
#ifdef max
#undef max       
#endif

#ifdef min
#undef min
#endif
#endif


BEGIN_NAMESPACE(FE::parallel)


template<typename T, typename max_length_type, class padding_size, class allocator, class iterator>
T array<T, max_length_type, padding_size, allocator, iterator>::s_null = T();

template<typename T, typename max_length_type, class padding_size, class allocator, class iterator>
std::atomic< max_length_type> array<T, max_length_type, padding_size, allocator, iterator>::s_reserve_length = 0;

template <typename T, typename max_length_type, class padding_size, class allocator, class iterator>
_FORCE_INLINE_ max_length_type array<T, max_length_type, padding_size, allocator, iterator>::max_length() const noexcept
{
	return std::numeric_limits< max_length_type>::max();
}


END_NAMESPACE


#if _MSVCPP_ == 1
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif


#endif