#ifndef _FE_CORE_TAGGED_OBJECT_HXX_
#define _FE_CORE_TAGGED_OBJECT_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "private/memory.hxx"


BEGIN_NAMESPACE(FE)


template< typename char_type >
#if _HAS_CXX20 == 1
	requires string_type<char_type>
#endif
class basic_cstring;


#pragma pack(push, _DWORD_SIZE_)

template <typename T, class padding_size = ::FE::memory::align_null, class string = basic_cstring<char>>
class alignas(padding_size::s_size) tagged_object final
{
private:
	string m_tag;
	T m_object;

public:
	typedef T value_type;
	typedef padding_size alignment_type;
	typedef string tag_type;

	_FORCE_INLINE_ tagged_object() noexcept = default;

	_FORCE_INLINE_ tagged_object(T&& object_p) noexcept : m_object(object_p) {}
	_FORCE_INLINE_ tagged_object(T&& object_p, string&& tag_p) noexcept : m_tag(tag_p), m_object(object_p) {}
	_FORCE_INLINE_ tagged_object(T&& object_p, string& tag_ref_p) noexcept : m_tag(tag_ref_p), m_object(object_p) {}

	_FORCE_INLINE_ tagged_object(const T& object_cref_p) noexcept : m_object(object_cref_p) {}
	_FORCE_INLINE_ tagged_object(const T& object_cref_p, string& tag_ref_p) noexcept : m_tag(tag_ref_p), m_object(object_cref_p) {}
	_FORCE_INLINE_ tagged_object(const T& object_cref_p, string&& tag_p) noexcept : m_tag(tag_p), m_object(object_cref_p) {}


	_FORCE_INLINE_ tagged_object(const tagged_object<T, padding_size, string>& object_cref_p) noexcept
	{
		this->m_object = object_cref_p.m_object;
		this->m_tag = object_cref_p.m_tag;
	}


	_FORCE_INLINE_ tagged_object(tagged_object<T, padding_size, string>&& rvalue_p) noexcept
	{
		this->m_object = rvalue_p.m_object;
		this->m_tag = rvalue_p.m_tags;
	}


	_FORCE_INLINE_ ~tagged_object() noexcept = default;


	_FORCE_INLINE_ T& operator=(const T& value_cref_p) noexcept
	{
		this->m_object = value_cref_p;
		return this->m_object;
	}
	
	_FORCE_INLINE_ string& operator=(string& value_ref_p) noexcept
	{
		this->m_tag = value_ref_p;
		return this->m_tag;
	}


	_FORCE_INLINE_ tagged_object& operator=(const tagged_object<T, padding_size, string>& value_cref_p) noexcept
	{
		this->m_object = value_cref_p.m_object;
		this->m_tag = value_cref_p.m_tag;

		return *this;
	}


	_FORCE_INLINE_ tagged_object& operator=(T&& rvalue_p) noexcept
	{
		this->m_object = rvalue_p;
		return this->m_object;
	}


	_FORCE_INLINE_ string& operator=(string&& rvalue_p) noexcept
	{
		this->m_tag = rvalue_p;
		return this->m_tag;
	}

	_FORCE_INLINE_ tagged_object& operator=(tagged_object<T, padding_size, string>&& rvalue_p) noexcept
	{
		this->m_object = rvalue_p.m_object;
		this->m_tag = rvalue_p.m_tag;

		return *this;
	}


	_FORCE_INLINE_ T copy() const noexcept { return this->m_object; }


	_FORCE_INLINE_ friend boolean operator==(const tagged_object<T, padding_size, string>& element_cref_p, string& tag_ref_p) noexcept
	{
		return element_cref_p.m_tag == tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator==(string& tag_ref_p, const tagged_object<T, padding_size, string>& element_cref_p) noexcept
	{
		return tag_ref_p == element_cref_p.m_tag ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(const tagged_object<T, padding_size, string>& element_cref_p, string& tag_ref_p) noexcept
	{
		return element_cref_p.m_tag != tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(string& tag_ref_p, const tagged_object<T, padding_size, string>& element_cref_p) noexcept
	{
		return tag_ref_p != element_cref_p.m_tag ? true : false;
	}

	_FORCE_INLINE_ boolean operator==(const tagged_object<T, padding_size, string>& element_cref_p) noexcept
	{
		if (this->m_object != element_cref_p.m_object)
		{
			return false;
		}

		if (this->m_tag != element_cref_p.m_tag)
		{
			return false;
		}

		return true;
	}

	_FORCE_INLINE_ boolean operator!=(const tagged_object<T, padding_size, string>& element_cref_p) noexcept
	{
		if (this->m_object == element_cref_p.m_object)
		{
			return false;
		}

		if (this->m_tag == element_cref_p.m_tag)
		{
			return false;
		}

		return true;
	}
};

#pragma pack(pop)


END_NAMESPACE
#endif 
