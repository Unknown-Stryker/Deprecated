#ifndef _FE_CORE_CSTRING_HXX_
#define _FE_CORE_CSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../miscellaneous/google_test_extension.h"
#include "prerequisite_symbols.h"
#include "algorithm/string.hxx"
#include <cstring>
#include <optional>


ENABLE_TEST_FOR(basic_cstring);


BEGIN_NAMESPACE(FE)


template< typename char_type = char >
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
class basic_cstring final
{
#if _VISUAL_STUDIO_CPP_ == 1
    ALLOW_ITS_FRIEND_TESTING(basic_cstring);
#endif
    static_assert(sizeof(char_type) <= sizeof(int32), "char_type is not a valid character type");

public:
    typedef const char_type* value_type;
    typedef char_type buffer_type;

private:
    ::std::optional<const char_type*> m_string;

public:
    _FORCE_INLINE_ constexpr basic_cstring() noexcept {};

    _FORCE_INLINE_ constexpr ~basic_cstring() noexcept {};


    _FORCE_INLINE_ basic_cstring(char_type* const cstr_ptrc_p) noexcept { this->m_string.emplace(cstr_ptrc_p); }
    _FORCE_INLINE_ constexpr basic_cstring(const char_type* const cstr_ptrc_p) noexcept { this->m_string.emplace(cstr_ptrc_p); }


    _FORCE_INLINE_ constexpr basic_cstring(basic_cstring<char_type>& copy_other_ref_p) noexcept { this->m_string.emplace(*copy_other_ref_p.m_string); }


    _FORCE_INLINE_ constexpr basic_cstring(basic_cstring<char_type>&& move_p) noexcept { this->m_string.emplace(*move_p.m_string); }


    _FORCE_INLINE_ basic_cstring<char_type>& operator=(char_type* const cstr_ptrc_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(cstr_ptrc_p);

        return *this;
    }

    _FORCE_INLINE_ constexpr basic_cstring<char_type>& operator=(const char_type* const cstr_ptrc_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(cstr_ptrc_p);

        return *this;
    }


    _FORCE_INLINE_ constexpr basic_cstring<char_type>& operator=(basic_cstring<char_type>& copy_other_ref_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*copy_other_ref_p.m_string);

        return *this;
    }


    _FORCE_INLINE_ constexpr basic_cstring<char_type>& operator=(basic_cstring<char_type>&& move_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*move_p.m_string);

        return *this;
    }


    _FORCE_INLINE_ constexpr const char_type* begin() noexcept { return *this->m_string; }
    _FORCE_INLINE_ constexpr const char_type* end() noexcept { return (*this->m_string) + ::FE::algorithm::string::strlen(*this->m_string); }

    _FORCE_INLINE_ constexpr char_type front() noexcept { return *(*this->m_string); }
    _FORCE_INLINE_ constexpr char_type back() noexcept { return  (*this->m_string)[::FE::algorithm::string::strlen(*this->m_string) - 1]; }

    _FORCE_INLINE_ constexpr const char_type* c_str() noexcept { return *this->m_string; }


    _FORCE_INLINE_ constexpr char_type operator[](index_t index_p) noexcept { return (*this->m_string)[index_p]; }

    _FORCE_INLINE_ friend constexpr boolean operator==(basic_cstring<char_type>& A_ref_p, basic_cstring<char_type>& B_ref_p) noexcept
    {
        return ::FE::algorithm::string::strcmp(*A_ref_p.m_string, *B_ref_p.m_string);
    }
    _FORCE_INLINE_ friend constexpr boolean operator==(const char_type* A_cwstr_ptr_p, basic_cstring<char_type>& B_ref_p) noexcept
    {
        return ::FE::algorithm::string::strcmp(A_cwstr_ptr_p, *B_ref_p.m_string);
    }
    _FORCE_INLINE_ friend constexpr boolean operator==(basic_cstring<char_type>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {
        return ::FE::algorithm::string::strcmp(*A_ref_p.m_string, B_cwstr_ptr_p);
    }

    _FORCE_INLINE_ friend constexpr boolean operator!=(basic_cstring<char_type>& A_ref_p, basic_cstring<char_type>& B_ref_p) noexcept
    {
        return !::FE::algorithm::string::strcmp(*A_ref_p.m_string, *B_ref_p.m_string);
    }
    _FORCE_INLINE_ friend constexpr boolean operator!=(const char_type* A_cwstr_ptr_p, basic_cstring<char_type>& B_ref_p) noexcept
    {
        return !::FE::algorithm::string::strcmp(A_cwstr_ptr_p, *B_ref_p.m_string);
    }
    _FORCE_INLINE_ friend constexpr boolean operator!=(basic_cstring<char_type>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {
        return !::FE::algorithm::string::strcmp(*A_ref_p.m_string, B_cwstr_ptr_p);
    }


    _FORCE_INLINE_ static constexpr void swap(basic_cstring<char_type>& A_ref_p, basic_cstring<char_type>& B_ref_p) noexcept
    {
        basic_cstring<char_type> l_temp = A_ref_p;
        A_ref_p = B_ref_p;
        B_ref_p = l_temp;
    }
};

using cstring = basic_cstring<char>;
using wcstring = basic_cstring<var::wchar>;

#if _HAS_CXX20 == 1
using cstring8 = basic_cstring<var::char8>;
#endif

using ucstring = basic_cstring<var::uchar>;
using scstring = basic_cstring<var::schar>;
using cstring16 = basic_cstring<var::char16>;
using cstring32 = basic_cstring<var::char32>;

END_NAMESPACE


#endif