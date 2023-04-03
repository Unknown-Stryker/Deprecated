#include "../Public/Projectile.h"
#include "../Public/Core.h"
Projectile::Projectile() : Shooter(nullptr), LevelData(nullptr)
{
  
  bActiveObject = false;
  BPropertyName = "Projectile" + UnsignedLongLongToStr( SeperateDigits( Projectile::GetChildInstanceNumber() ) );
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, BPropertyName);

}

Projectile::~Projectile()
{
}

void Projectile::Move()
{
  if(this->bActiveObject == false)
  {
    this->CoordX = this->Shooter->GetCoordX() - 1;
    this->CoordY = this->Shooter->GetCoordY();
    return;
  }
  
  if(this->CoordX > 0)
  {
  --this->CoordX;
  return;
  }
  
  this->bActiveObject = false;
}

void Projectile::Init(string ShooterName_Param, string SpriteModel_Param)
{
  this->Shooter = (BPlayerCharacter*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(ShooterName_Param);
  this->CoordX = this->Shooter->GetCoordX() - 1;
  this->CoordY = this->Shooter->GetCoordY();

  this->LevelData = (B_2DLevel*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("B_2DLevel");
  this->WorldSizeX = LevelData->GetWorldSizeX();
  this->WorldSizeY = LevelData->GetWorldSizeY();

  this->ObjectSpriteModel.SetSprite(SpriteModel_Param);
}