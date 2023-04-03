// Copyright © Jan, 2022. Team Creator, 20211084 Stryker

#pragma once
#include <iostream>
#include "DynamicLinkedArray.h"
using std::cout;
using std::endl;

/*
Dynamic Stack Function List : 
    bool Is_It_Full();

	bool Is_It_Empty();

	long long GetSizeOfStack() { return Top; };

	void Push(STACK Element_P);

	STACK Pop();

	STACK Peak(unsigned long long Index) { return DynamicStack.GetElement(Index); };

	STACK GetTheMostGreatestNumber();

	bool FreezeSizeOfStack();
*/
template<typename STACK>
struct DynamicStack
{
private:
	long long Top;
	
	long long SizeOfStack;

	STACK GreatestNumber;
	
	DynamicLinkedArray<STACK> DynamicLinkedStack;

	bool IsSizeFrozen;
	
public:

	//스택 크기, 초깃값
	DynamicStack(long long StackSize_P);

	~DynamicStack();

	bool Is_It_Full();

	bool Is_It_Empty();

	long long GetSizeOfStack() { return Top; };

	void Push(STACK Element_P);

	STACK Pop();

	STACK Peak(unsigned long long Index) { return DynamicLinkedStack.GetElement(Index); };

	STACK GetTheMostGreatestNumber();

	bool FreezeSizeOfStack();
	bool UnFreezeSizeOfStack();
	bool GetIsSizeFrozen();
};




template<typename STACK>
inline DynamicStack<STACK>::DynamicStack(long long StackSize_P) : DynamicLinkedStack(StackSize_P), Top(-1), GreatestNumber(0), IsSizeFrozen(true)
{
	SizeOfStack = DynamicLinkedStack.GetCapacity();
}

template<typename STACK>
inline DynamicStack<STACK>::~DynamicStack()
{
}

template<typename STACK>
inline bool DynamicStack<STACK>::Is_It_Full()
{
	if (Top >= SizeOfStack - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename STACK>
inline bool DynamicStack<STACK>::Is_It_Empty()
{
	if (Top >= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<typename STACK>
inline void DynamicStack<STACK>::Push(STACK Element_P)
{
	switch ( this->GetIsSizeFrozen() )
	{
	case true:

		if (Is_It_Full() == false)
		{
			++Top;
			DynamicLinkedStack.Insert(Top, Element_P);
			if (Element_P > this->GreatestNumber)
			{
				this->GreatestNumber = Element_P;
			}
		}
		else
		{
			cout << "FATAL ERROR! : Stack Overflow Occurred" << std::endl;
		}

		break;

	case false:

		++Top;
		DynamicLinkedStack.Insert(Top, Element_P);
		if (Element_P > this->GreatestNumber)
		{
			this->GreatestNumber = Element_P;
		}

		SizeOfStack = DynamicLinkedStack.GetCapacity();
		break;
	}
}

template<typename STACK>
inline STACK DynamicStack<STACK>::Pop()
{
	if (Is_It_Empty() == false)
	{
		STACK pop = DynamicLinkedStack.GetElement(Top);
		for (long long Delete = Top; Delete < SizeOfStack; ++Delete)
		{
			DynamicLinkedStack.Insert(Top, NULL);
		}
		--Top;
		return pop;
	}
	else
	{
		return -1;
	}
}

template<typename STACK>
inline STACK DynamicStack<STACK>::GetTheMostGreatestNumber()
{
	return this->GreatestNumber;
}

template<typename STACK>
inline bool DynamicStack<STACK>::FreezeSizeOfStack()
{
	IsSizeFrozen = true;
	return IsSizeFrozen;
}

template<typename STACK>
inline bool DynamicStack<STACK>::UnFreezeSizeOfStack()
{
	IsSizeFrozen = false;
	return IsSizeFrozen;
}

template<typename STACK>
inline bool DynamicStack<STACK>::GetIsSizeFrozen()
{
	return this->IsSizeFrozen;
}
