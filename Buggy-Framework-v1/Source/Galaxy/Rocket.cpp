#include "Rocket.h"
#include "../Engine/Public/CPU_TaskManager.h"


Rocket::Rocket(long long BObjectSpawnWorldCoordX_P, long long BObjectSpawnWorldCoordY_P) : LevelData(nullptr)
{
  this->CoordX = BObjectSpawnWorldCoordX_P;
  this->CoordY = BObjectSpawnWorldCoordY_P;

   //Code Here
  this->BPropertyName = typeid(Rocket).name();
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);

  //Code Here
  ObjectSpriteModel.SetSprite("Rocket");

  //Code Here
  this->LevelData = (B_2DLevel*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("B_2DLevel");
  this->WorldSizeX = this->LevelData->GetWorldSizeX() - 1;
  this->WorldSizeY = this->LevelData->GetWorldSizeY() - 1;

  //Initialize Dynamic Member Function Address Container
  Function_Pointer<Rocket>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Initialize(10);

  // Store Function Pointer to Distribute Tasks to Threads (1 Function Unit(FU) = 1 Task);  
  Function_Pointer<Rocket>::GetFunction_Pointer(0, 1)->VoidFunction_Pointer.Insert(0, &Rocket::Move, "Move");
}

Rocket::~Rocket()
{
}

void Rocket::Move()
{
  switch(getch())
  {
    // w
    case 119:
      if(this->CoordX > 0)
      {
        --this->CoordX;
        return;
      }
      break;

    // a
    case 97:
      if(this->CoordY > 0)
      {
        --this->CoordY;
        return;
      }
      break;
    
    // s
    case 115:
      if(this->CoordX < this->WorldSizeX)
      {
        ++this->CoordX;
        return;
      }
      break;
    
    // d
    case 100:
      if(this->CoordY < this->WorldSizeY)
      {
        ++this->CoordY;
        return;
      }
      break;

    // [Space]
    case 32:
      break;

    default:
      return;
  }
}