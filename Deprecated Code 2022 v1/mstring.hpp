#pragma once
#ifndef _M_STRING_HPP_
#define _M_STRING_HPP_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"
#include <string>


FROGMAN_FUNDAMENTAL_CLASS_LIBRARY
{
	frogman_fundamental_class mstring
	{
	private_member_variables:
		char* m_string;
		length m_length;

		char null;

	private_methods:
		void realloc(const char*& string_p);

	constructors:
		mstring();
		mstring(const char* string_p);
		mstring(char* string_p);
		mstring(const FFC::mstring& string_p);

	destructor:
		~mstring();

	public_operators:
		void operator=(const char* string_p);
		FFC::mstring& operator=(const FFC::mstring& string_archetype_p);
		char& operator[](index idx_p);

		mstring operator+(const char* right_string_p);
		mstring operator+(FFC::mstring& right_string_p);
		friend mstring operator+(const char* left_string_p, FFC::mstring& right_string_p)
		{
			FFC::mstring l_left_value = left_string_p;
			l_left_value += right_string_p;
			return l_left_value;
		}

		void operator+=(const char* right_string_p);
		void operator+=(char right_string_p);
		void operator+=(const FFC::mstring& right_string_p);
		
		bool operator==(const char* right_string_p);
		bool operator==(const FFC::mstring& right_string_p);
		friend bool operator==(const char* left_string_p, FFC::mstring& right_string_p)
		{
			if ( std::stoll(left_string_p) == std::stoll(right_string_p.primitive_string()) )
			{
				return true;
			}
			return false;
		}

		bool operator!=(const char* right_string_p);
		bool operator!=(const FFC::mstring& right_string_p);
		friend bool operator!=(const char* left_string_p, FFC::mstring& right_string_p)
		{
			if ( std::stoll(left_string_p) != std::stoll(right_string_p.primitive_string()) )
			{
				return true;
			}
			return false;
		}

		void operator<<(const u_int_64 move_left_p);
		void operator>>(const u_int_64 move_right_p);

	GETTERS:
		char* primitive_string() const;
		std::string std_string() const;
		hash GET_hash()  const;
		length GET_length() const;

	public_methods:
		void UPPERCASE();
		void lowercase();
		void delete_spaces();
		void capitalize_all_the_first_letters_of_words();
		void invert_string();
		FFC::mstring* extract_words_from_string()  const;
		char* extract_letters_from_string(const index A_p, const index Z_p)  const;
	};
};
#endif