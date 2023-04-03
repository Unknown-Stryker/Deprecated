
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved

#if WINDOWS == true
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#include <malloc.h>
#include <crtdbg.h>
#endif

#include <string>
using std::string;

#include "DynamicContainer.h"
using dynamic::DynamicLinkedArray;


namespace smartpointers
{
#if WINDOWS == 1
	struct MemoryLeakMonitor
	{
		~MemoryLeakMonitor()
		{
			_CrtDumpMemoryLeaks();
		}
	};
#endif

	template <typename UNIQUE_OBJECT_TYPE>
	class unique_pointer
	{
		class unique_object
		{
			friend class unique_pointer;

			UNIQUE_OBJECT_TYPE* DATA;
			string DATA_Description;
			long long Owner_ID;
			bool Is_is_an_array;

			unique_object();
			unique_object(string DATA_Description_param);
			~unique_object();
		};


		unique_object* Pointer;
		long long ID;

	public:
		unique_pointer();
		unique_pointer(const unique_object* initial_unique_object_param);
		~unique_pointer();

		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* make_unique()" more than once for the same unique pointer.
		static unique_object* make_unique();
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param);" more than once for the same unique pointer.
		static unique_object* make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);" more than once for the same unique pointer.
		static unique_object* make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* make_unique(string DATA_Description_param);" more than once for the same unique pointer.
		static unique_object* make_unique(string DATA_Description_param);

		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* allocate_unique_array(unsigned long long length_param);" more than once for the same unique pointer.
		static unique_object* allocate_unique_array(unsigned long long length_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param);" more than once for the same unique pointer.
		static unique_object* allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);" more than once for the same unique pointer.
		static unique_object* allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static unique_object* allocate_unique_array(unsigned long long length_param, string DATA_Description_param);" more than once for the same unique pointer.
		static unique_object* allocate_unique_array(unsigned long long length_param, string DATA_Description_param);

		void operator = (unique_object* unique_object_param);
		void operator = (UNIQUE_OBJECT_TYPE DATA_param);
		void operator = (string DATA_Description_param);
		UNIQUE_OBJECT_TYPE* operator->();
		void DELETE();
		UNIQUE_OBJECT_TYPE operator*();
		UNIQUE_OBJECT_TYPE& operator[](unsigned long long Index);

	private:
		unique_pointer(const unique_pointer& Illegal);
		unique_pointer& operator = (const unique_pointer& forbidden);

	public:
		void Insert(UNIQUE_OBJECT_TYPE DATA_param);
		void Insert(UNIQUE_OBJECT_TYPE DATA_param, string DATA_Description_param);
		void Insert(string DATA_Description_param);

		unique_object* relinquish_ownership();
		static void swap(unique_pointer& A, unique_pointer& B);
		UNIQUE_OBJECT_TYPE* release();

#if WINDOWS == true
		// Perverting the usage of "void confine(SHARED_OBJECT_TYPE* Object_param);" will result in unregulated and undefined behavior
		void confine(UNIQUE_OBJECT_TYPE* Object_param);
		// Perverting the usage of "void confine(UNIQUE_OBJECT_TYPE* Object_param, string DATA_Description_param);" will result in unregulated and undefined behavior
		void confine(UNIQUE_OBJECT_TYPE* Object_param, string DATA_Description_param);
