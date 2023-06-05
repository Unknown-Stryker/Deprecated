// visit https://savory-moth-a00.notion.site/Welcome-to-Frogman-Engine-API-Programming-Convention-Guideline-Documentation-ce98aa7b99bd41a18bced807031b1f81 for Frogman Engine Coding Conventions
#include "source/core.debug.h"
#include "source/core.types.h"
//
#include "source/memory.allocator.hxx"
//#include "source/memory.dynamic array.hxx"
//#include "source/memory.string.hxx"

#include "source/utility.clock.hpp"
#include "source/core.macro restrictions.h"


int main()
{

	RETURN(0); // The pre-processor macro "RETURN(0)" checks any memory leaks before finishing the entire application process if MSVC pre-processor macro NDEBUG is not defined.
}


// The Frogman Engine API is under development and is not a complete version.
	// Memory pool proof of concept.
	//{
	//// Allocate memory pool unconstructed
	//void* g_s_pool = malloc(sizeof(FE::memory::block< FE::memory::basic_string<> >) * 2);

	//// Assign memory block addresses to the pointers below
	//FE::memory::block< FE::memory::basic_string<> >* obj1 = static_cast<FE::memory::block< FE::memory::basic_string<> >*>( g_s_pool );
	//FE::memory::block< FE::memory::basic_string<> >* obj2 = ( FE::memory::block< FE::memory::basic_string<> >* )g_s_pool + 1; // it is equal to g_s_pool[1]

	//// Construct objects
	//obj1->call_constructor();
	//obj2->call_constructor();

	//// Neutralize objects
	//obj1->call_destructor();
	//obj2->call_destructor();

	//// Re-construct objects
	//obj1->call_constructor();
	//obj2->call_constructor();

	//// Re-neutralize objects
	//obj1->call_destructor();
	//obj2->call_destructor();

	//// Returns the entire memory pool
	//free(g_s_pool);
	//}




	// Demonstration of a few Frogman Engine memory module classes.
	//{
	//	FE::string l_string; // string is specified template dynamic ASCII character array manager class of Frogman Engine API memory module. The size of its instances is sixteen bytes. std::string is 40 bytes in Microsoft Visual Studio C++ (MSVC++).
	//	FE::wstring l_wstring; // wstring is a specified template dynamic wide character array manager class of the Frogman Engine API memory module. The size of its instance is sixteen bytes. std::wstring is forty bytes in Microsoft Visual Studio C++ (MSVC++).
	//	l_string[9];  // std::string ignores memory access violations without any runtime errors.
	//	l_wstring[2]; // std::wstring can handle memory access violations with no runtime errors.


	//	// Exempli Gratia of Frogman Engine API memory module smart pointers One
	//	{
	//		FE::unique<int>::ptr l_unique_int; // unique is a templated smart pointer class of the Frogman Engine API memory module that provides performant minimal garbage collection with unique ownership policy, similar to moving rvalue objects in rust language.  // The memory overhead of the class unique will be optimized soon.
	//		FE::indirect<int>::ptr l_indirect_int; // indirect is a templated smart pointer class of the Frogman Engine API memory module which shares a similarity with std::weak_ptr<T> but is slightly different. The one outstanding factor differentiating indirect from weak_ptr is null-safety ensurance( search on the scrabble web dictionary Merriam webster if you doubt the spells of the word "ensurance" ).

	//		l_unique_int[7]; // It ignores memory access violations at the address with no runtime errors.
	//		l_indirect_int[5]; // It disregards access violations at the memory address with no runtime errors.

	//		*l_unique_int; // It ignores dereferencing nullptr. You can set a strict memory access violation policy by changing the value of the pre-processor macro " _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ " to one or two.
	//		*l_indirect_int; // It disregards dereferencing nullptr. You can set a strict memory access violation policy by changing the value of the pre-processor macro " _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ " to one or two, which is originated from core.flags.h file.
	//	}


	//	// Exempli Gratia of Frogman Engine API memory module smart pointers Two
	//	{
	//		FE::unique<int>::ptr l_unique_int = 7; // Assign value and invoke new operator to set.

	//		{
	//			FE::indirect<int>::ptr l_indirect_int = l_unique_int; // get reference of an object from unique
	//		} // l_indirect_int automatically pops out from the block scope you can see in this code line.
	//	} // l_unique_int is garbage collected and no longer valid.


	//	// Exempli Gratia of Frogman Engine API memory module smart pointers Three
	//	{
	//		FE::indirect<int>::ptr l_indirect_int;
	//		FE::unique<int>::ptr l_unique_int = 7;
	//		
	//		{
	//			FE::unique<int>::ptr l_unique_int = 5;
	//			l_indirect_int = l_unique_int;
	//		} // It does the same thing here (Scope Based Garbage Collection)
	//	} // It does the same thing here (Scope Based Garbage Collection)
	//}


//FE::utility::clock clock;
//FE::var::uint64 fps = 0;
//FE::var::uint64 game_time = 0;
//while ( game_time < 300 )
//{
//	clock.start_clock();
//	while ( clock.get_delta_time() < 1 )
//	{
//		++fps;
//		clock.end_clock();
//	}
//	FE_LOG(fps);
//	fps = 0;
//	++game_time;
//}