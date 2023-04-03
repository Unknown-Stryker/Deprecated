#pragma once
#include "../Engine/Public/GPU.h"
#include "../Engine/Public/BGameManager.h"
#include "Bug.h"

//BugGameMode에 게임모드 데이터 저장
class BugGameMode : public BGameManager
{
private:
  BugGameMode();
  BugGameMode(const BugGameMode& BugGameMode_Param);
  BugGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);

  static BugGameMode * SingletonInstance;
  
  GPU* BGPU;
  B_2DLevel* BLevel;
  Bug* BBug;

public:
  ~BugGameMode();

  static BugGameMode* GetBugGameMode();
  static BugGameMode* GetBugGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, 
const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);

  //Map Presets
  virtual void MapDataPreset_0() override;
  virtual void MapDataPreset_1() override;

  virtual void SubMain() override;
  virtual void EventCheck() override;
};