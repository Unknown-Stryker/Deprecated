#pragma once
#ifndef _TYPES_H_
#define _TYPES_H_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved

#include <string> // temporary header

#include <typeinfo>
#include "engine definitions.h"


#define NULL_f 0.0f
#define _UINT32_MAX_LENGTH_ 4294967295
#define _UINT64_MAX_LENGTH_ 18446744073709551615
#define _MINIMUM_RANGE_OF_ACCURATE_FLOAT_VALUE_ 0.000001

#define type(P) sizeof(P)

#define _BYTE_SIZE_ 1
#define _WORD_SIZE_ 2
#define _DWORD_SIZE_ 4
#define _QWORD_SIZE_ 8




BEGIN NAMESPACE(fstd)

// reflect code to get class name and auto generate typedef names here

typedef const bool boolean;

typedef const signed char schar;
typedef const unsigned char uchar;
typedef const wchar_t wchar;
typedef const char16_t char16;
typedef const char32_t char32;

typedef const float float32;
typedef const double float64;
typedef const long double float128;

typedef const signed char int8;
typedef const unsigned char uint8;
typedef const signed short int16;
typedef const unsigned short uint16;
typedef const signed int int32;
typedef const unsigned int uint32;
typedef const signed long long int64;
typedef const unsigned long long uint64;

typedef uint64 size_t;
typedef uint64 length_t;
typedef uint64 index_t;

	namespace var 
	{
		typedef bool boolean;

		typedef signed char schar;
		typedef unsigned char uchar;
		typedef wchar_t wchar;
		typedef char16_t char16;
		typedef char32_t char32;

		typedef float float32;
		typedef double float64;
		typedef long double float128;

		typedef signed char int8;
		typedef unsigned char uint8;
		typedef signed short int16;
		typedef unsigned short uint16;
		typedef signed int int32;
		typedef unsigned int uint32;
		typedef signed long long int64;
		typedef unsigned long long uint64;

		typedef uint64 size_t;
		typedef uint64 length_t;
		typedef uint64 index_t;

		typedef bool* BYTE_PTR;
		typedef unsigned short* WORD_PTR;
		typedef unsigned int* DWORD_PTR;
		typedef unsigned long long* QWORD_PTR;
	}

	//x64 cpu cache line is 64 byte
	uint64 one_mb = 1048576;
	uint64 one_gb = one_mb * 1024;

#define MB * one_mb
#define GB * one_gb


_FORCE_INLINE_ boolean Is_it_nearly_equal(float64 A_p, float64 B_p, var::float64 tolerance_p)
{
	if ( tolerance_p < _MINIMUM_RANGE_OF_ACCURATE_FLOAT_VALUE_ )
	{
		tolerance_p = _MINIMUM_RANGE_OF_ACCURATE_FLOAT_VALUE_;
	}
	if ( A_p + tolerance_p >= B_p && B_p >= A_p - tolerance_p )
	{
		return true;
	}
	return false;
}

_FORCE_INLINE_ boolean Is_it__ptr(const auto pointer) noexcept
{
	std::string l_memory = typeid( pointer ).name();
	uint64 l_len = l_memory.length();

	for ( var::uint64 char_idx = 0; char_idx < l_len; ++char_idx )
	{
		if ( char_idx + 2 < l_len && l_memory[char_idx] == 'p' && l_memory[char_idx + 1] == 't' && l_memory[char_idx + 2] == 'r' )
		{
			return true;
		}
	}

	return false;
}

_FORCE_INLINE_ boolean compare_data_types(const auto& typename_A_p, const auto& typename_B_p) noexcept
{
	if ( typeid( typename_A_p ).raw_name() == typeid( typename_B_p ).raw_name() )
	{
		return true;
	}
	else
	{
		if ( Is_it__ptr(typename_A_p) == true && Is_it__ptr(typename_B_p) == true )
		{
			return true;
		}

		return false;
	}
}

_FORCE_INLINE_ const uint64_t typename_hash_code(const std::string& typename_p) noexcept
{
	uint64_t l_hash_value = 0;

	uint32_t l_multiplier = 0;
	for ( char c : typename_p )
	{
		++l_multiplier;
		for ( uint32_t i = 0; i < l_multiplier; ++i )
		{
			l_hash_value += ( (var::uint64)c * (var::uint64)c );
		}
	}

	return l_hash_value;
}


END_FSTD


#endif