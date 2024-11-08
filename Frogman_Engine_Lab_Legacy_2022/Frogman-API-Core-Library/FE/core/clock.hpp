#ifndef _FE_CORE_CLOCK_HPP_
#define _FE_CORE_CLOCK_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <chrono>
#include <memory>
#include "prerequisite_symbols.h"


BEGIN_NAMESPACE(FE)


// const char* FE::clock::get_current_local_time() noexcept;
_MAYBE_UNUSED_ constexpr auto _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_ = 70;


class clock final
{
public:
    typedef char char_type;

private:
    std::chrono::steady_clock::time_point m_starting_point;
    std::chrono::steady_clock::time_point m_ending_point;
    std::chrono::duration<var::float64> m_delta_time;
    thread_local static std::unique_ptr<char_type[]> tl_s_current_time;

public:
    clock() noexcept : m_starting_point(), m_ending_point(), m_delta_time() {}
    ~clock() noexcept = default;

    void start_clock() noexcept;

    void end_clock() noexcept;

    var::float64 get_delta_time() noexcept;

    const char_type* get_current_local_time() noexcept;
};


END_NAMESPACE
#endif