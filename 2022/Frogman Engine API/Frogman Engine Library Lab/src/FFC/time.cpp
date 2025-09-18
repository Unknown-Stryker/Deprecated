// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved
#include "time.hpp"
using fstd::time;




_FORCE_INLINE_ time::time() noexcept : m_delta_time()
{
}


_FORCE_INLINE_ void time::start_clock() noexcept
{
    this->m_starting_point = std::chrono::high_resolution_clock::now();
}

_FORCE_INLINE_ void time::end_clock() noexcept
{
    this->m_ending_point = std::chrono::high_resolution_clock::now();
}

_FORCE_INLINE_ fstd::float64 time::delta_time() noexcept
{
    this->m_delta_time = this->m_ending_point - this->m_starting_point;
    return this->m_delta_time.count();
}