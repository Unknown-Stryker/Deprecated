#ifndef _STRING_HXX_
#define _STRING_HXX_
#define _ENGLISH_ONLY_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include <cstdlib>
#include "core.debug.h"
#include "core.types.h"
#include "memory.allocator.hxx"
#include <string>




BEGIN_NAMESPACE(FE)


BEGIN_NAMESPACE(memory)


#define _LAST_CHAR_ this->m_string_length
#define _STRING_MALLOC_SIZE_ this->m_string_length + 1
#define _STRING_TOTAL_LENGTH_ this->m_total_string_length


constexpr uint8 ASCII_a = 97;
constexpr uint8 ASCII_z = 122;

constexpr uint8 ASCII_A = 65;
constexpr uint8 ASCII_Z = 90;
constexpr uint8 ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase = 32;


template< typename char_type = char, typename max_string_length = var::uint32, class allocator = string_allocator<char_type> > 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
class basic_string final
{
    static_assert( sizeof(max_string_length) <= sizeof(uint64), "max_string_length is not a valid numeric type" );
    static_assert( sizeof(char_type) <= sizeof(int32), "char_type is not a valid character type" );

    typedef max_string_length uint_t;
member_variables:
    char_type* m_string_ptr;
    uint_t m_string_length;
    uint_t m_total_string_length;

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
    static char_type s_null;
#endif
    typedef const max_string_length uint;
constructors:
    basic_string() noexcept;
    
destructor:
    ~basic_string() noexcept;

constructors:
    basic_string(const char_type* cstr_ptr_p) noexcept;

copy_constructor:
    basic_string(const basic_string<char_type, max_string_length, allocator>& copy_other_ref_p) noexcept;

move_constructor:
    basic_string(basic_string<char_type, max_string_length, allocator>&& move_p) noexcept;

assignment_operator:
    basic_string<char_type, max_string_length, allocator>& operator=(const char_type* cstr_ptr_p) noexcept;

copy_assignment_operator:
    basic_string<char_type, max_string_length, allocator>& operator=(const basic_string<char_type, max_string_length, allocator>& copy_other_ref_p) noexcept;

move_assignment_operator:
    basic_string<char_type, max_string_length, allocator>& operator=(basic_string<char_type, max_string_length, allocator>&& move_p) noexcept;

methods:
    char_type* begin() const noexcept { return this->m_string_ptr; }
    char_type* end() const noexcept { return &( this->m_string_ptr[_LAST_CHAR_]); }

    char_type front() const noexcept { return this->m_string_ptr[0]; }
    char_type back() const noexcept { return this->m_string_ptr[_LAST_CHAR_ - 1]; }

    uint string_length() const noexcept { return this->m_string_length; }
    uint string_total_length() const noexcept { return this->m_total_string_length; }
    uint spare_elements() const noexcept { return this->m_total_string_length - this->m_string_length; }
    uint max_length() const noexcept;

    void reserve(uint new_size_p) noexcept;
    void resize(uint length_p) noexcept;
    void shrink_to_fit() noexcept;

    void insert(uint index_p, const char_type* cstr_ptr_p) noexcept;
    void insert(uint index_p, const basic_string<char_type, max_string_length, allocator>& str_ref_p) noexcept;
   
    void pop_at(uint index_p) noexcept;
    char_type pop_back() noexcept;

    void clear_all() noexcept;
    boolean is_it_empty() const noexcept;

operators:
    char_type& operator[](uint index_p) noexcept;

    uint operator+=(char_type char_p) noexcept;
    uint operator+=(const char_type* cstr_ptr_p) noexcept;
    uint operator+=(const basic_string<char_type, max_string_length, allocator>& str_ref_p) noexcept;

methods:
    _ENGLISH_ONLY_ void UPPERCASE() noexcept;
    _ENGLISH_ONLY_ void lowercase() noexcept;
    void delete_spaces() noexcept;
    _ENGLISH_ONLY_ void capitalize_all_the_first_letter_of_words() noexcept;
    void invert_string() noexcept;
    _DEPRECATED_ _NODISCARD basic_string<char_type, max_string_length, allocator>* extract_words_from_string() const noexcept;
    _NODISCARD_ basic_string<char_type, max_string_length, allocator>&& extract_letters_from_string(uint A_p, uint Z_p) const noexcept;
    uint64 hash_code() const noexcept;

