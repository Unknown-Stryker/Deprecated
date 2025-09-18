#pragma warning (disable : 4244)
#pragma warning (disable : 26495)
#include "string.hpp"
#include <iostream>
#include <cstdlib>


#define LAST_CHAR this->m_string_length
#define STRING_MALLOC_SIZE this->m_string_length + 1u

fstd::uint8 ASCII_a = 97;
fstd::uint8 ASCII_z = 122;

fstd::uint8 ASCII_A = 65;
fstd::uint8 ASCII_Z = 90;

fstd::uint8 ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase = 32;


fstd::string::string(fstd::string&& move_p) noexcept
{
}

fstd::string& fstd::string::operator=(fstd::string&& move_p) noexcept
{
	return *this;
}

fstd::string::string() noexcept : m_string_ptr(new var::uchar[2] {"\0"}), m_string_length(), m_string_total_length(1), m_capacity(), m_capacity_divider(2), m_null('\0')
{
}

fstd::string::~string() noexcept
{
	if ( this->m_string_ptr == nullptr ) _UNLIKELY_ { return; }

	delete[] this->m_string_ptr;
}

fstd::string::string(var::uchar* move_str_ptr_p) noexcept : m_capacity(), m_capacity_divider(2), m_null('\0')
{
	if ( move_str_ptr_p == nullptr ) _UNLIKELY_ { return; }

	this->m_string_ptr = move_str_ptr_p;

	for ( ; this->m_string_ptr[this->m_string_length] != '\0'; ++this->m_string_length ) {}
	this->m_string_total_length = this->m_string_length;
}

fstd::string::string(const char* copy_cstr_ptr_p) noexcept : m_capacity(), m_string_length(), m_capacity_divider(2), m_null('\0')
{
	if ( copy_cstr_ptr_p == nullptr ) _UNLIKELY_ { return; }

	for ( ; copy_cstr_ptr_p[this->m_string_length] != '\0'; ++this->m_string_length ) {}

	this->m_string_ptr = new var::uchar[STRING_MALLOC_SIZE] {'\0'};

	memcpy(this->m_string_ptr, copy_cstr_ptr_p, STRING_MALLOC_SIZE);
}

fstd::string::string(const fstd::string& copy_other_ref_p) noexcept : m_null('\0')
{
	this->m_string_length = copy_other_ref_p.m_string_length;

	this->m_string_ptr = new var::uchar[STRING_MALLOC_SIZE] {'\0'};

	memcpy(this->m_string_ptr, copy_other_ref_p.m_string_ptr, STRING_MALLOC_SIZE);

	this->m_string_total_length = this->m_string_length;

	this->m_capacity = copy_other_ref_p.m_capacity;
	this->m_capacity_divider = copy_other_ref_p.m_capacity_divider;
}	

fstd::string& fstd::string::operator=(var::uchar* move_str_ptr_p) noexcept
{
	if ( move_str_ptr_p == nullptr ) _UNLIKELY_ { return *this; }

	var::uint32 l_str_ptr_len = 0;
	for ( ; move_str_ptr_p[l_str_ptr_len] != '\0'; ++l_str_ptr_len ) {}

	if ( l_str_ptr_len >= this->m_string_total_length )
	{
		this->m_capacity = l_str_ptr_len / this->m_capacity_divider;

		char* l_new_str = new char[l_str_ptr_len + this->m_capacity + 1] {'\0'};
	}

	this->m_string_total_length = this->m_string_length;

	return *this;
}

