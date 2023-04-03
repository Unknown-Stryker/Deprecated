#include "../Public/BClass.h"
#include "../Public/Core.h"

BClass::BClass() : Index(0), Func_ptr(5)
{
  // Construction Code Here

  
  // Post Construction
  this->BeginPlay();
}

BClass::~BClass()
{
}

string BClass::GetBPropertyName() { return this->BPropertyName; }

unsigned long long BClass::ChildInstanceNumber = 0;

unsigned long long BClass::GetChildInstanceNumber()
{
	++ChildInstanceNumber;

	return ChildInstanceNumber;
}

unsigned long long BClass::IndexIterator(unsigned long long IndexLimit)
{
  if(this->Index < IndexLimit)
  {
    ++this->Index;
    return this->Index;
  }
  else
  {
    this->Index = 0;
    return this->Index;
  }
}

void BClass::MakeTick()
{
  
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Initialize(50);
  
  // Set Tags
  this->BPropertyName = typeid(this).name() + SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.IndexIterator();
  ObjectSerialNumber = SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.GetIndex();
  TickNameTag = this->BPropertyName + "Tick";
  
  // Store this Pointer(self) with Bproperty Name Tag in the Global Data Container
  SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.Insert( ObjectSerialNumber, this, this->BPropertyName );

  // Store Member Function Pointer in the Global Function Address Container
  Func_ptr.Local_void_func_ptr.Insert(ObjectSerialNumber, &BClass::Tick, TickNameTag);
  
  thread TickThread
  (
    []()
    {
      cout << typeid(this).name() << " Tick Started " << endl;

      BClass* TickExecutor = (BClass*)SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.GetElement( SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.GetIndex() );
      auto Tick = TickExecutor->Func_ptr.Local_void_func_ptr.GetElement( SendDataToThreads<BClass*>::DeliverDataToThreads()->Container.GetIndex() );
      
      do
      {
        //CPU_TaskManager::GetManagerInstance()->BarrierLock.Insert(SendDataToThreads<string>::DeliverDataToThreads()->Container.GetIndex(), true);
        (TickExecutor->*Tick)();
        //CPU_TaskManager::GetManagerInstance()->BarrierLock.Insert(0, false);
        //CPU_TaskManager::GetManagerInstance()->GetThreadSleeper().SleepUntilTrue();   
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
      
       cout << typeid(this).name() << " Tick Ended " << endl;
    }
  );

  TickThread.join();
}


void BClass::Tick()
{  
}

void BClass::BeginPlay()
{
}