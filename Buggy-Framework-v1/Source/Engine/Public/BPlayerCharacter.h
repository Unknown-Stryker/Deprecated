#pragma once
#include "BPawn.h"

// A Base Class For Movable Buggy Engine Player Objects
class BPlayerCharacter : public BPawn
{
private:

public:
  BPlayerCharacter();
  ~BPlayerCharacter();

  virtual void Move() override;
};
