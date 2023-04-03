#include "Bug.h"
#include "../Engine/Public/Core.h"


Bug::Bug(long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P) : LevelData(nullptr)
{
  //Code Here
  this->BPropertyName = "Bug";
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
  
  this->CoordX = BObjectSpawnWorldCoordX_P;
  this->CoordY = BObjectSpawnWorldCoordY_P;
  ObjectSpriteModel.SetSprite("Bug");
  
  //Code Here
  this->LevelData = (B_2DLevel*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("B_2DLevel");
  this->WorldSizeX = this->LevelData->GetWorldSizeX() - 1;
  this->WorldSizeY = this->LevelData->GetWorldSizeY() - 1;
  this->BeginPlay();
}

Bug::~Bug() 
{
}


void Bug::Tick()
{
  Move();
  // 0.5 sec delay
  // 1 move per 5 fps
  usleep(500000);
  DidItEscape();
}


void Bug::Move()
{
  switch(Random.GetRangedRandomInteger(0, 3))
  {
    case 0:
      if(CoordX > 1)
      {
        --CoordX;
      }
      else
      {
        ++CoordX;
      }
    break;

    case 1:
      if(CoordY < this->WorldSizeY)
      {
        ++CoordY;
      }
      else
      {
        --CoordY;
      }
    break;

    case 2:
      if(CoordX < this->WorldSizeX)
      {
        ++CoordX;
      }
      else
      {
        --CoordX;
      }
    break;

    case 3:
      if(CoordY > 1)
      {
        --CoordY;
      }
      else
      {
        ++CoordY;
      }
    break;
  }
}

void Bug::DidItEscape()
{
  if(CoordX == 9 && CoordY == 9)
  {
    cout << "Congratulations! : The Bug Successfully Managed to Escape!" << endl;
    sleep(4);
    EngineSystemManager::GetEngineSystemManager()->SetMainActive(false);
  }
}

void Bug::BeginPlay()
{
  
}