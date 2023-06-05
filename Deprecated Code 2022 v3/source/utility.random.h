#ifndef _RANDOM_H_
#define _RANDOM_H_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.types.h"
#include <random>




BEGIN_NAMESPACE(FE)


BEGIN_NAMESPACE(utility)


_FORCE_INLINE_ uint16 ranged_random_uint16(uint16 min_range_p, uint16 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::uint16> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}

_FORCE_INLINE_ int16 ranged_random_int16(int16 min_range_p, int16 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::int16> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}


_FORCE_INLINE_ uint32 ranged_random_uint32(uint32 min_range_p, uint32 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::uint32> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}

_FORCE_INLINE_ int32 ranged_random_int32(int32 min_range_p, int32 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::int32> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}


_FORCE_INLINE_ uint64 ranged_random_uint64(uint64 min_range_p, uint64 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::uint64> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}

_FORCE_INLINE_ int64 ranged_random_int64(int64 min_range_p, int64 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_int_distribution<var::int64> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}


_FORCE_INLINE_ float32 ranged_random_float32(float32 min_range_p, float32 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_real_distribution<var::float32> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}

_FORCE_INLINE_ float64 ranged_random_float64(float64 min_range_p, float64 max_range_p) noexcept
{
	std::mt19937_64 l_rand((var::uint64)time(NULL));

	std::uniform_real_distribution<var::float64> l_ranged_random_value(min_range_p, max_range_p);

	return l_ranged_random_value(l_rand);
}

END_NAMESPACE

END_FE

#endif
#endif