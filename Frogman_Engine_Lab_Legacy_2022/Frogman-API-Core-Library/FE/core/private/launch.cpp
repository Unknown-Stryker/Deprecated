// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../private/launch.hpp"
#include "../private/configuration_deserializer.hpp"
#include "../runtime_exception.hpp"


thread_local FE::clock FE::main::tl_s_clock;

thread_local FE::var::boolean FE::main::tl_s_is_API_initialized = false;


// read serialized configuration file. 
void FE::main::initialize_API() noexcept
{
	if (tl_s_is_API_initialized == true) { abort(); }
	tl_s_is_API_initialized = true;

	atexit(at_shutdown);

	FE::exception::__construct_exception_on_main_thread();
}

void FE::main::at_shutdown() noexcept
{
	FE::exception::__destruct_exception();

#if _VISUAL_STUDIO_CPP_ == 1
	_CrtDumpMemoryLeaks();
#endif
}