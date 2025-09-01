#pragma once
#ifndef _STRING_H_
#define _STRING_H_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"


namespace memory
{
	class string
	{
		char* m_string;
		length m_length;

	public:
		string();
		string(const char* string_param);
		string(char* string_param);
		string(const memory::string& string_param);
		~string();

		void operator = (const char* string_param);
		memory::string& operator=(const memory::string& string_archetype_param);
		char operator [] (index idx)  const;

		string operator+(const char* string_param);
		string operator+(const memory::string& string_param);

		void operator+=(const char* string_param);
		void operator+=(char char_param);
		void operator+=(const memory::string& string_param);

		bool operator==(const char* string_param);
		bool operator==(const memory::string& string_param);

		bool operator!=(const char* string_param);
		bool operator!=(const memory::string& string_param);

		void operator<<(const u_int_64 move_left_param);
		void operator>>(const u_int_64 move_right_param);

		const char* get_string() const;
		hash get_hash()  const;
		length get_length() const;

		void UPPERCASE();
		void lowercase();

		void delete_spaces();
		void capitalize_all_the_first_letters_of_words();
		
		void invert_string();

		const char* get_letters_from_string(const index A, const index Z)  const;
		memory::string* extract_words_from_string()  const;

	private:
		void realloc(const char*& string_param);
	};
};
#endif