#include "Public/BGameManager.h"
#include "Public/CPU_TaskManager.h"
#include "../Bug/BugGameMode.h"
#include "../Galaxy/GalaxyGameMode.h"

BGameManager* BGameManager::SingletonInstance = nullptr;

BGameManager* BGameManager::GetBGameManager(const string BGameModeName_P = "")
{
  if(SingletonInstance == nullptr)
  {
    SingletonInstance = new BGameManager(BGameModeName_P);
    return SingletonInstance;
  }
  
  return SingletonInstance;
}

void BGameManager::ChangeGameMode(const string BGameModeName_P)
{
  //UI and Call StrToInt Switch Case Here
}

BGameManager::BGameManager() : GameMode(nullptr) {}

BGameManager::BGameManager(const string BGameModeName_P) : GameMode(nullptr)
{
  //Code Here
  this->BPropertyName = typeid(BGameManager).name();
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);

  //Code Here
  switch(StrToInt(BGameModeName_P))
  {
    case 6465:
      //                                    레벨크기, 캐릭터이름, 캐릭터스폰위치
      //생성된 게임모드 객체 주소값 BGameManager 부모 포인터에 반환
      GameMode = BugGameMode::GetBugGameMode(10, 10, "Bug",        5, 5);
    break;

    case 10460:
      GameMode = GalaxyGameMode::GetGalaxyGameMode(20, 20, "Rocket", 10, 10);
      break;
  }
}

BGameManager::~BGameManager() 
{
  delete GameMode;
  delete SingletonInstance;
}

BGameManager* BGameManager::GetGameModeAddress() {return this->GameMode;}


void BGameManager::SubMain()
{
}

void BGameManager::EventCheck()
{ 
}