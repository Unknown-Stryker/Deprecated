#pragma once
#include "../Engine/Public/BPawn.h"
#include "../Engine/Public/B2DLevel.h"
#include "../Engine/Public/MT19937.h"

//부모 포인터에 저장된 주소값을 참조하여 객체 위치 데이터 가져오기 
class Bug : public BPawn
{
private:
  B_2DLevel* LevelData;
  unsigned long long WorldSizeX;
  unsigned long long WorldSizeY;

  MT19937 Random;

public:
  Bug(long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P);
  ~Bug();

  virtual void Move() override;
};