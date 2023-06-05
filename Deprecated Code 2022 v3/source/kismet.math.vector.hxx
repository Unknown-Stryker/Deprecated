#ifndef _VECTOR_HXX_
#define _VECTOR_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.debug.h"
#include "core.types.h"




BEGIN_NAMESPACE(FE)

BEGIN_NAMESPACE(kismet)

BEGIN_NAMESPACE(math)


template<typename T>
struct vector_2D
{
field_variables:
	T _x;
	T _y;

constructors:
	vector_2D() noexcept;
};

template<typename T>
vector_2D<T>::vector_2D() noexcept : _x(), _y()
{
	static_assert( sizeof(T) <= 16, "T is not a valid numeric type" );
}




template<typename T>
struct vector
{
field_variables:
	T _x;
	T _y;
	T _z;

constructors:
	vector() noexcept;
};

template<typename T>
vector<T>::vector() noexcept : _x(), _y(), _z()
{
	static_assert( sizeof(T) <= 16, "T is not a valid numeric type" );
}


END_NAMESPACE;

END_NAMESPACE;

// an integral second dimensional vector
using ivector_2D = kismet::math::vector_2D<var::int64>;

// a floating point second dimensional vector
using fvector_2D = kismet::math::vector_2D<var::float128>;

// an integral third dimensional vector
using ivector = kismet::math::vector<var::int64>;

// a floating point third dimensional vector
using fvector = kismet::math::vector<var::float128>;

END_FE

#endif
#endif