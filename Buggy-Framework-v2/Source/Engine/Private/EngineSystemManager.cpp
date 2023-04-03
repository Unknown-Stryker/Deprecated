#include "../Public/EngineSystemManager.h"
#include <fstream>
#include <unistd.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ios;

//여기서 Play 함수 관리하기

EngineSystemManager* EngineSystemManager::instance = nullptr;

EngineSystemManager* EngineSystemManager::GetEngineSystemManager()
{
  if(instance == nullptr)
  {
    instance = new EngineSystemManager;
    //cout << "Engine System Manager Instance Allocated : " << instance << endl;
    return instance;
  }
  //cout << "Engine System Manager Instance Address: " << instance << endl;
  return instance;
}

EngineSystemManager::EngineSystemManager() : GMPointer(nullptr), Active(true), UnLongLongToStrArrSize(0),
Public(" : public "), Protected(" : protected "), Private(" : private "),
ClassName("\0"), ParentClassName("\0"), 
DelClass_H(nullptr), DelClass_CPP(nullptr), 
DelHFC(nullptr), DelCFC(nullptr), HasPostConstructorBeenCalled(false)
{
}

void EngineSystemManager::PostConstructor()
{
  if(instance != nullptr && HasPostConstructorBeenCalled == false)
  {
    this->HasPostConstructorBeenCalled = true;
    string CMD = MainMenu();
    
    bool BullShit = true;
    while(BullShit == true)
    {
      switch(StrToInt(CMD))
      {
        default:
          BullShit = true;
          CMD = MainMenu();
          break;
      
        case 81:
          BullShit = false;
          cout << "\tThe Process has been Expired." << endl;
          exit(0);
          break;
    
        case 2172:
          //파일입출력으로 클래스 생성 및 소스코드 추가
          Generate_New_Class();
          system("clear");
          break;
      
        case 2204:
          BullShit = false;
          //파일 입출력으로 존재하는 게임모드 리스트 출력
          cout << "0. Default Game Mode : The Bug's Journey" << endl
            << "1. Game Mode : Alien Invader(Not Avaliable)" << endl
            << "Select Mode Number : ";
          unsigned int Mode = 0;
          cin >> Mode;
          cout << endl;
      
          switch(Mode)
          {
            case 0: CMD = "BugGameMode";
              break;

            case 1: CMD = "GalaxyGameMode";
              break;
            
            default: CMD = "BugGameMode";
          }
        
          cout << endl << "*|------DEBUG LOG------|*" << endl;
          cout << "Compilation Successful!" << endl;

          //게임 매니저 생성 후, GMPointer에 생성된 게임모드 객체 주소값 반환
          SetGameManager( BGameManager::GetBGameManager(CMD) );
          break;
      }
    }
    
    system("clear");
  }
  else
  {
    return;
  }
}

EngineSystemManager::EngineSystemManager(const EngineSystemManager& EngineSystemManager_Param)
{
}

EngineSystemManager& EngineSystemManager::operator=(const EngineSystemManager& EngineSystemManager_Param)
{ 
  *this = EngineSystemManager_Param; 
  return *this;
}

EngineSystemManager::~EngineSystemManager()
{
  delete GMPointer;
  delete instance;
  std::cout << "\tThe Process has been Expired." << std::endl;
}


string EngineSystemManager::MainMenu()
{
  system("clear");
  cout << "\t<Main Menu>" << endl << endl 
    << "1. Input \"Create\" to Gernerate a New Class" << endl 
    << "2. Input \"Select\" to Play Existing Game Modes" << endl 
    << "3. Input \"Q\" to Exit" << endl
    << "Command : ";
  string CMD;
  cin >> CMD;
  system("clear");

  return CMD;
}


void EngineSystemManager::SetGameManager(BGameManager* pointer_P) {this->GMPointer = pointer_P;}

BGameManager* EngineSystemManager::GetGameManagerAddress() 
{
  this->PostConstructor();
  return this->GMPointer;
}


void EngineSystemManager::Intro()
{
  system("clear");
	cout << "Use Command \"cancel\" to quit" << endl 
    << "Name a New Class to Create : ";
  
  //클래스 파일이름 입력
	cin >> ClassName;
	cout << endl;

  if(ClassName == "cancel")
  {
    cout << "Class Generation Cancelled" << endl;
    exit(0);
  }
}


string* EngineSystemManager::SetClassHeader()
{
  //경로 설정
	string* Class_H = new string(ClassName + ".h");
  this->DelClass_H = Class_H;
  return Class_H;
}

string* EngineSystemManager::SetClassCPP()
{
  //경로 설정
	string* Class_CPP = new string(ClassName + ".cpp");
  this->DelClass_CPP = Class_CPP;
  return Class_CPP;
}


