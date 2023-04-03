#pragma once
#include "BClass.h"
using std::string;

// A Class For Managing All Buggy Engine Objects via Utilizing BClass* 
class BPropertyListManager
{
private:
	BPropertyListManager();
	BPropertyListManager(const BPropertyListManager& BPropertyPropertyListManager_Param);

  static BPropertyListManager* ListManagerSingletonInstance;

  // A Class that Contains Child Addresses and Tags of a Child Classes
  class BPropertyDataNode
  {
    friend class BPropertyListManager;
  private:
	  //Link that's Pointing Next Node
	  BPropertyDataNode* NextBPropertyLink;

	  //Link that's Pointing Previous Node
	  BPropertyDataNode* PreviousBPropertyLink;

	  //Gate for Child Data
	  BClass* Child;

		// Node and its Datafield "Child*" are Tagged with std::string object
	  string NameTag;

	  BPropertyDataNode();
	  ~BPropertyDataNode();
  };


	// Points the First Node : Head Node
	BPropertyDataNode* AlphaNodePointer;
public:
	BPropertyDataNode* GetAlphaNodePointer();
	void SetAlphaNodePointer(BPropertyDataNode* AlphaNodePointer_Param);


private:
	// Points the Last Node
	BPropertyDataNode* OmegaNodePointer;

	//Avoids Allocating a New Node to AlphaNodePointer after Initialization
	bool InitGuard;

public:
  ~BPropertyListManager();

	static BPropertyListManager* GetBPropertyListManager();

	//Returns Grand Parent Pointer : Possible to Cast All Child Pointers
	BClass* GetChildAddress(string BPropertyTag_Param);

	//Regist a Child Object's Address as BProperty to Parent Pointer Linked List 
	//Tag the Object when Registering it to The BPropertyList(Singleton) 
	void RegisterChild(BClass* Child_Param, string Tag_Param);

	//Must Be Called Before the Destructer gets Called
    //If The Node is NOT Being Used Anywhere, The Node Wil Delete Itself Via Calling this Function.
	void DeleteBProperty(string BPropertyTag_Param);

	unsigned long long CountDataNode();
};