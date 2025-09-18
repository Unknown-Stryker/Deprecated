#pragma once
#ifndef _SINGLETON_HXX_
#define _SINGLETON_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved
#include "../../config/types.h"




BEGIN NAMESPACE(fstd)


template<typename T>
class singleton
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


END_FSTD

#endif
