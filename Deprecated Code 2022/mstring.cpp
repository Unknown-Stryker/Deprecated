#pragma once
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "mstring.hpp"
ASCII ASCII_a = 97;
ASCII ASCII_z = 122;

ASCII ASCII_A = 65;
ASCII ASCII_Z = 90;

ASCII ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase = 32;


FFC::mstring::mstring() : m_string(new char[2] {'\0'}), m_length(0), null('\0') {}

FFC::mstring::mstring(const char* string_p) : m_string(nullptr), m_length(0), null('\0')
{
	if (string_p == nullptr) { return; }
	for(this->m_length; string_p[this->m_length] != '\0'; ++this->m_length) {}
	this->m_string = new char[this->m_length+1] {'\0'};

	for (index idx = 0; string_p[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_p[idx];
	}
	this->m_string[this->m_length] = '\0';
}

FFC::mstring::mstring(char* string_p) : m_string(nullptr), m_length(0), null('\0')
{
	if (string_p == nullptr) { return; }
	this->m_string = string_p;

	for (this->m_length; this->m_string[this->m_length] != '\0'; ++this->m_length) {}
}

FFC::mstring::mstring(const FFC::mstring& string_p) : m_string(nullptr), m_length(0), null('\0')
{
	if (string_p.m_string == nullptr) { return; }
	for (this->m_length; string_p.m_string[this->m_length] != '\0'; ++this->m_length) {}
	this->m_string = new char[this->m_length + 1] {'\0'};

	for (index idx = 0; string_p.m_string[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_p.m_string[idx];
	}
	this->m_string[this->m_length] = '\0';
}

FFC::mstring::~mstring()
{
	if (this != nullptr && this->m_string != nullptr)
	{
		delete[] this->m_string;
		this->m_string = nullptr;
	}
}


void FFC::mstring::operator=(const char* right_string_p)
{
	if (right_string_p == nullptr) { return; }
	length l_prev_str_len = this->m_length;
	for (this->m_length = 0; right_string_p[this->m_length] != '\0'; ++this->m_length) {}
	
	if (this->m_length == l_prev_str_len)
	{
		for (index idx = 0; right_string_p[idx] != '\0'; ++idx)
		{
			this->m_string[idx] = right_string_p[idx];
		}

		this->m_string[this->m_length] = '\0';
		return;
	}
	this->realloc(right_string_p);
}

FFC::mstring& FFC::mstring::operator=(const FFC::mstring& string_archetype_p)
{
	if (this->m_length == string_archetype_p.m_length)
	{
		for (index idx = 0; idx < this->m_length; ++idx)
		{
			this->m_string[idx] = string_archetype_p.m_string[idx];
		}
		this->m_string[string_archetype_p.m_length] = '\0';

		return *this;
	}

	this->m_length = string_archetype_p.m_length;
	if (this->m_string != nullptr) { delete[] this->m_string; }
	this->m_string = new char[string_archetype_p.m_length + 1] {'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		this->m_string[idx] = string_archetype_p.m_string[idx];
	}
	this->m_string[string_archetype_p.m_length] = '\0';

	return *this;
}


char& FFC::mstring::operator[](index idx_p)
{
	if (this->m_string == nullptr) { return null; }
	if (idx_p < 0 || idx_p >= this->m_length) { return null; }

	return this->m_string[idx_p];
}


FFC::mstring FFC::mstring::operator+(const char* right_string_p)
{
	if (right_string_p == nullptr) { return mstring(); }
	length l_str_param_length = 0;
	for (; right_string_p[l_str_param_length] != '\0'; ++l_str_param_length) {}
	char* new_string = new char[this->m_length + l_str_param_length + 1]{'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_string[idx] = this->m_string[idx];
	}

	for (index l_left_idx = this->m_length, l_right_idx = 0; l_right_idx < l_str_param_length; ++l_left_idx, ++l_right_idx)
	{
		new_string[l_left_idx] = right_string_p[l_right_idx];
	}
	return new_string;
}

FFC::mstring FFC::mstring::operator+(FFC::mstring& right_string_p)
{	
	if (right_string_p.m_string == nullptr) { return mstring(); }
	char* l_new_string = new char[this->m_length + right_string_p.m_length + 1] {'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		l_new_string[idx] = this->m_string[idx];
	}

	for (index l_idx = this->m_length, r_idx = 0; r_idx < right_string_p.m_length; ++l_idx, ++r_idx)
	{
		l_new_string[l_idx] = right_string_p.m_string[r_idx];
	}
	return l_new_string;
}


void FFC::mstring::operator+=(const char* right_string_p)
{
	if (right_string_p == nullptr) { return; }
	length l_str_param_length = 0;
	for (; right_string_p[l_str_param_length] != '\0'; ++l_str_param_length) {}

	char* l_new_string = new char[this->m_length + l_str_param_length + 1] {'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		l_new_string[idx] = this->m_string[idx];
	}

	for (index l_idx = this->m_length, r_idx = 0; r_idx < l_str_param_length; ++l_idx, ++r_idx)
	{
		l_new_string[l_idx] = right_string_p[r_idx];
	}

	delete[] this->m_string;
	this->m_string = l_new_string;
}

void FFC::mstring::operator+=(char right_char_p)
{
	if (this->m_string == nullptr) { return; }
	if (right_char_p == '\0') { return; }

	char* l_new_string = new char[this->m_length + 1 + 1] {'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		l_new_string[idx] = this->m_string[idx];
	}

	l_new_string[this->m_length] = right_char_p;
	delete[] this->m_string;
	this->m_string = l_new_string;
}

void FFC::mstring::operator+=(const FFC::mstring& right_string_p)
{
	if (right_string_p.m_string == nullptr) { return; }
	char* l_new_string = new char[this->m_length + right_string_p.m_length + 1] {'\0'};

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		l_new_string[idx] = this->m_string[idx];
	}

	for (index l_left_idx = this->m_length, l_right_idx = 0; l_right_idx < right_string_p.m_length; ++l_left_idx, ++l_right_idx)
	{
		l_new_string[l_left_idx] = right_string_p.m_string[l_right_idx];
	}

	delete[] this->m_string;
	this->m_string = l_new_string;
}


bool FFC::mstring::operator==(const char* right_string_p)
{
	if (right_string_p == nullptr) { return false; }

	//
	{
		length l_str_len = 0;
		for ( ; right_string_p[l_str_len] != '\0'; ++l_str_len ) {}
		if ( l_str_len != this->m_length ) { return false; }
	}

	length l_match_count = 0;
	for ( index idx = 0; this->m_string[idx] != '\0'; ++idx )
	{
		if ( right_string_p[idx] == this->m_string[idx] )
		{
			++l_match_count;
		}
	}

	if ( l_match_count == this->m_length ) { return true; }
	return false;
}

bool FFC::mstring::operator==(const FFC::mstring& right_string_p)
{
	if ( right_string_p.m_string == nullptr ) { return false; }
	if ( right_string_p.m_length != this->m_length ) { return false; }

	length l_match_count = 0;
	for ( index idx = 0; this->m_string[idx] != '\0'; ++idx )
	{
		if ( right_string_p.m_string[idx] == this->m_string[idx] )
		{
			++l_match_count;
		}
	}

	if ( l_match_count == this->m_length ) { return true; }
	return false;
}

bool operator==(const char* left_string_p, FFC::mstring& right_string_p)
{
	if ( std::stoll(left_string_p) == std::stoll(right_string_p.primitive_string()) )
	{
		return true;
	}
	return false;
}


bool FFC::mstring::operator!=(const char* right_string_p)
{
	if (right_string_p == nullptr) { return true; }
	
	//
	{
		length l_str_len = 0;
		for ( ; right_string_p[l_str_len] != '\0'; ++l_str_len ) {}
		if ( l_str_len != this->m_length ) { return true; }
	}

	length l_match_count = 0;
	for ( index idx = 0; this->m_string[idx] != '\0'; ++idx )
	{
		if ( right_string_p[idx] == this->m_string[idx] )
		{
			++l_match_count;
		}
	}

	if ( l_match_count != this->m_length ) { return true; }
	return false;
}

bool FFC::mstring::operator!=(const FFC::mstring& right_string_p)
{
	if (right_string_p.m_string == nullptr) { return true; }
	
	//
	{
		length l_str_len = 0;
		for ( ; right_string_p.m_string[l_str_len] != '\0'; ++l_str_len ) {}
		if ( l_str_len != this->m_length ) { return true; }
	}

	length l_match_count = 0;
	for (index idx = 0; this->m_string[idx] != '\0'; ++idx)
	{
		if (right_string_p.m_string[idx] == this->m_string[idx])
		{
			++l_match_count;
		}
	}

	if (l_match_count != this->m_length) { return true; }
	return false;
}

bool operator!=(const char* left_string_p, FFC::mstring& right_string_p)
{
	if ( std::stoll(left_string_p) != std::stoll(right_string_p.primitive_string()) )
	{
		return true;
	}
	return false;
}


void FFC::mstring::operator<<(const u_int_64 move_left_p)
{
	if (this->m_string == nullptr) { return; }

	char* l_new_str = new char[this->m_length - move_left_p + 1] {'\0'};

	for (index l_idx = 0, r_idx = move_left_p; r_idx < this->m_length; ++l_idx, ++r_idx)
	{
		l_new_str[l_idx] = this->m_string[r_idx];
	}

	this->m_length -= move_left_p;
	delete[] this->m_string;
	this->m_string = l_new_str;
}

void FFC::mstring::operator>>(const u_int_64 move_right_p)
{
	if (this->m_string == nullptr) { return; }

	char* new_str = new char[this->m_length - move_right_p + 1] {'\0'};

	this->m_length -= move_right_p;

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		new_str[idx] = this->m_string[idx];
	}

	delete[] this->m_string;
	this->m_string = new_str;
}


