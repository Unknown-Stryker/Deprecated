#include "Source/Engine/Public/EngineSystemManager.h"


// Classes which need Tick(), BeginPlay(), and Task Management must be DERIVED FROM BClass.

int main() 
{
  EngineSystemManager::GetEngineSystemManager()->GetGameManagerAddress()->GetGameModeAddress()->SubMain();
  return 0;
}