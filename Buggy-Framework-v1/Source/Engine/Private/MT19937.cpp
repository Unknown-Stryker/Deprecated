#include "../Public/MT19937.h"


MT19937::MT19937()
{
}

MT19937::~MT19937()
{
}

long long MT19937::GetRangedRandomInteger(long long Min_Range, long long Max_Range)
{
  mt19937_64 Rand((unsigned long long)time(NULL));

  std::uniform_int_distribution<long long> RandomIntegerRange(Min_Range, Max_Range);

  return RandomIntegerRange(Rand);
}