#include "UFO.h"


UFO::UFO()
{
  this->Somewhere = (FlightDirection)0;
    /*this->RightOrLeft.GetRangedRandomInteger(0, 1);*/

  this->CoordX = 0;
  this->CoordY = 0;
  
}

UFO::~UFO()
{
}

void UFO::Move()
{
  switch(Somewhere)
  {
    case FlightDirection::Right:
      ++CoordX;
      break;

    case FlightDirection::Left:
       --CoordX;
      break;
  }
}

FlightDirection UFO::ChangeDirection()
{
  this->Somewhere = (FlightDirection)this->RightOrLeft.GetRangedRandomInteger(0, 1);

  return Somewhere;
}

void UFO::GenerateAliens()
{
  
}