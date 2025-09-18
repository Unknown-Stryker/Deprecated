#pragma once
#ifndef _WSTRING_HPP_
#define _WSTRING_HPP_
#define _ENGLISH_ONLY_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "../../config/types.h"




BEGIN NAMESPACE(fstd)
    

class wstring
{
member_variables:
    var::wchar* m_wstring_ptr;
    var::uint32 m_wstring_length;
    var::uint32 m_wstring_total_length;

    var::uint32 m_capacity;
    var::uint32 m_capacity_divider;

    var::wchar m_null;

constructors:
    wstring() noexcept;

destructor:
    ~wstring() noexcept;

constructors:
    wstring(var::wchar* move_wstr_ptr_p) noexcept;
    wstring(wchar* copy_cwstr_ptr_p) noexcept;

copy_constructor:
    wstring(const wstring& copy_other_ref_p) noexcept; 

move_constructor:
    wstring(wstring&& move_p) noexcept;

assignment_operator:
    wstring& operator=(var::wchar* move_wstr_ptr_p) noexcept;
    wstring& operator=(wchar* copy_cwstr_ptr_p) noexcept;
    
copy_assignment_operator:
    wstring& operator=(const wstring& copy_other_ref_p) noexcept; 

move_assignment_operator:
    wstring& operator=(wstring&& move_p) noexcept; 

methods:
    wchar* begin() const noexcept;
    wchar* end() const noexcept;

    uint32 length() const noexcept;
    uint32 total_length() const noexcept;
    uint32 capacity() const noexcept;
    uint32 max_length() const noexcept { return _UINT32_MAX_LENGTH_; }

    void set_capacity_by_percent(uint32 percent_p) noexcept;
    uint32 get_capacity_by_percent() const noexcept;

    void reserve(uint32 length_p) noexcept;
    void resize(uint32 length_p) noexcept;

    void clear_all() noexcept;
    void erase(uint32 index_p) noexcept;
    boolean is_it_empty() const noexcept;
    void shrink_to_fit() noexcept;

operators:
    var::wchar& operator[](uint32 index_p) noexcept;

methods:
    wchar front() const noexcept;
    wchar back() const noexcept;

operators:
    uint32 operator+=(wchar wchar_p) noexcept;
    uint32 operator+=(var::wchar* copy_str_ptr_p) noexcept;
    uint32 operator+=(wchar* copy_cwstr_ptr_p) noexcept;
    uint32 operator+=(const wstring& copy_str_ref_p) noexcept;

methods:
    void insert(uint32 index_p, var::wchar* copy_wstr_ptr_p) noexcept;
    void insert(uint32 index_p, wchar* copy_cwstr_ptr_p) noexcept;
    void insert(uint32 index_p, const wstring& copy_str_ref_p) noexcept;
    wchar pop_back() noexcept;

    _NODISCARD_ var::uchar* copy_string() const noexcept;
    _NODISCARD_ wchar* copy_wstring() const noexcept;

    static void swap(wstring& A_ref_p, wstring& B_ref_p) noexcept;
    void print() const noexcept;
    void println() const noexcept;

    _ENGLISH_ONLY_ void UPPERCASE() noexcept;
    _ENGLISH_ONLY_ void lowercase() noexcept;
    void delete_spaces() noexcept;
    _ENGLISH_ONLY_ void capitalize_all_the_first_letter_of_words() noexcept;
    void invert_string() noexcept;
    _DEPRECATED_ _NODISCARD_ fstd::wstring* extract_words_from_string() const noexcept;
    _NODISCARD_ var::wchar* extract_letters_from_string(uint32 A_p, uint32 Z_p) const noexcept;
    uint64 hash_code() noexcept;

operators:
    inline friend boolean operator==(const wstring& A_ref_p, const wstring& B_ref_p) noexcept;

    inline friend boolean operator==(wchar* A_cwstr_ptr_p, const wstring& B_ref_p) noexcept;
    inline friend boolean operator==(const wstring& A_ref_p, wchar* B_cwstr_ptr_p ) noexcept;

    inline friend boolean operator==(var::wchar* A_wstr_ptr_p, const wstring& B_ref_p) noexcept;
    inline friend boolean operator==(const wstring& A_ref_p, var::wchar* B_wstr_ptr_p) noexcept;


    inline friend boolean operator!=(const wstring& A_ref_p, const wstring& B_ref_p) noexcept;

    inline friend boolean operator!=(wchar* A_cwstr_ptr_p, const wstring& B_ref_p) noexcept;
    inline friend boolean operator!=(const wstring& A_ref_p, wchar* B_cwstr_ptr_p) noexcept;

    inline friend boolean operator!=(var::wchar* A_wstr_ptr_p, const wstring& B_ref_p) noexcept;
    inline friend boolean operator!=(const wstring& A_ref_p, var::wchar* B_wstr_ptr_p) noexcept;
};

END_FSTD

#endif