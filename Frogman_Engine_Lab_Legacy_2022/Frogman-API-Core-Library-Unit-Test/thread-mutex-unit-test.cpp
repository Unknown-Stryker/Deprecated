#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/thread.hpp>
#include <FE/core/mutex.hpp>


void void_fn(int param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
}

int int_fn(int param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
	return param_p;
}


TEST(thread, fork_and_join)
{
	FE::thread l_thread;
	FE::one_arg<int> l_arg = 0;
	FE::void_function_with_1_arg<int> l_void_fn(void_fn, l_arg);
	l_thread.fork(&l_void_fn);
	l_thread.join();

	FE::function_with_1_arg<int, int> l_int_fn(int_fn, l_arg);
	int l_result;
	l_thread.fork(&l_int_fn, &l_result);
	l_thread.join();

	EXPECT_EQ(l_result, 0);
}

//TEST(thread, mutex)
//{
//
//}
//
//TEST(thread, timed_mutex)
//{
//
//}