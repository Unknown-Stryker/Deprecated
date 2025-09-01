#pragma once
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved

#ifndef COMMON_DEFINITIONS
#define COMMON_DEFINITIONS true

#define constructors public
#define HIDDEN_constructors private
#define destructors public

#define HIDDEN_member_variables private
#define PROTECTED_member_variables protected

#define private_methods private
#define protected_methods protected
#define public_methods public

#define private_recursive private
#define protected_recursive protected
#define public_recursive public

#define HIDDEN_operators private
#define protected_operators protected
#define public_operators public

#define GETTERS public
#define SETTERS public

#define return_nullptr return nullptr
#define NULL_f 0.0f
#define exit_loop goto

#define ENUM enum struct
#define abstract_class class
#define abstract_struct struct
#define abstract_method = 0

#define private_implement : private
#define protected_implement : protected
#define public_implement : public

#define NODISCARD [[nodiscard]]
#define FALLTHROUGH [[fallthrough]]
#define MAYBE_UNUSED [[maybe_unused]]
#define NORETURN [[noreturn]]
#define DEPRECATED [[deprecated]]

#define WIN64_FROGMAN_main int main

#define STD using std
#define STL using std

// Frogman Fundamental Class Library
#define FROGMAN_FUNDAMENTAL_CLASS_LIBRARY namespace FFC

// Frogman Template Class Library
#define FROGMAN_TEMPLATE_CLASS_LIBRARY namespace FTC

#define TEMPLATE template <typename T>

// Classes and structs Provided by Frogman Engine Library
#define frogman_class class
#define frogman_struct struct


typedef unsigned long long index;
typedef unsigned long long length;
typedef unsigned long long hash;
typedef unsigned long long u_int_64;
typedef long double float_8_byte;


// etc

#define PERFORMANCE_BENCHMARKER FFC::time Clock
#define START_BENCHMARK Clock.start_clock()
#define END_BENCHMARK Clock.end_clock()
#define GET_BENCHMARKING_RESULT Clock.GET_delta_time()

//1000000
#define STRESS_TEST() for (index idx = 0; idx < 1000000; ++idx)

#define PRINT_ std::cout <<
#define INPUT_ std::cin >>

#endif
