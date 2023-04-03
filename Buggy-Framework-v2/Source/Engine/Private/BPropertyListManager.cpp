#include "../Public/BPropertyListManager.h"
#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

BPropertyListManager* BPropertyListManager::ListManagerSingletonInstance = nullptr;

BPropertyListManager::BPropertyListManager() :InitGuard(false), AlphaNodePointer(nullptr), OmegaNodePointer(nullptr)
{
}

BPropertyListManager::BPropertyListManager(const BPropertyListManager& BPropertyPropertyListManager_P) :InitGuard(false), AlphaNodePointer(nullptr), OmegaNodePointer(nullptr)
{
}

BPropertyListManager::~BPropertyListManager()
{
  delete ListManagerSingletonInstance;
}

BPropertyListManager* BPropertyListManager::GetBPropertyListManager()
{
  if(ListManagerSingletonInstance == nullptr)
  {
    ListManagerSingletonInstance = new BPropertyListManager;
    return ListManagerSingletonInstance; 
  }
  else
  {
    return ListManagerSingletonInstance;
  }
}


BPropertyListManager::BPropertyDataNode* BPropertyListManager::GetAlphaNodePointer()
{
	return this->AlphaNodePointer;
}

void BPropertyListManager::SetAlphaNodePointer(BPropertyDataNode* AlphaNodePointer_Param)
{
	this->AlphaNodePointer = AlphaNodePointer_Param;
}


//Regist a Child Object's Address as BProperty to Parent Pointer Linked List 
//Tag the Object when Registering it to The BPropertyList(Singleton) 
void BPropertyListManager::RegisterChild(BClass* Child_Param, string Tag_Param)
{
	if (InitGuard == true)
	{
		//Generate New Node
		BPropertyDataNode* NewBPropertyManagerNode = new BPropertyDataNode;

		//Point Child
		NewBPropertyManagerNode->Child = Child_Param;
		//Initialize Tag
		NewBPropertyManagerNode->NameTag = Tag_Param;

		NewBPropertyManagerNode->NextBPropertyLink = nullptr;
		NewBPropertyManagerNode->PreviousBPropertyLink = nullptr;

		OmegaNodePointer->NextBPropertyLink = NewBPropertyManagerNode;
		NewBPropertyManagerNode->PreviousBPropertyLink = OmegaNodePointer;

		OmegaNodePointer = NewBPropertyManagerNode;

		OmegaNodePointer->NextBPropertyLink = nullptr;
	}
	else
	{
		InitGuard = true;
		AlphaNodePointer = new BPropertyDataNode;

		AlphaNodePointer->Child = Child_Param;
		AlphaNodePointer->NameTag = Tag_Param;

		AlphaNodePointer->NextBPropertyLink = nullptr;
		AlphaNodePointer->PreviousBPropertyLink = nullptr;

		OmegaNodePointer = AlphaNodePointer;
	}
}

//Returns Grand Parent Pointer : Possible to Cast All Child Pointers
BClass* BPropertyListManager::GetChildAddress(string BPropertyTag_Param)
{
	//Gets Next Node Link
	for (BPropertyDataNode* ThatBProperty = AlphaNodePointer; ThatBProperty != nullptr; ThatBProperty = ThatBProperty->NextBPropertyLink)
	{
		if (BPropertyTag_Param == ThatBProperty->NameTag)
		{
			cout << ThatBProperty->NameTag << endl;
			return ThatBProperty->Child;
		}
	}
	cout << "The Property That You Searched Doesn't Exist in the Property List" << endl;
	return nullptr;
}

//Must Be Called Before the Destructer gets Called
void BPropertyListManager::DeleteBProperty(string BPropertyTag_Param)
{
	if (AlphaNodePointer == nullptr)
	{
		InitGuard = false;
	}
	else
	{
		//Gets Next Node Link
		for (BPropertyDataNode* ThatBProperty = AlphaNodePointer; ThatBProperty != nullptr; ThatBProperty = ThatBProperty->NextBPropertyLink)
		{
			if (BPropertyTag_Param == ThatBProperty->NameTag)
			{
				cout << "Subject Object to Delete Tag : " << ThatBProperty->NameTag << endl;

				delete ThatBProperty->Child;

				ThatBProperty->Child = nullptr;
				
				if (ThatBProperty->PreviousBPropertyLink != nullptr)
				{
					// Connect NextLink of Previous Node of ThatBProperty to Next Node of ThatBProperty
					ThatBProperty->PreviousBPropertyLink->NextBPropertyLink = ThatBProperty->NextBPropertyLink;
					OmegaNodePointer = OmegaNodePointer->PreviousBPropertyLink;
				}
				else
				{
					// Connect PreviousLink of Next Node of ThatBProperty to Previous Node of ThatBProperty
					ThatBProperty->NextBPropertyLink->PreviousBPropertyLink = ThatBProperty->PreviousBPropertyLink;
					AlphaNodePointer = AlphaNodePointer->NextBPropertyLink;
				}

				delete ThatBProperty;
				return;
			}
		}
	}
}

unsigned long long BPropertyListManager::CountDataNode()
{
	unsigned long long Length = 0;
	for (BPropertyDataNode* ThatBProperty = AlphaNodePointer; ThatBProperty != nullptr; ThatBProperty = ThatBProperty->NextBPropertyLink)
	{
		++Length;
	}
	return Length;
}