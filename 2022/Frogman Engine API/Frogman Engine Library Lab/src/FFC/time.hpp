#pragma once
#ifndef _TIME_HPP_
#define _TIME_HPP_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved
#include "../../config/types.h"
#include <chrono>




BEGIN NAMESPACE(fstd)


// A Class that has an Ability to Force a Thread to Sleep for the  Certain Amount of Time
class time final
{
member_variables:
    std::chrono::steady_clock::time_point m_starting_point;
    std::chrono::steady_clock::time_point m_ending_point;
    std::chrono::duration<var::float64> m_delta_time;

constructors:
        _FORCE_INLINE_ time() noexcept;

methods:
        _FORCE_INLINE_ void start_clock() noexcept;
        _FORCE_INLINE_ void end_clock() noexcept;
        _FORCE_INLINE_ float64 delta_time() noexcept;
};

#define PERFORMANCE_BENCHMARKER fstd::time Clock
#define START_BENCHMARK Clock.start_clock()
#define END_BENCHMARK Clock.end_clock()
#define GET_BENCHMARKING_RESULT Clock.delta_time()

END_FSTD


#endif