#endif

		bool Is_it_nullptr();
		bool Is_unique_object_empty();
		string Get_DATA_Description();
	};


	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object::unique_object() 
		: DATA(nullptr), DATA_Description("\0"), Owner_ID(0), Is_is_an_array(false)
	{
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object::unique_object(string DATA_Description_param)
		: DATA(nullptr), DATA_Description(DATA_Description_param), Owner_ID(0), Is_is_an_array(false)
	{
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object::~unique_object()
	{
		if (this->Owner_ID != 0 && this->DATA != nullptr)
		{
			if (this->Is_is_an_array == true)
			{
				delete[] this->DATA;
			}
			else
			{
				delete this->DATA;
			}
		}
	}


	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_pointer() : Pointer(nullptr)
	{
		this->ID = (long long)this;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_pointer(const unique_object* initial_unique_object_param) : Pointer( (unique_object*) initial_unique_object_param)
	{
		this->ID = (long long)this;
		this->Pointer->Owner_ID = this->ID;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_pointer(const unique_pointer& Illegal) : Pointer(nullptr)
	{
		this->ID = (long long)this;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::~unique_pointer()
	{
		if (this->Pointer != nullptr)
		{
			if (this->ID == this->Pointer->Owner_ID || this->Pointer->Owner_ID == 0)
			{
				delete Pointer;
			}
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::make_unique()
	{
		unique_object* Temporary = new unique_object;
		Temporary->DATA = new UNIQUE_OBJECT_TYPE;
		return Temporary;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param)
	{
		unique_object* Temporary = new unique_object;
		Temporary->DATA = new UNIQUE_OBJECT_TYPE(Initial_Value_param);
		return Temporary;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::make_unique(UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param)
	{
		unique_object* Temporary = new unique_object(DATA_Description_param);
		Temporary->DATA = new UNIQUE_OBJECT_TYPE(Initial_Value_param);
		return Temporary;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::make_unique(string DATA_Description_param)
	{
		unique_object* Temporary = new unique_object(DATA_Description_param);
		Temporary->DATA = new UNIQUE_OBJECT_TYPE;
		return Temporary;
	}


	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::allocate_unique_array(unsigned long long length_param)
	{
		unique_object* allocator = new unique_object;
		allocator->DATA = new UNIQUE_OBJECT_TYPE[length_param];

		allocator->Is_is_an_array = true;

		return allocator;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param)
	{
		unique_object* allocator = new unique_object;
		allocator->DATA = new UNIQUE_OBJECT_TYPE[length_param];

		for (unsigned long long idx = 0; idx < length_param; ++idx)
		{
			allocator->DATA[idx] = Initial_Value_param;
		}

		allocator->Is_is_an_array = true;

		return allocator;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::allocate_unique_array(unsigned long long length_param, UNIQUE_OBJECT_TYPE Initial_Value_param, string DATA_Description_param)
	{
		unique_object* allocator = new unique_object;
		allocator->DATA = new UNIQUE_OBJECT_TYPE[length_param];
		allocator->DATA_Description = DATA_Description_param;

		for (unsigned long long idx = 0; idx < length_param; ++idx)
		{
			allocator->DATA[idx] = Initial_Value_param;
		}

		allocator->Is_is_an_array = true;

		return allocator;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::allocate_unique_array(unsigned long long length_param, string DATA_Description_param)
	{
		unique_object* allocator = new unique_object;
		allocator->DATA = new UNIQUE_OBJECT_TYPE[length_param];
		allocator->DATA_Description = DATA_Description_param;

		allocator->Is_is_an_array = true;

		return allocator;
	}


	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::operator=(unique_object* unique_object_param)
	{
		if (this->Pointer != nullptr)
		{
			delete Pointer;
		}

		this->Pointer = unique_object_param;
		this->Pointer->Owner_ID = this->ID;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::operator=(UNIQUE_OBJECT_TYPE DATA_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::operator=(string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline UNIQUE_OBJECT_TYPE* unique_pointer<UNIQUE_OBJECT_TYPE>::operator->()
	{
		if (this->Pointer != nullptr)
		{
			return this->Pointer->DATA;
		}
		return nullptr;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::DELETE()
	{
		if (this->Pointer != nullptr)
		{
			delete this->Pointer;
		}
		this->Pointer = nullptr;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline UNIQUE_OBJECT_TYPE unique_pointer<UNIQUE_OBJECT_TYPE>::operator*()
	{
		if (this->Pointer != nullptr)
		{
			return *this->Pointer->DATA;
		}
		return NULL;
	}

#pragma warning(disable : 4172)
	template<typename UNIQUE_OBJECT_TYPE>
	inline UNIQUE_OBJECT_TYPE& unique_pointer<UNIQUE_OBJECT_TYPE>::operator[](unsigned long long Index)
	{
		if (this->Pointer != nullptr)
		{
			return this->Pointer->DATA[Index];
		}

		UNIQUE_OBJECT_TYPE null;
		return null;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>& unique_pointer<UNIQUE_OBJECT_TYPE>::operator=(const unique_pointer& forbidden)
	{
		return nullptr;
	}


	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::Insert(UNIQUE_OBJECT_TYPE DATA_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::Insert(UNIQUE_OBJECT_TYPE DATA_param, string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::Insert(string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}


	template<typename UNIQUE_OBJECT_TYPE>
	inline unique_pointer<UNIQUE_OBJECT_TYPE>::unique_object* unique_pointer<UNIQUE_OBJECT_TYPE>::relinquish_ownership()
	{
		if (this->Pointer != nullptr)
		{
			unique_object* var = this->Pointer;
			this->Pointer = nullptr;
			return var;
		}
		return nullptr;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::swap(unique_pointer& A, unique_pointer& B)
	{
		unique_object* Temporary_A = A.relinquish_ownership();
		unique_object* Temporary_B = B.relinquish_ownership();
		A = Temporary_B;
		B = Temporary_A;
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline UNIQUE_OBJECT_TYPE* unique_pointer<UNIQUE_OBJECT_TYPE>::release()
	{
		if (this->Pointer != nullptr)
		{
			unique_object* Temporary = this->relinquish_ownership();

			// The Destructor of unique_object won't delete DATA, if its Owner_ID is Zero. It's being released.
			Temporary->Owner_ID = 0;
			UNIQUE_OBJECT_TYPE* var = Temporary->DATA;
			delete Temporary;
			return var;
		}
		return nullptr;
	}

#if WINDOWS == true
	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::confine(UNIQUE_OBJECT_TYPE* Object_param)
	{
		if (Object_param != nullptr)
		{
			if (this->Pointer == nullptr)
			{
				unsigned long long Size = _msize(Object_param) / sizeof(UNIQUE_OBJECT_TYPE);

				this->Pointer = new unique_object;

				if (Size == 1)
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->Is_is_an_array = false;
					this->Pointer->Owner_ID = this->ID;
				}
				else
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->Is_is_an_array = true;
					this->Pointer->Owner_ID = this->ID;
				}
			}
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline void unique_pointer<UNIQUE_OBJECT_TYPE>::confine(UNIQUE_OBJECT_TYPE* Object_param, string DATA_Description_param)
	{
		if (Object_param != nullptr)
		{
			if (this->Pointer == nullptr)
			{
				unsigned long long Size = _msize(Object_param) / sizeof(UNIQUE_OBJECT_TYPE);

				this->Pointer = new unique_object;

				if (Size == 1)
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->DATA_Description = DATA_Description_param;
					this->Pointer->Is_is_an_array = false;
					this->Pointer->Owner_ID = this->ID;
				}
				else
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->DATA_Description = DATA_Description_param;
					this->Pointer->Is_is_an_array = true;
					this->Pointer->Owner_ID = this->ID;
				}
			}
		}
	}
#endif

	template<typename UNIQUE_OBJECT_TYPE>
	inline bool unique_pointer<UNIQUE_OBJECT_TYPE>::Is_it_nullptr()
	{
		if (this->Pointer == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline bool unique_pointer<UNIQUE_OBJECT_TYPE>::Is_unique_object_empty()
	{
		if (this->Pointer != nullptr)
		{
			if (this->Pointer->DATA == nullptr)
			{
				return true;
			}

			return false;

		}

		return true;

	}

	template<typename UNIQUE_OBJECT_TYPE>
	inline string unique_pointer<UNIQUE_OBJECT_TYPE>::Get_DATA_Description()
	{
		if (this->Pointer != nullptr)
		{
			return this->Pointer->DATA_Description;
		}
		return string("\0");
	}




	template <typename SHARED_OBJECT_TYPE>
	class shared_pointer
	{
		enum class DEAD_OR_ALIVE : bool
		{
			DEAD = false,
			ALIVE = true
		};

		class shared_object
		{
			friend class shared_pointer;

			SHARED_OBJECT_TYPE* DATA;
			string DATA_Description;
			unsigned long long Reference_Count;
			bool Is_is_an_array;
			bool Is_it_released;

			shared_object();
			shared_object(string DATA_Description_param);
			~shared_object();

			static DynamicLinkedArray<DEAD_OR_ALIVE> InfoContainer;
			static unsigned long long ContainerIndex;
			unsigned long long Info_Index_Key;
		};

		friend class shared_object;


		shared_object* Pointer;
		unsigned long long shared_object_Info_Index_Key;
	public:
		shared_pointer();
		shared_pointer(const shared_object* initial_shared_object_param);
		shared_pointer(const shared_pointer &shared_pointer_param);
		~shared_pointer();

		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* make_shared()" more than once for the same shared pointer.
		static shared_object* make_shared();
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* make_shared()" more than once for the same shared pointer.
		static shared_object* make_shared(SHARED_OBJECT_TYPE Initial_Value_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* make_shared()" more than once for the same shared pointer.
		static shared_object* make_shared(SHARED_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* make_shared()" more than once for the same shared pointer.
		static shared_object* make_shared(string DATA_Description_param);

		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* allocate_shared_array(unsigned long long length_param);" more than once for the same shared pointer.
		static shared_object* allocate_shared_array(unsigned long long length_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* allocate_shared_array(unsigned long long length_param);" more than once for the same shared pointer.
		static shared_object* allocate_shared_array(unsigned long long length_param, SHARED_OBJECT_TYPE Initial_Value_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* allocate_shared_array(unsigned long long length_param);" more than once for the same shared pointer.
		static shared_object* allocate_shared_array(unsigned long long length_param, SHARED_OBJECT_TYPE Initial_Value_param, string DATA_Description_param);
		// It will automatically deallocate the previous object and allocate a new object, If you call this function "static shared_object* allocate_shared_array(unsigned long long length_param);" more than once for the same shared pointer.
		static shared_object* allocate_shared_array(unsigned long long length_param, string DATA_Description_param);

		void operator = (shared_object* shared_object_param);
		void operator = (SHARED_OBJECT_TYPE DATA_param);
		void operator = (string DATA_Description_param);
		shared_pointer& operator = (const shared_pointer& shared_pointer_param);
		SHARED_OBJECT_TYPE* operator->();
		static void DELETE(shared_pointer& Subject);
		SHARED_OBJECT_TYPE operator*();
		SHARED_OBJECT_TYPE& operator[](unsigned long long Index);

	public:
		void Insert(SHARED_OBJECT_TYPE DATA_param);
		void Insert(SHARED_OBJECT_TYPE DATA_param, string DATA_Description_param);
		void Insert(string DATA_Description_param);

		shared_object* relinquish_ownership();
		static void swap(shared_pointer& A, shared_pointer& B);
		SHARED_OBJECT_TYPE* release();

#if WINDOWS == true
		// Perverting the usage of "void confine(SHARED_OBJECT_TYPE* Object_param);" will result in unregulated and undefined behavior
		void confine(SHARED_OBJECT_TYPE* Object_param);
		// Perverting the usage of "void confine(UNIQUE_OBJECT_TYPE* Object_param, string DATA_Description_param);" will result in unregulated and undefined behavior
		void confine(SHARED_OBJECT_TYPE* Object_param, string DATA_Description_param);
#endif

		bool Is_it_nullptr();
		bool Is_shared_object_empty();
		string Get_DATA_Description();
	};


	template<typename SHARED_OBJECT_TYPE>
	DynamicLinkedArray<typename shared_pointer<SHARED_OBJECT_TYPE>::DEAD_OR_ALIVE> shared_pointer<SHARED_OBJECT_TYPE>::shared_object::InfoContainer(100);

	template<typename SHARED_OBJECT_TYPE>
	unsigned long long shared_pointer<SHARED_OBJECT_TYPE>::shared_object::ContainerIndex = 0;


	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object::shared_object() : DATA(nullptr), DATA_Description("\0"), Reference_Count(0), Is_is_an_array(false), Is_it_released(false)
	{
		this->Info_Index_Key = shared_object::ContainerIndex;

		shared_object::InfoContainer.Insert(shared_object::ContainerIndex, DEAD_OR_ALIVE::ALIVE);
		++shared_object::ContainerIndex;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object::shared_object(string DATA_Description_param) : DATA(nullptr), DATA_Description(DATA_Description_param), Reference_Count(0), Is_is_an_array(false), Is_it_released(false)
	{
		this->Info_Index_Key = shared_object::ContainerIndex;

		shared_object::InfoContainer.Insert(shared_object::ContainerIndex, DEAD_OR_ALIVE::ALIVE);
		++shared_object::ContainerIndex;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object::~shared_object()
	{
		if (this->DATA != nullptr && this->Is_it_released == false)
		{
			if (this->Is_is_an_array == true)
			{
				shared_object::InfoContainer.Insert(this->Info_Index_Key, DEAD_OR_ALIVE::DEAD);
				delete[] this->DATA;
			}
			else
			{
				shared_object::InfoContainer.Insert(this->Info_Index_Key, DEAD_OR_ALIVE::DEAD);
				delete this->DATA;
			}
		}
	}


	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_pointer() : Pointer(nullptr), shared_object_Info_Index_Key(0)
	{
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_pointer(const shared_object* initial_shared_object_param) : Pointer( (shared_object*) initial_shared_object_param)
	{
		++this->Pointer->Reference_Count;
		this->shared_object_Info_Index_Key = initial_shared_object_param->Info_Index_Key;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_pointer(const shared_pointer &shared_pointer_param)
	{
		this->Pointer = shared_pointer_param.Pointer;
		++this->Pointer->Reference_Count;
		this->shared_object_Info_Index_Key = shared_pointer_param.Pointer->Info_Index_Key;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::~shared_pointer()
	{
		if (this->Pointer != nullptr)
		{
			DEAD_OR_ALIVE info = shared_object::InfoContainer.SearchElement(this->shared_object_Info_Index_Key);
			
			if (info == DEAD_OR_ALIVE::ALIVE)
			{
				--this->Pointer->Reference_Count;
				if (0 >= this->Pointer->Reference_Count)
				{
					delete Pointer;
				}
			}
		}
	}


	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::make_shared()
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE;
		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::make_shared(SHARED_OBJECT_TYPE Initial_Value_param)
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE(Initial_Value_param);
		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::make_shared(SHARED_OBJECT_TYPE Initial_Value_param, string DATA_Description_param)
	{
		shared_object* allocator = new shared_object(DATA_Description_param);
		allocator->DATA = new SHARED_OBJECT_TYPE(Initial_Value_param);
		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::make_shared(string DATA_Description_param)
	{
		shared_object* allocator = new shared_object(DATA_Description_param);
		allocator->DATA = new SHARED_OBJECT_TYPE;
		return allocator;
	}


	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::allocate_shared_array(unsigned long long length_param)
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE[length_param];
		allocator->Is_is_an_array = true;
		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::allocate_shared_array(unsigned long long length_param, SHARED_OBJECT_TYPE Initial_Value_param)
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE[length_param];

		for (unsigned long long idx = 0; idx < length_param; ++idx)
		{
			allocator->DATA[idx] = Initial_Value_param;
		}

		allocator->Is_is_an_array = true;

		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::allocate_shared_array(unsigned long long length_param, SHARED_OBJECT_TYPE Initial_Value_param, string DATA_Description_param)
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE[length_param];
		allocator->DATA_Description = DATA_Description_param;

		for (unsigned long long idx = 0; idx < length_param; ++idx)
		{
			allocator->DATA[idx] = Initial_Value_param;
		}

		allocator->Is_is_an_array = true;

		return allocator;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::allocate_shared_array(unsigned long long length_param, string DATA_Description_param)
	{
		shared_object* allocator = new shared_object;
		allocator->DATA = new SHARED_OBJECT_TYPE[length_param];
		allocator->DATA_Description = DATA_Description_param;

		allocator->Is_is_an_array = true;

		return allocator;
	}


	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::operator=(shared_object* shared_object_param)
	{
		if (this->Pointer != nullptr)
		{
			delete Pointer;
		}
		this->Pointer = shared_object_param;
		++this->Pointer->Reference_Count;
		this->shared_object_Info_Index_Key = shared_object_param->Info_Index_Key;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::operator=(SHARED_OBJECT_TYPE DATA_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::operator=(string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>& shared_pointer<SHARED_OBJECT_TYPE>::operator=(const shared_pointer& shared_pointer_param)
	{
		this->Pointer->DATA = shared_pointer_param.Pointer->DATA;
		++this->Pointer->Reference_Count;
		this->shared_object_Info_Index_Key = shared_pointer_param.Pointer->Info_Index_Key;
		return *this;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline SHARED_OBJECT_TYPE* shared_pointer<SHARED_OBJECT_TYPE>::operator->()
	{
		if (this->Pointer != nullptr)
		{
			return this->Pointer->DATA;
		}
		return nullptr;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::DELETE(shared_pointer& Subject)
	{
		if (Subject.Pointer != nullptr)
		{
			delete Subject.Pointer;
			Subject.Pointer = nullptr;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline SHARED_OBJECT_TYPE shared_pointer<SHARED_OBJECT_TYPE>::operator*()
	{
		if (this->Pointer != nullptr)
		{
			return *this->Pointer->DATA;
		}
		return NULL;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline SHARED_OBJECT_TYPE& shared_pointer<SHARED_OBJECT_TYPE>::operator[](unsigned long long Index)
	{
		return this->Pointer->DATA[Index];
	}


	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::Insert(SHARED_OBJECT_TYPE DATA_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::Insert(SHARED_OBJECT_TYPE DATA_param, string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			*this->Pointer->DATA = DATA_param;
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::Insert(string DATA_Description_param)
	{
		if (this->Pointer != nullptr)
		{
			this->Pointer->DATA_Description = DATA_Description_param;
		}
	}


	template<typename SHARED_OBJECT_TYPE>
	inline shared_pointer<SHARED_OBJECT_TYPE>::shared_object* shared_pointer<SHARED_OBJECT_TYPE>::relinquish_ownership()
	{
		if (this->Pointer != nullptr)
		{
			shared_object* var = this->Pointer;
			--this->Pointer->Reference_Count;
			this->Pointer = nullptr;
			return var;
		}
		return nullptr;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::swap(shared_pointer& A, shared_pointer& B)
	{
		shared_pointer* Temporary_A = A.relinquish_ownership();
		shared_pointer* Temporary_B = B.relinquish_ownership();
		A = Temporary_B;
		B = Temporary_A;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline SHARED_OBJECT_TYPE* shared_pointer<SHARED_OBJECT_TYPE>::release()
	{
		if (this->Pointer != nullptr)
		{
			shared_object* Temporary = this->relinquish_ownership();
			SHARED_OBJECT_TYPE* var = Temporary->DATA;
			Temporary->Is_it_released = true;
			return var;
		}
		return nullptr;
	}

#if WINDOWS == true
	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::confine(SHARED_OBJECT_TYPE* Object_param)
	{
		if (Object_param != nullptr)
		{
			if (this->Pointer == nullptr)
			{
				unsigned long long Size = _msize(Object_param) / sizeof(SHARED_OBJECT_TYPE);

				this->Pointer = new shared_object;

				if (Size == 1)
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->Is_is_an_array = false;
					this->Pointer->Owner_ID = this->ID;
				}
				else
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->Is_is_an_array = true;
					this->Pointer->Owner_ID = this->ID;
				}
			}
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline void shared_pointer<SHARED_OBJECT_TYPE>::confine(SHARED_OBJECT_TYPE* Object_param, string DATA_Description_param)
	{
		if (Object_param != nullptr)
		{
			if (this->Pointer == nullptr)
			{
				unsigned long long Size = _msize(Object_param) / sizeof(SHARED_OBJECT_TYPE);

				this->Pointer = new shared_object;

				if (Size == 1)
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->DATA_Description = DATA_Description_param;
					this->Pointer->Is_is_an_array = false;
					this->Pointer->Owner_ID = this->ID;
				}
				else
				{
					this->Pointer->DATA = Object_param;
					this->Pointer->DATA_Description = DATA_Description_param;
					this->Pointer->Is_is_an_array = true;
					this->Pointer->Owner_ID = this->ID;
				}
			}
		}
	}
#endif

	template<typename SHARED_OBJECT_TYPE>
	inline bool shared_pointer<SHARED_OBJECT_TYPE>::Is_it_nullptr()
	{
		if (this->Pointer == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename SHARED_OBJECT_TYPE>
	inline bool shared_pointer<SHARED_OBJECT_TYPE>::Is_shared_object_empty()
	{
		if (this->Pointer != nullptr)
		{
			if (this->Pointer->DATA == nullptr)
			{
				return true;
			}

			return false;

		}

		return true;
	}

	template<typename SHARED_OBJECT_TYPE>
	inline string shared_pointer<SHARED_OBJECT_TYPE>::Get_DATA_Description()
	{
		if (this->Pointer != nullptr)
		{
			return this->Pointer->DATA_Description;
		}
		return string("\0");
	}
}


using smartpointers::unique_pointer;
using smartpointers::shared_pointer;