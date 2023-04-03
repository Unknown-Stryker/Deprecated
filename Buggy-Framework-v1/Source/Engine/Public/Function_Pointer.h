#pragma once
#include "DynamicLinkedArray.h"

template<typename ClassName>
struct Function_Pointer
{
private:
    Function_Pointer();
    static Function_Pointer* InstanceArray;
public:
    static Function_Pointer* GetFunction_Pointer(unsigned long long ProcessNumber, unsigned long long InstanceAmount = 10);
    ~Function_Pointer();

    DynamicLinkedArray<void(ClassName::*)()> VoidFunction_Pointer;
};


template<typename ClassName>
Function_Pointer<ClassName>* Function_Pointer<ClassName>::InstanceArray = nullptr;

template<typename ClassName>
Function_Pointer<ClassName>* Function_Pointer<ClassName>::GetFunction_Pointer(unsigned long long ProcessNumber, unsigned long long InstanceAmount)
{
    if (InstanceArray == nullptr)
    {
        InstanceArray = new Function_Pointer[InstanceAmount];
    }

    return &InstanceArray[ProcessNumber];
}

template<typename ClassName>
Function_Pointer<ClassName>::Function_Pointer() : VoidFunction_Pointer(50)
{
    for (unsigned long long i = 0; i < VoidFunction_Pointer.GetCapacity(); ++i)
    {
        VoidFunction_Pointer.Insert(i, nullptr, " ");
    }
}

template<typename ClassName>
Function_Pointer<ClassName>::~Function_Pointer()
{
    if (InstanceArray != nullptr)
    {
        delete[] InstanceArray;
    }
}