// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once
#include <unistd.h>
#include "EngineSystemManager.h"
#include "BPropertyListManager.h"
#include "Time.h"
#include "Function_Pointer.h"
#include "DataPackage.h"

#include <thread>
using std::thread;

#include <string>
using std::string;

class BugGameMode;
class Bug;
class GPU;

// Data Update Speed < Draw Speed

// Job Stealing 추가 예정
class CPU_TaskManager
{
private:
    CPU_TaskManager();
    static CPU_TaskManager * TaskManagerInstance;
    Time ThreadSleeper;
    long long Index;

public:
    ~CPU_TaskManager();
    static CPU_TaskManager& GetCPU_TaskManager();
    
    long long GetBarrierIndex();
    long long IncreaseBarrierIndex();
    DynamicLinkedArray<bool> BarrierLock;
    Time& GetThreadSleeper();

private:
    static bool bIsBarrierValid;

public:
    static void SetBarrierValid();
    static void SetBarrierInvalid();
    static bool IsBarrierValid();

    template<typename Thread_0_ClassName, typename Thread_0_ClassName2, typename Thread_1_ClassName>
    void DualThreads();

    template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName>
    void QuadThreads();

    template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName>
    void HexaThreads();

    template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName, typename Thread_6_ClassName, typename Thread_7_ClassName>
    void OctaThreads();

    template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName, typename Thread_6_ClassName, typename Thread_7_ClassName, typename Thread_8_ClassName, typename Thread_9_ClassName>
    void DecaThreads();
};

template<typename Thread_0_ClassName, typename Thread_0_ClassName2, typename Thread_1_ClassName>
void CPU_TaskManager::DualThreads()
{
    thread Thread_0
  (
    []()
    {
      cout << "thread 0 Started " << endl;

      auto Task0 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("RainbowMapDataPresets");
      auto Task0Obj = (Thread_0_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_0_ClassName).name());
      
      auto Task3 = Function_Pointer<Thread_1_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("ClearScreen");
      auto Task3Obj = (Thread_1_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_1_ClassName).name());
      
      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(0, true);
        (Task0Obj->*Task0)();
        usleep(400000);
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(0, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();   
        (Task3Obj->*Task3)();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
            
      cout << "thread 0 Ended " << endl;
    }
  );

  thread Thread_1
  (
    []()
    {
      cout << "thread 1 Started " << endl;
      
      auto Task1 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("EventCheck");
      auto Task1Obj = (Thread_0_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_0_ClassName).name());

      auto Task2 = Function_Pointer<Thread_0_ClassName2>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Move");
      auto Task2Obj = (Thread_0_ClassName2*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_0_ClassName2).name());
      
      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(1, true);    
        usleep(400000);
        (Task2Obj->*Task2)();
        (Task1Obj->*Task1)();
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(1, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
            
      cout << "thread 1 Ended " << endl;
    }
  );

    thread BarrierLockManager
    (
        [](void)
        {
            while (CPU_TaskManager::IsBarrierValid() == true)
            {
                if (
                    CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(0) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(1) == false
                    )
                {
                    CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().WakeUp();
                    break;
                }
            }

        }
    );

    Thread_0.join();
    Thread_1.join();
    BarrierLockManager.join();
}

