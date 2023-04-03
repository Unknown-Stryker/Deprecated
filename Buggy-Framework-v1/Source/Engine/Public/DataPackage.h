#pragma once
#include "DynamicLinkedArray.h"


struct SendDataToThreads
{
private:
    SendDataToThreads();
    static SendDataToThreads* InstanceArray;
    long long IntegerIndex;
    long long FloatIndex;
    long long BooleanIndex;
    long long StringIndex;

public:
    static SendDataToThreads* GetSendDataToThreads(unsigned long long ThreadNumber, unsigned long long InstanceAmount = 10);
    ~SendDataToThreads();

    DynamicLinkedArray<long long > Integer;
    long long IncreaseIntegerIndex();

    DynamicLinkedArray<long double > Float;
    long long IncreaseFloatIndex();

    DynamicLinkedArray<bool> Boolean;
    long long IncreaseBooleanIndex();

    DynamicLinkedArray<string> String;
    long long IncreaseStringIndex();
};




struct DataFromThreads
{
private:
    DataFromThreads();
    static DataFromThreads* InstanceArray;
    long long IntegerIndex;
    long long FloatIndex;
    long long BooleanIndex;
    long long StringIndex;

public:
    static DataFromThreads* GetDataFromThreads(unsigned long long ThreadNumber, unsigned long long InstanceAmount = 10);
    ~DataFromThreads();

    DynamicLinkedArray<long long> Integer;
    long long IncreaseIntegerIndex();

    DynamicLinkedArray<long double> Float;
    long long IncreaseFloatIndex();

    DynamicLinkedArray<bool> Boolean;
    long long IncreaseBooleanIndex();

    DynamicLinkedArray<string> String;
    long long IncreaseStringIndex();
};
