#pragma once
#ifndef _DOUBLE_BUFFER_HXX_
#define _DOUBLE_BUFFER_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved
#include "../../config/types.h"




BEGIN NAMESPACE( fstd )


template <typename T>	
class double_buffer final
{
member_variables:
	T m_read_only;
	T m_write_only;

constructors:
	double_buffer() noexcept {}
	double_buffer(const T& input_ref_p) noexcept : m_read_only(input_ref_p), m_write_only(input_ref_p) {}

methods:
	void apply_next() noexcept;
	const T& read_buffer() const noexcept;
	void write_buffer(const T& input_ref_p) noexcept;
};


template<typename T>
inline void double_buffer<T>::apply_next() noexcept
{
		this->m_read_only = this->m_write_only;
}

template<typename T>
inline const T& double_buffer<T>::read_buffer() const noexcept
{
	return this->m_read_only;
}

template<typename T>
inline void double_buffer<T>::write_buffer(const T& input_ref_p) noexcept
{
	this->m_write_only = input_ref_p;
}


END_FSTD


#endif // !
