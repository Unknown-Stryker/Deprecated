#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/cstring.hxx>




DECLARE_TEST_CLASS(FE, cstring);




TEST_FROGMAN_API(cstring, basic_cstring)
{
	FE::cstring::buffer_type l_buffer[] = "FE::basic_cstring is a compile-time string class template.";
	FE::cstring l_cstring = l_buffer;

	EXPECT_TRUE(l_cstring == l_buffer);
}

TEST_FROGMAN_API(cstring, constexpr_basic_cstring)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";

	EXPECT_TRUE(l_cstring == "FE::basic_cstring is a compile-time string class template.");
}




TEST_FROGMAN_API(cstring, constexpr_basic_cstring_copy_constructor)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";
	FE::cstring l_subject = l_cstring;

	EXPECT_TRUE(l_subject == l_cstring);
}


TEST_FROGMAN_API(cstring, constexpr_basic_cstring_move_constructor)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";
	FE::cstring l_subject = std::move(l_cstring);

	EXPECT_TRUE(l_subject == l_cstring);
}




TEST_FROGMAN_API(cstring, basic_cstring_assignment_operator)
{
	FE::cstring::buffer_type l_buffer[] = "FE::basic_cstring is a compile-time string class template.";

	FE::cstring l_cstring;
	l_cstring = l_buffer;

	EXPECT_TRUE(l_cstring == l_buffer);
}

TEST_FROGMAN_API(cstring, constexpr_basic_cstring_assignment_operator)
{
	FE::cstring l_cstring;
	l_cstring = "FE::basic_cstring is a compile-time string class template.";

	EXPECT_TRUE("FE::basic_cstring is a compile-time string class template." == l_cstring);
}




TEST_FROGMAN_API(cstring, constexpr_basic_cstring_copy_assignment_operator)
{
	FE::cstring::buffer_type l_buffer[] = "FE::basic_cstring is a compile-time string class template.";

	FE::cstring l_cstring;
	l_cstring = l_buffer;

	EXPECT_TRUE(l_cstring == l_buffer);
}

TEST_FROGMAN_API(cstring, constexpr_basic_cstring_move_assignment_operator)
{
	FE::cstring l_cstring;
	l_cstring = "FE::basic_cstring is a compile-time string class template.";

	FE::cstring l_subject;
	l_subject = std::move(l_cstring);

	EXPECT_TRUE(l_subject == l_cstring);
}




TEST_FROGMAN_API(cstring, basic_cstring_begin_end)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";
	FE::cstring::buffer_type l_buffer[60] = "\0";

	FE::var::index_t l_idx = 0;
	for (auto character = l_cstring.begin(); character != l_cstring.end(); ++character)
	{
		l_buffer[l_idx] = *character;
		++l_idx;
	}

	EXPECT_TRUE(l_cstring == l_buffer);
}




TEST_FROGMAN_API(cstring, basic_cstring_front_back)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";
	
	FE::cstring::buffer_type l_buffer[3] = "\0";
	FE::algorithm::string::concatenate_characters<FE::cstring::buffer_type>( l_buffer, 3, { l_cstring.front(), l_cstring.back() } );

	EXPECT_TRUE( ::FE::algorithm::string::strcmp(l_buffer, "F.") );
}




TEST_FROGMAN_API(cstring, basic_cstring_c_str)
{
	FE::cstring l_cstring = "FE::basic_cstring is a compile-time string class template.";

	EXPECT_TRUE( ::FE::algorithm::string::strcmp("FE::basic_cstring is a compile-time string class template.", l_cstring.c_str()) );
}




TEST_FROGMAN_API(cstring, basic_cstring_swap)
{
	FE::cstring l_first_cstring = "ABC";
	FE::cstring l_second_cstring = "CBA";

	FE::cstring::swap(l_first_cstring, l_second_cstring);

	EXPECT_TRUE(l_first_cstring == "CBA");
}