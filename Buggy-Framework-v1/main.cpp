#include "Source/Engine/Public/EngineSystemManager.h"


// Classes which need Framework System Functions must be DERIVED FROM BClass.

int main() 
{
  EngineSystemManager::GetEngineSystemManager()->GetGameManagerAddress()->GetGameModeAddress()->SubMain();
  return 0;
}