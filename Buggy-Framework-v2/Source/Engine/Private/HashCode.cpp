// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#include "../Public/HashCode.h"



HashCode::HashCode()
{
}

HashCode::~HashCode()
{
}


void HashCode::StoreHashCode(long long ObjectHashCode)
{
	for (auto iterator : HashCodeWarehouse)
	{
		if (HashCodeWarehouse[iterator] == 0)
		{
			HashCodeWarehouse[iterator] = ObjectHashCode;
			return;
		}
	}

	this->HashCodeWarehouse.push_back(ObjectHashCode);
}

unsigned long long HashCode::StrToInt(const string str)
{
	//Get Length Of a String
	unsigned long long length = 0;
	for (; str[length] != '\0'; ++length) {}

	//Convert String into Integer Value
	unsigned long long CODE = 0;
	for (unsigned long long i = 0; i < length; ++i)
	{
		CODE = CODE + ((unsigned long long)str[i] * (i + 1));
	}
	return CODE;
}


unsigned long long* HashCode::SeperateDigits(unsigned long long Input_Param)
{
	if (Input_Param < 10)
	{
		ArraySize = 1;
		return new unsigned long long(Input_Param);
	}

	// Count Digits
	unsigned long long DigitLength = 0;
	unsigned long long TenTimes = 1;
	for (; TenTimes <= Input_Param; TenTimes *= 10)
	{
		++DigitLength;
	}

	// Allocate an Array to Return 
	unsigned long long* Digits = new unsigned long long[DigitLength] {0};

	// Segregate Based on Digit : 123 Equals to 123, 23, 3
	unsigned long long Multi = 1;
	for (unsigned long long Digit = 1; Digit <= DigitLength; ++Digit)
	{
		for (unsigned long long i = 1; i < Digit; ++i)
		{
			Multi *= 10;
		}
		Digits[DigitLength - Digit] = Input_Param % (10 * Multi);
		Multi = 1;
	}

	// Segregate Based On the First Number : 123 Equals to 100, 20, 3
	for (unsigned long long polish = 0; polish < DigitLength - 1; ++polish)
	{
		Digits[polish] -= Digits[polish + 1];
	}

	// Divide Segregated Numbers Based on Digits
	unsigned long long Index = 0;
	for (unsigned long long Divider = TenTimes /= 10; Divider > 0; Divider /= 10)
	{
		Digits[Index] /= Divider;
		++Index;
	}
	ArraySize = DigitLength;
	return Digits;
}

string HashCode::UnsignedLongLongToStr(unsigned long long* UInt_Param)
{
	unsigned long long ArrayLength = ArraySize / 8;

	string Integer("");

	for (unsigned long long Digit = 0; Digit < ArrayLength; ++Digit)
	{
		Integer += (char)(UInt_Param[Digit] + ASCII);
	}

	if (ArrayLength > 1)
	{
		delete[] UInt_Param;
	}
	else
	{
		delete UInt_Param;
	}

	return Integer;
}


template<typename Object>
inline long long HashCode::HashObjectAddress(Object* Address)
{
	return (long long)Address;
}

template<typename Object>
inline void HashCode::TrashStoredHash(Object* Address)
{
	long long HashCode = HashObjectAddress(Address);

	for (auto iterator : HashCodeWarehouse)
	{
		if (HashCodeWarehouse[iterator] == HashCode)
		{
			HashCodeWarehouse[iterator] = 0;
			return;
		}
	}
}