#include "GalaxyGameMode.h"
#include "../Engine/Public/CPU_TaskManager.h"


GalaxyGameMode* GalaxyGameMode::GalaxyGameModeInstance = nullptr;

GalaxyGameMode* GalaxyGameMode::GetGalaxyGameMode()
{
  if(GalaxyGameModeInstance == nullptr)
  {
    GalaxyGameModeInstance = new GalaxyGameMode;
    return GalaxyGameModeInstance;
  }

  return GalaxyGameModeInstance;
}

GalaxyGameMode* GalaxyGameMode::GetGalaxyGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P)
{
  if(GalaxyGameModeInstance == nullptr)
  {
    GalaxyGameModeInstance = new GalaxyGameMode(WorldSizeX_P, WorldSizeY_P, BObjectName_P, BObjectSpawnWorldCoordX_P, BObjectSpawnWorldCoordY_P);
    return GalaxyGameModeInstance;
  }

  return GalaxyGameModeInstance;
}



GalaxyGameMode::GalaxyGameMode()
{
}

GalaxyGameMode::GalaxyGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P)
{
  //Code Here
  this->BPropertyName = typeid(GalaxyGameMode).name();;
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
    
  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 2D레벨 객체의 주소값 저장
  this->GLevel = new B_2DLevel(WorldSizeX_P, WorldSizeY_P);

  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 버그 객체의 주소값 저장
  this->Player = new Rocket(BObjectSpawnWorldCoordX_P, BObjectSpawnWorldCoordY_P);
  
  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 그래픽 처리 유닛 객체의 주소값 저장
  this->GGPU = new GPU("GalaxyGameMode");

  //Initialize Dynamic Member Function Address Container
  Function_Pointer<GalaxyGameMode>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Initialize(10);

  // Store Function Pointer to Distribute Tasks to Threads (1 Function Unit(FU) = 1 Task);  
  Function_Pointer<GalaxyGameMode>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Insert(0, &GalaxyGameMode::SpaceMapData, "SpaceMapData");

  CPU_TaskManager::GetCPU_TaskManager().SetBarrierValid();
}

GalaxyGameMode::~GalaxyGameMode()
{
}



void GalaxyGameMode::SubMain()
{
  CPU_TaskManager::GetCPU_TaskManager().QuadThreads<GalaxyGameMode, Rocket, Projectile, GPU>();
}

void GalaxyGameMode::EventCheck()
{
  
}

void GalaxyGameMode::SpaceMapData()
{
   for(unsigned long long ScreenSpaceX = 0; ScreenSpaceX <= this->GLevel->GetWorldSizeX(); ++ScreenSpaceX)
  {
    for(unsigned long long ScreenSpaceY = 0; ScreenSpaceY <= this->GLevel->GetWorldSizeY(); ++ScreenSpaceY)
    {
      if(ScreenSpaceX == this->Player->GetCoordX() && ScreenSpaceY == this->Player->GetCoordY())
      {
        cout << Player->GetObjectSpriteModel().GetSprite();
      }
      else
      {
        cout << "  ";
      }
    }
    cout << endl;
  }
}