fstd::string& fstd::string::operator=(const char* str_ptr_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

fstd::string& fstd::string::operator=(const fstd::string& other_ref_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

fstd::var::uchar* fstd::string::begin() const noexcept
{
	return this->m_string_ptr;
}

fstd::var::uchar* fstd::string::end() const noexcept
{
	return &( this->m_string_ptr[LAST_CHAR] );
}

fstd::uint32 fstd::string::length() const noexcept
{
	return this->m_string_length;
}

fstd::uint32 fstd::string::total_length() const noexcept
{
	return this->m_string_total_length;
}

fstd::uint32 fstd::string::capacity() const noexcept
{
	return this->m_capacity;
}

void fstd::string::set_capacity_by_percent(uint32 percent_p)
{
	this->m_capacity_divider = 100 / percent_p;
	this->m_capacity = this->m_string_length / this->m_capacity_divider;
}

fstd::uint32 fstd::string::get_capacity_by_percent() const noexcept
{
	return this->m_capacity_divider / 100;
}

void fstd::string::reserve(fstd::uint32 length_p) noexcept
{
}

void fstd::string::resize(fstd::uint32 length_p) noexcept
{
}

void fstd::string::clear_all() noexcept
{
}

void fstd::string::erase(fstd::uint32 index_p) noexcept
{
}

fstd::boolean fstd::string::is_it_empty() const noexcept
{
	return false;
}

void fstd::string::shrink_to_fit() noexcept
{
}

fstd::uchar& fstd::string::operator[](uint32 index_p) noexcept
{
	if ( this->m_string_length < index_p ) _UNLIKELY_ { return this->m_null; }

	return this->m_string_ptr[index_p];
}

fstd::uchar fstd::string::front() const noexcept
{
	return this->m_string_ptr[0];
}

fstd::uchar fstd::string::back() const noexcept
{
	return this->m_string_ptr[LAST_CHAR - 1u];
}

fstd::uint32 fstd::string::operator+=(uchar char_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::string::operator+=(var::uchar* str_ptr_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::string::operator+=(const char* str_ptr_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::string::operator+=(const fstd::string& str_ref_p) noexcept
{
	return 0;  //index
}

void fstd::string::insert(fstd::uint32 index_p, var::uchar* str_ptr_p) noexcept
{
}

void fstd::string::insert(fstd::uint32 index_p, const fstd::string& str_ref_p) noexcept
{
}

fstd::uchar fstd::string::pop_back() noexcept
{
	var::uchar l_ret_val = this->m_string_ptr[LAST_CHAR];
	this->m_string_ptr[LAST_CHAR] = '\0';
	--this->m_string_length;
	return l_ret_val;
}

_NODISCARD fstd::var::uchar* fstd::string::copy_string() const noexcept
{
	var::uchar* l_str = new var::uchar[STRING_MALLOC_SIZE] {'\0'};
	memcpy(l_str, this->m_string_ptr, STRING_MALLOC_SIZE);

	return l_str;
}

_NODISCARD wchar_t* fstd::string::copy_wstring() const noexcept
{
	var::wchar* l_wstr = new var::wchar[STRING_MALLOC_SIZE] {L'\0'};
	memcpy(l_wstr, this->m_string_ptr, STRING_MALLOC_SIZE);

	return l_wstr;
}

void fstd::string::swap(const fstd::string& A_ref_p, const fstd::string& B_ref_p) noexcept
{
}

void fstd::string::print() const noexcept
{
	std::cout << this->m_string_ptr;
}

void fstd::string::println() const noexcept
{
	std::cout << this->m_string_ptr << std::endl;
}

_ENGLISH_ONLY_ void fstd::string::UPPERCASE() noexcept
{
	for (var::uint32 idx = 0; idx < this->m_string_length; ++idx )
	{
		if ( ASCII_a <= (uint8)this->m_string_ptr[idx] && (uint8)this->m_string_ptr[idx] <= ASCII_z )
		{
			this->m_string_ptr[idx] = (char)( (uint8)this->m_string_ptr[idx] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
		}
	}
}

_ENGLISH_ONLY_ void fstd::string::lowercase() noexcept
{
	for ( var::uint32 idx = 0; idx < this->m_string_length; ++idx )
	{
		if ( ASCII_A <= (uint8)this->m_string_ptr[idx] && (uint8)this->m_string_ptr[idx] <= ASCII_Z )
		{
			this->m_string_ptr[idx] = (char)( (uint8)this->m_string_ptr[idx] + ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
		}
	}
}

void fstd::string::delete_spaces() noexcept
{
}

_ENGLISH_ONLY_ void fstd::string::capitalize_all_the_first_letter_of_words() noexcept
{
	if ( this->m_string_ptr[0] != ' ' )
	{
		this->m_string_ptr[0] = (uint8)this->m_string_ptr[0] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
	}

	for ( var::uint64 idx = 0; idx < this->m_string_length; ++idx )
	{
		if ( this->m_string_ptr[idx] == ' ' && idx + 1 < this->m_string_length && this->m_string_ptr[idx + 1] != ' ' )
		{
			if ( ASCII_A <= this->m_string_ptr[idx + 1] && this->m_string_ptr[idx + 1] <= ASCII_Z
				|| ASCII_a <= this->m_string_ptr[idx + 1] && this->m_string_ptr[idx + 1] <= ASCII_z )
			{
				this->m_string_ptr[idx + 1] = (uint8)this->m_string_ptr[idx + 1] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
			}
		}
	}
}

void fstd::string::invert_string() noexcept
{
	var::uint64 l_start = 0;
	var::uint64 l_end = this->m_string_length;

	var::uchar l_temporary = '\0';
	while ( l_start < l_end )
	{
		l_temporary = this->m_string_ptr[l_start];
		this->m_string_ptr[l_start] = this->m_string_ptr[l_end - 1];
		this->m_string_ptr[l_end - 1] = l_temporary;

		++l_start;
		--l_end;
	}
}

_IN_DEVELOPMENT_ _NODISCARD fstd::string* fstd::string::extract_words_from_string() const noexcept
{
	return nullptr;
}

_NODISCARD fstd::var::uchar* fstd::string::extract_letters_from_string(uint32 A_p, uint32 Z_p) const noexcept
{
	return nullptr;
}

fstd::uint64 fstd::string::hash_code() noexcept
{
	var::uint64 l_hash_value = 0;

	var::uint64 l_multiplier = 0;
	for ( var::uchar c : *this )
	{
		++l_multiplier;
		for ( var::uint64 i = 0; i < l_multiplier; ++i )
		{
			l_hash_value += ( (uint64)c * (uint64)c );
		}
	}
	return l_hash_value;
}
