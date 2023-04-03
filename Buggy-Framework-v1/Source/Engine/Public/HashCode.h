// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
const unsigned int ASCII = 48;


class HashCode
{
private:
	vector<long long> HashCodeWarehouse;

	unsigned long long ArraySize = 0;

public:
	HashCode();
	~HashCode();

	template <typename Object>
	long long HashObjectAddress(Object* Address);

	void StoreHashCode(long long ObjectHashCode);

	template <typename Object>
	void TrashStoredHash(Object* Address);


	unsigned long long StrToInt(const string str);

	unsigned long long* SeperateDigits(unsigned long long Input_Param);

	string UnsignedLongLongToStr(unsigned long long* UInt_Param);

};