#ifndef _FE_CORE_LAUNCH_HPP_
#define _FE_CORE_LAUNCH_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../clock.hpp"


BEGIN_NAMESPACE(FE)

constexpr auto _MAIN_THREAD_ID_ = -1;

class main
{
	thread_local static FE::clock tl_s_clock;
	thread_local static var::boolean tl_s_is_API_initialized;

public:
	//NOTE: DO NOT MANUALLY CALL THIS FUNCTION FROM OUTSIDE OF int main();
	static void initialize_API() noexcept;
	static void at_shutdown() noexcept;
};


END_NAMESPACE

#endif // 