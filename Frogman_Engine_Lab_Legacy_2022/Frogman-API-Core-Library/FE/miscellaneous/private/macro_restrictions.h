﻿#ifndef _MACRO_RESTRICTIONS_H_
#define _MACRO_RESTRICTIONS_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../../core/types.h"


#if _VISUAL_STUDIO_CPP_ != 1 && _GNUC_ != 1 && _CLANG_ != 1
#error Frogman API requires Microsoft Visual Studio 2022 C++ v143, LLVM Clang, g++ 11 ,or latest g++ to compile. Please use one of these compilers.
#endif

#if _WINDOWS_64BIT_OS_ != 1 && _LINUX_64BIT_OS_ != 1
#error An Incompatible System Environment Detected: Frogman API supports Windows x86-64 and Linux(Ubuntu) x86-64. Please use one of them.
#endif

#ifdef __APPLE__
#error Apple platforms are not supported. Please use Windows x86-64 or Linux(Ubuntu) x84-64 Operating System.
#endif

#if _X64_ == 0
#error Frogman Engine only runs on X86-64 environments.
#endif


#ifdef FE
#error Frogman Engine API Prohibits macroizing the keyword "FE".
#endif
#ifdef var
#error Frogman Engine API Prohibits macroizing the keyword "var".
#endif

#ifdef const
#error Frogman Engine API Prohibits macroizing the keyword "const".
#endif
#ifdef constexpr
#error Frogman Engine API Prohibits macroizing the keyword "constexpr".
#endif

#ifdef nodiscard
#error Frogman Engine API Prohibits macroizing the keyword "nodiscard".
#endif
#ifdef likely
#error Frogman Engine API Prohibits macroizing the keyword "likely".
#endif
#ifdef unlikely
#error Frogman Engine API Prohibits macroizing the keyword "unlikely".
#endif
#ifdef fallthrough
#error Frogman Engine API Prohibits macroizing the keyword "fallthrough".
#endif
#ifdef maybe_unused
#error Frogman Engine API Prohibits macroizing the keyword "maybe_unused".
#endif
#ifdef noreturn
#error Frogman Engine API Prohibits macroizing the keyword "noreturn".
#endif
#ifdef deprecated
#error Frogman Engine API Prohibits macroizing the keyword "deprecated".
#endif


#ifdef max_value
#error Frogman Engine API Prohibits macroizing the keyword "max_value".
#endif

#ifdef min_value
#error Frogman Engine API Prohibits macroizing the keyword "min_value".
#endif

#ifdef _NULL_
#error Frogman Engine API Prohibits macroizing the keyword "_NULL_".
#endif

#ifdef _NULL_f_
#error Frogman Engine API Prohibits macroizing the keyword "_NULL_f_".
#endif

#ifdef _FOUND_
#error Frogman Engine API Prohibits macroizing the keyword "_FOUND_".
#endif

#ifdef _NOT_FOUND_
#error Frogman Engine API Prohibits macroizing the keyword "_NOT_FOUND_".
#endif

#ifdef _SUCCESSFUL_
#error Frogman Engine API Prohibits macroizing the keyword "_SUCCESSFUL_".
#endif

#ifdef _FAILED_
#error Frogman Engine API Prohibits macroizing the keyword "_FAILED_".
#endif


#ifdef boolean
#error Frogman Engine API Prohibits macroizing the keyword "boolean".
#endif

#ifdef schar
#error Frogman Engine API Prohibits macroizing the keyword "schar".
#endif
#ifdef uchar
#error Frogman Engine API Prohibits macroizing the keyword "uchar".
#endif
#ifdef wchar
#error Frogman Engine API Prohibits macroizing the keyword "wchar".
#endif
#ifdef char8
#error Frogman Engine API Prohibits macroizing the keyword "char8".
#endif
#ifdef char16
#error Frogman Engine API Prohibits macroizing the keyword "char16".
#endif
#ifdef char32
#error Frogman Engine API Prohibits macroizing the keyword "char32".
#endif

#ifdef float32
#error Frogman Engine API Prohibits macroizing the keyword "float32".
#endif
#ifdef float64
#error Frogman Engine API Prohibits macroizing the keyword "float64".
#endif

#ifdef binary
#error Frogman Engine API Prohibits macroizing the keyword "binary".
#endif
#ifdef sbyte
#error Frogman Engine API Prohibits macroizing the keyword "sbyte".
#endif
#ifdef ubyte
#error Frogman Engine API Prohibits macroizing the keyword "ubyte".
#endif
#ifdef int8
#error Frogman Engine API Prohibits macroizing the keyword "int8".
#endif
#ifdef uint8
#error Frogman Engine API Prohibits macroizing the keyword "uint8".
#endif
#ifdef int16
#error Frogman Engine API Prohibits macroizing the keyword "int16".
#endif
#ifdef uint16
#error Frogman Engine API Prohibits macroizing the keyword "uint16".
#endif
#ifdef int32
#error Frogman Engine API Prohibits macroizing the keyword "int32".
#endif
#ifdef uint32
#error Frogman Engine API Prohibits macroizing the keyword "uint32".
#endif
#ifdef int64
#error Frogman Engine API Prohibits macroizing the keyword "int64".
#endif
#ifdef uint64
#error Frogman Engine API Prohibits macroizing the keyword "uint64".
#endif

#ifdef size_t
#error Frogman Engine API Prohibits macroizing the keyword "size_t".
#endif
#ifdef length_t
#error Frogman Engine API Prohibits macroizing the keyword "length_t".
#endif
#ifdef index_t
#error Frogman Engine API Prohibits macroizing the keyword "index_t".
#endif
#ifdef count_t
#error Frogman Engine API Prohibits macroizing the keyword "count_t".
#endif

#ifdef object
#error Frogman Engine API Prohibits macroizing the keyword "object".
#endif

#ifdef T
#error Frogman Engine API Prohibits macroizing the keyword "T".
#endif
#ifdef U
#error Frogman Engine API Prohibits macroizing the keyword "U".
#endif
#ifdef integral_type
#error Frogman Engine API Prohibits macroizing the keyword "integral_type".
#endif
#ifdef string_type
#error Frogman Engine API Prohibits macroizing the keyword "string_type".
#endif

#ifdef ATOMIC_BYTE_PTR
#error Frogman Engine API Prohibits macroizing the keyword "ATOMIC_BYTE_PTR".
#endif
#ifdef BYTE_PTR
#error Frogman Engine API Prohibits macroizing the keyword "BYTE_PTR".
#endif
#ifdef WORD_PTR
#error Frogman Engine API Prohibits macroizing the keyword "WORD_PTR".
#endif
#ifdef DWORD_PTR
#error Frogman Engine API Prohibits macroizing the keyword "DWORD_PTR".
#endif
#ifdef QWORD_PTR
#error Frogman Engine API Prohibits macroizing the keyword "QWORD_PTR".
#endif

#ifdef auto_cast
#error Frogman Engine API Prohibits macroizing the keyword "auto_cast".
#endif

#ifdef exception
#error Frogman Engine API Prohibits macroizing the keyword "exception".
#endif
#ifdef handle_exceptions
#error Frogman Engine API Prohibits macroizing the keyword "handle_exceptions".
#endif

#endif