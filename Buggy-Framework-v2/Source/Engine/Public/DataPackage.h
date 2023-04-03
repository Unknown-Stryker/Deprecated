#pragma once
#include "DynamicLinkedArray.h"

template<typename DataType>
struct SendDataToThreads
{
private:
    SendDataToThreads();
    static SendDataToThreads* Instance;

public:
    static SendDataToThreads* DeliverDataToThreads();
    ~SendDataToThreads();

    DynamicLinkedArray<DataType> Container;
};


template<typename DataType>
SendDataToThreads<DataType>* SendDataToThreads<DataType>::Instance = nullptr;

template<typename DataType>
SendDataToThreads<DataType>* SendDataToThreads<DataType>::DeliverDataToThreads()
{
    if (Instance == nullptr)
    {
        Instance = new SendDataToThreads<DataType>;
    }

    return Instance;
}

template<typename DataType>
SendDataToThreads<DataType>::SendDataToThreads()
{
}

template<typename DataType>
SendDataToThreads<DataType>::~SendDataToThreads()
{
    if (Instance != nullptr)
    {
        delete Instance;
    }
}




template<typename DataType>
struct DataFromThreads
{
private:
    DataFromThreads();
    static DataFromThreads* Instance;

public:
    static DataFromThreads* GetDataFromThreads();
    ~DataFromThreads();

    DynamicLinkedArray<DataType> Container;
};


template<typename DataType>
DataFromThreads<DataType>* DataFromThreads<DataType>::Instance = nullptr;

template<typename DataType>
DataFromThreads<DataType>* DataFromThreads<DataType>::GetDataFromThreads()
{
    if (Instance == nullptr)
    {
        Instance = new DataFromThreads<DataType>;
    }

    return Instance;
}

template<typename DataType>
DataFromThreads<DataType>::DataFromThreads()
{
}

template<typename DataType>
DataFromThreads<DataType>::~DataFromThreads()
{
    if (Instance != nullptr)
    {
        delete Instance;
    }
}