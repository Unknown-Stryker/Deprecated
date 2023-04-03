#include "../Public/BObject.h"


BObject::BObject() : CoordX(0), CoordY(0), ObjectSpriteModel(""), bActiveObject(true)
{
  this->BPropertyName = "BObject";
}

BObject::~BObject() 
{
}


long long BObject::GetCoordX() {return this->CoordX;}

long long BObject::GetCoordY() {return this->CoordY;}

void BObject::SetCoordX(long long CoordX_Param) {this->CoordX = CoordX_Param;}
void BObject::SetCoordY(long long CoordY_Param) {this->CoordY = CoordY_Param;}

Sprite& BObject::GetObjectSpriteModel()
{
  return ObjectSpriteModel;
}

void BObject::SetbActiveObject(bool Active_Param)
{
  this->bActiveObject = Active_Param;
}

bool BObject::GetbActiveObject()
{
  return this->bActiveObject;
}

