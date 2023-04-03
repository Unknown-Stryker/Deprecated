#include "BugGameMode.h"
#include "../Engine/Public/Core.h"
#include <unistd.h>

BugGameMode* BugGameMode::SingletonInstance = nullptr;

BugGameMode* BugGameMode::GetBugGameMode()
{
  if(SingletonInstance == nullptr)
  {
    SingletonInstance = new BugGameMode;
    return SingletonInstance;
  }
  
  return SingletonInstance;
}

BugGameMode* BugGameMode::GetBugGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, 
const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P)
{
  if(SingletonInstance == nullptr)
  {
    SingletonInstance = new BugGameMode(WorldSizeX_P, WorldSizeY_P, BObjectName_P, BObjectSpawnWorldCoordX_P, BObjectSpawnWorldCoordY_P);
    return SingletonInstance;
  }
  
  return SingletonInstance;
}


BugGameMode::BugGameMode()
{ 
}

BugGameMode::BugGameMode(const BugGameMode& BugGameMode_Param)
{ 
}

BugGameMode::BugGameMode(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P, 
const string BObjectName_P, long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P)
{
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Initialize(5);
  //Code Here
  this->BPropertyName = "BugGameMode";
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Insert( SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.IndexIterator(), this, this->BPropertyName );
  
  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 2D레벨 객체의 주소값 저장
  this->BLevel = new B_2DLevel(WorldSizeX_P, WorldSizeY_P);

  //Code Here
  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 버그 객체의 주소값 저장
  this->BBug = new Bug(BObjectSpawnWorldCoordX_P, BObjectSpawnWorldCoordY_P);
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Insert(SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.IndexIterator(), this->BBug, "Bug");

  
  //Code Here
  //부모 포인터에 주소값 반환
  //BPropertyManager 부모 포인터 배열로부터 맴버 포인터에 그래픽 처리 유닛 객체의 주소값 저장
  this->BGPU = new GPU(" ");
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this->BGPU, "GPU");
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Insert(SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.IndexIterator(), this->BGPU, "GPU");
  
  CPU_TaskManager::GetManagerInstance()->SetBarrierValid();
}

BugGameMode::~BugGameMode() 
{
  delete BLevel;
  delete BBug;
  delete BGPU;
}


void BugGameMode::SubMain()
{
  thread Graphics
  (
    []()
    {
      BPropertyListManager::GetBPropertyListManager()->GetChildAddress("GPU")->MakeTick();
    }
  );

  thread GamePlay
  (
    []()
    {
      // delay for 0.1 sec to prevent data race condition
      usleep(100000);
      BPropertyListManager::GetBPropertyListManager()->GetChildAddress("Bug")->MakeTick();
    }
  );

  Graphics.join();
  GamePlay.join();
}

void BugGameMode::EventCheck()
{
  if(BBug->GetCoordX() == 9 && BBug->GetCoordY() == 9)
  {
    CPU_TaskManager::GetManagerInstance()->SetBarrierInvalid();
    cout << "Congratulations! : The Bug Successfully Managed to Escape!" << endl;
    sleep(10);
    EngineSystemManager::GetEngineSystemManager()->SetMainActive(false);
  }
}


void BugGameMode::MapDataPreset_0()
{
  for(unsigned long long ScreenSpaceX = 0; ScreenSpaceX <= this->BLevel->GetWorldSizeX(); ++ScreenSpaceX)
  {
    for(unsigned long long ScreenSpaceY = 0; ScreenSpaceY <= this->BLevel->GetWorldSizeY(); ++ScreenSpaceY)
    {
      if(ScreenSpaceX == this->BBug->GetCoordX() && ScreenSpaceY == this->BBug->GetCoordY())
      {
        cout << BBug->GetObjectSpriteModel().GetSprite();
      }
      else
      {
        if(ScreenSpaceX == 0 || ScreenSpaceX == 10 || ScreenSpaceY == 0 || ScreenSpaceY == 10)
        {
          cout << "🟨";
        }
        else if(ScreenSpaceX == 9 && ScreenSpaceY == 9)
        {
          cout << "🤑";
        }
        else
        {
          cout << "  ";
        }
      }
    }
    cout << endl;
  }
}

