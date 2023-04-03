#pragma once
#include "../Engine/Public/BPawn.h"
#include "../Engine/Public/MT19937.h"
#include "../Engine/Public/B2DLevel.h"


class Alien : public BPawn
{
private:
  MT19937 Random;
  B_2DLevel* LevelData;
  unsigned long long WorldSizeX;
  unsigned long long WorldSizeY;


public:
  Alien();
  ~Alien();

  virtual void Move() override;
};
