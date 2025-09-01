#ifndef _SINGLETON_HXX_
#define _SINGLETON_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.types.h"




BEGIN_NAMESPACE(FE)


BEGIN_NAMESPACE(utilty)


template<typename T>
class singleton final
{
member_variables:
	static T* s_instance_ptr;

private_constructors:
	singleton() noexcept;

methods:
	singleton(const singleton& nope_ref_p) noexcept = delete;
	singleton& operator=(const singleton& prohibited_ref_p) noexcept = delete;
	singleton(singleton&& nope_p) noexcept = delete;
	singleton& operator=(singleton&& prohibited_p) noexcept = delete;

	static T& singleton_instance() noexcept;
	static void destruct_singleton() noexcept;
};


template<typename T>
T* singleton<T>::s_instance_ptr = nullptr;


template<typename T>
inline T& singleton<T>::singleton_instance() noexcept
{
	if ( s_instance_ptr != nullptr ) _LIKELY_
	{
		return *s_instance_ptr;
	}

	s_instance_ptr = new T;
	return *s_instance_ptr;
}

template<typename T>
inline void singleton<T>::destruct_singleton() noexcept
{
	if ( s_instance_ptr == nullptr ) { return; }

	delete s_instance_ptr;
	s_instance_ptr = nullptr;
}

END_NAMESPACE

END_FE

#endif
#endif
