#ifndef _FE_CORE_CSTRING_HXX_
#define _FE_CORE_CSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/iterator.hxx>
#include <FE/core/char_traits.hxx>
#include <cstring>




BEGIN_NAMESPACE(FE)


template< typename char_type = char , class traits = FE::char_traits<char_type>>
class compile_time_constant_string final
{
    FE_STATIC_ASSERT(FE::is_char<char_type>::value == false, "static assertion failed: the template argument char_type is not a valid character type.");
    FE_STATIC_ASSERT(std::is_class<traits>::value == false, "static assertion failed: the template argument traits is not a class or a struct type.");
    FE_STATIC_ASSERT((std::is_same<char_type, traits::value_type>::value == false), "static assertion failed: enforcing traits' value_type to be equivalent to char_type. The template parameter char_type must be identical to traits::value_type.");
    
    
    std::optional<const char_type*> m_string;

public:
    using traits_type = traits;
    using value_type = const char_type*;
    using buffer_type = char_type;
    using const_iterator = FE::const_iterator<FE::contiguous_iterator<const char_type>>;
    using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>>;


    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string() noexcept {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~compile_time_constant_string() noexcept {}

    template <typename T>
    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string(T* c_style_read_only_string_ptr_p) noexcept
    {
        static_assert(FE::is_c_style_constant_string<T*>::value == true, "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.");

        this->m_string.emplace(c_style_read_only_string_ptr_p);
    }

    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string(compile_time_constant_string& other_ref_p) noexcept { this->m_string.emplace(*other_ref_p.m_string); }
    _CONSTEXPR17_ _FORCE_INLINE_  compile_time_constant_string(compile_time_constant_string&& move_p) noexcept { this->m_string.emplace(*move_p.m_string); }

    template <typename T>
    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string& operator=(T* c_style_read_only_string_ptr_p) noexcept
    {
        static_assert(FE::is_c_style_constant_string<T*>::value == true, "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.");

        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(c_style_read_only_string_ptr_p);

        return *this;
    }

    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string& operator=(compile_time_constant_string& other_ref_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*other_ref_p.m_string);

        return *this;
    }

    _CONSTEXPR17_ _FORCE_INLINE_ compile_time_constant_string& operator=(compile_time_constant_string&& move_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*move_p.m_string);

