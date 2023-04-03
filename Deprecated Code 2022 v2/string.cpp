#pragma once
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "string.h"
#include <iostream>
typedef const unsigned int ASCII;

ASCII ASCII_a = 97;
ASCII ASCII_z = 122;
ASCII ASCII_A = 65;
ASCII ASCII_Z = 90;
ASCII ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase = 32;
ASCII _NULL_ = 0;


memory::string::string() : m_string(new char[2]{'\0'}), m_length(0)
{
}

memory::string::string(const char* string_param) : m_string(nullptr), m_length(0)
{
	if (string_param == nullptr) { return; }

	// measure length
	for(this->m_length; string_param[this->m_length] != '\0'; ++this->m_length) {}

	// alloc
	this->m_string = new char[this->m_length+1] {'\0'};

	// copy string
	for (index idx = 0; string_param[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_param[idx];
	}

	// end string
	this->m_string[this->m_length] = '\0';
}

memory::string::string(char* string_param) : m_string(nullptr), m_length(0)
{
	if (string_param == nullptr) { return; }

	this->m_string = string_param;

	// measure length
	for (this->m_length; this->m_string[this->m_length] != '\0'; ++this->m_length) {}
}

memory::string::string(const memory::string& string_param) : m_string(nullptr), m_length(0)
{
	if (string_param.m_string == nullptr) { return; }

	// measure length
	for (this->m_length; string_param.m_string[this->m_length] != '\0'; ++this->m_length) {}

	// alloc
	this->m_string = new char[this->m_length + 1] {'\0'};

	// copy string
	for (index idx = 0; string_param.m_string[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_param.m_string[idx];
	}

	// end string
	this->m_string[this->m_length] = '\0';
}

memory::string::~string()
{
	if (this != nullptr && this->m_string != nullptr)
	{
		delete[] this->m_string;
	}
}


void memory::string::operator=(const char* string_param)
{
	if (string_param == nullptr) { return; }

	length prev_str_len = this->m_length;

	// measure length
	for (this->m_length = 0; string_param[this->m_length] != '\0'; ++this->m_length) {}
	
	if (this->m_length == prev_str_len)
	{
		// copy string
		for (index idx = 0; string_param[idx] != '\0'; ++idx)
		{
			this->m_string[idx] = string_param[idx];
		}

		// end string
		this->m_string[this->m_length] = '\0';
		
		return;
	}

	this->realloc(string_param);
}

memory::string& memory::string::operator=(const memory::string& string_archetype_param)
{
	if (this->m_length == string_archetype_param.m_length)
	{
		// copy string
		for (index idx = 0; idx < this->m_length; ++idx)
		{
			this->m_string[idx] = string_archetype_param.m_string[idx];
		}

		this->m_string[string_archetype_param.m_length] = '\0';

		return *this;
	}




	this->m_length = string_archetype_param.m_length;

	if (this->m_string != nullptr) { delete[] this->m_string; }

	this->m_string = new char[string_archetype_param.m_length + 1] {'\0'};

	// copy string
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		this->m_string[idx] = string_archetype_param.m_string[idx];
	}

	this->m_string[string_archetype_param.m_length] = '\0';

	return *this;
}


char memory::string::operator[](index idx) const
{
	if (this->m_string == nullptr) { return '\0'; }
	if (idx < 0 || this->m_length >= idx) { return '\0'; }

	return this->m_string[idx];
}


memory::string memory::string::operator+(const char* string_param)
{
	if (string_param == nullptr) { return string(); }

	// measure length
	length string_param_length = 0;
	for (; string_param[string_param_length] != '\0'; ++string_param_length) {}

	// alloc new 
	char* new_string = new char[this->m_length + string_param_length + 1]{'\0'};

	// move prev
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	// register_stock new
	for (index l_idx = this->m_length, r_idx = 0; r_idx < string_param_length; ++l_idx, ++r_idx)
	{
		new_string[l_idx] = string_param[r_idx];
	}

	return new_string;
}

memory::string memory::string::operator+(const memory::string& string_param)
{	
	if (string_param.m_string == nullptr) { return string(); }

	// alloc new 
	char* new_string = new char[this->m_length + string_param.m_length + 1] {'\0'};

	// move prev
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	// register_stock new
	for (index l_idx = this->m_length, r_idx = 0; r_idx < string_param.m_length; ++l_idx, ++r_idx)
	{
		new_string[l_idx] = string_param.m_string[r_idx];
	}

	return new_string;
}


void memory::string::operator+=(const char* string_param)
{
	if (string_param == nullptr) { return; }

	// measure length
	length string_param_length = 0;
	for (; string_param[string_param_length] != '\0'; ++string_param_length) {}

	// alloc new 
	char* new_string = new char[this->m_length + string_param_length + 1] {'\0'};

	// move prev
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	// register_stock new
	for (index l_idx = this->m_length, r_idx = 0; r_idx < string_param_length; ++l_idx, ++r_idx)
	{
		new_string[l_idx] = string_param[r_idx];
	}

	delete[] this->m_string;

	this->m_string = new_string;
}

void memory::string::operator+=(char char_param)
{
	if (this->m_string == nullptr) { return; }
	if (char_param == '\0') { return; }

	// alloc new 
	char* new_string = new char[this->m_length + 1 + 1] {'\0'};

	// move prev
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	// register_stock new
	new_string[this->m_length] = char_param;

	delete[] this->m_string;

	this->m_string = new_string;
}

void memory::string::operator+=(const memory::string& string_param)
{
	if (string_param.m_string == nullptr) { return; }

	// alloc new 
	char* new_string = new char[this->m_length + string_param.m_length + 1] {'\0'};

	// move prev
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	// register_stock new
	for (index l_idx = this->m_length, r_idx = 0; r_idx < string_param.m_length; ++l_idx, ++r_idx)
	{
		new_string[l_idx] = string_param.m_string[r_idx];
	}

	delete[] this->m_string;

	this->m_string = new_string;
}


bool memory::string::operator==(const char* string_param)
{
	if (string_param == nullptr) { return false; }

	{
		length str_len = 0;
		for (; string_param[str_len] != '\0'; ++str_len) {}

		if (str_len != this->m_length)
		{
			return false;
		}
	}


	{
		length match_count = 0;
		for (index idx = 0; this->m_string[idx] != '\0'; ++idx)
		{
			if (string_param[idx] == this->m_string[idx])
			{
				++match_count;
			}
		}

		if (match_count == this->m_length)
		{
			return true;
		}
	}

	return false;
}

bool memory::string::operator==(const memory::string& string_param)
{
	if (string_param.m_string == nullptr) { return false; }

	{
		length str_len = 0;
		for (; string_param[str_len] != '\0'; ++str_len) {}

		if (str_len != this->m_length)
		{
			return false;
		}
	}


	{
		length match_count = 0;
		for (index idx = 0; this->m_string[idx] != '\0'; ++idx)
		{
			if (string_param.m_string[idx] == this->m_string[idx])
			{
				++match_count;
			}
		}

		if (match_count == this->m_length)
		{
			return false;
		}
	}

	return true;
}


bool memory::string::operator!=(const char* string_param)
{
	if (string_param == nullptr) { return true; }

	{
		length str_len = 0;
		for (; string_param[str_len] != '\0'; ++str_len) {}

		if (str_len != this->m_length)
		{
			return true;
		}
	}
	

	{
		length match_count = 0;
		for (index idx = 0; this->m_string[idx] != '\0'; ++idx)
		{
			if (string_param[idx] == this->m_string[idx])
			{
				++match_count;
			}
		}

		if (match_count != this->m_length)
		{
			return true;
		}
	}

	return false;
}

bool memory::string::operator!=(const memory::string& string_param)
{
	if (string_param.m_string == nullptr) { return true; }

	{
		length str_len = 0;
		for (; string_param.m_string[str_len] != '\0'; ++str_len) {}

		if (str_len != this->m_length)
		{
			return true;
		}
	}


	length match_count = 0;
	for (index idx = 0; this->m_string[idx] != '\0'; ++idx)
	{
		if (string_param.m_string[idx] == this->m_string[idx])
		{
			++match_count;
		}
	}

	if (match_count != this->m_length)
	{
		return true;
	}

	return false;
}


void memory::string::operator<<(const u_int_64 move_left_param)
{
	if (this->m_string == nullptr) { return; }

	char* new_str = new char[this->m_length - move_left_param + 1] {'\0'};


	for (index l_idx = 0, r_idx = move_left_param; r_idx < this->m_length; ++l_idx, ++r_idx)
	{
		new_str[l_idx] = this->m_string[r_idx];
	}

	this->m_length -= move_left_param;

	delete[] this->m_string;

	this->m_string = new_str;
}

void memory::string::operator>>(const u_int_64 move_right_param)
{
	if (this->m_string == nullptr) { return; }

	char* new_str = new char[this->m_length - move_right_param + 1] {'\0'};

	this->m_length -= move_right_param;

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_str[idx] = this->m_string[idx];
	}

	delete[] this->m_string;

	this->m_string = new_str;
}


