#pragma once
#ifndef _ELEMENT_HXX_
#define _ELEMENT_HXX_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#pragma warning (disable : 26495)
#include "common_definitions.h"
#include "ELEMENT_STATUS.h"
#include "mstring.hpp"


FROGMAN_TEMPLATE_STRUCT_LIBRARY
{
	template<typename T>
	frogman_fundamental_struct element
	{
		T m_data;
		FFC::mstring m_tag;
		FFE::ELEMENT_STATUS m_element_status;

	constructors:
		element();
		element(T data_p);
	};


	template<typename T>
	inline element<T>::element() : m_tag("\0"), m_element_status(FFE::ELEMENT_STATUS::INVALID) {  }
	
	template<typename T>
	inline element<T>::element(T data_p) : m_data(data_p), m_tag("\0"), m_element_status(FFE::ELEMENT_STATUS::VALID) {  }
}

#endif
