#include "wstring.hpp"
#include <iostream>
#include <cstdlib>
#pragma warning (disable : 26495)
#define LAST_WCHAR this->m_wstring_length
#define WSTRING_MALLOC_SIZE this->m_wstring_length + 1u

fstd::uint8 ASCII_a = 97;
fstd::uint8 ASCII_z = 122;

fstd::uint8 ASCII_A = 65;
fstd::uint8 ASCII_Z = 90;

fstd::uint8 ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase = 32;


fstd::wstring::wstring(fstd::wstring&& move_p) noexcept
{
}

fstd::wstring& fstd::wstring::operator=(fstd::wstring&& move_p) noexcept
{
	return *this;
}

fstd::wstring::wstring() noexcept : m_wstring_ptr(new wchar_t[2]{L'\0'}), m_wstring_length(), m_wstring_total_length(1), m_capacity(), m_capacity_divider(2), m_null(L'\0')
{
}

fstd::wstring::~wstring() noexcept
{
	if ( this->m_wstring_ptr == nullptr ) _UNLIKELY_ { return; }

	delete[] this->m_wstring_ptr;
}

fstd::wstring::wstring(var::wchar* move_wstr_ptr_p) noexcept : m_capacity(), m_capacity_divider(2), m_null(L'\0')
{
	if ( move_wstr_ptr_p == nullptr ) _UNLIKELY_ { return; }

	this->m_wstring_ptr = move_wstr_ptr_p;

	for ( ; this->m_wstring_ptr[this->m_wstring_length] != L'\0'; ++this->m_wstring_length ) {}
	this->m_wstring_total_length = this->m_wstring_length;
}

fstd::wstring::wstring(wchar* copy_cwstr_ptr_p) noexcept : m_capacity(), m_wstring_length(), m_capacity_divider(2), m_null(L'\0')
{
	if ( copy_cwstr_ptr_p == nullptr ) _UNLIKELY_ { return; }

	for ( ; copy_cwstr_ptr_p[this->m_wstring_length] != L'\0'; ++this->m_wstring_length ) {}

	this->m_wstring_ptr = new var::wchar[WSTRING_MALLOC_SIZE] {L'\0'};

	wmemcpy(this->m_wstring_ptr, copy_cwstr_ptr_p, WSTRING_MALLOC_SIZE);
}

fstd::wstring::wstring(const fstd::wstring& move_other_ref_p) noexcept : m_null(L'\0')
{
	this->m_wstring_length = move_other_ref_p.m_wstring_length;

	this->m_wstring_ptr = new var::wchar[WSTRING_MALLOC_SIZE] {L'\0'};

	wmemcpy(this->m_wstring_ptr, move_other_ref_p.m_wstring_ptr, WSTRING_MALLOC_SIZE);

	this->m_wstring_total_length = this->m_wstring_length;

	this->m_capacity = move_other_ref_p.m_capacity;
	this->m_capacity_divider = move_other_ref_p.m_capacity_divider;
}

