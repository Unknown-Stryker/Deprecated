#include "Bug.h"
#include "../Engine/Public/CPU_TaskManager.h"


Bug::Bug(long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P) : LevelData(nullptr)
{
  //Code Here
  this->BPropertyName = typeid(Bug).name();
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
  
  this->CoordX = BObjectSpawnWorldCoordX_P;
  this->CoordY = BObjectSpawnWorldCoordY_P;
  ObjectSpriteModel.SetSprite("Bug");
  
  //Code Here
  this->LevelData = (B_2DLevel*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("B_2DLevel");
  this->WorldSizeX = this->LevelData->GetWorldSizeX() - 1;
  this->WorldSizeY = this->LevelData->GetWorldSizeY() - 1;

  //Initialize Dynamic Member Function Address Container
  Function_Pointer<Bug>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Initialize(10);

  // Store Function Pointer to Distribute Tasks to Threads (1 Function Unit(FU) = 1 Task);  
  Function_Pointer<Bug>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Insert(0, &Bug::Move, "Move");
}

Bug::~Bug() 
{
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