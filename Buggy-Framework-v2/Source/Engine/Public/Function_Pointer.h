#pragma once
#include "DynamicLinkedArray.h"

//Global Function Pointer Container (Singleton)
template<typename ClassName, typename ReturnType>
struct Global_func_ptr
{
private:
    Global_func_ptr();
    static Global_func_ptr* Instance;

public:
    static Global_func_ptr* Get_Global_func_ptr(unsigned long long ChunkSize);
    ~Global_func_ptr();

    DynamicLinkedArray<ReturnType(ClassName::*)()> Global_void_func_ptr;
};

template<typename ClassName, typename ReturnType>
Global_func_ptr<ClassName, ReturnType>* Global_func_ptr<ClassName, ReturnType>::Instance = nullptr;

template<typename ClassName, typename ReturnType>
Global_func_ptr<ClassName, ReturnType>* Global_func_ptr<ClassName, ReturnType>::Get_Global_func_ptr(unsigned long long ChunkSize)
{
    if (Instance == nullptr)
    {
        Instance = new Global_func_ptr<ClassName, ReturnType>(ChunkSize);
    }

    return &Instance;
}

template<typename ClassName, typename ReturnType>
Global_func_ptr<ClassName, ReturnType>::Global_func_ptr() : Global_void_func_ptr(50)
{
    for (unsigned long long i = 0; i < Global_void_func_ptr.GetCapacity(); ++i)
    {
        Global_void_func_ptr.Insert(i, nullptr, " ");
    }
}

template<typename ClassName, typename ReturnType>
Global_func_ptr<ClassName, ReturnType>::~Global_func_ptr()
{
    if (Instance != nullptr)
    {
        delete Instance;
    }
}


// Local Function Pointer Container
template<typename ClassName, typename ReturnType>
struct Local_func_ptr
{
public:
    Local_func_ptr(unsigned long long ChunkSize);
    ~Local_func_ptr();

    DynamicLinkedArray<ReturnType(ClassName::*)()> Local_void_func_ptr;
};

template<typename ClassName, typename ReturnType>
Local_func_ptr<ClassName, ReturnType>::Local_func_ptr(unsigned long long ChunkSize) : Local_void_func_ptr(ChunkSize)
{
    for (unsigned long long i = 0; i < Local_void_func_ptr.GetCapacity(); ++i)
    {
      Local_void_func_ptr.Insert(i, nullptr, " ");
    }
}

template<typename ClassName, typename ReturnType>
Local_func_ptr<ClassName, ReturnType>::~Local_func_ptr()
{
}