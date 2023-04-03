// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once
#pragma warning(disable : 4172)
#include <typeinfo>
#include <string>
using std::string;

#include<iostream>
using std::cout;
using std::endl;

const unsigned int ASCIICODE = 48;

struct DATA;

/*
Dynamic Linked Array Function List :

    Element& operator=(DynamicLinkedArray<DynamicType>::DATA Value);
	DATA& operator=(const DATA &Data);

	void Initialize(unsigned long long ChunkSize_Param);
	unsigned long long GetCapacity();
	string GetDataType();

	string SearchElementInfo(unsigned long long Index);
	unsigned long long CountPreExistingValue(DynamicType Value);
	DynamicType SearchElement(string DataInfo_Param);
	DynamicType GetElement(unsigned long long Index);

	void Insert(unsigned long long Index, DynamicType Value, string DataInfo_Param);
	void Insert(unsigned long long Index, DynamicType Value);

	void Emplace_Front(DynamicType Value, string DataInfo_Param);
	void Emplace_Front(DynamicType Value);

	void Emplace_Back(DynamicType Value, string DataInfo_Param);
	void Emplace_Back(DynamicType Value);

	void DeleteChunk(unsigned long long Index);
	void DeleteLatestChunk();

	Element& operator[] (unsigned long long Index);
*/
template <typename DynamicType>
class DynamicLinkedArray
{
public:
	class Element
	{
	private:
		friend class DynamicLinkedArray;

		// Link Field
		Element* NextChunkLink;
		Element* PreviousChunkLink;

		// Tag Field
		string DataInfo;

		// Data Field
		DynamicType Data;

		Element();
		~Element();
	};

	struct DATA
	{
		DATA(DynamicType Data_Param, string DataInfo_Param);
		~DATA();

		void SetData(DynamicType Data_Param);
		DynamicType GetData();

		void SetDataInfo(string DataInfo_Param);
		string GetDataInfo();

		// Data Field
		DynamicType Data;

		// Tag Field
		string DataInfo;
	};

	unsigned long long* SeperateDigits(unsigned long long Input_Param);

	string UnsignedLongLongToStr(unsigned long long* UInt_Param);

private:
	static unsigned long long StrToInt(const string str);

	// Configuration Field
	unsigned long long ChunkSize;
	unsigned long long ChunkCount;
	string DataTypeInfo;
	unsigned long long DataTypeHashCode;
	
	Element* EntryOfArrayChunk;
	Element* EndOfArrayChunk;
	bool bDidOnce;
	long long Index;
	unsigned long long NumToStrLength;
public:
	DynamicLinkedArray();
	DynamicLinkedArray(unsigned long long ChunkSize_Param);
	~DynamicLinkedArray();

	void Initialize(unsigned long long ChunkSize_Param);
	unsigned long long GetCapacity();
	string GetDataType();

	string SearchElementInfo(unsigned long long Index);
	unsigned long long CountPreExistingValue(DynamicType Value);
	DynamicType SearchElement(string DataInfo_Param);
	DynamicType GetElement(unsigned long long Index);

	void Insert(unsigned long long Index, DynamicType Value, string DataInfo_Param);
	void Insert(unsigned long long Index, DynamicType Value);

	void Emplace_Front(DynamicType Value, string DataInfo_Param);
	void Emplace_Front(DynamicType Value);

	void Emplace_Back(DynamicType Value, string DataInfo_Param);
	void Emplace_Back(DynamicType Value);

	void DeleteChunk(unsigned long long Index);
	void DeleteLatestChunk();

	long long GetIndex();
	long long IndexIterator();
};




template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::Element::Element() : NextChunkLink(nullptr), PreviousChunkLink(nullptr), DataInfo("\0"), Data()
{
}

template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::Element::~Element()
{
}




