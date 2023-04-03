// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once
#include <typeinfo>
#include <array>
using std::array;
#include <string>
using std::string;

const short NUMERIC_TYPES = 7;
const short MAX_DIGIT = 10;
const short TYPE_NAME_LENGTH = 12;
const short ASCIICODE = 48;
const short MAX_UNDER_DECIMAL_POINT = 10;

template <typename Any_Numeric_Data>
class Numeric
{
private:

	const array<string, 7> NumericDataType = { "short", "int", "long", "long long", "float", "double", "long double" };

	long long Digit;

	char NUMCHAR[MAX_DIGIT] = { '\0' };

	long long NUMBER[MAX_DIGIT];

public:

	Numeric() : Digit(0), NUMBER() {}

	bool Is_It_Numeric_DATA(Any_Numeric_Data Number_PARAM);

	long long GetDigit(Any_Numeric_Data Number_PARAM);

	long long* Seperate_Integer_Digits(long long Integer_PARAM/*, int*& Array_PARAM*/);

	// 정수와 실수 소수점 분리하기
	void SeperateNumber(long long& Integer, float& Float);
};



template<typename Any_Numeric_Data>
void  Numeric<Any_Numeric_Data>::SeperateNumber(long long& Integer, float& Float)
{
	float Floating_Point = 0.0f;
	array<char, MAX_UNDER_DECIMAL_POINT> DATA= { "\0" };
	array<int, MAX_UNDER_DECIMAL_POINT> Under_Decimal_Point = { 0 };

	//참조연산된 정수형 변수에 정수만 저장
	Integer = (long long)Float;
	Floating_Point = Float - (float)Integer;


	//참조연산된 부동소수형 변수에 소수점만 저장
	Float = Floating_Point * 1000000000;
}

template<typename Any_Numeric_Data>
bool Numeric<Any_Numeric_Data>::Is_It_Numeric_DATA(Any_Numeric_Data Number_PARAM)
{
	string TypeName = typeid(Number_PARAM).name();
	int WrongType = 0;

	for (int DataType = 0; DataType < NUMERIC_TYPES; DataType++)
	{
		if (NumericDataType[DataType] == TypeName)
		{
			return true;
		}
		else
		{
			++WrongType;
		}
	}
	if (WrongType == NUMERIC_TYPES)
	{
		return false;
	}
}


template<typename Any_Numeric_Data>
long long Numeric<Any_Numeric_Data>::GetDigit(Any_Numeric_Data Number_PARAM)
{
	long long Digit = 0;
	if (Is_It_Numeric_DATA(Number_PARAM) == true)
	{
		for (int count = 1; count < Number_PARAM; count *= 10)
		{
			++Digit;
		}
	}
	else
	{
		//cout << endl << "INVALID NUMERIC DATA TYPE!" << endl << "ERROR!" << endl;
		return -1;
	}
	return Digit;
}


template<typename Any_Numeric_Data>
long long* Numeric<Any_Numeric_Data>::Seperate_Integer_Digits(long long Integer_PARAM/*, int* &Array_PARAM*/)
{
	////맴버 정수 배열 NUMBER에 저장하기
	//Array_PARAM = new int[MAX_DIGIT];

	// 자료형이 숫자인지 검사한 후, 자리수 반환
	Digit = GetDigit(Integer_PARAM);

	//정수를  문자배열로 변환
	sprintf_s(NUMCHAR, "%d", Integer_PARAM);

	//정수 문자배열을 정수 배열에 자리수 분할 저장 
	for (long long index = 0; index < Digit; index++)
	{
		NUMBER[index] = (int)NUMCHAR[index] - ASCIICODE;

	}
	return NUMBER;
}