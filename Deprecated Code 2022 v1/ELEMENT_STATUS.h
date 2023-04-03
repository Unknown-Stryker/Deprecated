#pragma once
#ifndef _ELEMENT_STATUS_H_
#define _ELEMENT_STATUS_H_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"


FROGMAN_FUNDAMENTAL_ENUM_LIBRARY
{
	frogman_enum ELEMENT_STATUS : bool
	{
		INVALID = false,
		VALID = true
	};
}

#endif // !_ELEMENT_STATUS_H_
