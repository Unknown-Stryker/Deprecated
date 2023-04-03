#pragma once
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

// A Grand Class For All Buggy Engine Base Classes
class BClass
{
protected:
  string BPropertyName;
  static unsigned long long ChildInstanceNumber;
  unsigned long long Index;

  virtual void Tick();

public:
	static unsigned long long GetChildInstanceNumber();
  virtual unsigned long long IndexIterator(unsigned long long IndexLimit);

public:
  BClass();
  virtual ~BClass();
  virtual string GetBPropertyName();
};