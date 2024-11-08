#ifndef _FE_CORE_RUNTIME_EXCEPTION_HPP_
#define _FE_CORE_RUNTIME_EXCEPTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "private/runtime_exception_enum_structs.h"
#include "prerequisite_symbols.h"
#include <memory>


BEGIN_NAMESPACE(FE)

class thread;

class clock;


class exception final
{
public:
    typedef char char_type;

    friend class main;
    friend class ::FE::thread;
    
private:
    thread_local static ::std::ofstream tl_s_exception_reporter;
    thread_local static ::FE::clock tl_s_clock;
    thread_local static ::std::unique_ptr<char_type[]> tl_s_full_debug_info_buffer;
    thread_local static ::std::unique_ptr<char_type[]> tl_s_source_code_line_info_buffer;

public:
    static bool handle_exceptions(const bool expression_p, const EXCEPTION_MODE runtime_exception_mode_p, const char_type* message_ptr_p, const char_type* file_name_ptr_p, const char_type* function_name_ptr_p, const int line_p, const int exit_code_p = -1) noexcept;

private:
    static void __construct_exception_on_main_thread() noexcept;
    static void __destruct_exception() noexcept;
	static void __construct_exception(::FE::thread& thread_ref_p) noexcept;
};


#define FE_ASSERT(expression_p, message_p, asserted_location_p) ::FE::exception::handle_exceptions(expression_p, FE::_ABORT_IMMEDIATELY_, message_p, asserted_location_p)
#define _ASSERTED_LOCATION_ _EXCEPTION_ORIGIN_

END_NAMESPACE
#endif
