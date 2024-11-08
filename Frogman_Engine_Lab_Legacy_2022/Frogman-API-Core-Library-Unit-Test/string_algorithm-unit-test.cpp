#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/algorithm/string.hxx>




TEST(FE_algorithm_string, ascii_number_to_integer)
{
	char l_buffer[10] = "2023";
	::FE::int32 l_result = ::FE::algorithm::string::ascii_number_to_integer<char, ::FE::var::int32>(l_buffer);

	EXPECT_EQ(2023, l_result);
}

TEST(FE_algorithm_string, constexpr_ascii_number_to_integer)
{
	::FE::int32 l_result = ::FE::algorithm::string::ascii_number_to_integer<char, ::FE::var::int32>("2023");

	EXPECT_EQ(2023, l_result);
}




TEST(FE_algorithm_string, strlen)
{
	char l_buffer[126] = "FE::algorithm::string::strlen is a templated function that provides more functionalities than the traditional C-style strlen.";

	::FE::int64 l_result = ::FE::algorithm::string::strlen<char>(l_buffer);

	EXPECT_EQ(125, l_result);
}

TEST(FE_algorithm_string, constexpr_strlen)
{
	::FE::int64 l_result = ::FE::algorithm::string::strlen<::FE::var::wchar>(L"FE::algorithm::string::strlen is a templated function that provides more functionalities than the traditional C-style strlen.");

	EXPECT_EQ(125, l_result);
}




TEST(FE_algorithm_string, strcmp)
{
	char l_first_string[20] = "American";
	char l_second_string[20] = "British";

	EXPECT_TRUE( !::FE::algorithm::string::strcmp(l_first_string, l_second_string) );
}

TEST(FE_algorithm_string, constexpr_strcmp)
{
	EXPECT_TRUE( ::FE::algorithm::string::strcmp(L"Jesus Loves You", L"Jesus Loves You") );
}




TEST(FE_algorithm_string, strcpy)
{
	char l_string[20] = "\n";

	::FE::algorithm::string::strcpy(l_string, 20, "Hi, World", ::FE::algorithm::string::strlen("Hi, World"));

	EXPECT_TRUE( ::FE::algorithm::string::strcmp(l_string, "Hi, World") );
}




TEST(FE_algorithm_string, strcat)
{
	char l_string[50] = "Boost Libraries are ";
	::FE::algorithm::string::strcat( l_string, 50, "written in C++.", ::FE::algorithm::string::strlen("written in C++.") );

	EXPECT_TRUE( ::FE::algorithm::string::strcmp("Boost Libraries are written in C++.", l_string) );
}




TEST(FE_algorithm_string, UPPERCASE)
{
	std::string l_string = "experience our british premium bottle of water!";

	::FE::algorithm::string::UPPERCASE<std::string::value_type, std::string>(l_string);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string.c_str(), "EXPERIENCE OUR BRITISH PREMIUM BOTTLE OF WATER!"));
}




TEST(FE_algorithm_string, lowercase)
{
	std::string l_string = "EXPERIENCE OUR KOREAN PREMIUM KIMCHI!";

	::FE::algorithm::string::lowercase<std::string::value_type, std::string>(l_string);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string.c_str(), "experience our korean premium kimchi!"));
}




TEST(FE_algorithm_string, capitalize_every_first_letter_of_words)
{
	std::string l_string = "experience the speed of light!";

	::FE::algorithm::string::capitalize_every_first_letter_of_words<std::string::value_type, std::string>(l_string);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string.c_str(), "Experience The Speed Of Light!"));
}




TEST(FE_algorithm_string, invert_string)
{
	std::string l_string = "!hatU fo ytisrevinU ehT";

	::FE::algorithm::string::invert_string<std::string::value_type, std::string>(l_string);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string.c_str(), "The University of Utah!"));
}




TEST(FE_algorithm_string, constexpr_hash_code)
{
	const char* l_cstring = "A bottle of water.";

	switch (FE::algorithm::string::hash_code(l_cstring))
	{
	case FE::algorithm::string::hash_code("A bottle of water."):
		EXPECT_TRUE(true);
		break;

	case FE::algorithm::string::hash_code("A bucket of milk."):
		EXPECT_TRUE(false);
		break;

	case FE::algorithm::string::hash_code("A cup of coke."):
		EXPECT_TRUE(false);
		break;

	default:
		EXPECT_TRUE(false);
		break;
	}
}




TEST(FE_algorithm_string, find_a_character)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::find_a_character(l_string, 't');

	EXPECT_EQ(l_result.first, 7);
	EXPECT_EQ(l_result.second, 't');
}

TEST(FE_algorithm_string, constexpr_find_a_character)
{
	const char* l_string = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::find_a_character(l_string, 't');

	EXPECT_EQ(l_result.first, 7);
	EXPECT_EQ(l_result.second, 't');
}




TEST(FE_algorithm_string, find_letters)
{
	char l_string[] = "The World's Top game software engineering program is the University of Utah's Entertainment, Arts, and Engineering.";

	auto l_result = ::FE::algorithm::string::find_letters(l_string, "Utah");

	EXPECT_TRUE(l_result);
}

TEST(FE_algorithm_string, constexpr_find_letters)
{
	const char* l_string = "Jesus is the son of GOD";

	auto l_result = ::FE::algorithm::string::find_letters(l_string, "son");

	EXPECT_TRUE(l_result);
}




TEST(FE_algorithm_string, ascii_character_number_to_int)
{
	auto l_result = ::FE::algorithm::string::ascii_character_number_to_int<char, int>('1');

	EXPECT_EQ(l_result, 1);
}




TEST(FE_algorithm_string, concatenate_strings)
{
	char l_string_buffer[100] = "Today is";
	::FE::algorithm::string::concatenate_strings
	(
		l_string_buffer,
		100,
		{
			" May", " Fourteenth", " 2023."
		}
	);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string_buffer, "Today is May Fourteenth 2023."));
}




TEST(FE_algorithm_string, concatenate_characters)
{
	char l_string_buffer[10] = "M";
	::FE::algorithm::string::concatenate_characters
	(
		l_string_buffer,
		10,
		{
			'e', 'l', 'o', 'n'
		}
	);

	EXPECT_TRUE(::FE::algorithm::string::strcmp(l_string_buffer, "Melon"));
}
