#ifndef _FE_CORE_STRING_HXX_
#define _FE_CORE_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <cstdlib>
#include "allocator.hxx"
#include "algorithm/string.hxx"
#include "../miscellaneous/google_test_extension.h"
#include "../miscellaneous/undefine_max_min.h"

ENABLE_TEST_FOR(basic_string);


BEGIN_NAMESPACE(FE)


template< typename char_type = char, typename max_length_type = var::uint32, class allocator = FE::c_style_allocator<char_type> >
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
class basic_string final
{
#if _VISUAL_STUDIO_CPP_ == 1
    ALLOW_ITS_FRIEND_TESTING(basic_string);
#endif

    static_assert(std::is_integral<max_length_type>::value, "max_length_type is not a valid numeric type");
    static_assert(sizeof(char_type) <= sizeof(int32), "char_type is not a valid character type");

public:
    typedef char_type value_type;
    typedef allocator allocator_type;
    typedef char_type& reference;
    typedef const char_type& const_reference;
    typedef char_type* pointer;
    typedef const char_type* const_pointer;
    typedef max_length_type length_type;

private:
    length_type m_string_length;
    length_type m_total_string_length;
    char_type* m_string_ptr;
    var::boolean m_was_previous_access_violation;


    static char_type s_null;

public:
    _FORCE_INLINE_ basic_string() noexcept : m_string_length(), m_total_string_length() {}

    _FORCE_INLINE_ ~basic_string() noexcept
    {
        if (this->m_string_ptr == nullptr)
#if _HAS_CXX20_ == 1
            _UNLIKELY_
#endif
        {
            return;
        }
        allocator::deallocate(this->m_string_ptr, this->m_total_string_length);
    }


    _FORCE_INLINE_ basic_string(const char_type* cstr_ptr_p) noexcept : m_string_length(::FE::algorithm::string::strlen<char_type>(copy_cstr_ptr_p))
    {
        if (copy_cstr_ptr_p == nullptr)
#if _HAS_CXX20_ == 1
            _UNLIKELY_
#endif
        {
            return;
        }

        this->m_total_string_length = this->m_string_length + 1;
        this->m_string_ptr = allocator::allocate(this->m_total_string_length);
        FE::memory::memcpy_s(this->m_string_ptr, copy_cstr_ptr_p, this->m_string_length, sizeof(char_type), this->m_string_length, sizeof(char_type));
    }


    _FORCE_INLINE_ basic_string(const basic_string<char_type, max_length_type, allocator>& copy_other_ref_p) noexcept
        : m_string_length(copy_other_ref_p.m_string_length), m_total_string_length(copy_other_ref_p.m_total_string_length)
    {
        if (FE::exception::handle_exceptions(IF(copy_other_ref_p.m_total_string_length == 0 || copy_other_ref_p.m_string_ptr == nullptr), FE::_LOG_EXCEPTION_HISTORY_, "Error: copy_other_ref_p.m_total_string_length was zero or copy_other_ref_p.m_string_ptr is nullptr, canceling basic_string instance construction.", _EXCEPTION_ORIGIN_)) { return; }
        this->m_string_ptr = allocator::allocate(this->m_total_string_length);

        FE::memory::memcpy_s(this->m_string_ptr, copy_other_ref_p.m_string_ptr, this->m_total_string_length, sizeof(char_type), copy_other_ref_p.m_total_string_length, sizeof(char_type));
    }