    const char_type* get_primitive_string() const noexcept { return (const char_type*)this->m_string_ptr; }
    auto get_standard_string() const noexcept { return (const char_type*)this->m_string_ptr; }

operators:
    inline friend boolean operator==(const basic_string<char_type, max_string_length, allocator>& A_ref_p, const basic_string<char_type, max_string_length, allocator>& B_ref_p) noexcept
    {

    }
    inline friend boolean operator==(const char_type* A_cwstr_ptr_p, const basic_string<char_type, max_string_length, allocator>& B_ref_p)  noexcept
    {

    }
    inline friend boolean operator==(const basic_string<char_type, max_string_length, allocator>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {

    }

    inline friend boolean operator!=(const basic_string<char_type, max_string_length, allocator>& A_ref_p, const basic_string<char_type, max_string_length, allocator>& B_ref_p) noexcept
    {

    }
    inline friend boolean operator!=(const char_type* A_cwstr_ptr_p, const basic_string<char_type, max_string_length, allocator>& B_ref_p) noexcept
    {

    }
    inline friend boolean operator!=(const basic_string<char_type, max_string_length, allocator>& A_ref_p, const char_type* B_cwstr_ptr_p) noexcept
    {

    }

static_methods:
    static void swap(basic_string<char_type, max_string_length, allocator>& A_ref_p, basic_string<char_type, max_string_length, allocator>& B_ref_p) noexcept;
};

#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
char_type basic_string<char_type, max_string_length, allocator>::s_null = char_type'\0';
#endif

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::basic_string() noexcept : m_string_ptr(), m_string_length(), m_total_string_length() {}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::~basic_string() noexcept
{
    if ( this->m_string_ptr == nullptr ) { return; }
    allocator::deallocate(this->m_string_ptr, _STRING_TOTAL_LENGTH_);
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::basic_string(const char_type* copy_cstr_ptr_p) noexcept : m_string_length()
{
    if ( copy_cstr_ptr_p == nullptr ) _UNLIKELY_ { return; }

    for ( ; copy_cstr_ptr_p[this->m_string_length] != (char_type)'\0'; ++this->m_string_length ) {}

    this->m_string_ptr = allocator::allocate(_STRING_MALLOC_SIZE_);

    memcpy(this->m_string_ptr, copy_cstr_ptr_p, sizeof(char_type) * _STRING_MALLOC_SIZE_);

    this->m_total_string_length = this->m_string_length;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::basic_string(const basic_string<char_type, max_string_length, allocator>& copy_other_ref_p) noexcept
    : m_string_length(copy_other_ref_p.m_string_length), m_total_string_length(copy_other_ref_p.m_total_string_length)
{
    this->m_string_ptr = allocator::allocate(_STRING_MALLOC_SIZE_);

    memcpy(this->m_string_ptr, copy_other_ref_p.m_string_ptr, sizeof(char_type) * _STRING_MALLOC_SIZE_);
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::basic_string(basic_string<char_type, max_string_length, allocator>&& move_p) noexcept
    : m_string_length(std::move(move_p.m_string_length)), m_total_string_length(std::move(move_p.m_total_string_length)), m_string_ptr(std::move(move_p.m_string_ptr))
{
    move_p.m_string_ptr = nullptr;
    move_p.m_string_length = 0;
    move_p.m_total_string_length = 0;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>& basic_string<char_type, max_string_length, allocator>::operator=(const char_type* cstr_ptr_p) noexcept
{
    return *this;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>& basic_string<char_type, max_string_length, allocator>::operator=(const basic_string<char_type, max_string_length, allocator>& copy_other_ref_p) noexcept
{
    return *this;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>& basic_string<char_type, max_string_length, allocator>::operator=(basic_string<char_type, max_string_length, allocator>&& move_p) noexcept
{
    this->m_string_length = std::move(move_p.m_string_length);
    this->m_total_string_length = std::move(move_p.m_total_string_length);
    this->m_string_ptr = std::move(move_p.m_string_ptr);
    move_p.m_string_ptr = nullptr;
    move_p.m_string_length = 0;
    move_p.m_total_string_length = 0;
    return *this;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
basic_string<char_type, max_string_length, allocator>::uint  basic_string<char_type, max_string_length, allocator>::max_length() const noexcept
{
    switch ( typename_hash_code( typeid( uint ).name() ) )
    {
    case 0:
        return _UINT8_HASH_CODE_;
        break;

    case 1:
        return _UINT16_HASH_CODE_;
        break;

    case 2:
        return _UINT32_HASH_CODE_;
        break;

    case 3:
        return _UINT64_HASH_CODE_;
        break;
    }
}

template<typename char_type, typename max_string_length, class allocator>
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
void basic_string<char_type, max_string_length, allocator>::reserve(uint new_size_p) noexcept
{
    auto l_ptr = this->m_string_ptr;

    l_ptr = realloc(l_ptr, sizeof(char_type) * (this->m_total_string_length + new_size_p) );

    if ( l_ptr == nullptr )
    {
        l_ptr = allocator::allocate(this->m_total_string_length + new_size_p);
        memcpy(l_ptr, this->m_string_ptr, sizeof(char_type) * this->m_total_string_length);
        allocator::deallocate(this->m_string_ptr, this->m_total_string_length);
        this->m_total_string_length = this->m_total_string_length + new_size_p;
        return;
    }
    this->m_string_ptr = l_ptr;
    this->m_total_string_length = this->m_total_string_length + new_size_p;
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
char_type& basic_string<char_type, max_string_length, allocator>::operator[](uint index_p) noexcept
{
    if ( this->m_string_length < index_p ) _UNLIKELY_
    {
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
    return (char_type&)basic_string<max_string_length, allocator>::s_null;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
    exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
    exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
#endif
    }

    return this->m_string_ptr[index_p];
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
_ENGLISH_ONLY_ void basic_string<char_type, max_string_length, allocator>::UPPERCASE() noexcept
{
    for ( uint idx = 0; idx < this->m_string_length; ++idx )
    {
        if ( ASCII_a <= (uint8)this->m_string_ptr[idx] && (uint8)this->m_string_ptr[idx] <= ASCII_z )
        {
            this->m_string_ptr[idx] = (char_type)( (uint8)this->m_string_ptr[idx] - ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
        }
    }
}

template<typename char_type, typename max_string_length, class allocator>
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
_ENGLISH_ONLY_ void basic_string<char_type, max_string_length, allocator>::lowercase() noexcept
{
    for ( uint idx = 0; idx < this->m_string_length; ++idx )
    {
        if ( ASCII_A <= (uint8)this->m_string_ptr[idx] && (uint8)this->m_string_ptr[idx] <= ASCII_Z )
        {
            this->m_string_ptr[idx] = (char_type)( (uint8)this->m_string_ptr[idx] + ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase );
        }
    }
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
_ENGLISH_ONLY_ void basic_string<char_type, max_string_length, allocator>::capitalize_all_the_first_letter_of_words() noexcept
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

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
void basic_string<char_type, max_string_length, allocator>::invert_string() noexcept
{
    uint l_start = 0;
    uint l_end = this->m_string_length;

    char_type l_temporary = (char_type)'\0';
    while ( l_start < l_end )
    {
        l_temporary = this->m_string_ptr[l_start];
        this->m_string_ptr[l_start] = this->m_string_ptr[l_end - 1];
        this->m_string_ptr[l_end - 1] = l_temporary;

        ++l_start;
        --l_end;
    }
}

template<typename char_type, typename max_string_length, class allocator> 
#if _HAS_CXX20 == 1
    requires string_type<char_type>
#endif
FE::uint64 basic_string<char_type, max_string_length, allocator>::hash_code() const noexcept
{
    var::uint64 l_hash_value = 0;

    var::uint64 l_multiplier = 0;
    for ( char_type c : *this )
    {
        ++l_multiplier;
        for ( var::uint64 i = 0; i < l_multiplier; ++i )
        {
            l_hash_value += ( (uint64)c * (uint64)c );
        }
    }
    return l_hash_value;
}


END_NAMESPACE

using name = memory::basic_string<char, var::uint16>;
using tag = memory::basic_string<char, var::uint16>;
using string = memory::basic_string <char, var::uint32 >;
using article = memory::basic_string<char, var::uint64>;

using wname = memory::basic_string<var::wchar, var::uint16>;
using wtag = memory::basic_string<var::wchar, var::uint16>;
using wstring = memory::basic_string <var::wchar, var::uint32 >;
using warticle = memory::basic_string<var::wchar, var::uint64>;

#if _HAS_CXX20 == 1
using name8 = memory::basic_string<var::char8, var::uint16>;
using tag8 = memory::basic_string<var::char8, var::uint16>;
using string8 = memory::basic_string <var::char8, var::uint32 >;
using article8 = memory::basic_string<var::char8, var::uint64>;
#endif

using name16 = memory::basic_string<var::char16, var::uint16>;
using tag16 = memory::basic_string<var::char16, var::uint16>;
using string16 = memory::basic_string <var::char16, var::uint32 >;
using article16 = memory::basic_string<var::char16, var::uint64>;

using name32 = memory::basic_string<var::char32, var::uint16>;
using tag32 = memory::basic_string<var::char32, var::uint16>;
using string32 = memory::basic_string <var::char32, var::uint32 >;
using article32 = memory::basic_string<var::char32, var::uint64>;

END_FE


#endif
#endif

