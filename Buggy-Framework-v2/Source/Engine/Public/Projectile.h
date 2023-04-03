#pragma once
#include "BPlayerCharacter.h"
#include "B2DLevel.h"

class Projectile : public BPawn
{
private:
  BPlayerCharacter* Shooter;

  B_2DLevel* LevelData;
  unsigned long long WorldSizeX;
  unsigned long long WorldSizeY;

public:
  Projectile();
  ~Projectile();

  virtual void Move() override;

  void Init(string ShooterName_Param, string SpriteModel_Param);
};
