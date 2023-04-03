#pragma once
#include "../Engine/Public/BPawn.h"
#include "../Engine/Public/MT19937.h"
#include "../Engine/Public/B2DLevel.h"


enum class FlightDirection
{
  Right = 0,
  Left = 1
};


class UFO : public BPawn
{
private:
  MT19937 RightOrLeft;
  FlightDirection Somewhere;
  B_2DLevel* LevelData;
  unsigned long long WorldSizeX;
  unsigned long long WorldSizeY;

public:
  virtual void Tick() override;

  UFO();
  ~UFO();

  virtual void Move() override;

  FlightDirection ChangeDirection();

  void GenerateAliens();
};