char* FFC::mstring::primitive_string() const
{
	if (this->m_string == nullptr) { return nullptr; }

	return this->m_string;
}

std::string FFC::mstring::std_string() const
{
	if (this->m_string == nullptr) { return "\0"; }

	return std::string(this->m_string);
}

hash FFC::mstring::GET_hash()  const
{
	if (this->m_string == nullptr) { return 0; }

	hash* l_ASCII = new hash[this->m_length]{ 0 };

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		for (index exponent = idx + 1; exponent > 0; --exponent)
		{
			l_ASCII[idx] += ( (hash)this->m_string[idx] * (hash)this->m_string[idx] );
		}
	}

	hash l_sum = 0;
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		l_sum += l_ASCII[idx];
	}

	delete[] l_ASCII;
	return l_sum;
}

length FFC::mstring::GET_length() const
{
	return this->m_length;
}


void FFC::mstring::UPPERCASE()
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

void FFC::mstring::lowercase()
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


void FFC::mstring::delete_spaces()
{
	if (this->m_string == nullptr) { return; }

	length l_new_str_len = 0;
	for(index idx = 0; idx < this->m_length; ++idx) 
	{
		if (this->m_string[idx] != ' ')
		{
			++l_new_str_len;
		}
	}

	char* l_new_str = new char[l_new_str_len+1] {'\0'};


	index l_new_str_idx = 0;
	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (this->m_string[idx] != ' ')
		{
			l_new_str[l_new_str_idx] = this->m_string[idx];
			++l_new_str_idx;
		}
	}

	l_new_str[l_new_str_len] = '\0';
	delete[] this->m_string;
	this->m_string = l_new_str;
}

