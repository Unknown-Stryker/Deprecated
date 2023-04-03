#include "typeinfo.h"
#include <typeinfo>


bool FFF::Is_it__ptr(auto pointer)
{
	mstring memory = typeid(pointer).name();
	length len = memory.GET_length();

	for (index char_idx = 0; char_idx < len; ++char_idx)
	{
		if (char_idx + 2 < len && memory[char_idx] == 'p' && memory[char_idx + 1] == 't' && memory[char_idx + 2] == 'r')
		{
			return true;
		}
	}

	return false;
}

FFE::TYPE_COMPARISON_RESULT FFF::compare_data_types(auto typename_A_p, auto typename_B_p)
{
	if (typeid(typename_A_p).name() == typeid(typename_B_p).name())
	{
		return FFE::TYPE_COMPARISON_RESULT::THE_SAME;
	}
	else {
		if (Is_it__ptr(typename_A_p) == Is_it__ptr(typename_B_p))
		{
			return FFE::TYPE_COMPARISON_RESULT::THE_SAME;
		}

		return FFE::TYPE_COMPARISON_RESULT::DIFFERENT;
	}
}

mstring FFF::GET_type_name(auto data)
{
	return typeid(data).name();
}

hash FFF::GET_type_hash(auto data)
{
	return typeid(data).hash_code();
}