#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include <cassert>

#ifndef NDEBUG
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <iostream>
#define FE_LOG(contents_p) std::cout << contents_p << std::endl;
#define RETURN(P) _CrtDumpMemoryLeaks();\
return P;
#else
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#define FE_LOG(contents_p)
#define RETURN(P) return P;
#endif

#endif
#endif