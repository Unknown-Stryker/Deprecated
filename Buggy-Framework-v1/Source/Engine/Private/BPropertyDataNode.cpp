#include "../Public/BPropertyListManager.h"
#include <iostream>
using std::cout;
using std::endl;


BPropertyListManager::BPropertyDataNode::BPropertyDataNode() : NextBPropertyLink(nullptr), PreviousBPropertyLink(nullptr), Child(nullptr), NameTag("\0")
{
	cout << "Parent Pointer Node Generated" << endl;
}

BPropertyListManager::BPropertyDataNode::~BPropertyDataNode()
{
	cout << "Parent Pointer Node Deleted" << endl;
}