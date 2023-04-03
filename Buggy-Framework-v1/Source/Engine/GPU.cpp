#include "Public/GPU.h"
#include "Public/CPU_TaskManager.h"
#include "../Bug/BugGameMode.h"
#include "../Galaxy/GalaxyGameMode.h"

GPU::GPU(string GameMode_Param) : GameMode(0)
{
  this->BPropertyName = typeid(GPU).name();
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
  this->GameMode = StrToInt(GameMode_Param);

  //Initialize Dynamic Member Function Address Container
  Function_Pointer<GPU>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Initialize(10);

  // Store Function Pointer to Distribute Tasks to Threads (1 Function Unit(FU) = 1 Task);  
  Function_Pointer<GPU>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Insert(0, &GPU::ClearScreen, "ClearScreen");
}

GPU::~GPU()
{
}

void GPU::Rasterize()
{
}

void GPU::ClearScreen()
{
  system("clear");
}


