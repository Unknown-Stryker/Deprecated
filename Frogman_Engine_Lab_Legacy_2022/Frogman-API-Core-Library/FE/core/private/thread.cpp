﻿// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../thread.hpp"
#include "../algorithm/sort.hxx"
#include "../runtime_exception.hpp"


::FE::thread::thread() noexcept : m_id(__generate_id()) {}

::FE::thread::thread(thread& other_ref_p) noexcept : m_thread(::std::move(other_ref_p.m_thread)), m_id(std::move(other_ref_p.m_id)) { other_ref_p.m_id = 0; }

::FE::thread::thread(thread&& move_p) noexcept : m_thread(::std::move(move_p.m_thread)), m_id(std::move(move_p.m_id)) { move_p.m_id = 0; }

::FE::thread& FE::thread::operator=(thread& other_ref_p) noexcept
{
	this->m_thread = ::std::move(other_ref_p.m_thread);
	this->m_id = ::std::move(other_ref_p.m_id);
	other_ref_p.m_id = 0;
	return *this;
}

::FE::thread& FE::thread::operator=(thread&& move_p) noexcept
{
	this->m_thread = ::std::move(move_p.m_thread);
	this->m_id = ::std::move(move_p.m_id);
	move_p.m_id = 0;
	return *this;
};

::FE::var::uint64 FE::thread::get_id() const noexcept
{
	return this->m_id;
}

::FE::var::boolean FE::thread::is_this_thread_active() noexcept
{
	return this->m_thread.joinable();
}

void FE::thread::fork(FE::task_base* const function_ptrc_p) noexcept
{
	this->m_thread = ::std::thread
	(
		[&, function_ptrc_p]()
		{
			::FE::exception::__construct_exception(*this);
			_DISCARD_ auto l_ignore_nodiscard_ = function_ptrc_p->execute();
			::FE::exception::__destruct_exception();
		}
	);
}

void FE::thread::fork(FE::task_base* const function_ptrc_p, void* const out_return_ptrc_p) noexcept
{
	this->m_thread = ::std::thread
	(
		[&, function_ptrc_p, out_return_ptrc_p]()
		{
			::FE::exception::__construct_exception(*this);
			auto l_is_void = function_ptrc_p->execute(out_return_ptrc_p);
			::FE::exception::__destruct_exception();
			FE_ASSERT(l_is_void == FE::RETURN_TYPE::_VOID && out_return_ptrc_p != nullptr, "ERROR: a non-void function assigned to a void-return-type task object.", _ASSERTED_LOCATION_);
		}
	);
}

void FE::thread::join() noexcept
{
	this->m_thread.join();
}

void FE::thread::swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept
{
	::std::swap(left_thread_ref_p.m_thread, right_thread_ref_p.m_thread);
	::FE::algorithm::sort::swap(left_thread_ref_p.m_id, right_thread_ref_p.m_id);
}

::FE::var::uint64 FE::thread::calculate_suitable_thread_count() noexcept
{
	
	if ( ((::std::thread::hardware_concurrency() >> 1) + (::std::thread::hardware_concurrency() / 8)) < _MINIMUM_SUITABLE_THREAD_COUNT_)
	{
		return _MINIMUM_SUITABLE_THREAD_COUNT_;
	}

	return (::std::thread::hardware_concurrency() >> 1) + (::std::thread::hardware_concurrency() / 8);
}

::FE::var::uint64 FE::thread::__generate_id() noexcept
{
	static var::uint64 l_s_id = 0;

	return ++l_s_id;
}