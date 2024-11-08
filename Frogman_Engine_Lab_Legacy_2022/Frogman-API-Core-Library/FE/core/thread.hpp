#ifndef _FE_CORE_THREAD_HPP_
#define _FE_CORE_THREAD_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "runtime_exception.hpp"
#include "function.hxx"
#include <thread>


BEGIN_NAMESPACE(FE)


_MAYBE_UNUSED_ constexpr var::uint16 _MINIMUM_SUITABLE_THREAD_COUNT_ = 6;


class thread final
{
private:
	::std::thread m_thread;
	var::uint64 m_id;

public:
	typedef std::thread thread_type;
	typedef var::uint64 id_type;


	thread() noexcept;

	~thread() noexcept = default;


	thread(thread& other_ref_p) noexcept;


	thread(thread&& move_p) noexcept;


	thread& operator=(thread& other_ref_p) noexcept;


	thread& operator=(thread&& move_p) noexcept;


	var::uint64 get_id() const noexcept;
	var::boolean is_this_thread_active() noexcept;
	

	void fork(FE::task_base* const function_ptrc_p) noexcept;

	void fork(FE::task_base* const function_ptrc_p, void* const out_return_ptrc_p) noexcept;


	void join() noexcept;

	static void swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept;

	static var::uint64 calculate_suitable_thread_count() noexcept;

private:
	static var::uint64 __generate_id() noexcept;
};


END_NAMESPACE
#endif