void BugGameMode::MapDataPreset_1()
{
  for(unsigned long long ScreenSpaceX = 0; ScreenSpaceX <= this->BLevel->GetWorldSizeX(); ++ScreenSpaceX)
  {
    for(unsigned long long ScreenSpaceY = 0; ScreenSpaceY <= this->BLevel->GetWorldSizeY(); ++ScreenSpaceY)
    {
      if(ScreenSpaceX == this->BBug->GetCoordX() && ScreenSpaceY == this->BBug->GetCoordY())
      {
        cout << BBug->GetObjectSpriteModel().GetSprite();
      }
      else
      {
        if((ScreenSpaceX == 0 && ScreenSpaceY == 0) || (ScreenSpaceX == 5 && ScreenSpaceY == 0) 
          || (ScreenSpaceX == 0 && ScreenSpaceY == 5) || (ScreenSpaceX == 0 && ScreenSpaceY == 10)
          || (ScreenSpaceX == 5 && ScreenSpaceY == 10) || (ScreenSpaceX == 10 && ScreenSpaceY == 0)
          || (ScreenSpaceX == 10 && ScreenSpaceY == 5) || (ScreenSpaceX == 10 && ScreenSpaceY == 10))
        {
          cout << "🟥";
        }
        else if((ScreenSpaceX == 0 && ScreenSpaceY == 1) || (ScreenSpaceX == 0 && ScreenSpaceY == 6) 
          || (ScreenSpaceX == 1 && ScreenSpaceY == 10) || (ScreenSpaceX == 6 && ScreenSpaceY == 10)
          || (ScreenSpaceX == 10 && ScreenSpaceY == 9) || (ScreenSpaceX == 10 && ScreenSpaceY == 4)
          || (ScreenSpaceX == 9 && ScreenSpaceY == 0) || (ScreenSpaceX == 4 && ScreenSpaceY == 0))
        {
          cout << "🟧";
        }
        else if((ScreenSpaceX == 0 && ScreenSpaceY == 2) || (ScreenSpaceX == 0 && ScreenSpaceY == 7) 
          || (ScreenSpaceX == 2 && ScreenSpaceY == 10) || (ScreenSpaceX == 7 && ScreenSpaceY == 10)
          || (ScreenSpaceX == 10 && ScreenSpaceY == 8) || (ScreenSpaceX == 10 && ScreenSpaceY == 3)
          || (ScreenSpaceX == 8 && ScreenSpaceY == 0) || (ScreenSpaceX == 3 && ScreenSpaceY == 0))
        {
          cout << "🟨";
        }
        else if((ScreenSpaceX == 0 && ScreenSpaceY == 3) || (ScreenSpaceX == 0 && ScreenSpaceY == 8) 
          || (ScreenSpaceX == 3 && ScreenSpaceY == 10) || (ScreenSpaceX == 8 && ScreenSpaceY == 10)
          || (ScreenSpaceX == 10 && ScreenSpaceY == 7) || (ScreenSpaceX == 10 && ScreenSpaceY == 2)
          || (ScreenSpaceX == 7 && ScreenSpaceY == 0) || (ScreenSpaceX == 2 && ScreenSpaceY == 0))
        {
          cout << "🟩";
        }
        else if((ScreenSpaceX == 0 && ScreenSpaceY == 4) || (ScreenSpaceX == 0 && ScreenSpaceY == 9) 
          || (ScreenSpaceX == 4 && ScreenSpaceY == 10) || (ScreenSpaceX == 9 && ScreenSpaceY == 10)
          || (ScreenSpaceX == 10 && ScreenSpaceY == 6) || (ScreenSpaceX == 10 && ScreenSpaceY == 1)
          || (ScreenSpaceX == 6 && ScreenSpaceY == 0) || (ScreenSpaceX == 1 && ScreenSpaceY == 0))
        {
          cout << "🟦";
        } // Exfil Point Flag
        else if(ScreenSpaceX == 9 && ScreenSpaceY == 9)
        {
          cout << "🚩";
        } // Fill Screen with Space 
        else
        {
          cout << "  ";
        }
      }
    }
    cout << endl;
  }
}