#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.types.h"
#include <chrono>
#include <ctime>



BEGIN_NAMESPACE(FE)


BEGIN_NAMESPACE(utility)

// A Class that has an Ability to Force a Thread to Sleep for the  Certain Amount of Time
class clock final
{
member_variables:
    std::chrono::steady_clock::time_point m_starting_point;
    std::chrono::steady_clock::time_point m_ending_point;
    std::chrono::duration<var::float64> m_delta_time;

methods:
    _FORCE_INLINE_ void start_clock() noexcept 
    { 
        this->m_starting_point = std::chrono::steady_clock::now(); 
    }

    _FORCE_INLINE_ void end_clock() noexcept 
    { 
        this->m_ending_point = std::chrono::steady_clock::now();
    }

    _FORCE_INLINE_ auto get_delta_time() noexcept
    {
        this->m_delta_time = this->m_ending_point - this->m_starting_point;
        return this->m_delta_time.count();
    }
};

END_NAMESPACE

END_FE

#endif
#endif