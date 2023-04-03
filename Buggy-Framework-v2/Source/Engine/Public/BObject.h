#pragma once
#include "BClass.h"
#include "Sprite.h"

// A Base Class For Unmovable Fixed Static Buggy Engine Objects
class BObject : public BClass
{
protected:
  int CoordX, CoordY;
  bool bActiveObject;
  Sprite ObjectSpriteModel;

public:
  BObject();
  ~BObject();

  virtual long long GetCoordX();
  virtual long long GetCoordY();
  virtual void SetCoordX(long long CoordX_Param);
  virtual void SetCoordY(long long CoordY_Param);

  
  virtual Sprite& GetObjectSpriteModel();

  virtual void SetbActiveObject(bool Active_Param);
  virtual bool GetbActiveObject();
};