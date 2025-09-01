 CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
 
 
 
 
# Find the path to the clang compiler executable
FIND_PROGRAM(GNU_C NAMES gcc)

if(GNU_C)
    # Set the path to the found clang compiler executable
    SET(CMAKE_C_COMPILER ${GNU_C})
else()
    MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C Compilers")
endif()


# Find the path to the g++ compiler executable
FIND_PROGRAM(GNU_CPP NAMES g++-13 g++-12 g++-11 g++)

if(GNU_CPP)
    # Set the path to the found clang++ compiler executable
    SET(CMAKE_CXX_COMPILER ${GNU_CPP})
else()
    MESSAGE(FATAL_ERROR "Could Not Find Any of Executable g++ Compilers")
endif()





# Set C++ standard to C++20
SET(CMAKE_CXX_STANDARD 20)


# Set Project Name
PROJECT(Frogman_API_Unit_Test)


# Add compiler options
ADD_COMPILE_OPTIONS(-pthread -g )

ADD_COMPILE_DEFINITIONS(_HAS_CXX20=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX17=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX23=0)


SET(CMAKE_BUILD_TYPE "Debug")


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Frogman-API-Core-Library)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Unit-Test-Linux-Packages/include)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-APIs/OneAPI-TBB_2021_9_0/include)


# Find libtest.a
FIND_LIBRARY(UNIT_TEST libgtest.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../Unit-Test-Linux-Packages)

# Find libgtest_main.a
FIND_LIBRARY(UNIT_TEST_MAIN libgtest_main.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../Unit-Test-Linux-Packages)

# Find Intel One API TBB
FIND_LIBRARY(TBB libtbb.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-APIs/OneAPI-TBB_2021_9_0/binaries/Linux/.so/intel64/gcc4.8/release PATH_SUFFIXES release)

# Find Intel One API TBB malloc
FIND_LIBRARY(TBB_MALLOC libtbbmalloc.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-APIs/OneAPI-TBB_2021_9_0/binaries/Linux/.so/intel64/gcc4.8/release PATH_SUFFIXES release)

# Find libFrogman_API
FIND_LIBRARY(Frogman_API libFrogman_API.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../Binaries/Linux/g++-12-Compiler/Release/.a)


# Add the executable target
ADD_EXECUTABLE(	Frogman_API_Unit_Test
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/allocator_adaptors-unit-test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/cstring-unit-test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/math-unit-test.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/memory_block-unit-test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/movable_scoped_ref-unit-test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/singleton_templates-unit-test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/string_algorithm-unit-test.cpp
		#${CMAKE_CURRENT_SOURCE_DIR}/../Frogman-API-Core-Library-Unit-Test/thread-mutex-unit-test.cpp
		../Frogman-API-Core-Library-Unit-Test/thread-mutex-unit-test.cpp)
		
SET_TARGET_PROPERTIES(	Frogman_API_Unit_Test 
			PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
			SUFFIX ".test_exe"
			) 
		
# Link against the libraries
TARGET_LINK_LIBRARIES(	Frogman_API_Unit_Test stdc++fs
			${UNIT_TEST} 
			${UNIT_TEST_MAIN}
			${TBB} 
			${TBB_MALLOC} 
			${Frogman_API}
			)


