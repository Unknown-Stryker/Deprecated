#pragma once
#include "BClass.h"

// A Class For Drawing Text Graphics Utilizing A CPU Core
class GPU : public BClass
{
private:
  unsigned long long GameMode;

public:
  GPU(string GameMode_Param);
  ~GPU();

  void Rasterize();
  void ClearScreen();
};