void FFC::mstring::capitalize_all_the_first_letters_of_words()
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

void FFC::mstring::invert_string()
{
	if (this->m_string == nullptr) { return; }

	index l_start = 0;
	index l_end = this->m_length;

	char l_temporary = '\0';
	while (l_start < l_end)
	{
		l_temporary = this->m_string[l_start];
		this->m_string[l_start] = this->m_string[l_end - 1];
		this->m_string[l_end - 1] = l_temporary;

		++l_start;
		--l_end;
	}

}

char* FFC::mstring::extract_letters_from_string(const index A_p, const index Z_p)  const
{
	if (this->m_string == nullptr) { return nullptr; }
	if (A_p >= Z_p) { return nullptr; }
	if (Z_p > this->m_length) { return nullptr; }

	char* l_new_str = new char[Z_p - A_p + 1] {'\0'};

	index l_idx = 0;
	for (index r_idx = A_p; r_idx < Z_p; ++l_idx, ++r_idx)
	{
		l_new_str[l_idx] = this->m_string[r_idx];
	}

	l_new_str[l_idx] = '\0';
	return l_new_str;
}

FFC::mstring* FFC::mstring::extract_words_from_string()  const
{
	if (this->m_string == nullptr) { return nullptr; }

	// count number of words
	index l_word_count = 0;
	if (this->m_string[0] != ' ')
	{
		++l_word_count;
	}

	for (index idx = 0; idx < this->m_length; ++idx)
	{
		if (this->m_string[idx] == ' ' && idx + 1 < this->m_length 
			&& this->m_string[idx + 1] != ' ' && this->m_string[idx + 1] != '\0')
		{
			++l_word_count;
		}
	}


	// count length of each word
	length* l_word_length = new length[l_word_count + 1] {0};
	for (index milestone = 0, idx = 0; idx < l_word_count; ++idx, ++milestone)
	{
		for (; this->m_string[milestone] != ' '; ++milestone)
		{
			if (this->m_string[milestone] == '\0') { goto ESCAPE_LOOP_0; }
			++l_word_length[idx];
		}
	}
ESCAPE_LOOP_0:


	FFC::mstring* l_words = new FFC::mstring[l_word_count]{("\0")};
	for (index progress = 0, idx = 0; idx < l_word_count; ++idx, ++progress)
	{
		char* word = new char[l_word_length[idx] + 1] {'\0'};
		for (index word_idx = 0; this->m_string[progress] != ' '; ++word_idx, ++progress)
		{
			if (this->m_string[progress] == '\0') { goto ESCAPE_LOOP_1; }
			word[word_idx] = this->m_string[progress];
		}
ESCAPE_LOOP_1:
		l_words[idx] = word;
	}

	delete[] l_word_length;
	return l_words;
}


void FFC::mstring::realloc(const char*& string_p)
{
	if (this->m_string != nullptr)
	{
		delete[] this->m_string;
		this->m_string = nullptr;
	}

	this->m_string = new char[this->m_length + 1];

	for (index idx = 0; string_p[idx] != '\0'; ++idx)
	{
		this->m_string[idx] = string_p[idx];
	}

	this->m_string[this->m_length] = '\0';
}
