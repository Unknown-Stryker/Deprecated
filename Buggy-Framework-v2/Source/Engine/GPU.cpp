#include "Public/GPU.h"
#include "Public/Core.h"
#include "../Galaxy/GalaxyGameMode.h"

GPU::GPU(string MapDataName_Param) : GameModeHashCode(0)
{
  this->BPropertyName = typeid(GPU).name();
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
  this->GameModeHashCode = StrToInt(MapDataName_Param);

  this->GameMode = (BGameManager*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("BugGameMode");
}

GPU::~GPU()
{
}


void GPU::ClearScreen()
{
  system("clear");
}

// In order to avoid Screenspace flickering, avoid to get more than 5 frames per seconds as graphical output
void GPU::Rasterize()
{
  GameMode->MapDataPreset_1();
  // 10000 microseconds = 1 frame per 0.01 sec
  // 10000 mircoseconds = 100fps
  // 400000 mircoseconds = 2.5FPS
  usleep(400000);
  ClearScreen();
}

void GPU::Tick()
{
  Rasterize();
}