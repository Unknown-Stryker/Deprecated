#ifndef _FE_CORE_DEQUE_HXX_
#define _FE_CORE_DEQUE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>




BEGIN_NAMESPACE(FE)


template <typename T, class Allocator = FE::scalable_aligned_allocator<T>>
class deque final
{

};


namespace concurrency
{
	template <typename T, class Allocator = FE::cache_aligned_allocator<T>>
	class deque final
	{

	};
}


template <typename T>
using concurrent_deque = concurrency::deque<T>;


END_NAMESPACE
#endif