const char* memory::string::get_string() const
{
	if (this->m_string == nullptr) { return "\0"; }

	return (const char*)this->m_string;
}

hash memory::string::get_hash()  const
{
	if (this->m_string == nullptr) { return 0; }

	hash* ASCII = new hash[this->m_length]{ 0 };

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		for (index exponent = idx + 1; exponent > 0; --exponent)
		{
			ASCII[idx] += ( (hash)this->m_string[idx] * (hash)this->m_string[idx] );
		}
	}

	hash sum = 0;
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		sum += ASCII[idx];
	}

	delete[] ASCII;

	return sum;
}

length memory::string::get_length() const
{
	return this->m_length;
}


void memory::string::UPPERCASE()
{
	if (this->m_string == nullptr) { return; }

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (ASCII_a <= (unsigned int)this->m_string[idx] && (unsigned int)this->m_string[idx] <= ASCII_z)
		{
			this->m_string[idx] = (char)((unsigned int)this->m_string[idx] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase);
		}
	}
}

void memory::string::lowercase()
{
	if (this->m_string == nullptr) { return; }

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (ASCII_A <= (unsigned int)this->m_string[idx] && (unsigned int)this->m_string[idx] <= ASCII_Z)
		{
			this->m_string[idx] = (char)((unsigned int)this->m_string[idx] + ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase);
		}
	}
}


