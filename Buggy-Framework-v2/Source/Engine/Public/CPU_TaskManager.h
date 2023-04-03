// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once
#include "Time.h"
#include "DynamicLinkedArray.h"
#include <thread>
using std::thread;

// Data Update Speed < Draw Speed

// Job Stealing 추가 예정
class CPU_TaskManager
{
private:
  static CPU_TaskManager* ManagerInstance;
  CPU_TaskManager();
public:
  ~CPU_TaskManager();
  static CPU_TaskManager* GetManagerInstance();

private:
 Time ThreadSleeper;
public:
  Time& GetThreadSleeper();

private:
  long long Index;
public:
  long long GetBarrierIndex();
  long long IncreaseBarrierIndex();
  DynamicLinkedArray<bool> BarrierLock;

private:
  static bool bIsBarrierValid;
public:
  static void SetBarrierValid();
  static void SetBarrierInvalid();
  static bool IsBarrierValid();
  void BarrierManager();

private:
  long long InstanceNumber;
public:
  long long GetInstanceNumber();
  long long IterateInstanceNumber(long long IndexLimit);
};