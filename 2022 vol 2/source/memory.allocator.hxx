#ifndef _ALLOCATOR_HXX_
#define _ALLOCATOR_HXX_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.debug.h"
#include "core.types.h"
#include <atomic>




BEGIN_NAMESPACE(FE)



BEGIN_NAMESPACE(memory)




#define type(P) sizeof(P)

#define _BYTE_SIZE_ 1
#define _WORD_SIZE_ 2
#define _DWORD_SIZE_ 4
#define _QWORD_SIZE_ 8




//x64 cpu cache line is 64 bytes
_MAYBE_UNUSED_ constexpr uint64 one_mb = 1048576;
_MAYBE_UNUSED_ constexpr uint64 one_gb = one_mb * 1024;

#define MB * one_mb
#define GB * one_gb




enum struct MEMORY_ERROR_1XX : int16
{
	_NONE = 0,
	_ERROR_INVALID_SIZE = -100,
	_FATAL_ERROR_OUT_OF_RANGE = -101,
	_FATAL_ERROR_NULLPTR = -102
};
#define CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_P) (int16)MEMORY_ERROR_P




// it is used when reserving memory for every Frogman Engine API data containers during container initialization.
struct initial_reservation final
{
	var::uint64 _size = 0;
};




// it contains memory padding size.
struct align_null final
{
	static uint16 s_size;
};
_MAYBE_UNUSED_ uint16 align_null::s_size = 0;

// it contains memory padding size.
struct align_8bit_cache_line final
{
	static uint16 s_size;
};
_MAYBE_UNUSED_ uint16 align_8bit_cache_line::s_size = 8;

// it contains memory padding size.
struct align_16bit_cache_line final
{
	static uint16 s_size;
};
_MAYBE_UNUSED_ uint16 align_16bit_cache_line::s_size = 16;

// it contains memory padding size.
struct align_32bit_cache_line final
{
	static uint16 s_size;
};
_MAYBE_UNUSED_ uint16 align_32bit_cache_line::s_size = 32;

// it contains memory padding size.
struct align_64bit_cache_line final
{
	static uint16 s_size;
};
_MAYBE_UNUSED_ uint16 align_64bit_cache_line::s_size = 64;




template<typename T, class padding_size = align_64bit_cache_line>
class alignas(padding_size::s_size) block
{
member_variables:
	std::atomic<var::boolean> m_is_block_occupied = false;
	T m_object;

operators:
	T& operator*() noexcept;
	T* operator->() noexcept;
	
methods:

	_FORCE_INLINE_ boolean is_occupied() noexcept { return this->m_is_block_occupied; }

	// it forces m_object to be constructed
	_FORCE_INLINE_ void call_constructor();

	// it forces construction of m_object
	template<typename T0>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p);

	// forced constructor invocation
	template<typename T0, typename T1 = T0, typename T2 = T1>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p);

	// it forces m_object to be constructed
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p);

	// it forces construction of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p, T8 _8th_param_p);

	// it forces constructor invocation of m_object
	template<typename T0, typename T1 = T0, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8>
	_FORCE_INLINE_ void call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p, T8 _8th_param_p, T9 _9th_param_p);

	// it forces destruction of m_object without memory deletion
	_FORCE_INLINE_ void call_destructor();
};

template<typename T, class padding_size>
_FORCE_INLINE_ T& FE::memory::block<T, padding_size>::operator*() noexcept
{
	return this->m_object;
}

template<typename T, class padding_size>
_FORCE_INLINE_ T* FE::memory::block<T, padding_size>::operator->() noexcept
{
	return &this->m_object;
}

template<typename T, class padding_size>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor()
{
	new( &( this->m_object ) ) T();
}

template<typename T, class padding_size>
template<typename T0>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p, _5th_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p, _5th_param_p, _6th_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p, _5th_param_p, _6th_param_p, _7th_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p, T8 _8th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p, _5th_param_p, _6th_param_p, _7th_param_p, _8th_param_p);
}

