#include "../Public/DataPackage.h"


SendDataToThreads* SendDataToThreads::InstanceArray = nullptr;
SendDataToThreads* SendDataToThreads::GetSendDataToThreads(unsigned long long ThreadNumber, unsigned long long InstanceAmount)
{
    if (InstanceArray == nullptr)
    {
        InstanceArray = new SendDataToThreads[InstanceAmount];
    }

    return &InstanceArray[ThreadNumber];
}

SendDataToThreads::SendDataToThreads() : Integer(10), IntegerIndex(-1), Float(10), FloatIndex(-1), Boolean(10), BooleanIndex(-1), String(10), StringIndex(-1)
{
}

SendDataToThreads::~SendDataToThreads()
{
    if (InstanceArray != nullptr)
    {
        delete[] InstanceArray;
    }
}


long long SendDataToThreads::IncreaseIntegerIndex()
{
    if (this->IntegerIndex < (long long)this->Integer.GetCapacity())
    {
        ++this->IntegerIndex;
    }
    return this->IntegerIndex;
}

long long SendDataToThreads::IncreaseFloatIndex()
{
    if (this->FloatIndex < (long long)this->Float.GetCapacity())
    {
        ++this->FloatIndex;
    }
    return this->FloatIndex;
}

long long SendDataToThreads::IncreaseBooleanIndex()
{
    if (this->BooleanIndex < (long long)this->Boolean.GetCapacity())
    {
        ++this->BooleanIndex;
    }
    return this->BooleanIndex;
}

long long SendDataToThreads::IncreaseStringIndex()
{
    if (this->StringIndex < (long long)this->String.GetCapacity())
    {
        ++this->StringIndex;
    }
    return this->StringIndex;
}


DataFromThreads* DataFromThreads::InstanceArray = nullptr;
DataFromThreads* DataFromThreads::GetDataFromThreads(unsigned long long ThreadNumber, unsigned long long InstanceAmount)
{
    if (InstanceArray == nullptr)
    {
        InstanceArray = new DataFromThreads[InstanceAmount];
    }

    return &InstanceArray[ThreadNumber];
}

DataFromThreads::DataFromThreads() : Integer(10), IntegerIndex(-1), Float(10), FloatIndex(-1), Boolean(10), BooleanIndex(-1), String(10), StringIndex(-1)
{
}

DataFromThreads::~DataFromThreads()
{
    if (InstanceArray != nullptr)
    {
        delete[] InstanceArray;
    }
}


long long DataFromThreads::IncreaseIntegerIndex()
{
    if (this->IntegerIndex < (long long)this->Integer.GetCapacity())
    {
        ++this->IntegerIndex;
    }
    return this->IntegerIndex;
}

long long DataFromThreads::IncreaseFloatIndex()
{
    if (this->FloatIndex < (long long)this->Float.GetCapacity())
    {
        ++this->FloatIndex;
    }
    return this->FloatIndex;
}

long long DataFromThreads::IncreaseBooleanIndex()
{
    if (this->BooleanIndex < (long long)this->Boolean.GetCapacity())
    {
        ++this->BooleanIndex;
    }
    return this->BooleanIndex;
}

long long DataFromThreads::IncreaseStringIndex()
{
    if (this->StringIndex < (long long)this->String.GetCapacity())
    {
        ++this->StringIndex;
    }
    return this->StringIndex;
}