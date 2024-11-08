#ifndef _FE_CORE_FSTRING_HXX_
#define _FE_CORE_FSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "algorithm/string.hxx"
#include "prerequisite_symbols.h"
#include "private/memory.hxx"
#include "heap_utilization.hpp"


BEGIN_NAMESPACE(FE)


template<typename char_type, uint64 string_length>
class fixed_sized_string
{
    char_type m_fstring[string_length];

public:
    typedef char_type value_type;
    typedef char_type& reference;
    typedef const char_type& const_reference;
    typedef char_type* pointer;
    typedef const char_type* const_pointer;
    typedef uint64 length_type;


    constexpr fixed_sized_string() noexcept : m_fstring{ static_cast<const char_type>('\0') } {}

    constexpr fixed_sized_string(const char_type* cstr_ptr_p) noexcept : m_fstring{ static_cast<const char_type>('\0') }
    {
        ::FE::memcpy_s(this->m_fstring,
            (void*)cstr_ptr_p,
            string_length,
            sizeof(char_type),
            ::FE::algorithm::string::strlen<char_type>(cstr_ptr_p),
            sizeof(char_type)
        );
    }

    fixed_sized_string(char_type* cstr_ptr_p) noexcept : m_fstring{ static_cast<const char_type>('\0') }
    {
        ::FE::memcpy_s(this->m_fstring,
            (void*)cstr_ptr_p,
            string_length,
            sizeof(char_type),
            ::FE::algorithm::string::strlen<char_type>(cstr_ptr_p),
            sizeof(char_type)
        );
    }


    fixed_sized_string(const fixed_sized_string<char_type, string_length>& other_cref_p) noexcept : m_fstring{ static_cast<const char_type>('\0') }
    {
        ::FE::memcpy_s(this->m_fstring,
            other_cref_p.m_fstring,
            string_length,
            sizeof(char_type),
            string_length,
            sizeof(char_type)
        );
    }


    fixed_sized_string(fixed_sized_string<char_type, string_length>&& move_other_p) noexcept : m_fstring{ static_cast<const char_type>('\0') }
    {
        ::FE::memcpy_s(this->m_fstring,
            ::std::move(move_other_p.m_fstring),
            string_length,
            sizeof(char_type),
            string_length,
            sizeof(char_type)
        );
    }


    fixed_sized_string<char_type, string_length>& operator=(const fixed_sized_string<char_type, string_length>& other_cref_p) noexcept
    {
        ::FE::memcpy_s(this->m_fstring,
            other_cref_p.m_fstring,
            string_length,
            sizeof(char_type),
            string_length,
            sizeof(char_type)
        );
        return *this;
    }


    fixed_sized_string<char_type, string_length>& operator=(fixed_sized_string<char_type, string_length>&& move_other_p) noexcept
    {
        ::FE::memcpy_s(this->m_fstring,
            ::std::move(move_other_p.m_fstring),
            string_length,
            sizeof(char_type),
            string_length,
            sizeof(char_type)
        );
        return *this;
    }


    char_type& operator[](index_t idx_p) noexcept
    {
        ::FE::exception::handle_exceptions(IF(idx_p >= string_length), ::FE::_ABORT_IMMEDIATELY_, "Critical Memory Access Violation Error: The index out of range.", _EXCEPTION_ORIGIN_);

        return this->m_fstring[idx_p];
    }

    fixed_sized_string<char_type, string_length>& operator+=(const fixed_sized_string<char_type, string_length>& other_ref_p) noexcept
    {
        ::FE::algorithm::string::strcat<char_type>(this->m_fstring, this->capacity(), other_ref_p.m_fstring, other_ref_p.size());
        return *this;
    }

    fixed_sized_string<char_type, string_length>& operator+=(const char_type* c_style_string_ptr_p) noexcept
    {
        ::FE::algorithm::string::strcat<char_type>(this->m_fstring, this->capacity(), c_style_string_ptr_p, ::FE::algorithm::string::strlen<char_type>(c_style_string_ptr_p));
        return *this;
    }


    var::uint64 capacity() const noexcept { return string_length; }

    var::uint64 size() const noexcept { return ::FE::algorithm::string::strlen<char_type>(this->m_fstring); }

    const char_type* c_str() noexcept { return this->m_fstring; }

    char_type* begin() noexcept { return this->m_fstring; }

    char_type* end() noexcept
    {
        var::uint64 l_strlen = ::FE::algorithm::string::strlen<char_type>(this->m_fstring);
        return &(this->m_fstring[l_strlen]);
    }

    char_type front() noexcept { return this->m_fstring[0]; }

    char_type back() noexcept { return this->m_fstring[::FE::algorithm::string::strlen<char_type>(this->m_fstring) - 1]; }

    char_type pop_back() noexcept
    {
        const char_type l_return_value = this->back();
        this->m_fstring[::FE::algorithm::string::strlen<char_type>(this->m_fstring) - 1] = static_cast<const char_type>('\0');
        return l_return_value;
    }
};


template<uint64 string_length>
using fstring = FE::fixed_sized_string<char, string_length>;

template<uint64 string_length>
using fwstring = FE::fixed_sized_string<wchar_t, string_length>;

#if _HAS_CXX20_ == 1
template<uint64 string_length>
using fstring8 = FE::fixed_sized_string<char8_t, string_length>;
#endif

template<uint64 string_length>
using fstring16 = FE::fixed_sized_string<char16_t, string_length>;

template<uint64 string_length>
using fstring32 = FE::fixed_sized_string<char32_t, string_length>;


END_NAMESPACE;
#endif