void memory::string::delete_spaces()
{
	if (this->m_string == nullptr) { return; }

	length new_str_len = 0;
	for(index idx = 0; idx < this->m_length; ++idx) 
	{
		if (this->m_string[idx] != ' ')
		{
			++new_str_len;
		}
	}

	char* new_str = new char[new_str_len+1] {'\0'};


	index new_str_idx = 0;
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (this->m_string[idx] != ' ')
		{
			new_str[new_str_idx] = this->m_string[idx];
			++new_str_idx;
		}
	}

	new_str[new_str_len] = '\0';

	delete[] this->m_string;

	this->m_string = new_str;
}

void memory::string::capitalize_all_the_first_letters_of_words()
{
	if (this->m_string == nullptr) { return; }
	
	if (this->m_string[0] != ' ')
	{
		this->m_string[0] = (ASCII)this->m_string[0] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
	}

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (this->m_string[idx] == ' ' && idx + 1 < this->m_length && this->m_string[idx + 1] != ' ')
		{
			if (ASCII_A <= this->m_string[idx + 1] && this->m_string[idx+1] <= ASCII_Z 
				|| ASCII_a <= this->m_string[idx + 1] && this->m_string[idx + 1] <= ASCII_z)
			{
				this->m_string[idx + 1] = (ASCII)this->m_string[idx + 1] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
			}
		}
	}
}

void memory::string::invert_string()
{
	if (this->m_string == nullptr) { return; }

	index start = 0;
	index end = this->m_length;

	char temporary = '\0';
	while (start < end)
	{
		temporary = this->m_string[start];
		this->m_string[start] = this->m_string[end - 1];
		this->m_string[end - 1] = temporary;

		++start;
		--end;
	}

}

const char* memory::string::get_letters_from_string(const index A, const index Z)  const
{
	if (this->m_string == nullptr) { return "\0"; }
	if (A >= Z) { return "\0"; }
	if (Z > this->m_length) { return "\0" ; }

	char* new_str = new char[Z - A + 1] {'\0'};

	index l_idx = 0;
	for (index r_idx = A; r_idx < Z; ++l_idx, ++r_idx)
	{
		new_str[l_idx] = this->m_string[r_idx];
	}

	new_str[l_idx] = '\0';

	return new_str;
}

memory::string* memory::string::extract_words_from_string()  const
{
	if (this->m_string == nullptr) { return nullptr; }

	// count number of words
	index word_count = 0;
	if (this->m_string[0] != ' ')
	{
		++word_count;
	}

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (this->m_string[idx] == ' ' && idx + 1 < this->m_length 
			&& this->m_string[idx + 1] != ' ' && this->m_string[idx + 1] != '\0')
		{
			++word_count;
		}
	}


	// count length of each word
	length* word_length = new length[word_count + 1] {0};
	for (index milestone = 0, idx = 0; idx < word_count; ++idx, ++milestone)
	{
		for (; this->m_string[milestone] != ' '; ++milestone)
		{
			if (this->m_string[milestone] == '\0') { goto BREAK_0; }
			++word_length[idx];
		}
	}
BREAK_0:


	memory::string* words = new memory::string[word_count]{("\0")};
	for (index progress = 0, idx = 0; idx < word_count; ++idx, ++progress)
	{
		char* word = new char[word_length[idx] + 1] {'\0'};
		for (index word_idx = 0; this->m_string[progress] != ' '; ++word_idx, ++progress)
		{
			if (this->m_string[progress] == '\0') { goto BREAK_1; }
			word[word_idx] = this->m_string[progress];
		}
BREAK_1:
		words[idx] = word;
	}

	delete[] word_length;

	return words;
}


void memory::string::realloc(const char*& string_param)
{
	if (this->m_string != nullptr)
	{
		delete[] this->m_string;
		this->m_string = nullptr;
	}

	// alloc
	this->m_string = new char[this->m_length + 1];

	// copy string
	for (index idx = 0; string_param[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_param[idx];
	}

	// end string
	this->m_string[this->m_length] = '\0';
}