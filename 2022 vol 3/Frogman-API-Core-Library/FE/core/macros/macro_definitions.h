#ifndef _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
#define _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


#define abstract_class class
#define internal_class class
#define internal_struct struct


#define _EXIT_LOOP_ goto


#define BEGIN_NAMESPACE(NAME_P) namespace NAME_P {
#define END_NAMESPACE }


#define FORWARD_CLASS_DECLARATION(namespace_p, class_p) namespace namespace_p { class class_p; }
#define FORWARD_STRUCT_DECLARATION(namespace_p, struct_p) namespace namespace_p { struct struct_p; }

#define FORWARD_ENUM_STRUCT_DECLARATION(namespace_p, enum_struct_p) namespace namespace_p { enum struct enum_struct_p; }


#ifdef _WIN64
#define _WINDOWS_64BIT_OS_ 1
#else
#define _WINDOWS_64BIT_OS_ 0
#endif


#ifdef __linux__
#define _LINUX_64BIT_OS_ 1
#else
#define _LINUX_64BIT_OS_ 0
#endif


#if _MSC_VER > 1
#define _VISUAL_STUDIO_CPP_ 1
#else
#define _VISUAL_STUDIO_CPP_ 0
#endif

#ifdef __clang__
#define _CLANG_ 1
#else
#define _CLANG_ 0
#endif

#ifdef __GNUC__
#define _GNUC_ 1
#else
#define _GNUC_ 0
#endif


#ifdef __x86_64

#define _X64_ 1

#elif defined(_M_X64)

#define _X64_ 1

#elif defined(_M_AMD64)

#define _X64_ 1

#else

#define _X64_ 0

#endif

#endif


#if _CLANG_ == 1 || _GNUC_ == 1
#define _FORCE_INLINE_ inline
#define _STDCALL_ __cdecl
#elif _VISUAL_STUDIO_CPP_ == 1
#define _STDCALL_ __stdcall
#define _FORCE_INLINE_ __forceinline
#endif


#define _FASTCALL_ __fastcall
#define _CDECL_ __cdecl
#define _FE_EXCEPT_ noexcept


#if _VISUAL_STUDIO_CPP_ == 1
#include <vcruntime.h>
#endif


#define _HAS_CXX23_ _HAS_CXX23
#define _HAS_CXX20_ _HAS_CXX20
#define _HAS_CXX17_ _HAS_CXX17