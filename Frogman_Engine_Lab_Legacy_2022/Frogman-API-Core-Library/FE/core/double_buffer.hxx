#ifndef _FE_CORE_DOUBLE_BUFFER_HXX_
#define _FE_CORE_DOUBLE_BUFFER_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "private/memory.hxx"



BEGIN_NAMESPACE(FE::memory)


template <typename T, class padding_size = FE::memory::align_null>
class double_buffer final
{
private:
	alignas(padding_size::s_size) T m_read_only;
	alignas(padding_size::s_size) T m_write_only;

public:
	typedef T value_type;
	typedef padding_size alignment_type;

	_FORCE_INLINE_ double_buffer() noexcept = default;
	_FORCE_INLINE_ double_buffer(const T& input_ref_p) noexcept : m_read_only(input_ref_p), m_write_only(input_ref_p) {}

	_FORCE_INLINE_ ~double_buffer() noexcept = default;


	_FORCE_INLINE_ void apply_next() noexcept
	{
		this->m_read_only = this->m_write_only;
	}

	_FORCE_INLINE_ const T& read_buffer() const noexcept
	{
		return this->m_read_only;
	}

	_FORCE_INLINE_ void write_buffer(const T& input_ref_p) noexcept
	{
		this->m_write_only = input_ref_p;
	}
};


END_NAMESPACE

#endif