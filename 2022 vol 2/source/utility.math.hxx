#ifndef _MATH_HXX_
#define _MATH_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.debug.h"
#include "core.types.h"




BEGIN_NAMESPACE(FE)


BEGIN_NAMESPACE(utility)


BEGIN_NAMESPACE(math)

template<typename T>
_FORCE_INLINE_ T select_greatest(const T& a_p, const T& b_p) noexcept
{
	if ( a_p > b_p )
	{
		return a_p;
	}

	return b_p;
}

template<typename T>
_FORCE_INLINE_ T select_smallest(const T& a_p, const T& b_p) noexcept
{
	if ( a_p < b_p )
	{
		return a_p;
	}

	return b_p;
}

// it compares two floating point values if they are within the tolerance range
_FORCE_INLINE_ boolean Is_it_nearly_equal(float64 A_p, float64 B_p, var::float64 tolerance_p)
{
	if ( tolerance_p < FE::_ACCURATE_VALUE_OF_MINIMUM_FLOAT_ )
	{
		tolerance_p = FE::_ACCURATE_VALUE_OF_MINIMUM_FLOAT_;
	}
	if ( A_p + tolerance_p >= B_p && B_p >= A_p - tolerance_p )
	{
		return true;
	}
	return false;
}

END_NAMESPACE


END_NAMESPACE


END_FE

#endif
#endif