    _FORCE_INLINE_ basic_string(basic_string<char_type, max_length_type, allocator>&& move_p) noexcept
        : m_string_length(std::move(move_p.m_string_length)), m_total_string_length(std::move(move_p.m_total_string_length)), m_string_ptr(std::move(move_p.m_string_ptr))
    {
        move_p.m_string_ptr = nullptr;
        move_p.m_string_length = 0;
        move_p.m_total_string_length = 0;
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(const char_type* cstr_ptr_p) noexcept
    {
        return *this;
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(const basic_string<char_type, max_length_type, allocator>& copy_other_ref_p) noexcept
    {
        return *this;
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(basic_string<char_type, max_length_type, allocator>&& move_p) noexcept
    {
        this->m_string_length = std::move(move_p.m_string_length);
        this->m_total_string_length = std::move(move_p.m_total_string_length);
        this->m_string_ptr = std::move(move_p.m_string_ptr);
        move_p.m_string_ptr = nullptr;
        move_p.m_string_length = 0;
        move_p.m_total_string_length = 0;
        return *this;
    }


    _FORCE_INLINE_ char_type* begin() const noexcept { return this->m_string_ptr; }
    _FORCE_INLINE_ char_type* end() const noexcept { return &(this->m_string_ptr[this->m_string_length]); }

    _FORCE_INLINE_ char_type front() const noexcept { return this->m_string_ptr[0]; }
    _FORCE_INLINE_ char_type back() const noexcept { return this->m_string_ptr[this->m_string_length - 1]; }

    _FORCE_INLINE_ length_type size() const noexcept { return this->m_string_length; }
    _FORCE_INLINE_ length_type capacity() const noexcept { return this->m_total_string_length; }
    _FORCE_INLINE_ length_type max_length() const noexcept { return std::numeric_limits< max_length_type>::max(); }

    _FORCE_INLINE_ void reserve(length_type new_size_p) noexcept
    {
        if (FE::exception::handle_exceptions(IF(new_size_p == 0), FE::_LOG_EXCEPTION_HISTORY_, "invalid size: uint new_size_p is 0", _EXCEPTION_ORIGIN_)) { return; }

        this->m_string_ptr = FE::memory::trackable_realloc(this->m_string_ptr,
            this->m_total_string_length,
            sizeof(char_type),
            this->m_total_string_length + new_size_p,
            sizeof(char_type)
        );
        this->m_total_string_length += new_size_p;
    }

    _FORCE_INLINE_ void shrink_to_fit() noexcept
    {

    }

    _FORCE_INLINE_ void insert(length_type index_p, const char_type* cstr_ptr_p) noexcept
    {

    }

    _FORCE_INLINE_ void insert(length_type index_p, const basic_string<char_type, max_length_type, allocator>& str_ref_p) noexcept
    {

    }

    _FORCE_INLINE_ void try_pop_at(length_type index_p) noexcept
    {

    }

    _FORCE_INLINE_ char_type try_pop_back() noexcept
    {

    }

    _FORCE_INLINE_ void clear() noexcept
    {

    }

    _FORCE_INLINE_ boolean is_empty() const noexcept
    {

    }


    _FORCE_INLINE_ char_type& operator[](length_type index_p) noexcept
    {
        if (this->m_string_length <= index_p)
#if _HAS_CXX20 == 1
            _UNLIKELY_
#endif
        {
            this->m_was_previous_access_violation = true;
            return basic_string<char_type, max_length_type, allocator>::s_null;
        }
        this->m_was_previous_access_violation = false;
        return this->m_string_ptr[index_p];
    }

    _FORCE_INLINE_ length_type operator+=(char_type char_p) noexcept
    {

    }

    _FORCE_INLINE_ length_type operator+=(const char_type* cstr_ptr_p) noexcept
    {

    }

    _FORCE_INLINE_ length_type operator+=(const basic_string<char_type, max_length_type, allocator>& str_cref_p) noexcept
    {

    }


    _FORCE_INLINE_ const char_type* c_str() const noexcept { return static_cast<const char_type*>(this->m_string_ptr); }
    _FORCE_INLINE_ std::basic_string<char_type> std_str() const noexcept { return static_cast<const char_type*>(this->m_string_ptr); }


    _FORCE_INLINE_ friend boolean operator==(const basic_string<char_type, max_length_type, allocator>& A_ref_p, const basic_string<char_type, max_length_type, allocator>& B_ref_p) noexcept
    {
        return algorithm::string::strcmp<char_type>(static_cast<const char_type*>(A_ref_p.m_string_ptr), static_cast<const char_type*>(B_ref_p.m_string_ptr));
    }
    _FORCE_INLINE_ friend boolean operator==(const char_type* A_cwstr_ptr_p, const basic_string<char_type, max_length_type, allocator>& B_ref_p) noexcept
    {
        return algorithm::string::strcmp<char_type>(A_cwstr_ptr_p, static_cast<const char_type*>(B_ref_p.m_string_ptr));
    }
    _FORCE_INLINE_ friend boolean operator==(const basic_string<char_type, max_length_type, allocator>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {
        return algorithm::string::strcmp<char_type>(static_cast<const char_type*>(A_ref_p.m_string_ptr), B_cwstr_ptr_p);
    }

    _FORCE_INLINE_ friend boolean operator!=(const basic_string<char_type, max_length_type, allocator>& A_ref_p, const basic_string<char_type, max_length_type, allocator>& B_ref_p) noexcept
    {
        return !(algorithm::string::strcmp<char_type>(static_cast<const char_type*>(A_ref_p.m_string_ptr), static_cast<const char_type*>(B_ref_p.m_string_ptr)));
    }
    _FORCE_INLINE_ friend boolean operator!=(const char_type* A_cwstr_ptr_p, const basic_string<char_type, max_length_type, allocator>& B_ref_p) noexcept
    {
        return !(algorithm::string::strcmp<char_type>(A_cwstr_ptr_p, static_cast<const char_type*>(B_ref_p.m_string_ptr)));
    }
    _FORCE_INLINE_ friend boolean operator!=(const basic_string<char_type, max_length_type, allocator>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {
        return !(algorithm::string::strcmp<char_type>(static_cast<const char_type*>(A_ref_p.m_string_ptr), B_cwstr_ptr_p));
    }


    _FORCE_INLINE_ static void swap(basic_string<char_type, max_length_type, allocator>& A_ref_p, basic_string<char_type, max_length_type, allocator>& B_ref_p) noexcept;
};

template<typename char_type, typename max_length_type, class allocator>
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
char_type basic_string<char_type, max_length_type, allocator>::s_null = char_type('\0');



using name = basic_string<char, var::uint16>;
using tag = basic_string<char, var::uint16>;
using string = basic_string<char, var::uint32>;
using article = basic_string<char, var::uint64>;

using wname = basic_string<var::wchar, var::uint16>;
using wtag = basic_string<var::wchar, var::uint16>;
using wstring = basic_string<var::wchar, var::uint32>;
using warticle = basic_string<var::wchar, var::uint64>;

#if _HAS_CXX20_ == 1
using name8 = basic_string<var::char8, var::uint16>;
using tag8 = basic_string<var::char8, var::uint16>;
using string8 = basic_string<var::char8, var::uint32>;
using article8 = basic_string<var::char8, var::uint64>;
#endif

using name16 = basic_string<var::char16, var::uint16>;
using tag16 = basic_string<var::char16, var::uint16>;
using string16 = basic_string<var::char16, var::uint32>;
using article16 = basic_string<var::char16, var::uint64>;

using name32 = basic_string<var::char32, var::uint16>;
using tag32 = basic_string<var::char32, var::uint16>;
using string32 = basic_string<var::char32, var::uint32>;
using article32 = basic_string<var::char32, var::uint64>;


END_NAMESPACE
#include "../miscellaneous/define_max_min.h"
#endif