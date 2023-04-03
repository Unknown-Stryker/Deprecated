#pragma once
#include "../Engine/Public/BPawn.h"
#include "../Engine/Public/B2DLevel.h"


class AlienPoop : public BPawn
{
private:

public:
  virtual void Tick() override;

  AlienPoop();
  ~AlienPoop();

  virtual void Move() override;
};