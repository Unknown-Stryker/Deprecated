#pragma once
#include <random>
#include <ctime>
using std::mt19937_64;

class MT19937
{
public:
  MT19937();
  ~MT19937();

  long long GetRangedRandomInteger(long long Min_Range, long long Max_Range);
};