template<typename DynamicType>
inline unsigned long long* DynamicLinkedArray<DynamicType>::SeperateDigits(unsigned long long Input_Param)
{
	if (Input_Param < 10)
	{
		NumToStrLength = 1;
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
	NumToStrLength = DigitLength;
	return Digits;
}

template<typename DynamicType>
inline string DynamicLinkedArray<DynamicType>::UnsignedLongLongToStr(unsigned long long* UInt_Param)
{
	unsigned long long ArrayLength = NumToStrLength / 8;

	string Integer("");

	for (unsigned long long Digit = 0; Digit < ArrayLength; ++Digit)
	{
		Integer += (char)(UInt_Param[Digit] + ASCIICODE);
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

template<typename DynamicType>
inline unsigned long long DynamicLinkedArray<DynamicType>::StrToInt(const string str)
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




template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::DynamicLinkedArray() : ChunkSize(0), ChunkCount(1), DataTypeInfo(typeid(DynamicType).name()), EntryOfArrayChunk(nullptr), EndOfArrayChunk(nullptr), bDidOnce(false), NumToStrLength(1)
{
	this->DataTypeHashCode = StrToInt(DataTypeInfo);
}

template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::DynamicLinkedArray(unsigned long long ChunkSize_Param) : ChunkSize(ChunkSize_Param), ChunkCount(1), DataTypeInfo(typeid(DynamicType).name()), EntryOfArrayChunk(nullptr), EndOfArrayChunk(nullptr), bDidOnce(false), NumToStrLength(1)
{
	this->DataTypeHashCode = StrToInt(DataTypeInfo);

	if (this->ChunkSize < 5)
	{
		this->ChunkSize = 5;
	}

	if (this->EntryOfArrayChunk == nullptr)
	{
		this->EntryOfArrayChunk = new Element[this->ChunkSize];
		this->EndOfArrayChunk = this->EntryOfArrayChunk;
	}
}

template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::~DynamicLinkedArray()
{
	unsigned long long Iterator = ChunkCount;
	for (Element* deallocator = this->EndOfArrayChunk; 0 < Iterator; deallocator = deallocator->PreviousChunkLink)
	{
		if (deallocator == nullptr)
		{
			break;
		}
		if (deallocator->NextChunkLink != nullptr)
		{
			delete[] deallocator->NextChunkLink;
		}
		--Iterator;
	}
}




template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Initialize(unsigned long long ChunkSize_Param)
{
	if (bDidOnce == true)
	{
		return;
	}

	bDidOnce = true;
	ChunkSize = ChunkSize_Param;
	this->DataTypeHashCode = StrToInt(DataTypeInfo);

	if (this->EntryOfArrayChunk == nullptr)
	{
		this->EntryOfArrayChunk = new Element[this->ChunkSize];
		this->EndOfArrayChunk = this->EntryOfArrayChunk;
	}
}

template<typename DynamicType>
inline unsigned long long DynamicLinkedArray<DynamicType>::GetCapacity()
{
	return ChunkCount * ChunkSize;
}

template<typename DynamicType>
inline string DynamicLinkedArray<DynamicType>::GetDataType()
{
	return DataTypeInfo;
}

template<typename DynamicType>
inline string DynamicLinkedArray<DynamicType>::SearchElementInfo(unsigned long long Index)
{
	if (Index < this->ChunkSize)
	{
		return this->EntryOfArrayChunk[Index].DataInfo;
	}

	unsigned long long ChunkIter = 0;
	while (this->ChunkSize <= Index)
	{
		Index = Index - this->ChunkSize;
		++ChunkIter;
	}

	unsigned long long ChunkIndex = 0;
	unsigned long long Iterator = 0;
	for (Element* Iter = this->EntryOfArrayChunk; Iterator < ChunkCount; Iter = Iter->NextChunkLink)
	{
		if (ChunkIter == ChunkIndex)
		{
			return Iter[Index].DataInfo;
		}
		++ChunkIndex;
		++Iterator;
	}

	return string("\0");
}

template<typename DynamicType>
inline unsigned long long DynamicLinkedArray<DynamicType>::CountPreExistingValue(DynamicType Value)
{
	unsigned long long Pre_Existing = 0;

	unsigned long long Iterator = 0;
	for (Element* Iter = EntryOfArrayChunk; Iterator < ChunkCount; Iter = Iter->NextChunkLink, ++Iterator)
	{
		for (unsigned long long idx = 0; idx < this->ChunkSize; ++idx)
		{
			if (Value == Iter[idx])
			{
				++Pre_Existing;
			}
		}
	}
	return Pre_Existing;
}

template<typename DynamicType>
inline DynamicType DynamicLinkedArray<DynamicType>::SearchElement(string DataInfo_Param)
{
	unsigned long long Iterator = 0;
	for (Element* Iter = EntryOfArrayChunk; Iterator < ChunkCount; Iter = Iter->NextChunkLink)
	{
		for (unsigned long long idx = 0; idx < this->ChunkSize; ++idx)
		{
			if (Iter[idx].DataInfo == DataInfo_Param)
			{
				return Iter[idx].Data;
			}
		}
		++Iterator;
	}
	return DynamicType();
}

template<typename DynamicType>
inline DynamicType DynamicLinkedArray<DynamicType>::GetElement(unsigned long long Index)
{
	if (Index < this->ChunkSize)
	{
		return this->EntryOfArrayChunk[Index].Data;
	}

	unsigned long long ChunkIter = 0;
	while (this->ChunkSize <= Index)
	{
		Index = Index - this->ChunkSize;
		++ChunkIter;
	}

	
	Element* Iter = this->EntryOfArrayChunk;
	for (unsigned long long ChunkIndex = 0; ChunkIndex <= ChunkCount; ++ChunkIndex)
	{
		if (ChunkIter == ChunkIndex)
		{
			return Iter[Index].Data;
		}
		Iter = Iter->NextChunkLink;
	}

	return DynamicType();
}


template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Insert(unsigned long long Index, DynamicType Value, string DataInfo_Param)
{
	// 1. Check Whether the Data Tag Overlapps or NOT
	// 2. Insert without Allocating new Chunks If there is capacity
	// 3. Allocate New Array Chunk If the Index Overflows its Capacity
	unsigned long long Iterator = 0;
	for (Element* Iter = this->EntryOfArrayChunk; Iterator < ChunkCount; Iter = Iter->NextChunkLink)
	{
		for (unsigned long long idx = 0; idx < this->ChunkSize; ++idx)
		{
			if (Iter[idx].DataInfo == DataInfo_Param)
			{
				if (DataInfo_Param == " " || DataInfo_Param == "\0")
				{
					goto ESCAPE_DOUBLE_LOOP;
				}
				cout << "DataInfo Overlapped" << endl;
				return;
			}
		}
		++Iterator;
	}

ESCAPE_DOUBLE_LOOP:

	//If Index is smaller than its Capacity
	if (Index < this->ChunkSize && this->EntryOfArrayChunk != nullptr)
	{
		this->EntryOfArrayChunk[Index].Data = Value;
		this->EntryOfArrayChunk[Index].DataInfo = DataInfo_Param;
		return;
	}


	//If Index overflows its Capacity or is Greater than its ChunkSize
	unsigned long long ChunkIter = 0;
	while (this->ChunkSize <= Index)
	{
		Index = Index - this->ChunkSize;
		++ChunkIter;
	}


	// Insert Value, if it's unnecessary create new ones
	Element* Iter = this->EntryOfArrayChunk;
	for (unsigned long long ChunkIndex = 0; ChunkIndex < ChunkCount; ++ChunkIndex)
	{
		if (ChunkIter == ChunkIndex)
		{
			Iter[Index].Data = Value;
			Iter[Index].DataInfo = DataInfo_Param;
			return;
		}
		Iter = Iter->NextChunkLink;
	}


	// Generate New Node
	for (unsigned long long Iterator = ChunkCount - 1; Iterator < ChunkIter; ++Iterator)
	{
		Element* NewArrayChunk = new Element[this->ChunkSize];
		this->EndOfArrayChunk->NextChunkLink = NewArrayChunk;
		NewArrayChunk->PreviousChunkLink = this->EndOfArrayChunk;
		this->EndOfArrayChunk = NewArrayChunk;
		++ChunkCount;
	}
	this->EndOfArrayChunk[Index].Data = Value;
	this->EndOfArrayChunk[Index].DataInfo = DataInfo_Param;
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Insert(unsigned long long Index, DynamicType Value)
{
	//If Index is smaller than its Capacity
	if (Index < this->ChunkSize && this->EntryOfArrayChunk != nullptr)
	{
		this->EntryOfArrayChunk[Index].Data = Value;
		return;
	}
	

	//If Index overflows its Capacity or is Greater than its ChunkSize
	unsigned long long ChunkIter = 0;
	while (this->ChunkSize <= Index)
	{
		Index = Index - this->ChunkSize;
		++ChunkIter;
	}


	// Insert Value, if it's unnecessary create new ones
	Element* Iter = this->EntryOfArrayChunk;
	for (unsigned long long ChunkIndex = 0;  ChunkIndex < ChunkCount; ++ChunkIndex)
	{
		if (ChunkIter == ChunkIndex && Iter != nullptr)
		{
			Iter[Index].Data = Value;
			return;
		}
		Iter = Iter->NextChunkLink;
	}


	// Generate New Node
	for (unsigned long long Iterator = ChunkCount - 1; Iterator < ChunkIter; ++Iterator)
	{
		Element* NewArrayChunk = new Element[this->ChunkSize];
		this->EndOfArrayChunk->NextChunkLink = NewArrayChunk;
		NewArrayChunk->PreviousChunkLink = this->EndOfArrayChunk;
		this->EndOfArrayChunk = NewArrayChunk;
		++ChunkCount;
	}

	// Insert Value
	this->EndOfArrayChunk[Index].Data = Value;
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Emplace_Front(DynamicType Value, string DataInfo_Param)
{
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Emplace_Front(DynamicType Value)
{
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Emplace_Back(DynamicType Value, string DataInfo_Param)
{
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::Emplace_Back(DynamicType Value)
{
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::DeleteChunk(unsigned long long Index)
{
	//If Index is smaller than its Capacity
	if (Index < this->ChunkSize)
	{
		Element* Subject = this->EntryOfArrayChunk;
		this->EntryOfArrayChunk = this->EntryOfArrayChunk->NextChunkLink;
		delete[] Subject;
		--ChunkCount;
		return;
	}


	//If Index overflows its Capacity or is Greater than its ChunkSize
	unsigned long long ChunkIter = 0;
	while (this->ChunkSize <= Index)
	{
		Index = Index - this->ChunkSize;
		++ChunkIter;
	}

	unsigned long long ChunkIndex = 0;
	unsigned long long Iterator = 0;
	for (Element* Iter = this->EntryOfArrayChunk; Iterator < ChunkCount; Iter = Iter->NextChunkLink)
	{
		if (ChunkIter == ChunkIndex)
		{
			if (Iter->PreviousChunkLink != nullptr)
			{
				Iter->PreviousChunkLink->NextChunkLink = Iter->NextChunkLink;
			}

			if (Iter->NextChunkLink != nullptr)
			{
				Iter->NextChunkLink->PreviousChunkLink = Iter->PreviousChunkLink;
			}
			delete[] Iter;
			--ChunkCount;
			return;
		}
		++ChunkIndex;
		++Iterator;
	}
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::DeleteLatestChunk()
{
	if (this->EndOfArrayChunk != nullptr)
	{
		Element* Subject = this->EndOfArrayChunk;

		this->EndOfArrayChunk = EndOfArrayChunk->PreviousChunkLink;

		delete[] Subject;
		--ChunkCount;
	}
}

template<typename DynamicType>
inline long long DynamicLinkedArray<DynamicType>::GetIndex()
{
	return this->Index;
}

template<typename DynamicType>
inline long long DynamicLinkedArray<DynamicType>::IndexIterator()
{
	if (this->Index < (long long)GetCapacity() )
	{
		++this->Index;
	}
	else
	{
		this->Index = 0;
	}
	return this->Index;
}




template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::DATA::DATA(DynamicType Data_Param, string DataInfo_Param) : Data(Data_Param), DataInfo(DataInfo_Param)
{
}

template<typename DynamicType>
inline DynamicLinkedArray<DynamicType>::DATA::~DATA()
{
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::DATA::SetData(DynamicType Data_Param)
{
	this->Data = Data_Param;
}

template<typename DynamicType>
inline DynamicType DynamicLinkedArray<DynamicType>::DATA::GetData()
{
	return this->Data;
}

template<typename DynamicType>
inline void DynamicLinkedArray<DynamicType>::DATA::SetDataInfo(string DataInfo_Param)
{
	this->DataInfo = DataInfo_Param;
}

template<typename DynamicType>
inline string DynamicLinkedArray<DynamicType>::DATA::GetDataInfo()
{
	return this->DataInfo;
}