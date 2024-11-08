#ifndef _FE_CORE_ALGORITHM_STRING_HXX_
#define _FE_CORE_ALGORITHM_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../prerequisite_symbols.h"
#include <tuple>
#include <vector>


BEGIN_NAMESPACE(FE::algorithm::string)


_MAYBE_UNUSED_ static constexpr uint8 _ASCII_a_ = 97;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_z_ = 122;

_MAYBE_UNUSED_ static constexpr uint8 _ASCII_A_ = 65;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_Z_ = 90;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ = 32;


template <typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ int_type ascii_number_to_integer(char_type* cstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::int16 l_sign = 1;
    if (*cstr_ptr_p == static_cast<const char_type>('-')) { l_sign = -1; }
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        ++cstr_ptr_p;
    }
    --cstr_ptr_p;

    int_type l_result = 0;
    int_type l_multiplier = 1;
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        l_result += static_cast<int_type>(*cstr_ptr_p - static_cast < const char_type>('0')) * l_multiplier;
        l_multiplier *= 10;
        --cstr_ptr_p;
    }
    return l_sign * l_result;
}

template <typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr int_type ascii_number_to_integer(const char_type* cstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::int16 l_sign = 1;
    if (*cstr_ptr_p == static_cast<const char_type>('-')) { l_sign = -1; }
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        ++cstr_ptr_p;
    }
    --cstr_ptr_p;

    int_type l_result = 0;
    int_type l_multiplier = 1;
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        l_result += static_cast<int_type>(*cstr_ptr_p - static_cast <const char_type>('0')) * l_multiplier;
        l_multiplier *= 10;
        --cstr_ptr_p;
    }
    return l_sign * l_result;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::uint64 strlen(char_type* const str_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*l_iterator_ptr == '\0')
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != static_cast<char_type>('\0')) {}

    return (l_iterator_ptr - str_ptrc_p);
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::uint64 strlen(const char_type* const str_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*l_iterator_ptr == '\0')
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != static_cast<char_type>('\0')) {}

    return (l_iterator_ptr - str_ptrc_p);
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean strcmp(char_type* lstr_ptr_p, char_type* rstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean strcmp(const char_type* lstr_ptr_p, const char_type* rstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void strcpy(char_type* const destination_out_ptrc_p, count_t destination_count_p, const char_type* const source_ptrc_p, count_t source_count_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    if (destination_count_p < source_count_p)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    { 
        ::abort(); 
    }

    var::length_t l_copy_len;
    (destination_count_p >= source_count_p) ? l_copy_len = source_count_p : l_copy_len = destination_count_p;
    ::memcpy(destination_out_ptrc_p, source_ptrc_p, sizeof(char_type) * l_copy_len);
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void strcat(char_type* const destination_out_ptrc_p, count_t destination_total_count_p, const char_type* const source_ptrc_p, count_t source_total_count_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    if (destination_total_count_p < source_total_count_p)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    { 
        ::abort(); 
    }
    
    length_t l_destination_string_length = ::FE::algorithm::string::strlen<char_type>(destination_out_ptrc_p);

    var::length_t l_destination_string_capacity = destination_total_count_p - l_destination_string_length;

    if (l_destination_string_capacity >= source_total_count_p)
    {
        ::memcpy(destination_out_ptrc_p + l_destination_string_length, source_ptrc_p, sizeof(char_type) * source_total_count_p);
    }
    else
    {
        ::memcpy(destination_out_ptrc_p + l_destination_string_length, source_ptrc_p, sizeof(char_type) * l_destination_string_capacity);
    }
}


template<typename char_type, class string>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void UPPERCASE(string& in_out_string_ref_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_string_length = ::FE::algorithm::string::strlen(in_out_string_ref_p.c_str());

    for ( var::uint64 idx = 0; idx < l_string_length; ++idx )
    {
        if ( (_ASCII_a_ <= static_cast<uint8>(in_out_string_ref_p[idx])) && 
            (static_cast<uint8>(in_out_string_ref_p[idx]) <= _ASCII_z_ ))
        {
            in_out_string_ref_p[idx] = static_cast<char_type>( static_cast<uint8>(in_out_string_ref_p[idx]) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ );
        }
    }
}


template<typename char_type, class string>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void lowercase(string& in_out_string_ref_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_string_length = ::FE::algorithm::string::strlen(in_out_string_ref_p.c_str());

    for ( var::uint64 idx = 0; idx < l_string_length; ++idx )
    {
        if ( _ASCII_A_ <= static_cast<uint8>(in_out_string_ref_p[idx]) && 
            static_cast<uint8>(in_out_string_ref_p[idx]) <= _ASCII_Z_ )
        {
            in_out_string_ref_p[idx] = static_cast<char_type>( static_cast<uint8>(in_out_string_ref_p[idx]) + _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ );
        }
    }
}


template<typename char_type, class string>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void capitalize_every_first_letter_of_words(string& in_out_string_ref_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_string_length = ::FE::algorithm::string::strlen(in_out_string_ref_p.c_str());

    if ((in_out_string_ref_p[0] != static_cast<char_type>(' ')) 
|| (in_out_string_ref_p[0] != static_cast<char_type>('_')))
    {
        in_out_string_ref_p[0] = static_cast<uint8>(in_out_string_ref_p[0]) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
    }

    for ( var::uint64 idx = 0; idx < l_string_length; ++idx )
    {
        if (((in_out_string_ref_p[idx] == static_cast<char_type>(' ')) && (idx + 1 < l_string_length) && (in_out_string_ref_p[idx + 1] != static_cast<char_type>(' '))) ||
            ((in_out_string_ref_p[idx] == static_cast<char_type>('_')) && (idx + 1 < l_string_length) && (in_out_string_ref_p[idx + 1] != static_cast<char_type>('_'))))
        {
            if ( ((_ASCII_A_ <= in_out_string_ref_p[idx + 1]) && (in_out_string_ref_p[idx + 1] <= _ASCII_Z_))
                || ((_ASCII_a_ <= in_out_string_ref_p[idx + 1]) && (in_out_string_ref_p[idx + 1] <= _ASCII_z_)) )
            {
                in_out_string_ref_p[idx + 1] = static_cast<uint8>(in_out_string_ref_p[idx + 1]) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
            }
        }
    }
}


template<typename char_type, class string>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ void invert_string(string& in_out_string_ref_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_start = 0;
    var::uint64 l_end = ::FE::algorithm::string::strlen(in_out_string_ref_p.c_str());

    char_type l_temporary = static_cast<char_type>('\0');
    while ( l_start < l_end )
    {
        l_temporary = in_out_string_ref_p[l_start];
        in_out_string_ref_p[l_start] = in_out_string_ref_p[l_end - 1];
        in_out_string_ref_p[l_end - 1] = l_temporary;

        ++l_start;
        --l_end;
    }
}


// runtime version of hash_code();
// Please NOTE that 1.0 is equal to 100%.
// Average Hash Collision Ratio : 0.02
// The Chance of Hash Collisions: 2% out of 100%
template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
var::uint64 hash_code(char_type* const string_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");

    uint64 l_string_length = ::FE::algorithm::string::strlen(string_ptrc_p);
    if (l_string_length == 0)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    {
        abort();
    }

    var::uint64 l_hash = 0;
    for (var::uint64 i = 0; i < l_string_length; ++i)
    {
        l_hash = (l_hash * l_hash * l_hash) + string_ptrc_p[i];
    }

    return l_hash;
}

// This function can be useful when a string needs to be hashed during compile-time. 
// Please NOTE that 1.0 is equal to 100%.
// Average Hash Collision Ratio : 0.02
// The Chance of Hash Collisions: 2% out of 100%
template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
constexpr var::uint64 hash_code(const char_type* const string_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");

    uint64 l_string_length = ::FE::algorithm::string::strlen(string_ptrc_p);
    if (l_string_length == 0)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    {
        abort();
    }

    var::uint64 l_hash = 0;
    for (var::uint64 i = 0; i < l_string_length; ++i)
    {
        l_hash = (l_hash * l_hash * l_hash) + string_ptrc_p[i];
    }

    return l_hash;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ std::pair<var::uint64, char_type> find_a_character(char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_match_count = 0;

    while (*string_ptr_p != static_cast<char_type>('\0'))
    {
        if (target_char_p == *string_ptr_p)
        {
            ++l_match_count;
        }
        ++string_ptr_p;
    }

    char_type l_target_char_buffer = static_cast<char_type>('\0');

    if (l_match_count != 0)
    {
        l_target_char_buffer = target_char_p;
    }

    return std::make_pair<var::uint64, char_type>(std::move(l_match_count), std::move(l_target_char_buffer));
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr std::pair<var::uint64, char_type> find_a_character(const char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    var::uint64 l_match_count = 0;

    while (*string_ptr_p != static_cast<char_type>('\0'))
    {
        if (target_char_p == *string_ptr_p)
        {
            ++l_match_count;
        }
        ++string_ptr_p;
    }

    char_type l_target_char_buffer = static_cast<char_type>('\0');

    if (l_match_count != 0)
    {
        l_target_char_buffer = target_char_p;
    }

    return std::make_pair<var::uint64, char_type>(std::move(l_match_count), std::move(l_target_char_buffer));
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean find_letters(char_type* string_ptr_p, char_type* target_letters_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    uint64 l_string_length = ::FE::algorithm::string::strlen(string_ptr_p);
    uint64 l_target_letters_length = ::FE::algorithm::string::strlen(target_letters_ptr_p);


    const char_type* l_begin_target_letters_ptr = target_letters_ptr_p;


    if (l_string_length < l_target_letters_length) { return false; }


    while (*target_letters_ptr_p != static_cast<char_type>('\0'))
    {
        if (*string_ptr_p == *target_letters_ptr_p)
        {
            ++target_letters_ptr_p;
        }
        else
        {
            target_letters_ptr_p = l_begin_target_letters_ptr;
        }
        ++string_ptr_p;
    }

    if ((target_letters_ptr_p - l_begin_target_letters_ptr) == l_target_letters_length)
    {
        return true;
    }
    return false;
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean find_letters(const char_type* string_ptr_p, const char_type* target_letters_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    uint64 l_string_length = ::FE::algorithm::string::strlen(string_ptr_p);
    uint64 l_target_letters_length = ::FE::algorithm::string::strlen(target_letters_ptr_p);


    const char_type* l_begin_target_letters_ptr = target_letters_ptr_p;


    if (l_string_length < l_target_letters_length) { return false; }


    while (*target_letters_ptr_p != static_cast<char_type>('\0'))
    {
        if (*string_ptr_p == *target_letters_ptr_p)
        {
            ++target_letters_ptr_p;
        }
        else
        {
            target_letters_ptr_p = l_begin_target_letters_ptr;
        }
        ++string_ptr_p;
    }

    if (static_cast<var::uint64>(target_letters_ptr_p - l_begin_target_letters_ptr) == l_target_letters_length)
    {
        return true;
    }
    return false;
}


template<typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
_FORCE_INLINE_ int_type ascii_character_number_to_int(char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");
    static_assert(std::is_integral<int_type>::value == true, "typename int_type is not an integer");


    return static_cast<int_type>(target_char_p) - 48;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
void concatenate_strings(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, std::initializer_list<const char_type* const>&& strings_p, size_t resize_buffer_p = 0) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");


    thread_local static std::vector<var::size_t> tl_s_string_length_buffer;

    if (resize_buffer_p <= strings_p.size())
    {
        tl_s_string_length_buffer.reserve(strings_p.size());
    }
    else
    {
        tl_s_string_length_buffer.resize(resize_buffer_p);
    }

    var::size_t l_total_strings_length = 0;
    for (var::size_t i = 0; i < strings_p.size(); ++i)
    {
        tl_s_string_length_buffer.emplace_back( ::FE::algorithm::string::strlen( strings_p.begin()[i] ) );
        l_total_strings_length += tl_s_string_length_buffer[i];
    }

    if (string_buffer_size_p <= l_total_strings_length)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    {
        ::abort();
    }

    var::size_t l_current_begin_index = ::FE::algorithm::string::strlen(out_string_buffer_ptrc_p);

    for (var::size_t i = 0; i < strings_p.size(); ++i)
    {
        ::memcpy(out_string_buffer_ptrc_p + l_current_begin_index, strings_p.begin()[i], sizeof(char_type) * tl_s_string_length_buffer[i]);
        l_current_begin_index += tl_s_string_length_buffer[i];
    }

    tl_s_string_length_buffer.clear();
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires string_type<char_type>
#endif
void concatenate_characters(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, std::initializer_list<const char_type>&& strings_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(char32), "char_type is not a valid character type");

    var::length_t l_string_buffer_length = ::FE::algorithm::string::strlen(out_string_buffer_ptrc_p);

    if (string_buffer_size_p <= strings_p.size() + l_string_buffer_length)
#if _HAS_CXX20_
        _UNLIKELY_
#endif
    {
        ::abort();
    };
    
    ::memcpy(out_string_buffer_ptrc_p + l_string_buffer_length, strings_p.begin(), sizeof(char_type) * strings_p.size());
}


END_NAMESPACE
#endif // _ALGORITHM_STRING_ALGORITHM_
