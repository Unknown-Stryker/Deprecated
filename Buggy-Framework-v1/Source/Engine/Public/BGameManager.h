#pragma once
#include "BClass.h"

// A Class For Managing the Entire Game Play Flow (Singleton)
class BGameManager : public BClass
{
private:
  BGameManager* GameMode;
  static BGameManager* SingletonInstance;

  void ChangeGameMode(const string BGameModeName_P);

protected:
  BGameManager();
  BGameManager(const string BGameModeName_P);
  BGameManager(const BGameManager& BGameManager_Param);
  
public:
  ~BGameManager();

  static BGameManager* GetBGameManager(const string BGameModeName_P);

  void SetGameManager(BGameManager* pointer_P);

  BGameManager* GetGameModeAddress();

  virtual void SubMain();
  virtual void EventCheck();

protected:
  string Model;
};