string* EngineSystemManager::DeclareHeader()
{
  cout << "is This Class Derived From a Parent Class?\nInput the Name of Parent Class if it is : ";
  cin >> ParentClassName;
  cout << endl;

  string DerivationProtectionLevel("\0");
  string ParentClassHeaderName("\0");
  
  if(ParentClassName != "no")
  {
    cout << "Header File Name of the Parent Class\nEX) \"Parent.h\" : ";
    
    cin >> ParentClassHeaderName;
    ParentClassHeaderName = "#include " + ParentClassHeaderName;
    cout << endl;

    cout << "Default is public\n0. public\n1. protected\n2. private\nDerivation Protection Level : ";
    unsigned short ProtectionLevel(0);
    cin >> ProtectionLevel;
    cout << endl;
    
    switch(ProtectionLevel)
    {
      case 0:
        DerivationProtectionLevel = Public;
        break;

      case 1:
        DerivationProtectionLevel = Protected;
        break;

      case 2:
        DerivationProtectionLevel = Private;
        break;

      default:
        DerivationProtectionLevel = Public;
        break;
    }
  }
  else if(ParentClassName == "no")
  {
    ParentClassName = "\0";
  }
  
  //헤더 파일코드 작성
  string* HeaderFileCode = new string
  (
  "#pragma once\n" 
  + ParentClassHeaderName + "\n\nclass " 
  + ClassName + DerivationProtectionLevel + ParentClassName
  + "\n{\nprivate:\n\nprotected:\n\npublic:\n  "
  + ClassName + "();\n  ~"
  + ClassName + "();\n};\n"
  );
  this->DelHFC = HeaderFileCode;
  return HeaderFileCode;
}

string* EngineSystemManager::DefineClassCPP()
{
  //Cpp 소스코드 작성
	string* CppFileCode = new string
  (
  "#include \"" + ClassName + ".h\"\n\n"
  + ClassName + "::" + ClassName + "()\n{\n}\n\n"
  + ClassName + "::~" + ClassName + "()\n{\n}\n\n"
  );
  this->DelCFC = CppFileCode;
  return CppFileCode;
}


void EngineSystemManager::Generate_New_Class()
{
  Intro();

  //헤더 파일 생성 및 출력
  const char* Class_H = SetClassHeader()->c_str();
	fstream HeaderFile(Class_H, ios::out);
  //경로 확인 <디버깅>
  cout << Class_H << endl;
  
  //헤더 파일코드 출력
  HeaderFile << DeclareHeader()->c_str();
	HeaderFile.close();
  delete this->DelClass_H;
  delete this->DelHFC;


  
  //cpp 파일 생성 및 출력
  const char* Class_CPP = SetClassCPP()->c_str();
	fstream CppFile(Class_CPP, ios::out);
  //경로 확인 <디버깅>
  cout  << Class_CPP << endl;
  
  // Cpp 소스코드 출력
  CppFile << DefineClassCPP()->c_str();
	CppFile.close();
  delete this->DelClass_CPP;
  delete this->DelCFC;

  sleep(1);
  system("clear");
}


bool EngineSystemManager::SetMainActive(bool Active_P = true)
{
  this->Active = Active_P;

  return this->Active;
}

bool EngineSystemManager::GetMainStatus()
{
  return this->Active;
}

unsigned long long StrToInt(const string str)
{
  //Get Length Of a String
  unsigned long long length = 0;
  for(; str[length] != '\0'; ++length){}

  //Convert String into Integer Value
  unsigned long long CODE = 0; 
  for(unsigned long long i = 0; i < length; ++i)
  {
    CODE = CODE + ((unsigned long long)str[i] * (i+1));
  }
  return CODE;
}

const unsigned int ASCII = 48;

unsigned long long* SeperateDigits(unsigned long long Input_Param)
{
	if (Input_Param < 10)
	{
    EngineSystemManager::GetEngineSystemManager()->SetUnLongLongToStrArrSize(1);
		return new unsigned long long(Input_Param);
	}
	else
	{
		// Count Digits
		unsigned long long DigitLength = 0;
		unsigned long long TenTimes = 1;
		for (; TenTimes <= Input_Param; TenTimes *= 10)
		{
			++DigitLength;
		}

		// Allocate an Array to Return 
		unsigned long long* Digits = new unsigned long long[DigitLength] {0};

		// Segregate Based on Digit : 123 Equals to 123, 23, 3
		unsigned long long Multi = 1;
		for (unsigned long long Digit = 1; Digit <= DigitLength; ++Digit)
		{
			for (unsigned long long i = 1; i < Digit; ++i)
			{
				Multi *= 10;
			}
			Digits[DigitLength - Digit] = Input_Param % (10 * Multi);
			Multi = 1;
		}

		// Segregate Based On the First Number : 123 Equals to 100, 20, 3
		for (unsigned long long polish = 0; polish < DigitLength-1; ++polish)
		{
			Digits[polish] -= Digits[polish + 1];
		}

		// Divide Segregated Numbers Based on Digits
		unsigned long long Index = 0;
		for (unsigned long long Divider = TenTimes /= 10; Divider > 0; Divider /= 10)
		{
			Digits[Index] /= Divider;
			++Index;
		}
    EngineSystemManager::GetEngineSystemManager()->SetUnLongLongToStrArrSize(DigitLength);
		return Digits;
	}
}

string UnsignedLongLongToStr(unsigned long long* UInt_Param)
{
	unsigned long long ArrayLength = (unsigned long long)EngineSystemManager::GetEngineSystemManager()->GetUnLongLongToStrArrSize() / 8;

	string Integer("");

	for (unsigned long long Digit = 0; Digit < ArrayLength; ++Digit)
	{
		Integer += (char)(UInt_Param[Digit] + ASCII);
	}

  if(ArrayLength > 1)
  {
    delete[] UInt_Param;
  }
  else
  {
    delete UInt_Param;
  }
  
	return Integer;
}

void EngineSystemManager::SetUnLongLongToStrArrSize(unsigned long long UnLongLongToStrArrLength_Param)
{
  this->UnLongLongToStrArrSize = UnLongLongToStrArrLength_Param;
}

unsigned long long EngineSystemManager::GetUnLongLongToStrArrSize()
{
  return this->UnLongLongToStrArrSize;
}