#ifndef _TYPES_H_
#define _TYPES_H_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee.
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include <string> // temporary header
#include <typeinfo>
#include "core.engine definitions.h"




BEGIN_NAMESPACE(FE)


#define NULL_f 0.0f

// reflect code to get class name and auto generate typedef names here

typedef const bool boolean; // primitive types are const by default
#define _BOOLEAN_HASH_CODE_ 117865

typedef const signed char schar; // primitive types are const by default
#define _SCHAR_HASH_CODE_ 646473

typedef const unsigned char uchar; // primitive types are const by default
#define _UCHAR_HASH_CODE_ 906774

typedef const wchar_t wchar; // primitive types are const by default
#define _WCHAR_HASH_CODE_ 317169


#if _HAS_CXX20 == 1
typedef const char8_t char8;
#endif


typedef const char16_t char16; // primitive types are const by default
#define _CHAR16_HASH_CODE_ 311968

typedef const char32_t char32; // primitive types are const by default
#define _CHAR32_HASH_CODE_ 310472

typedef const float float32; // primitive types are const by default
#define _FLOAT32_HASH_CODE_ 175611

typedef const double float64; // primitive types are const by default
#define _FLOAT64_HASH_CODE_ 233651

typedef const long double float128; // primitive types are const by default
#define _FLOAT128_HASH_CODE_ 691208

typedef const signed char sbyte; // primitive types are const by default
#define _SBYTE_HASH_CODE_ 646473

typedef const unsigned char ubyte; // primitive types are const by default
#define _UBYTE_HASH_CODE_ 906774

typedef const signed char int8; // primitive types are const by default
#define _INT8_HASH_CODE_ 646473

typedef const unsigned char uint8; // primitive types are const by default
#define _UINT8_HASH_CODE_ 906774

typedef const signed short int16; // primitive types are const by default
#define _INT16_HASH_CODE_ 191084

typedef const unsigned short uint16; // primitive types are const by default
#define _UINT16_HASH_CODE_ 1164342

typedef const signed int int32; // primitive types are const by default
#define _INT32_HASH_CODE_ 75593

typedef const unsigned int uint32; // primitive types are const by default
#define _UINT32_HASH_CODE_ 812754

typedef const signed long long int64; // primitive types are const by default
#define _INT64_HASH_CODE_ 212254

typedef const unsigned long long uint64; // primitive types are const by default
#define _UINT64_HASH_CODE_ 1162445

typedef uint64 size_t; // primitive types are const by default 
typedef uint64 length_t; // primitive types are const by default 
typedef uint64 index_t; // primitive types are const by default
typedef uint64 count_t; // primitive types are const by default
typedef void generic;
	

#if _HAS_CXX20 == 1
template <typename T>
concept integral_type = sizeof(T) <= 8;

template <typename T>
concept string_type = sizeof(T) <= 4;
#endif


	// variable types
	namespace var 
	{
		typedef bool boolean;

		typedef signed char schar;
		typedef unsigned char uchar;
		typedef wchar_t wchar;


#if _HAS_CXX20 == 1
		typedef char8_t char8;
#endif


		typedef char16_t char16;
		typedef char32_t char32;

		typedef float float32;
		typedef double float64;
		typedef long double float128;

		typedef signed char sbyte;
		typedef unsigned char ubyte;
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
		typedef uint64 count_t;

		typedef bool* BYTE_PTR;
#define _BYTE_PTR_HASH_CODE_ 799334

		typedef unsigned short* WORD_PTR;
#define _WORD_PTR_HASH_CODE_ 2510591

		typedef unsigned int* DWORD_PTR;
#define _DWORD_PTR_HASH_CODE_ 2026047

		typedef unsigned long long* QWORD_PTR;
#define _QWORD_PTR_HASH_CODE_ 2641650

	}
	
	_MAYBE_UNUSED_	constexpr FE::uint8 _UINT8_MAX_ = 255;
	_MAYBE_UNUSED_	constexpr FE::uint16 _UINT16_MAX_ = 65535;
	_MAYBE_UNUSED_	constexpr FE::uint32 _UINT32_MAX_ = 4294967295;
	_MAYBE_UNUSED_	constexpr FE::uint64 _UINT64_MAX_ = 18446744073709551615ull;

	_MAYBE_UNUSED_	constexpr FE::float64 _ACCURATE_VALUE_OF_MINIMUM_FLOAT_ = 1.0E-6;

// it checks whether a variable is a pointer or not regardless of data type
template <typename T>
_FORCE_INLINE_ boolean Is_it__ptr(const T* pointer) noexcept
{
	std::string l_memory = typeid( pointer ).name();
	uint64 l_len = l_memory.length();

	for ( var::uint64 char_idx = 0; char_idx < l_len; ++char_idx )
	{
		if ( char_idx + 2 < l_len 
			&& l_memory[char_idx] == 'p' 
			&& l_memory[char_idx + 1] == 't' 
			&& l_memory[char_idx + 2] == 'r' )
		{
			return true;
		}
	}

	return false;
}

// it checks whether a variable is a pointer or not regardless of data type
template <typename T, typename T1 = T>
_FORCE_INLINE_ boolean compare_data_types(const T& typename_A_p, const T1& typename_B_p) noexcept
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

// it returns hash code of data type name
_FORCE_INLINE_ uint64 typename_hash_code(const std::string& typename_p) noexcept
{
	var::uint64 l_hash_value = 0;

	var::uint32 l_multiplier = 0;
	for ( var::schar c : typename_p )
	{
		++l_multiplier;
		for ( var::uint32 i = 0; i < l_multiplier; ++i )
		{
			l_hash_value += ( (var::uint64)c * (var::uint64)c );
		}
	}

	return l_hash_value;
}


END_FE

#endif
#endif