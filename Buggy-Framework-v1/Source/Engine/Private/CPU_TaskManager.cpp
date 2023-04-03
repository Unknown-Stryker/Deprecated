// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#include "../Public/CPU_TaskManager.h"
using std::cout;
using std::endl;

const unsigned int MAX_THREAD = 10;


CPU_TaskManager* CPU_TaskManager::TaskManagerInstance = nullptr;
CPU_TaskManager& CPU_TaskManager::GetCPU_TaskManager()
{
    if (TaskManagerInstance == nullptr)
    {
        TaskManagerInstance = new CPU_TaskManager;
    }
    return *TaskManagerInstance;
}

CPU_TaskManager::CPU_TaskManager() : BarrierLock(10), Index(-1)
{
    for (int i = 0; i < BarrierLock.GetCapacity(); ++i)
    {
        BarrierLock.Insert( i, true, " ");
    }
}

CPU_TaskManager::~CPU_TaskManager()
{
    if (TaskManagerInstance != nullptr)
    {
        delete TaskManagerInstance;
    }
}

long long CPU_TaskManager::GetBarrierIndex()
{
    return this->Index;
}

long long CPU_TaskManager::IncreaseBarrierIndex()
{
    if (this->Index < MAX_THREAD)
    {
        ++this->Index;
    }
    return this->Index;
}

Time& CPU_TaskManager::GetThreadSleeper()
{
    return ThreadSleeper;
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