fstd::wstring& fstd::wstring::operator=(var::wchar* wstr_ptr_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

fstd::wstring& fstd::wstring::operator=(wchar* wstr_ptr_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

fstd::wstring& fstd::wstring::operator=(const fstd::wstring& other_ref_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

fstd::wchar* fstd::wstring::begin() const noexcept
{
	return this->m_wstring_ptr;
}

fstd::wchar* fstd::wstring::end() const noexcept
{
	return &( this->m_wstring_ptr[LAST_WCHAR] );
}

fstd::uint32 fstd::wstring::length() const noexcept
{
	return this->m_wstring_length;
}

fstd::uint32 fstd::wstring::total_length() const noexcept
{
	return this->m_wstring_total_length;
}

fstd::uint32 fstd::wstring::capacity() const noexcept
{
	return this->m_capacity;
}

void fstd::wstring::set_capacity_by_percent(uint32 percent_p) noexcept
{
	this->m_capacity_divider = 100 / percent_p;
	this->m_capacity = this->m_wstring_length / this->m_capacity_divider;
}

fstd::uint32 fstd::wstring::get_capacity_by_percent() const noexcept
{
	return this->m_capacity_divider / 100;
}

void fstd::wstring::reserve(uint32 length_p) noexcept
{
}

void fstd::wstring::resize(uint32 length_p) noexcept
{
}

void fstd::wstring::clear_all() noexcept
{
}

void fstd::wstring::erase(uint32 index_p) noexcept
{
}

fstd::boolean fstd::wstring::is_it_empty() const noexcept
{
	return false;
}

void fstd::wstring::shrink_to_fit() noexcept
{
}

fstd::var::wchar& fstd::wstring::operator[](uint32 index_p) noexcept
{
	if ( this->m_wstring_length < index_p ) _UNLIKELY_ { return this->m_null; }
	
	return this->m_wstring_ptr[index_p];
}

fstd::wchar fstd::wstring::front() const noexcept
{
	return this->m_wstring_ptr[0];
}

fstd::wchar fstd::wstring::back() const noexcept
{
	return this->m_wstring_ptr[LAST_WCHAR - 1u];
}

fstd::uint32 fstd::wstring::operator+=(var::wchar wchar_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::wstring::operator+=(var::wchar* str_ptr_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::wstring::operator+=(wchar* str_ptr_p) noexcept
{
	return 0;  //index
}

fstd::uint32 fstd::wstring::operator+=(const fstd::wstring& str_ref_p) noexcept
{
	return 0;  //index
}

void fstd::wstring::insert(uint32 index_p, var::wchar* wstr_ptr_p) noexcept
{
}

void fstd::wstring::insert(uint32 index_p, wchar* wstr_ptr_p) noexcept
{
}

void fstd::wstring::insert(uint32 index_p, const fstd::wstring& str_ref_p) noexcept
{
}

fstd::wchar fstd::wstring::pop_back() noexcept
{
	var::wchar l_ret_val = this->m_wstring_ptr[LAST_WCHAR];
	this->m_wstring_ptr[LAST_WCHAR] = L'\0';
	--this->m_wstring_length;
	return l_ret_val;
}


_NODISCARD_ fstd::var::uchar* fstd::wstring::copy_string() const noexcept
{
	var::uchar* l_str = new var::uchar[WSTRING_MALLOC_SIZE] {'\0'};
	memcpy(l_str, this->m_wstring_ptr, WSTRING_MALLOC_SIZE);

	return l_str;
}

_NODISCARD_ fstd::wchar* fstd::wstring::copy_wstring() const noexcept
{
	var::wchar* l_wstr = new var::wchar[WSTRING_MALLOC_SIZE] {L'\0'};
	wmemcpy(l_wstr, this->m_wstring_ptr, WSTRING_MALLOC_SIZE);

	return l_wstr;
}

void fstd::wstring::swap(fstd::wstring& A_ref_p, fstd::wstring& B_ref_p) noexcept
{
}

void fstd::wstring::print() const noexcept
{
	std::wcout << this->m_wstring_ptr;
}

void fstd::wstring::println() const noexcept
{
	std::wcout << this->m_wstring_ptr << std::endl;
}

_ENGLISH_ONLY_ void fstd::wstring::UPPERCASE() noexcept
{
	for ( var::uint32 idx = 0; idx < this->m_wstring_length; ++idx )
	{
		if ( ASCII_a <= (uint8)this->m_wstring_ptr[idx] && (uint8)this->m_wstring_ptr[idx] <= ASCII_z )
		{
			this->m_wstring_ptr[idx] = (wchar)( (uint8)this->m_wstring_ptr[idx] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
		}
	}
}

_ENGLISH_ONLY_ void fstd::wstring::lowercase() noexcept
{
	for ( var::uint32 idx = 0; idx < this->m_wstring_length; ++idx )
	{
		if ( ASCII_A <= (uint8)this->m_wstring_ptr[idx] && (uint8)this->m_wstring_ptr[idx] <= ASCII_Z )
		{
			this->m_wstring_ptr[idx] = (wchar)( (uint8)this->m_wstring_ptr[idx] + ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
		}
	}
}

void fstd::wstring::delete_spaces() noexcept
{

}

_ENGLISH_ONLY_ void fstd::wstring::capitalize_all_the_first_letter_of_words() noexcept
{
	if ( this->m_wstring_ptr[0] != L' ' )
	{
		this->m_wstring_ptr[0] = (uint8)this->m_wstring_ptr[0] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
	}

	for ( var::uint32 idx = 0; idx < this->m_wstring_length; ++idx )
	{
		if ( this->m_wstring_ptr[idx] == L' ' && idx + 1 < this->m_wstring_length && this->m_wstring_ptr[idx + 1] != L' ' )
		{
			if ( ASCII_A <= this->m_wstring_ptr[idx + 1] && this->m_wstring_ptr[idx + 1] <= ASCII_Z
				|| ASCII_a <= this->m_wstring_ptr[idx + 1] && this->m_wstring_ptr[idx + 1] <= ASCII_z )
			{
				this->m_wstring_ptr[idx + 1] = (uint8)this->m_wstring_ptr[idx + 1] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase;
			}
		}
	}
}

void fstd::wstring::invert_string() noexcept
{
	var::uint32 l_start = 0;
	var::uint32 l_end = this->m_wstring_length;

	var::wchar l_temporary = L'\0';
	while ( l_start < l_end )
	{
		l_temporary = this->m_wstring_ptr[l_start];
		this->m_wstring_ptr[l_start] = this->m_wstring_ptr[l_end - 1];
		this->m_wstring_ptr[l_end - 1] = l_temporary;

		++l_start;
		--l_end;
	}
}

_NODISCARD_ fstd::wstring* fstd::wstring::extract_words_from_string() const noexcept
{
	return nullptr;
}

_NODISCARD_ wchar_t* fstd::wstring::extract_letters_from_string(const uint32_t A_p, const uint32_t Z_p) const noexcept
{
	if ( A_p >= Z_p ) _UNLIKELY_ { return nullptr; }
	if ( Z_p > this->m_wstring_length ) _UNLIKELY_{ return nullptr; }

	var::wchar* l_ret = new var::wchar[Z_p - A_p + 1] {L'\0'};

	var::uint32 l_idx = 0;
	for ( var::uint32 r_idx = A_p; r_idx <= Z_p; ++l_idx, ++r_idx )
	{
		l_ret[l_idx] = this->m_wstring_ptr[r_idx];
	}

	l_ret[l_idx] = L'\0';
	return l_ret;
}

fstd::uint64 fstd::wstring::hash_code() noexcept
{
	var::uint64 l_hash_value = 0;

	var::uint64 l_multiplier = 0;
	for ( var::wchar wchar : *this )
	{
		++l_multiplier;
		for ( var::uint64 i = 0; i < l_multiplier; ++i )
		{
			l_hash_value += ((uint64)wchar * (uint64)wchar);
		}
	}
	return l_hash_value;
}
