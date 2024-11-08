// Visual-Studio-2022-v143-Compiler.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#define _CRT_SECURE_NO_WARNINGS

#include <FE/core/prerequisite_symbols.h>

#include <FE/core/clock.hpp>
#include <FE/core/private/clock.cpp>

#include <FE/core/heap_utilization.hpp>
#include <FE/core/private/heap_utilization.cpp>

#include <FE/core/private/launch.hpp>
#include <FE/core/private/launch.cpp>

#include <FE/core/memory_metrics.h>
#include <FE/core/private/memory_metrics.cpp>

#include <FE/core/mutex.hpp>
#include <FE/core/private/mutex.cpp>

#include <FE/core/runtime_exception.hpp>
#include <FE/core/private/runtime_exception.cpp>

#include <FE/core/thread.hpp>
#include <FE/core/private/thread.cpp>