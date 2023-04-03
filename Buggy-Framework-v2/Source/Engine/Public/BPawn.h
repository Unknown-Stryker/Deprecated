#pragma once
#include "BObject.h"

// A Base Class For Movable Buggy Engine Objects
class BPawn : public BObject
{
protected:
  bool bDead;

public:
  BPawn();
  ~BPawn();

  virtual void Move();

  virtual int getch();
};