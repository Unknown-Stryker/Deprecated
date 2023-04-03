// Copyright © June 6th, 2022. Team Creator, 20211084 Stryker
#include "../Public/Time.h"


void Time::SetSleepUntilTrueValid()
{
  this->Wake = false;
}

void Time::WakeUp()
{
  this->Wake = true;
}