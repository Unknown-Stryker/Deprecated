#ifndef _FE_CORE_MOVABLE_SCOPED_REF_HXX_
#define _FE_CORE_MOVABLE_SCOPED_REF_HXX_
#pragma warning(disable:4390)
#include "prerequisite_symbols.h"
#include "runtime_exception.hpp"


BEGIN_NAMESPACE(FE::concurrency)
using IN_USE = FE::atomic_volatile<bool>;
END_NAMESPACE


BEGIN_NAMESPACE(FE)


template <typename T>
class movable_scoped_ref
{
	T* m_data_ptr;
	concurrency::IN_USE* m_signal_ptr;

public:
	using value_type = T;
	using flag_type = concurrency::IN_USE*;


	constexpr movable_scoped_ref() noexcept : m_data_ptr() {};
	movable_scoped_ref(T* const data_ptrc_p, concurrency::IN_USE* const signal_ptr_p, bool value_for_is_being_used_p) noexcept : m_data_ptr(data_ptrc_p)
	{
		signal_ptr_p->store(value_for_is_being_used_p, std::memory_order_release);
		this->m_signal_ptr = signal_ptr_p;
	}


	~movable_scoped_ref() noexcept
	{
		if (this->m_signal_ptr == nullptr) { return; }

		this->m_signal_ptr->store(false, std::memory_order_release);
	}


	movable_scoped_ref(const movable_scoped_ref& other_cref_p) noexcept = delete;


	movable_scoped_ref(movable_scoped_ref&& rvalue_p) noexcept : m_data_ptr(rvalue_p.m_data_ptr), m_signal_ptr(rvalue_p.m_signal_ptr)
	{
		rvalue_p.m_signal_ptr = nullptr;
		rvalue_p.m_data_ptr = nullptr;
	}


	movable_scoped_ref& operator=(const movable_scoped_ref& other_cref_p) noexcept = delete;


	movable_scoped_ref& operator=(movable_scoped_ref&& rvalue_p) noexcept
	{
		this->m_signal_ptr = rvalue_p.m_signal_ptr;
		rvalue_p.m_signal_ptr = nullptr;
		this->m_data_ptr = rvalue_p.m_data_ptr;
		rvalue_p.m_data_ptr = nullptr;
		return *this;
	}


	var::boolean is_being_used() noexcept
	{
		return (this->m_signal_ptr == nullptr) ? _FAILED_ : this->m_signal_ptr->load(std::memory_order_relaxed);
	}

	var::boolean stop_using() noexcept
	{
		if (FE::exception::handle_exceptions(this->m_signal_ptr == nullptr, FE::_LOG_EXCEPTION_HISTORY_, "WARNING: The signal pointer is nullptr. This function will return early with false.", _EXCEPTION_ORIGIN_))
#if _HAS_CXX20_
			_LIKELY_
#endif
		{ return _FAILED_; }

		this->m_signal_ptr->store(false, std::memory_order_release);
		return _SUCCESSFUL_;
	}

	T& operator*() noexcept
	{
		FE::exception::handle_exceptions(this->m_signal_ptr == nullptr, FE::_ABORT_IMMEDIATELY_, "ERROR: The signal pointer is nullptr. Failed to acquire the data.", _EXCEPTION_ORIGIN_);
		return *this->m_data_ptr;
	}
};


END_NAMESPACE

#endif // !_FE_CORE_SIGNAL_HXX_
