#pragma once
#include "Function_Pointer.h"
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

// A Grand Class For All Buggy Engine Classes
class BClass
{
protected:
  string BPropertyName;
  static unsigned long long ChildInstanceNumber;
  unsigned long long Index;
  
  Local_func_ptr<BClass, void> Func_ptr;
public:
  virtual void MakeTick();
  virtual void Tick();
protected:
  string TickNameTag;
  long long ObjectSerialNumber;
  virtual void BeginPlay();

public:
	static unsigned long long GetChildInstanceNumber();
  virtual unsigned long long IndexIterator(unsigned long long IndexLimit);

public:
  BClass();
  virtual ~BClass();
  virtual string GetBPropertyName();
};