template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName>
void CPU_TaskManager::QuadThreads()
{
  thread Thread_0
  (
    []()
    {
      cout << "thread 0 Started " << endl;

      auto Task0 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("SpaceMapData");
      auto Task0Obj = (Thread_0_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_0_ClassName).name());
      
      auto Task3 = Function_Pointer<Thread_3_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("ClearScreen");
      auto Task3Obj = (Thread_3_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_3_ClassName).name());
      
      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(0, true);
        (Task0Obj->*Task0)();
        usleep(150000);
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(0, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();   
        (Task3Obj->*Task3)();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
          
      cout << "thread 0 Ended " << endl;
    }
  );

  thread Thread_1
  (
    []()
    {
      cout << "thread 1 Started " << endl;
      
      auto Task1 = Function_Pointer<Thread_1_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Move");
      auto Task1Obj = (Thread_1_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress(typeid(Thread_1_ClassName).name());
      
      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(1, true); 
        (Task1Obj->*Task1)();
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(1, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
            
      cout << "thread 1 Ended " << endl;
    }
  );

  thread Thread_2
  (
    []()
    {
      cout << "thread 2 Started " << endl;

      //auto Task2 = Function_Pointer<Thread_2_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Move");
      //auto Task2Obj = (Thread_2_ClassName*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("Projectile");

      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(2, true);
        //(Task2Obj->*Task2)();
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(2, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);
    
      cout << "thread 2 Ended " << endl;
    }
  );

  thread Thread_3
  (
    []()
    {
      cout << "thread 3 Started " << endl;
/*
      auto Task3 = Function_Pointer<Thread_3_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("ClearScreen");
      auto Task3Obj = (GPU*)BPropertyListManager::GetBPropertyListManager()->GetChildAddress("GPU");*/

      do
      {
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(3, true);
        //usleep(290000);
        //(Task3Obj->*Task3)();
        CPU_TaskManager::GetCPU_TaskManager().BarrierLock.Insert(3, false);
        CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().SleepUntilTrue();
      }
      while(EngineSystemManager::GetEngineSystemManager()->GetMainStatus() == true);

      cout << "thread 3 Ended " << endl;
    }
  );

    thread BarrierLockManager
    (
        [](void)
        {
            while (CPU_TaskManager::IsBarrierValid() == true)
            {
                if (
                    CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(0) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(1) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(2) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(3) == false
                    )
                {
                    CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().WakeUp();
                }
            }

        }
    );

    Thread_0.join();
    Thread_1.join();
    Thread_2.join();
    Thread_3.join();

    BarrierLockManager.join();
}

template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName>
void CPU_TaskManager::HexaThreads()
{
    thread Thread_0
    (
        []()
        {
            cout << "thread 0 Started " << endl;

            auto Task0 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 0");

            //(Class::GetClass()->*Task0)();

            cout << "thread 0 Ended " << endl;

        }
    );

    thread Thread_1
    (
        []()
        {
            cout << "thread 1 Started " << endl;

            auto Task1 = Function_Pointer<Thread_1_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 1");

            //(Class::GetClass()->*Task1)();

            cout << "thread 1 Ended " << endl;

        }
    );

    thread Thread_2
    (
        []()
        {
            cout << "thread 2 Started " << endl;

            auto Task2 = Function_Pointer<Thread_2_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 2");

            //(Class::GetClass()->*Task2)();

            cout << "thread 2 Ended " << endl;

        }
    );

    thread Thread_3
    (
        []()
        {
            cout << "thread 3 Started " << endl;

            auto Task3 = Function_Pointer<Thread_3_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 3");

            //(Class::GetClass()->*Task3)();

            cout << "thread 3 Ended " << endl;

        }
    );

    thread Thread_4
    (
        []()
        {
            cout << "thread 4 Started " << endl;

            auto Task4 = Function_Pointer<Thread_4_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 4");

            //(Class::GetClass()->*Task4)();

            cout << "thread 4 Ended " << endl;

        }
    );

    thread Thread_5
    (
        []()
        {
            cout << "thread 5 Started " << endl;

            auto Task5 = Function_Pointer<Thread_5_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 5");

            //(Class::GetClass()->*Task5)();

            cout << "thread 5 Ended " << endl;

        }
    );

    thread BarrierLockManager
    (
        [](void)
        {
            while (CPU_TaskManager::IsBarrierValid() == true)
            {
                if (
                    CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(0) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(1) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(2) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(3) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(4) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(5) == false
                    )
                {
                    CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().WakeUp();
                    break;
                }
            }

        }
    );

    Thread_0.join();
    Thread_1.join();
    Thread_2.join();
    Thread_3.join();
    Thread_4.join();
    Thread_5.join();

    BarrierLockManager.join();
}

template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName, typename Thread_6_ClassName, typename Thread_7_ClassName>
void CPU_TaskManager::OctaThreads()
{
    thread Thread_0
    (
        []()
        {
            cout << "thread 0 Started " << endl;

            auto Task0 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 0");

            //(Class::GetClass()->*Task0)();

            cout << "thread 0 Ended " << endl;

        }
    );

    thread Thread_1
    (
        []()
        {
            cout << "thread 1 Started " << endl;

            auto Task1 = Function_Pointer<Thread_1_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 1");

            //(Class::GetClass()->*Task1)();

            cout << "thread 1 Ended " << endl;

        }
    );

    thread Thread_2
    (
        []()
        {
            cout << "thread 2 Started " << endl;

            auto Task2 = Function_Pointer<Thread_2_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 2");

            //(Class::GetClass()->*Task2)();

            cout << "thread 2 Ended " << endl;

        }
    );

    thread Thread_3
    (
        []()
        {
            cout << "thread 3 Started " << endl;

            auto Task3 = Function_Pointer<Thread_3_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 3");

            //(Class::GetClass()->*Task3)();

            cout << "thread 3 Ended " << endl;

        }
    );

    thread Thread_4
    (
        []()
        {
            cout << "thread 4 Started " << endl;

            auto Task4 = Function_Pointer<Thread_4_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 4");

            //(Class::GetClass()->*Task4)();

            cout << "thread 4 Ended " << endl;

        }
    );

    thread Thread_5
    (
        []()
        {
            cout << "thread 5 Started " << endl;

            auto Task5 = Function_Pointer<Thread_5_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 5");

            //(Class::GetClass()->*Task5)();

            cout << "thread 5 Ended " << endl;

        }
    );

    thread Thread_6
    (
        []()
        {
            cout << "thread 6 Started " << endl;

            auto Task6 = Function_Pointer<Thread_6_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 6");

            //(Class::GetClass()->*Task6)();

            cout << "thread 6 Ended " << endl;

        }
    );

    thread Thread_7
    (
        []()
        {
            cout << "thread 7 Started " << endl;

            auto Task7 = Function_Pointer<Thread_7_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 7");

            //(Class::GetClass()->*Task7)();

            cout << "thread 7 Ended " << endl;

        }
    );

    thread BarrierLockManager
    (
        [](void)
        {
            while (CPU_TaskManager::IsBarrierValid() == true)
            {
                if (
                    CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(0) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(1) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(2) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(3) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(4) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(5) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(6) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(7) == false
                    )
                {
                    CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().WakeUp();
                    break;
                }
            }

        }
    );

    Thread_0.join();
    Thread_1.join();
    Thread_2.join();
    Thread_3.join();
    Thread_4.join();
    Thread_5.join();
    Thread_6.join();
    Thread_7.join();

    BarrierLockManager.join();
}

template<typename Thread_0_ClassName, typename Thread_1_ClassName, typename Thread_2_ClassName, typename Thread_3_ClassName, typename Thread_4_ClassName, typename Thread_5_ClassName, typename Thread_6_ClassName, typename Thread_7_ClassName, typename Thread_8_ClassName, typename Thread_9_ClassName>
void CPU_TaskManager::DecaThreads()
{
    thread Thread_0
    (
        []()
        {
            cout << "thread 0 Started " << endl;

            auto Task0 = Function_Pointer<Thread_0_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 0");

            //(Class::GetClass()->*Task0)();

            cout << "thread 0 Ended " << endl;

        }
    );

    thread Thread_1
    (
        []()
        {
            cout << "thread 1 Started " << endl;

            auto Task1 = Function_Pointer<Thread_1_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 1");

            //(Class::GetClass()->*Task1)();

            cout << "thread 1 Ended " << endl;

        }
    );

    thread Thread_2
    (
        []()
        {
            cout << "thread 2 Started " << endl;

            auto Task2 = Function_Pointer<Thread_2_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 2");

            //(Class::GetClass()->*Task2)();

            cout << "thread 2 Ended " << endl;

        }
    );

    thread Thread_3
    (
        []()
        {
            cout << "thread 3 Started " << endl;

            auto Task3 = Function_Pointer<Thread_3_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 3");

            //(Class::GetClass()->*Task3)();

            cout << "thread 3 Ended " << endl;

        }
    );

    thread Thread_4
    (
        []()
        {
            cout << "thread 4 Started " << endl;

            auto Task4 = Function_Pointer<Thread_4_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 4");

            //(Class::GetClass()->*Task4)();

            cout << "thread 4 Ended " << endl;

        }
    );

    thread Thread_5
    (
        []()
        {
            cout << "thread 5 Started " << endl;

            auto Task5 = Function_Pointer<Thread_5_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 5");

            //(Class::GetClass()->*Task5)();

            cout << "thread 5 Ended " << endl;

        }
    );

    thread Thread_6
    (
        []()
        {
            cout << "thread 6 Started " << endl;

            auto Task6 = Function_Pointer<Thread_6_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 6");

            //(Class::GetClass()->*Task6)();

            cout << "thread 6 Ended " << endl;

        }
    );

    thread Thread_7
    (
        []()
        {
            cout << "thread 7 Started " << endl;

            auto Task7 = Function_Pointer<Thread_7_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 7");

            //(Class::GetClass()->*Task7)();

            cout << "thread 7 Ended " << endl;

        }
    );

    thread Thread_8
    (
        []()
        {
            cout << "thread 8 Started " << endl;

            auto Task8 = Function_Pointer<Thread_8_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 8");

            //(Class::GetClass()->*Task8)();

            cout << "thread 8 Ended " << endl;

        }
    );

    thread Thread_9
    (
        []()
        {
            cout << "thread 9 Started " << endl;

            auto Task9 = Function_Pointer<Thread_9_ClassName>::GetFunction_Pointer(0)->VoidFunction_Pointer.SearchElement("Task 9");

            //(Class::GetClass()->*Task9)();

            cout << "thread 9 Ended " << endl;

        }
    );

    thread BarrierLockManager
    (
        [](void)
        {
            while (CPU_TaskManager::IsBarrierValid() == true)
            {
                if (
                    CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(0) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(1) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(2) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(3) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(4) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(5) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(6) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(7) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(8) == false
                    && CPU_TaskManager::GetCPU_TaskManager().BarrierLock.GetElement(9) == false
                    )
                {
                    CPU_TaskManager::GetCPU_TaskManager().GetThreadSleeper().WakeUp();
                    break;
                }
            }

        }
    );

    Thread_0.join();
    Thread_1.join();
    Thread_2.join();
    Thread_3.join();
    Thread_4.join();
    Thread_5.join();
    Thread_6.join();
    Thread_7.join();
    Thread_8.join();
    Thread_9.join();

    BarrierLockManager.join();
}