template<typename T, class padding_size>
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
_FORCE_INLINE_ void block<T, padding_size>::call_constructor(T0 _0_param_p, T1 _1st_param_p, T2 _2nd_param_p, T3 _3rd_param_p, T4 _4th_param_p, T5 _5th_param_p, T6 _6th_param_p, T7 _7th_param_p, T8 _8th_param_p, T9 _9th_param_p)
{
	new( &( this->m_object ) ) T(_0_param_p, _1st_param_p, _2nd_param_p, _3rd_param_p, _4th_param_p, _5th_param_p, _6th_param_p, _7th_param_p, _8th_param_p, _9th_param_p);
}

template<typename T, class padding_size>
_FORCE_INLINE_ void block<T, padding_size>::call_destructor()
{
	this->m_object.~T();
}





template<typename T, class padding_size = align_64bit_cache_line>
class pool
{
member_variables:
	std::atomic<block<T, padding_size>*> m_pool_ptr;

constructors:
	_FORCE_INLINE_ pool() noexcept {};
	_FORCE_INLINE_ pool(initial_reservation&& initial_reservation_p) noexcept;

copy_constructor:
	_FORCE_INLINE_ pool(const pool& copy_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ pool(pool&& move_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ pool& operator=(const pool& copy_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ pool& operator=(pool&& move_p) noexcept;

methods:
	_FORCE_INLINE_ boolean initialize(size_t pool_size_p) noexcept;
	_FORCE_INLINE_ boolean discard() noexcept;
	_FORCE_INLINE_ boolean is_valid() noexcept;
};

template<typename T, class padding_size>
_FORCE_INLINE_ pool<T, padding_size>::pool(initial_reservation&& initial_reservation_p) noexcept
{
}

template<typename T, class padding_size>
_FORCE_INLINE_ pool<T, padding_size>::pool(const pool<T, padding_size>& copy_ref_p) noexcept
{
}

template<typename T, class padding_size>
_FORCE_INLINE_ pool<T, padding_size>::pool(pool<T, padding_size>&& move_p) noexcept
{
}

template<typename T, class padding_size>
_FORCE_INLINE_ pool<T, padding_size>& FE::memory::pool<T, padding_size>::operator=(const pool<T, padding_size>& copy_ref_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

template<typename T, class padding_size>
_FORCE_INLINE_ pool<T, padding_size>& FE::memory::pool<T, padding_size>::operator=(pool<T, padding_size>&& move_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

template<typename T, class padding_size>
_FORCE_INLINE_ boolean pool<T, padding_size>::initialize(size_t pool_size_p) noexcept
{
	return boolean();
}

template<typename T, class padding_size>
_FORCE_INLINE_ boolean pool<T, padding_size>::discard() noexcept
{
	if ( this->m_pool_ptr == nullptr )
	{
		return false;
	}
	
	free(this->m_pool_ptr);
	return true;
}

template<typename T, class padding_size>
_FORCE_INLINE_ boolean pool<T, padding_size>::is_valid() noexcept
{
	return this->m_pool_ptr != nullptr ? true : false;
}





template<>
class pool<void, align_64bit_cache_line>
{
member_variables:
	std::atomic<void*> m_generic_pool_ptr;

constructors:
	_FORCE_INLINE_ pool() noexcept {};
	_FORCE_INLINE_ pool(initial_reservation&& initial_reservation_p) noexcept;

copy_constructor:
	_FORCE_INLINE_ pool(const pool& copy_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ pool(pool&& move_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ pool& operator=(const pool& copy_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ pool& operator=(pool&& move_p) noexcept;

methods:
	_FORCE_INLINE_ boolean initialize(size_t pool_size_p) noexcept;
	_FORCE_INLINE_ boolean discard() noexcept;
	_FORCE_INLINE_ boolean is_valid() noexcept;
};

_FORCE_INLINE_ pool<void, align_64bit_cache_line>::pool(initial_reservation&& initial_reservation_p) noexcept
{
}

_FORCE_INLINE_ pool<void, align_64bit_cache_line>::pool(const pool<void, align_64bit_cache_line>& copy_ref_p) noexcept
{
}

_FORCE_INLINE_ pool<void, align_64bit_cache_line>::pool(pool<void, align_64bit_cache_line>&& move_p) noexcept
{
}

_FORCE_INLINE_ pool<void, align_64bit_cache_line>& FE::memory::pool<void, align_64bit_cache_line>::operator=(const pool<void, align_64bit_cache_line>& copy_ref_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

_FORCE_INLINE_ pool<void, align_64bit_cache_line>& FE::memory::pool<void, align_64bit_cache_line>::operator=(pool<void, align_64bit_cache_line>&& move_p) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

_FORCE_INLINE_ boolean pool<void, align_64bit_cache_line>::initialize(size_t pool_size_p) noexcept
{
	return boolean();
}

_FORCE_INLINE_ boolean pool<void, align_64bit_cache_line>::discard() noexcept
{
	if ( this->m_generic_pool_ptr == nullptr )
	{
		return false;
	}

	free(this->m_generic_pool_ptr);
	return true;
}

_FORCE_INLINE_ boolean FE::memory::pool<void, align_64bit_cache_line>::is_valid() noexcept
{
	return this->m_generic_pool_ptr != nullptr ? true : false;
}





template <typename T, class padding_size = align_64bit_cache_line, class memory_pool = pool<T, padding_size>>
class block_allocator
{
field_variables:
	memory_pool s_pool;
static_methods:
	_NODISCARD_ _FORCE_INLINE_ T* allocate(size_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ T* allocate(size_t count_p, const T& initial_value_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ T* allocate(size_t count_p, T&& initial_rvalue_p) noexcept;
	_FORCE_INLINE_ void deallocate(T* ptr_p, size_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ T* reallocate(T* src_ptr_p, size_t new_count_p) noexcept;
};

template<typename T, class padding_size, class memory_pool>
_NODISCARD_ _FORCE_INLINE_ T* block_allocator<T, padding_size, memory_pool>::allocate(size_t count_p) noexcept
{
	return nullptr;
}

template<typename T, class padding_size, class memory_pool>
_NODISCARD_ _FORCE_INLINE_ T* block_allocator<T, padding_size, memory_pool>::allocate(size_t count_p, const T& initial_value_p) noexcept
{
	return nullptr;
}

template<typename T, class padding_size, class memory_pool>
_NODISCARD_ _FORCE_INLINE_ T* block_allocator<T, padding_size, memory_pool>::allocate(size_t count_p, T&& initial_rvalue_p) noexcept
{
	return nullptr;
}

template<typename T, class padding_size, class memory_pool>
_FORCE_INLINE_ void block_allocator<T, padding_size, memory_pool>::deallocate(T* ptr_p, size_t count_p) noexcept
{
	return;
}

template<typename T, class padding_size, class memory_pool>
_NODISCARD_ _FORCE_INLINE_ T* block_allocator<T, padding_size, memory_pool>::reallocate(T* src_ptr_p, size_t new_count_p) noexcept
{
	return nullptr;
}






template <typename T, class padding_size = align_null, class string = std::string>
class alignas(padding_size::s_size) object_with_tag
{
member_variables:
	string m_tag; // TO DO: complete FE::string class and replace standard string with native frogman API string 
	T m_object;

constructors:
	_FORCE_INLINE_ object_with_tag() noexcept {}

	_FORCE_INLINE_ object_with_tag(T&& object_p) noexcept : m_object(object_p) {}
	_FORCE_INLINE_ object_with_tag(T&& object_p, string&& tag_p) noexcept : m_tag(tag_p), m_object(object_p) {}
	_FORCE_INLINE_ object_with_tag(T&& object_p, const string& tag_ref_p) noexcept : m_tag(tag_ref_p), m_object(object_p) {}

	_FORCE_INLINE_ object_with_tag(const T& object_ref_p) noexcept : m_object(object_ref_p) {}
	_FORCE_INLINE_ object_with_tag(const T& object_ref_p, const string& tag_ref_p) noexcept : m_tag(tag_ref_p), m_object(object_ref_p) {}
	_FORCE_INLINE_ object_with_tag(const T& object_ref_p, string&& tag_p) noexcept : m_tag(tag_p), m_object(object_ref_p) {}

copy_constructor:
	_FORCE_INLINE_ object_with_tag(const object_with_tag<T, padding_size, string>& object_ref_p) noexcept;

move_constructor:
	_FORCE_INLINE_ object_with_tag(object_with_tag<T, padding_size, string>&& rvalue_p) noexcept;

destructor:
	_FORCE_INLINE_ ~object_with_tag() {}

assignment_operator:
	_FORCE_INLINE_ T& operator=(const T& value_ref_p) noexcept;
	_FORCE_INLINE_ string& operator=(const string& value_ref_p) noexcept;

copy_assignment_operator:
	_FORCE_INLINE_ object_with_tag& operator=(const object_with_tag<T, padding_size, string>& value_ref_p) noexcept;

move_assignment_operator:
	_FORCE_INLINE_ object_with_tag& operator=(T&& rvalue_p) noexcept;

assignment_operator:
	_FORCE_INLINE_ string& operator=(string&& rvalue_p) noexcept;
	_FORCE_INLINE_ object_with_tag& operator=(object_with_tag<T, padding_size, string>&& rvalue_p) noexcept;

methods:
	_FORCE_INLINE_ T copy() const noexcept { return this->m_object; }

operators:
	_FORCE_INLINE_ friend boolean operator==(const object_with_tag<T, padding_size, string>& element_ref_p, const string& tag_ref_p) noexcept
	{
		return element_ref_p.m_tag == tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator==(const string& tag_ref_p, const object_with_tag<T, padding_size, string>& element_ref_p) noexcept
	{
		return tag_ref_p == element_ref_p.m_tag ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(const object_with_tag<T, padding_size, string>& element_ref_p, const string& tag_ref_p) noexcept
	{
		return element_ref_p.m_tag != tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(const string& tag_ref_p, const object_with_tag<T, padding_size, string>& element_ref_p) noexcept
	{
		return tag_ref_p != element_ref_p.m_tag ? true : false;
	}

	_FORCE_INLINE_ boolean operator==(const object_with_tag<T, padding_size, string>& element_ref_p) noexcept;
	_FORCE_INLINE_ boolean operator!=(const object_with_tag<T, padding_size, string>& element_ref_p) noexcept;
};

template <typename T, class padding_size, class string>
_FORCE_INLINE_ boolean object_with_tag<T, padding_size, string>::operator==(const object_with_tag<T, padding_size, string>& element_ref_p) noexcept
{
	if ( this->m_object != element_ref_p.m_object )
	{
		return false;
	}

	if ( this->m_tag != element_ref_p.m_tag )
	{
		return false;
	}

	return true;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ boolean object_with_tag<T, padding_size, string>::operator!=(const object_with_tag<T, padding_size, string>& element_ref_p) noexcept
{
	if ( this->m_object == element_ref_p.m_object )
	{
		return false;
	}

	if ( this->m_tag == element_ref_p.m_tag )
	{
		return false;
	}

	return true;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ object_with_tag<T, padding_size, string>::object_with_tag(const object_with_tag<T, padding_size, string>& copy_ref_p) noexcept
{
	this->m_object = copy_ref_p.m_object;
	this->m_tag = copy_ref_p.m_tag;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ object_with_tag<T, padding_size, string>::object_with_tag(object_with_tag<T, padding_size, string>&& move_p) noexcept
{
	this->m_object = move_p.m_object;
	this->m_tag = move_p.m_tag;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ T& object_with_tag<T, padding_size, string>::operator=(const T& value_ref_p) noexcept
{
	this->m_object = value_ref_p;
	return this->m_object;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ string& object_with_tag<T, padding_size, string>::operator=(const string& value_ref_p) noexcept
{
	this->m_tag = value_ref_p;
	return this->m_tag;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ object_with_tag<T, padding_size, string>& object_with_tag<T, padding_size, string>::operator=(const object_with_tag<T, padding_size, string>& value_ref_p) noexcept
{
	this->m_object = value_ref_p.m_object;
	this->m_tag = value_ref_p.m_tag;

	return *this;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ object_with_tag<T, padding_size, string>& object_with_tag<T, padding_size, string>::operator=(T&& rvalue_p) noexcept
{
	this->m_object = rvalue_p;
	return this->m_object;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ string& object_with_tag<T, padding_size, string>::operator=(string&& rvalue_p) noexcept
{
	this->m_tag = rvalue_p;
	return this->m_tag;
}

template <typename T, class padding_size, class string>
_FORCE_INLINE_ object_with_tag<T, padding_size, string>& object_with_tag<T, padding_size, string>::operator=(object_with_tag<T, padding_size, string>&& rvalue_p) noexcept
{
	this->m_object = rvalue_p.m_object;
	this->m_tag = rvalue_p.m_tag;

	return *this;
}





template <typename T>
class t_allocator
{
static_methods:
	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p, const T& initial_value_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p, T&& initial_rvalue_p) noexcept;
	_FORCE_INLINE_ static void deallocate(T* ptr_p, size_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* src_ptr_p, size_t new_count_p) noexcept;
};

template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* t_allocator<T>::allocate(size_t count_p) noexcept
{
	// must invoke delete[] when returning memory block to the system. Calling delete without index operator [] will cause a critical error.
	return new T[count_p];
}

template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* t_allocator<T>::allocate(size_t count_p, const T& initial_value_p) noexcept
{
	return new T[count_p]{ initial_value_p };
}

template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* t_allocator<T>::allocate(size_t count_p, T&& initial_rvalue_p) noexcept
{
	return new T[count_p]{ initial_rvalue_p };
}

template<typename T>
_FORCE_INLINE_ void t_allocator<T>::deallocate(T* ptr_p, size_t count_p) noexcept
{
	assert(ptr_p != nullptr);


	switch ( count_p )
	{
	case 0:
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
		return;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
		assert(false);
		return;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
		exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
#endif
		break;

	default:
		delete[] ptr_p;
	}
}

template<typename T>
_NODISCARD_ _FORCE_INLINE_ T* t_allocator<T>::reallocate(T* src_ptr_p, size_t new_count_p) noexcept
{
	T* l_ptr = src_ptr_p;
	l_ptr = static_cast<T*>( std::realloc(l_ptr, sizeof(T) * new_count_p) );

	if ( l_ptr == nullptr )
	{
		l_ptr = new T[new_count_p];

		memcpy(l_ptr, src_ptr_p, sizeof(T) * new_count_p);

		delete[] src_ptr_p;
	}

	return l_ptr;
}





template <typename T> 
#if _HAS_CXX20 == 1 
	requires string_type<T>
#endif
class string_allocator
{
	static_assert(sizeof(T) <= 4);
static_methods:
	_NODISCARD_ _FORCE_INLINE_ static T* allocate(size_t count_p) noexcept;
	_FORCE_INLINE_ static void deallocate(T* ptr_p, size_t count_p) noexcept;
	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* src_ptr_p, size_t new_count_p) noexcept;
};

template<typename T> 
#if _HAS_CXX20 == 1 
	requires string_type<T>
#endif
_NODISCARD_ _FORCE_INLINE_ T* string_allocator<T>::allocate(size_t count_p) noexcept
{
	// must invoke delete[] when returning memory block to the system. Calling delete without index operator [] will cause a critical error.
	return new T[count_p]{T('\0')};
}

template<typename T> 
#if _HAS_CXX20 == 1 
	requires string_type<T>
#endif
_FORCE_INLINE_ void string_allocator<T>::deallocate(T* ptr_p, size_t count_p) noexcept
{
	assert(ptr_p != nullptr);


	switch ( count_p )
	{
	case 0:
#if _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 0
		return;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 1
		assert(false);
		return;
#elif _FROGMAN_ENGINE_API_MEMORY_SEVERITY_LEVEL_ == 2
		exit(CAST_MEMORY_ERROR_TO_INT8(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
#endif
		break;

	default:
		delete[] ptr_p;
	}
}

template<typename T> 
#if _HAS_CXX20 == 1 
	requires string_type<T>
#endif
_NODISCARD_ _FORCE_INLINE_ T* string_allocator<T>::reallocate(T* src_ptr_p, size_t new_count_p) noexcept
{
	T* l_ptr = src_ptr_p;
	l_ptr = static_cast<T*>( std::realloc(l_ptr, sizeof(T) * new_count_p) );

	if ( l_ptr == nullptr )
	{
		l_ptr = new T[new_count_p]{ T('\0') };

		memcpy(l_ptr, src_ptr_p, sizeof(T) * new_count_p);

		delete[] src_ptr_p;
	}

	return l_ptr;
}





END_NAMESPACE


END_FE

#endif
#endif 


