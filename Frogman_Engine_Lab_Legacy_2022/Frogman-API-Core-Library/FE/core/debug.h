#ifndef _FE_CORE_DEBUG_H_
#define _FE_CORE_DEBUG_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#ifndef NDEBUG
#include <iostream>
#define FE_LOG(contents_p) std::cout << contents_p << std::endl;
#define _DEBUG_MODE_ 1
#else
#define FE_LOG(contents_p)
#define _DEBUG_MODE_ 0
#endif

#endif
