#pragma once
#ifndef COMMON_DEFINITIONS
#define COMMON_DEFINITIONS

// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved

#define DEBUG true
#if DEBUG == true
#include<iostream>
#endif

#define constructors public
#define protected_constructors protected
#define private_constructors private
#define destructor public

#define private_member_variables private
#define protected_member_variables protected

#define private_methods private
#define protected_methods protected
#define public_methods public

#define private_recursive private
#define protected_recursive protected
#define public_recursive public

#define private_operators private
#define protected_operators protected
#define public_operators public

#define GETTERS public
#define SETTERS public

#define NULL_f 0.0f
#define exit_loop goto

#define abstract_class class
#define abstract_struct struct
#define abstract_method = 0

#define private_inherit : private
#define protected_inherit : protected
#define public_inherit : public

#define public_factory_methods public

#define NODISCARD [[nodiscard]]
#define FALLTHROUGH [[fallthrough]]
#define MAYBE_UNUSED [[maybe_unused]]
#define NORETURN [[noreturn]]
#define DEPRECATED [[deprecated]]

#define Windows64_FROGMAN_main int main

#define FROGMAN_FUNDAMENTAL_CLASS_LIBRARY namespace FFC
#define FROGMAN_TEMPLATE_CLASS_LIBRARY namespace FTC

#define FROGMAN_FUNDAMENTAL_STRUCT_LIBRARY namespace FFS
#define FROGMAN_TEMPLATE_STRUCT_LIBRARY namespace FTS

#define FROGMAN_FUNDAMENTAL_FUNCTION_LIBRARY namespace FFF
#define FROGMAN_TEMPLATE_FUNCTION_LIBRARY namespace FTF

#define FROGMAN_DESIGN_PATTERN_LIBRARY namespace FDP

#define FROGMAN_FUNDAMENTAL_ENUM_LIBRARY namespace FFE

// Classes and structs Provided by Frogman Engine Library
#define frogman_fundamental_class class
#define frogman_fundamental_struct struct
#define frogman_abstract_class class
#define frogman_abstract_struct struct
#define frogman_design_pattern_class class
#define frogman_design_pattern_struct struct
#define frogman_enum enum struct
#define internal_class class
#define internal_struct struct

typedef unsigned long long index;
typedef unsigned long long length;
typedef unsigned long long hash;
typedef unsigned short thread_id;
typedef unsigned short thread_idx;
typedef long double float_8_byte;
typedef unsigned long long seconds_in_integer;
typedef long double seconds_in_float;
typedef unsigned long long decimal;
typedef const unsigned short ASCII;
typedef unsigned long long u_int_64;
typedef long long int_64;
typedef unsigned int u_int_32;
typedef int int_32;
typedef unsigned short u_int_16;
typedef short int_16;

#define PERFORMANCE_BENCHMARKER FFC::time Clock
#define START_BENCHMARK Clock.start_clock()
#define END_BENCHMARK Clock.end_clock()
#define GET_BENCHMARKING_RESULT Clock.GET_delta_time()

#define PRINT_ std::cout <<
#define INPUT_ std::cin >>
#define _ENDL << std::endl

#endif
