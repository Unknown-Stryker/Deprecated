#pragma once
#ifndef _TYPE_COMPARISON_RESULT_H_
#define _TYPE_COMPARISON_RESULT_H_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"


FROGMAN_FUNDAMENTAL_ENUM_LIBRARY
{
	frogman_enum TYPE_COMPARISON_RESULT : bool
	{
		THE_SAME = true,
		DIFFERENT = false
	};
}

#endif // !_ELEMENT_STATUS_H_