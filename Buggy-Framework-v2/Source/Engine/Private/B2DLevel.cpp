#include "../Public/B2DLevel.h"
#include "../Public/BPropertyListManager.h"

B_2DLevel::B_2DLevel(unsigned long long WorldSizeX_P, unsigned long long WorldSizeY_P)
{
  //Code Here
  this->WSizeX = WorldSizeX_P;
  this->WSizeY = WorldSizeY_P;
  
  this->World = new unsigned int*[WorldSizeX_P] {nullptr};
  for(unsigned int init; init < WorldSizeY_P; ++init)
  {
    this->World[init] = new unsigned int[WorldSizeY_P] {0};
  }

  //Code Here
  this->BPropertyName = "B_2DLevel";
  BPropertyListManager::GetBPropertyListManager()->RegisterChild(this, this->BPropertyName);
}

B_2DLevel::~B_2DLevel()
{
  for(unsigned int del; del < WSizeY; ++del)
  {
    delete [] this->World[del];
  }
  delete [] this->World;
}

unsigned long long B_2DLevel::GetWorldSizeX() { return this->WSizeX; }

unsigned long long B_2DLevel::GetWorldSizeY() { return this->WSizeY; }