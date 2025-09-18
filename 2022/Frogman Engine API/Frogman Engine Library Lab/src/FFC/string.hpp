#ifndef _STRING_HPP_
#define _STRING_HPP_
#define _ENGLISH_ONLY_
#include "../../config/types.h"




BEGIN NAMESPACE(fstd)


class string
{
member_variables:
    var::uchar* m_string_ptr;
    var::uint32 m_string_length;
    var::uint32 m_string_total_length;

    var::uint32 m_capacity;
    var::uint32 m_capacity_divider;

    var::uchar m_null;

constructors:
    string() noexcept;
    
destructor:
    ~string() noexcept;

constructors:
    string(var::uchar* str_ptr_p) noexcept;
    string(const char* cstr_ptr_p) noexcept;

copy_constructor:
    string(const string& copy_other_ref_p) noexcept;

move_constructor:
    string(string&& move_p) noexcept;

assignment_operator:
    string& operator=(var::uchar* str_ptr_p) noexcept;
    string& operator=(const char* cstr_ptr_p) noexcept;

copy_assignment_operator:
    string& operator=(const string& copy_other_ref_p) noexcept;

move_assignment_operator:
    string& operator=(string&& move_p) noexcept;

methods:
    var::uchar* begin() const noexcept;
    var::uchar* end() const noexcept;

    uint32 length() const noexcept ;
    uint32 total_length() const noexcept;
    uint32 capacity() const noexcept;
    uint32 max_length() const noexcept { return _UINT32_MAX_LENGTH_; }

    void set_capacity_by_percent(uint32 percent_p);
    uint32 get_capacity_by_percent() const noexcept;

    void reserve(uint32 length_p) noexcept;
    void resize(uint32 length_p) noexcept;

    void clear_all() noexcept;
    void erase(uint32 index_p) noexcept;
    boolean is_it_empty() const noexcept;
    void shrink_to_fit() noexcept;

    uchar& operator[](uint32 index_p) noexcept;
    uchar front() const noexcept;
    uchar back() const noexcept;

operators:
    uint32 operator+=(uchar char_p) noexcept;
    uint32 operator+=(var::uchar* str_ptr_p) noexcept;
    uint32 operator+=(const char* cstr_ptr_p) noexcept;
    uint32 operator+=(const string& str_ref_p) noexcept;

methods:
    void insert(uint32 index_p, var::uchar* str_ptr_p) noexcept;
    void insert(uint32 index_p, const char* cstr_ptr_p) noexcept;
    void insert(uint32 index_p, const string& str_ref_p) noexcept;
    uchar pop_back() noexcept;

    _NODISCARD_ var::uchar* copy_string() const noexcept;
    _NODISCARD_ var::wchar* copy_wstring() const noexcept;

    static void swap(const string& A_ref_p, const string& B_ref_p) noexcept;
    void print() const noexcept;
    void println() const noexcept;

    _ENGLISH_ONLY_ void UPPERCASE() noexcept;
    _ENGLISH_ONLY_ void lowercase() noexcept;
    void delete_spaces() noexcept;
    _ENGLISH_ONLY_ void capitalize_all_the_first_letter_of_words() noexcept;
    void invert_string() noexcept;
    _DEPRECATED_ _NODISCARD fstd::string* extract_words_from_string() const noexcept;
    _NODISCARD_ var::uchar* extract_letters_from_string(uint32 A_p, uint32 Z_p) const noexcept;
    uint64 hash_code() noexcept;

operators:
    inline friend boolean operator==(const string& A_ref_p, const string& B_ref_p);

    inline friend boolean operator==(const char* A_cwstr_ptr_p, const string& B_ref_p);
    inline friend boolean operator==(const string& A_ref_p, const char* B_cwstr_ptr_p);

    inline friend boolean operator==(var::uchar* A_wstr_ptr_p, const string& B_ref_p);
    inline friend boolean operator==(const string& A_ref_p, var::uchar* B_wstr_ptr_p);


    inline friend boolean operator!=(const string& A_ref_p, const string& B_ref_p);

    inline friend boolean operator!=(const char* A_cwstr_ptr_p, const string& B_ref_p);
    inline friend boolean operator!=(const string& A_ref_p, const char* B_cwstr_ptr_p);

    inline friend boolean operator!=(var::uchar* A_wstr_ptr_p, const string& B_ref_p);
    inline friend boolean operator!=(const string& A_ref_p, var::uchar* B_wstr_ptr_p);
};


END_NAMESPACE

#endif