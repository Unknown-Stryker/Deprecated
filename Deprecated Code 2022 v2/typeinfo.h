#pragma once
#ifndef _TYPEINFO_H_
#define _TYPEINFO_H_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include <typeinfo>
#include "common_definitions.h"
#include "string.h"
using memory::string;


namespace typeinfo
{
	enum class TYPE_COMPARISON_RESULT : bool
	{
		THE_SAME = true,
		DIFFERENT = false
	};

	bool Is_it__ptr(auto pointer)
	{
		string memory = typeid(pointer).name();
		length len = memory.get_length();

		for (index char_idx = 0; char_idx < len; ++char_idx)
		{
			if (char_idx+2 < len && memory[char_idx] == 'p' && memory[char_idx+1] == 't' && memory[char_idx + 2] == 'r')
			{
				return true;
			}
		}
		
		return false;
	}

	TYPE_COMPARISON_RESULT compare_data_types(auto ASCII_a, auto b)
	{
		if (typeid(ASCII_a).name() == typeid(b).name())
		{
			return TYPE_COMPARISON_RESULT::THE_SAME;
		}
		else
		{	
			if ( Is_it__ptr(ASCII_a) == Is_it__ptr(b) )
			{
				return TYPE_COMPARISON_RESULT::THE_SAME;
			}

			return TYPE_COMPARISON_RESULT::DIFFERENT;
		}
	}

	string GET_type_name(auto data)
	{
		return typeid(data).name();
	}

	hash GET_type_hash(auto data)
	{
		return typeid(data).hash_code();
	}
}
#endif