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
PROJECT(Frogman_API)




# Add compiler options
ADD_COMPILE_OPTIONS(-pthread -g )


SET(CMAKE_BUILD_TYPE "Debug")


ADD_COMPILE_DEFINITIONS(_HAS_CXX20=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX17=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX23=0)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/OneAPI-TBB_2021_9_0/include)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/source)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-API-Core-Library)



# Find Intel One API TBB
FIND_LIBRARY(TBB libtbb_debug.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/OneAPI-TBB_2021_9_0/binaries/Linux/.so/intel64/gcc4.8/debug PATH_SUFFIXES debug)

# Find Intel One API TBB malloc
FIND_LIBRARY(TBB_MALLOC libtbbmalloc_debug.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/OneAPI-TBB_2021_9_0/binaries/Linux/.so/intel64/gcc4.8/debug PATH_SUFFIXES debug)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_ATOMIC libboost_atomic.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_CHRONO libboost_chrono.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_CONTAINER libboost_container.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_CONTEXT libboost_context.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_CONTRACT libboost_contract.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_COROUTINE libboost_coroutine.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_DATE_TIME libboost_date_time.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_FIBER libboost_fiber.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_FILESYSTEM libboost_filesystem.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_GRAPH libboost_graph.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_IOSTREAMS libboost_iostreams.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_JSON libboost_json.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_LOCALE libboost_locale.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_LOG libboost_log.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_LOG_SETUP libboost_log_setup.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_C99 libboost_math_c99.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_C99F libboost_math_c99f.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_C99L libboost_math_c99l.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_TR1 libboost_math_tr1.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_TR1L libboost_math_tr1l.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_MATH_TR1F libboost_math_tr1f.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_NOWIDE libboost_nowide.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_PRG_EXEC_MONITOR libboost_prg_exec_monitor.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_PROGRAM_OPTIONS libboost_program_options.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_RANDOM libboost_random.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_REGEX libboost_regex.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_SERIALIZATION libboost_serialization.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_STACKTRACE_BASIC libboost_stacktrace_basic.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_SYSTEM libboost_system.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_THREAD libboost_thread.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_TIMER libboost_timer.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_TYPE_ERASURE libboost_type_erasure.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_URL libboost_url.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_WAVE libboost_wave.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)

# Find Boost Libraries
#FIND_LIBRARY(BOOST_WSERIALIZATION libboost_wserialization.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-APIs/Boost-Libraries_1_82_0/binaries/Linux PATH_SUFFIXES Linux)



# Add the executable target
ADD_EXECUTABLE(	Frogman_API_Debugger 
		main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/configuration_deserializer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/launch.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/heap_utilization.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}}/../../FE/core/private/memory_metrics.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}}/../../FE/core/private/mutex.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}}/../../FE/core/private/thread.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}}/../../FE/core/private/runtime_exception.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}}/../../FE/core/private/clock.cpp 
		)

# Link against the libraries
TARGET_LINK_LIBRARIES(	Frogman_API_Debugger stdc++fs 
			${TBB}
			${TBB_MALLOC}
			#${BOOST_ATOMIC}
			#${BOOST_CHRONO}
			#${BOOST_CONTAINER}
			#${BOOST_CONTEXT}
			#${BOOST_CONTRACT}
			#${BOOST_COROUTINE}
			#${BOOST_DATE_TIME}
			#${BOOST_FIBER}
			#${BOOST_FILESYSTEM}
			#${BOOST_GRAPH}
			#${BOOST_IOSTREAMS}
			#${BOOST_JSON}
			#${BOOST_LOCALE}
			#${BOOST_LOG}
			#${BOOST_LOG_SETUP}
			#${BOOST_MATH_C99}
			#${BOOST_MATH_C99F}
			#${BOOST_MATH_C99L}
			#${BOOST_MATH_TR1}
			#${BOOST_MATH_TR1L}
			#${BOOST_MATH_TR1F}
			#${BOOST_NOWIDE}
			#${BOOST_PRG_EXEC_MONITOR}
			#${BOOST_PROGRAM_OPTIONS}
			#${BOOST_RANDOM}
			#${BOOST_REGEX}
			#${BOOST_SERIALIZATION}
			#${BOOST_STACKTRACE_BASIC}
			#${BOOST_SYSTEM}
			#${BOOST_THREAD}
			#${BOOST_TIMER}
			#${BOOST_TYPE_ERASURE}
			#${BOOST_URL}
			#${BOOST_WAVE}
			#${BOOST_WSERIALIZATION}
			)

# Check the Links Below for further Korean Explanation about CMake.
# https://kkastory.tistory.com/29
# https://www.tuwlab.com/27260
