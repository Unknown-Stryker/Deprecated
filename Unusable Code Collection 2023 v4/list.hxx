#ifndef _FE_CORE_LIST_HXX_
#define _FE_CORE_LIST_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>
#include <FE/core/memory.hxx>
#include <FE/core/iterator.hxx>
#include <FE/core/memory_metrics.h>
#include <FE/core/smart_pointers/smart_ptrs.h>




BEGIN_NAMESPACE(FE)


template<typename T>
struct should_nodes_be_pooled
{
	constexpr static boolean value = (sizeof(T) < 1 KB);
};


template <typename T, class Allocator = FE::scalable_aligned_allocator<T>, boolean NodePooling = should_nodes_be_pooled<T>::value>
class list final
{
	struct node
	{
		T _data;
		// exclusive ptr
		// proxy ptr
	};
};


template <typename T, class Allocator>
class list<T, Allocator, true> final
{

};




namespace concurrency
{
	template <typename T, class Allocator = FE::cache_aligned_allocator<T>>
	class list final
	{

	};
}


template <typename T>
using concurrent_list = concurrency::list<T>;


END_NAMESPACE
#endif