        return *this;
    }

    _FORCE_INLINE_ char_type operator[](index_t index_p) const noexcept
    {
        FE_ASSERT(index_p >= algorithm::string::string_length(*(this->m_string)), "ERROR: an input index value passed to operator[]() exceeded the index boundary of a cstring instance.");
        return (*this->m_string)[index_p];
    }

    _FORCE_INLINE_ char_type front() const noexcept { return *(*this->m_string); }
    _FORCE_INLINE_ char_type back() const noexcept { return  (*this->m_string)[algorithm::string::string_length(*this->m_string) - 1]; }

    // It returns a pointer to the data
    _FORCE_INLINE_ const char_type* data() const noexcept { return (*this->m_string); }

    // It returns a pointer to a traditional c-style read-only string
    _FORCE_INLINE_ const char_type* c_str() const noexcept { return *this->m_string; }

    // It returns a standard string
    _FORCE_INLINE_::std::basic_string<char_type> std_str() const noexcept { return *this->m_string; }

    _FORCE_INLINE_ const_iterator cbegin() const noexcept { return *this->m_string; }
    _FORCE_INLINE_ const_iterator cend() const noexcept { return (*this->m_string) + algorithm::string::string_length(*this->m_string); }
    _FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept { return (*this->m_string) + (algorithm::string::string_length(*this->m_string) - 1); }
    _FORCE_INLINE_ const_reverse_iterator crend() const noexcept { return (*this->m_string) - 1; }

    _FORCE_INLINE_ var::boolean is_empty() const noexcept { return !(this->m_string.has_value()); }
    _FORCE_INLINE_ var::size_t length() const noexcept { return algorithm::string::string_length<char_type>(*this->m_string); }
    _FORCE_INLINE_ var::uint64 max_length() const noexcept { return ::FE::_MAX_VALUE_<var::uint64>(); }
    _FORCE_INLINE_ void clear() noexcept { this->m_string.reset(); }

    _FORCE_INLINE_ var::boolean starts_with(compile_time_constant_string& substring_ref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ 0, l_substring_length },
            substring_ref_p.data(), algorithm::string::range{ 0, l_substring_length }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean starts_with(const char_type target_character_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ 0, 1 },
            &target_character_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean starts_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_ASSERT(substring_ptrc_p == nullptr, "${%s@0}: substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ 0, l_substring_length },
            substring_ptrc_p, algorithm::string::range{ 0, l_substring_length }
        );
    }

    _FORCE_INLINE_ var::boolean ends_with(compile_time_constant_string& substring_ref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ l_this_string_length - l_substring_length, l_this_string_length },
            substring_ref_p.data(), algorithm::string::range{ 0, l_substring_length }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean ends_with(const char_type target_character_p) const noexcept
    {
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ l_this_string_length - 1, l_this_string_length },
            &target_character_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean ends_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_ASSERT(substring_ptrc_p == nullptr, "${%s@0}: substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(this->data(), algorithm::string::range{ l_this_string_length - l_substring_length, l_this_string_length },
            substring_ptrc_p, algorithm::string::range{ 0, l_substring_length }
        );
    }

    _FORCE_INLINE_ var::boolean contains(compile_time_constant_string& substring_ref_p) const noexcept
    {
        return this->contains(substring_ref_p.data());
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean contains(const char_type target_character_p) const noexcept
    {
        algorithm::string::char_info<char_type> l_target_char_search_result = algorithm::string::search_first_char(this->data(), target_character_p);
        return (l_target_char_search_result._target_data != static_cast<char_type>('\0')) ? true : false;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ var::boolean contains(const char_type* const target_substring_ptrc_p) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return (algorithm::string::search_first_substring(this->data(), target_substring_ptrc_p)).has_value();
    }

    _CONSTEXPR20_ _FORCE_INLINE_ void copy(char_type* const in_out_buffer_ptrc_p, size_t in_out_buffer_capacity_p, index_t begin_p, index_t end_p) const noexcept
    {
        FE_ASSERT(in_out_buffer_ptrc_p == nullptr, "${%s@0}: in_out_buffer_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(begin_p >= end_p, "ERROR: end_p cannot be greater than or equal to end_p.");
        FE_ASSERT(end_p > algorithm::string::string_length(this->data()), "ERROR: end_p cannot be greater than the left operand string length.");
        algorithm::string::copy_string(in_out_buffer_ptrc_p, in_out_buffer_capacity_p, *(this->m_string) + begin_p, end_p - begin_p);
    }

    _FORCE_INLINE_ std::optional<algorithm::string::range> find(compile_time_constant_string& target_substring_ref_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        std::optional<algorithm::string::range> l_result = algorithm::string::search_first_substring(this->data() + position_p, target_substring_ref_p.data());
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> find(const char_type* const target_substring_ptrc_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        std::optional<algorithm::string::range> l_result = algorithm::string::search_first_substring(this->data() + position_p, target_substring_ptrc_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_info<char_type> find(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        algorithm::string::char_info l_result = algorithm::string::search_first_char(this->data() + position_p, target_character_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _FORCE_INLINE_ std::optional<algorithm::string::range> rfind(compile_time_constant_string& target_substring_ref_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_substring_within_range(this->data(), algorithm::string::range{ 0, position_p }, target_substring_ref_p.data());
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> rfind(const char_type* const target_substring_ptrc_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_substring_within_range(this->data(), algorithm::string::range{ 0, position_p }, target_substring_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_info<char_type> rfind(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_char_within_range(this->data(), algorithm::string::range{ 0, position_p }, target_character_p);;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_count<char_type> count_chars(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::count_chars(this->data() + position_p, target_character_p);
    }

    _FORCE_INLINE_ void swap(compile_time_constant_string& second_ref_p) noexcept
    {
        compile_time_constant_string<char_type> l_temp = *this;
        *this = second_ref_p;
        second_ref_p = l_temp;
    }

    _FORCE_INLINE_ boolean operator==(compile_time_constant_string& other_ref_p) noexcept
    {
        return algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator==(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: cstr_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    _FORCE_INLINE_ boolean operator!=(compile_time_constant_string& other_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator!=(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: cstr_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return !algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator==(const char_type* const cstr_ptrc_p, compile_time_constant_string& cstring_ref_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: cstr_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator!=(const char_type* const cstr_ptrc_p, compile_time_constant_string& cstring_ref_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: cstr_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return !algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }
};


using cstring = compile_time_constant_string<char>;
using ucstring = compile_time_constant_string<var::uchar>;
using scstring = compile_time_constant_string<var::schar>;
using wcstring = compile_time_constant_string<var::wchar>;

#ifdef _HAS_CXX20_
using cstring8 = compile_time_constant_string<var::UTF8>;
#endif

using cstring16 = compile_time_constant_string<var::UTF16>;
using cstring32 = compile_time_constant_string<var::UTF32>;


END_NAMESPACE
#endif
