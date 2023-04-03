#pragma once
#include "BGameManager.h"


unsigned long long StrToInt(const string str_P);
unsigned long long* SeperateDigits(unsigned long long Input_Param);
string UnsignedLongLongToStr(unsigned long long* UnsignedInt_Param);

// A Class For Managing The Entire System and the Flow of Buggy Engine
class EngineSystemManager
{
private:
  EngineSystemManager();
  EngineSystemManager(const EngineSystemManager& EngineSystemManager_Param);
  EngineSystemManager& operator=(const EngineSystemManager& EngineSystemManager_Param);

  bool HasPostConstructorBeenCalled;
  void PostConstructor();

  static EngineSystemManager* instance;

  BGameManager* GMPointer;

  bool Active;

  unsigned long long UnLongLongToStrArrSize;

public:
  ~EngineSystemManager();

  static EngineSystemManager* GetEngineSystemManager();

  bool SetMainActive(bool Active_P);
  bool GetMainStatus();

  void SetGameManager(BGameManager* pointer_P);
  BGameManager* GetGameManagerAddress();

private:
  //String Presets
  const string Public;
  const string Protected;
  const string Private;
  
  //경로 저장할 문자열 할당
	string ClassName;
  string ParentClassName;

  //할당 해제 전용
  string* DelClass_H;
  string* DelClass_CPP;
  string* DelHFC;
  string* DelCFC;

  void Intro();

  string* SetClassHeader();
  string* SetClassCPP();

  string* DeclareHeader();
  string* DefineClassCPP();

public:
  string MainMenu();

  void Generate_New_Class();

  void SetUnLongLongToStrArrSize(unsigned long long UnLongLongToStrArrSize_Param);
  unsigned long long GetUnLongLongToStrArrSize();
};