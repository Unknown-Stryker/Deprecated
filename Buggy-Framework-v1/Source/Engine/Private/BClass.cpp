#include "../Public/BClass.h"


BClass::BClass() : BPropertyName("BClass"), Index(0)
{
}

BClass::~BClass()
{
}

string BClass::GetBPropertyName() { return this->BPropertyName; }


unsigned long long BClass::ChildInstanceNumber = 0;
unsigned long long BClass::GetChildInstanceNumber()
{
	++ChildInstanceNumber;

	return ChildInstanceNumber;
}

unsigned long long BClass::IndexIterator(unsigned long long IndexLimit)
{
  if(this->Index < IndexLimit)
  {
    ++this->Index;
    return this->Index;
  }
  else
  {
    this->Index = 0;
    return this->Index;
  }
}

void BClass::Tick()
{
  
}