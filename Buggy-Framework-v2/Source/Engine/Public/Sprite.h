#pragma once
#include <string>
using std::string;

// Sprite Component Class : It Always Must Be Owned by Other In Game Object Classes (Has-A Only)
class Sprite
{
private:
  string SpriteModel;

public:
  Sprite();
  Sprite(string ModelName_Param);
  ~Sprite();
  void SetSprite(string ModelName_Param);
  string GetSprite();
};
