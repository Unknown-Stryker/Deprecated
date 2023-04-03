#include "Rocket.h"
#include "../Engine/Public/Core.h"


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


}

Rocket::~Rocket()
{
}


void Rocket::Tick()
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

