// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#pragma once

// A Class that has an Ability to Force a Thread to Sleep for the Amount of Time that meets the Given Condition  
// Multithreaded Environment Only 
class Time
{
private:
  bool Wake = false;

public:

  void SleepUntilTrue()
  {
    do
    {

    } while (Wake == false);
  }

  void SetSleepUntilTrueValid();

  void WakeUp();
};