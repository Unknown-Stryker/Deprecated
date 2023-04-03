#pragma once
#include "BClass.h"
#include "BGameManager.h"
#include "Function_Pointer.h"

// A Class For Drawing Text Graphics Utilizing A CPU Core
class GPU : public BClass
{
private:
  unsigned long long GameModeHashCode;
  BGameManager* GameMode;

public:
  virtual void Tick() override;
  GPU(string MapDataName_Param);
  ~GPU();

  void Rasterize();
  void ClearScreen();
};
