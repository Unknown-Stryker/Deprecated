#pragma once
#ifndef _SINGLETON_HXX_
#define _SINGLETON_HXX_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"
#include "mstring.hpp"
#include "typeinfo.h"


FROGMAN_DESIGN_PATTERN_LIBRARY
{
	template<typename T>
	frogman_design_pattern_class singleton
	{
	private_member_variables:
		static T* s_instance;
		static FFC::mstring s_typename;

	constructors:
		singleton() {}
		
	private_constructors:
		singleton(const singleton& nope_p) {}

	private_operators:
		singleton& operator=(const singleton& prohibited_p) { return *this; }

	destructor:
		~singleton();

	GETTERS:
		static T& GET_singleton_instance();

	public_methods:
		static void delete_singleton_instance();
	};

	template<typename T>
	T* singleton<T>::s_instance = nullptr;

	template<typename T>
	FFC::mstring singleton<T>::s_typename = "\0";

	template<typename T>
	singleton<T>::~singleton()
	{
		if (s_instance != nullptr)
		{
			s_typename = "\0";
			delete s_instance;
			s_instance = nullptr;
		}
	}

	template<typename T>
	T& singleton<T>::GET_singleton_instance()
	{
		if (s_instance == nullptr)
		{
			s_typename = typeid(T).name();
			s_instance = new T;
			return *s_instance;
		}

		return *s_instance;
	}

	template<typename T>
	void singleton<T>::delete_singleton_instance()
	{
		if (s_instance == nullptr) { return; }

		s_typename = "\0";
		delete s_instance;
		s_instance = nullptr;
	}
}


#endif
