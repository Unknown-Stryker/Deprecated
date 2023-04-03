// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#include <unistd.h>
#include "../Public/CPU_TaskManager.h"
#include "../Public/Function_Pointer.h"
using std::cout;
using std::endl;

CPU_TaskManager* CPU_TaskManager::ManagerInstance = nullptr;

CPU_TaskManager* CPU_TaskManager::GetManagerInstance()
{
  if(ManagerInstance != nullptr)
  {
    return ManagerInstance;
  }

  ManagerInstance = new CPU_TaskManager;
  return ManagerInstance;
}

CPU_TaskManager::CPU_TaskManager() : BarrierLock(50), Index(-1)
{
  for (int i = 0; i < BarrierLock.GetCapacity(); ++i)
  {
    BarrierLock.Insert( i, true, " ");
  }
}

CPU_TaskManager::~CPU_TaskManager()
{
}


Time& CPU_TaskManager::GetThreadSleeper()
{
  return ThreadSleeper;
}


long long CPU_TaskManager::GetBarrierIndex()
{
  return this->Index;
}

long long CPU_TaskManager::IncreaseBarrierIndex()
{
  ++this->Index;
  return this->Index;
}


bool CPU_TaskManager::bIsBarrierValid = false;

void CPU_TaskManager::SetBarrierValid()
{
    bIsBarrierValid = true;
}

void CPU_TaskManager::SetBarrierInvalid()
{
    bIsBarrierValid = false;
}

bool CPU_TaskManager::IsBarrierValid()
{
    return bIsBarrierValid;
}


long long CPU_TaskManager::GetInstanceNumber()
{
  return this->InstanceNumber;
}

long long CPU_TaskManager::IterateInstanceNumber(long long IndexLimit)
{
  if(this->InstanceNumber < IndexLimit)
  {
    ++this->InstanceNumber;
    return this->InstanceNumber;
  }
  else
  {
    return this->InstanceNumber;
  }
}


void CPU_TaskManager::BarrierManager()
{
  thread BarrierLockManager
  (
    [](void)
    {
      unsigned long long UnlockSign = 0;
      
      while (CPU_TaskManager::IsBarrierValid() == true)
      {
        if ( CPU_TaskManager::GetManagerInstance()->BarrierLock.GetElement
          (
            CPU_TaskManager::GetManagerInstance()->IterateInstanceNumber
            (
              CPU_TaskManager::GetManagerInstance()->BarrierLock.GetCapacity()
            )
          ) == false )
        {
          ++UnlockSign;
          if(CPU_TaskManager::GetManagerInstance()->InstanceNumber == UnlockSign)
          {
            CPU_TaskManager::GetManagerInstance()->ThreadSleeper.WakeUp();
          }
        }
      }
    }
  );

  BarrierLockManager.join();
}
