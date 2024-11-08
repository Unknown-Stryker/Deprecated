#ifndef _FE_CORE_ALGORITHM_NUMERIC_HXX_
#define _FE_CORE_ALGORITHM_NUMERIC_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../prerequisite_symbols.h"


BEGIN_NAMESPACE(FE::numeric)


template<typename N>
_FORCE_INLINE_ _NODISCARD_ var::uint8 count_integral_digit_length(N value_p) noexcept
{
	static_assert(std::is_integral<N>::value == true || std::is_floating_point<N>::value == true, "the type of the template parameter N is not numeric");

	var::int8 l_length_of_n = 0;
	if (value_p < 0)
	{
		for (; value_p <= static_cast<N>(-10); value_p /= static_cast<N>(10)) { ++l_length_of_n; }
		return l_length_of_n;
	}

	for (; value_p >= static_cast<N>(10); value_p /= static_cast<N>(10)) { ++l_length_of_n; }
	return l_length_of_n;
}

template<typename N>
_NODISCARD_ constexpr var::uint8 constexpr_count_integral_digit_length(N value_p) noexcept
{
	static_assert(std::is_integral<N>::value == true || std::is_floating_point<N>::value == true, "the type of the template parameter N is not numeric");

	var::int8 l_length_of_n = 0;
	if (value_p < 0)
	{
		for (; value_p <= static_cast<N>(-10); value_p /= static_cast<N>(10)) { ++l_length_of_n; }
		return l_length_of_n;
	}

	for (; value_p >= static_cast<N>(10); value_p /= static_cast<N>(10)) { ++l_length_of_n; }
	return l_length_of_n;
}

template<typename integral_type, typename char_type>
void convert_integer_to_string(char_type* const string_in_out_ptrc_p, integral_type value_p) noexcept
{
	static_assert(std::is_integral<integral_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");

	var::int8 l_integral_digits = numeric::count_integral_digit_length<integral_type>(value_p);
	var::boolean l_is_negative = false;

	if (value_p < 0)
	{
		l_is_negative = true;
		value_p = -value_p;
		++l_integral_digits;
	}

	var::int8 l_idx = l_integral_digits - 1;
	while (value_p > 0)
	{
		string_in_out_ptrc_p[l_idx] = 48 + (value_p % 10);
		value_p /= 10;
		--l_idx;
	}


	if (l_is_negative) { *string_in_out_ptrc_p = static_cast<char_type>('-'); }

	string_in_out_ptrc_p[l_integral_digits] = static_cast<char_type>('\0');
}

template<typename integral_type, typename char_type>
constexpr void constexpr_convert_integer_to_string(char_type* const string_in_out_ptrc_p, integral_type value_p) noexcept
{
	static_assert(std::is_integral<integral_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");

	var::int8 l_integral_digits = numeric::count_integral_digit_length<integral_type>(value_p);
	var::boolean l_is_negative = false;

	if (value_p < 0)
	{
		l_is_negative = true;
		value_p = -value_p;
		++l_integral_digits;
	}

	var::int8 l_idx = l_integral_digits - 1;
	while (value_p > 0)
	{
		string_in_out_ptrc_p[l_idx] = 48 + (value_p % 10);
		value_p /= 10;
		--l_idx;
	}


	if (l_is_negative) { *string_in_out_ptrc_p = static_cast<char_type>('-'); }

	string_in_out_ptrc_p[l_integral_digits] = static_cast<char_type>('\0');
}


template<typename float_type, typename char_type>
void convert_float_to_string(char_type* string_in_out_ptr_p, float_type value_p) noexcept
{
	static_assert(std::is_floating_point<float_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");


}

template<typename float_type, typename char_type>
constexpr void constexpr_convert_float_to_string(char_type* string_in_out_ptr_p, float_type value_p) noexcept
{
	static_assert(std::is_floating_point<float_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");


}

template<typename char_type>
_FORCE_INLINE_ const char* convert_boolean_to_string(boolean value_p) noexcept
{
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");

	return (value_p == true) ? "true" : "false";
}

template<typename char_type>
constexpr const char* constexpr_convert_boolean_to_string(boolean value_p) noexcept
{
	static_assert(sizeof(char_type) <= sizeof(char32), "an illegal type of value_p assigned to the template argument char_type");

	return (value_p == true) ? "true" : "false";
}

END_NAMESPACE
#endif