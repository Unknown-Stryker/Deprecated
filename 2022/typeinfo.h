#pragma once
#ifndef _TYPEINFO_H_
#define _TYPEINFO_H_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"
#include "TYPE_COMPARISON_RESULT.h"
#include "mstring.hpp"
using FFC::mstring;


FROGMAN_FUNDAMENTAL_FUNCTION_LIBRARY
{
	bool Is_it__ptr(auto pointer);

	FFE::TYPE_COMPARISON_RESULT compare_data_types(auto typename_A_p, auto typename_B_p);

	mstring GET_type_name(auto data);

	hash GET_type_hash(auto data);
}
#endif