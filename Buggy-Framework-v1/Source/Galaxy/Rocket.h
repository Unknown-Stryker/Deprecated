#pragma once
#include "../Engine/Public/BPlayerCharacter.h"
#include "../Engine/Public/B2DLevel.h"
#include "../Engine/Public/Projectile.h"

class Rocket : public BPlayerCharacter
{
private:
  B_2DLevel* LevelData;
  unsigned long long WorldSizeX;
  unsigned long long WorldSizeY;

public:
  Rocket(long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);
  ~Rocket();

  virtual void Move() override;
};