#pragma once
#include "BClass.h"

// A Basic Level Class thats Stores 2D Map Data as 2D Array 
class B_2DLevel : public BClass
{
public:
  B_2DLevel(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P);
  ~B_2DLevel();
  unsigned long long GetWorldSizeX();
  unsigned long long GetWorldSizeY();

protected:
  unsigned int** World;
  unsigned long long WSizeX;
  unsigned long long WSizeY;
};