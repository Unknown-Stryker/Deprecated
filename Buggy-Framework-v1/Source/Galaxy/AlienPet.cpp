#include "AlienPet.h"
#include "../Engine/Public/CPU_TaskManager.h"


AlienPet::AlienPet()
{
}

AlienPet::~AlienPet()
{
}

void AlienPet::Move()
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