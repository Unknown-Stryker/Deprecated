#pragma once
#include "../Engine/Public/BGameManager.h"
#include "../Engine/Public/GPU.h"
#include "UFO.h"
#include "Gift.h"
#include "Rocket.h"


class GalaxyGameMode : public BGameManager
{
private:
  GalaxyGameMode();
  GalaxyGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);
  
  static GalaxyGameMode* GalaxyGameModeInstance;

  GPU* GGPU;
  B_2DLevel* GLevel;

  UFO* GUFO;

  Gift* GGift;

  Rocket* Player;

  Projectile* ProjectileOfAPlayer;

public:
  ~GalaxyGameMode();

  static GalaxyGameMode* GetGalaxyGameMode();
  static GalaxyGameMode* GetGalaxyGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);

  virtual void SubMain() override;
  virtual void EventCheck() override;
  void SpaceMapData();
};
