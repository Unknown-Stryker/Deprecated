﻿#ifndef _FE_CORE_UNIQUE_PTR_HXX_
#define _FE_CORE_UNIQUE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>
#include <FE/core/iterator.hxx>
#include <FE/core/memory.hxx>
#include <initializer_list>




BEGIN_NAMESPACE(FE)


template<typename T, class Allocator = FE::new_delete_allocator<FE::aligned_allocator<typename std::remove_all_extents<T>::type>>>
class unique_ptr final
{
	FE_STATIC_ASSERT((std::is_same<T, Allocator::value_type>::value == false), "static assertion failed: enforcing Allocator's value_type to be equivalent to the typename T. The template parameter T must be identical to the value_type of the Allocator.");
	FE_STATIC_ASSERT(std::is_class<Allocator>::value == false, "Static Assertion Failed: The template argument Allocator is not a class or a struct type.");

public:
	using pointer = typename Allocator::pointer;
	using element_type = typename Allocator::value_type;
	using allocator_type = Allocator;

private:
	_NO_UNIQUE_ADDRESS_ allocator_type m_allocator;
	pointer m_smart_ptr;

public:
	_FORCE_INLINE_ unique_ptr(const Allocator& allocator_p = Allocator()) noexcept : m_allocator(allocator_p), m_smart_ptr() {}
	
	_FORCE_INLINE_ _CONSTEXPR23_ ~unique_ptr() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		this->m_allocator.deallocate(this->m_smart_ptr, 1);
	}

	_CONSTEXPR20_ unique_ptr(const unique_ptr& other_p) noexcept = delete;

	_FORCE_INLINE_ unique_ptr(unique_ptr&& rvalue_p) noexcept : m_allocator(rvalue_p.m_allocator), m_smart_ptr(rvalue_p.m_smart_ptr)
	{
		rvalue_p.m_smart_ptr = nullptr;
	}

	_FORCE_INLINE_ unique_ptr(element_type value_p, const Allocator& allocator_p = Allocator()) noexcept : m_allocator(allocator_p), m_smart_ptr(m_allocator.allocate(1))
	{
		*this->m_smart_ptr = std::move(value_p);
	}

	_CONSTEXPR20_ unique_ptr& operator=(const unique_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ unique_ptr& operator=(unique_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		if (this->m_smart_ptr != nullptr)
		{
			this->m_smart_ptr.deallocate(this->m_smart_ptr, 1);
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;
		return *this;
	}

	_CONSTEXPR20_ unique_ptr& operator=(element_type value_p) noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			this->m_smart_ptr = this->m_allocator.allocate(1);
		}

		*this->m_smart_ptr = std::move(value_p);
		return *this;
	}

	_NODISCARD_ _CONSTEXPR20_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		return l_result;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		this->m_allocator.deallocate(this->m_smart_ptr, 1);
		this->m_smart_ptr = nullptr;
	}

	_CONSTEXPR20_ void reset(element_type value_p) noexcept
	{
		this->operator=(std::move(value_p));
	}

	_CONSTEXPR20_ void swap(unique_ptr& in_out_other_p) noexcept
	{
		pointer l_temporary_smart_ptr = in_out_other_p.m_smart_ptr;
		in_out_other_p.m_smart_ptr = this->m_smart_ptr;
		this->m_smart_ptr = l_temporary_smart_ptr;
	}

	_FORCE_INLINE_ allocator_type& get_allocator() noexcept
	{
		return this->m_allocator;
	}

	_FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return this->m_smart_ptr != nullptr;
	}

	_FORCE_INLINE_ bool operator!() const noexcept
	{
		return this->m_smart_ptr == nullptr;
	}

	_FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return *this->m_smart_ptr;
	}

	_FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}


	_FORCE_INLINE_ boolean operator==(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr == nullptr_p;
	}

	_FORCE_INLINE_ boolean operator!=(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr != nullptr_p;
	}

	_FORCE_INLINE_ boolean operator==(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}
};

template<typename T, class Allocator = FE::new_delete_allocator<FE::aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ unique_ptr<T, Allocator> make_unique() noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return unique_ptr<T, Allocator>(T());
}

template<typename T, class Allocator = FE::new_delete_allocator<FE::aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ unique_ptr<T, Allocator> make_unique(T value_p) noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return unique_ptr<T, Allocator>( T( std::move(value_p) ) );
}




template<typename T, class Allocator>
class unique_ptr<T[], Allocator> final
{
	FE_STATIC_ASSERT((std::is_same<T, Allocator::value_type>::value == false), "static assertion failed: enforcing Allocator's value_type to be equivalent to the typename T. The template parameter T must be identical to the value_type of the Allocator.");
	FE_STATIC_ASSERT(std::is_class<Allocator>::value == false, "Static Assertion Failed: The template argument Allocator is not a class or a struct type.");

public:
	using pointer = typename Allocator::pointer;
	using element_type = typename Allocator::value_type;
	using allocator_type = Allocator;

private:
	_NO_UNIQUE_ADDRESS_ allocator_type m_allocator;
	pointer m_smart_ptr;
	pointer m_smart_ptr_end;

public:
	_FORCE_INLINE_ unique_ptr(const Allocator& allocator_p = Allocator()) noexcept : m_allocator(allocator_p), m_smart_ptr(), m_smart_ptr_end() {}

	_FORCE_INLINE_ _CONSTEXPR23_ ~unique_ptr() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}
	
		this->m_allocator.deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
	}

	_CONSTEXPR20_ unique_ptr(const unique_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ unique_ptr(unique_ptr&& rvalue_p) noexcept : m_allocator(rvalue_p.m_allocator), m_smart_ptr(rvalue_p.m_smart_ptr), m_smart_ptr_end(rvalue_p.m_smart_ptr_end)
	{
		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_smart_ptr_end = nullptr;
	}

	_FORCE_INLINE_ unique_ptr(FE::reserve&& array_size_p, const Allocator& allocator_p = Allocator()) noexcept : m_allocator(allocator_p), m_smart_ptr(m_allocator.allocate(array_size_p._value)), m_smart_ptr_end(m_smart_ptr + array_size_p._value)
	{
	}

	_CONSTEXPR20_ unique_ptr(std::initializer_list<element_type>&& values_p, const Allocator& allocator_p = Allocator()) noexcept : m_allocator(allocator_p), m_smart_ptr(m_allocator.allocate( values_p.size() )), m_smart_ptr_end(m_smart_ptr + values_p.size())
	{
		if (values_p.size() == 0)
		{
			return;
		}

		this->__copy_from_initializer_list(std::move(values_p));
	}

	_CONSTEXPR20_ unique_ptr& operator=(const unique_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ unique_ptr& operator=(unique_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		if (this->m_smart_ptr != nullptr)
		{
			this->m_allocator.deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		this->m_smart_ptr_end = rvalue_p.m_smart_ptr_end;

		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_smart_ptr_end = nullptr;
		return *this;
	}

	_CONSTEXPR20_ unique_ptr& operator=(std::initializer_list<element_type>&& values_p) noexcept
	{
		if (values_p.size() == 0)
		{
			return *this;
		}

		this->__reallocate(values_p.size());
		this->__copy_from_initializer_list(std::move(values_p));
		return *this;
	}

	_FORCE_INLINE_ unique_ptr& operator=(FE::resize_to&& new_array_size_p) noexcept
	{
		this->__reallocate(new_array_size_p._value);
		return *this;
	}

	_NODISCARD_ _CONSTEXPR20_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		this->m_smart_ptr_end = nullptr;
		return l_result;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		this->m_allocator.deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
		this->m_smart_ptr = nullptr;
		this->m_smart_ptr_end = nullptr;
	}

	_CONSTEXPR23_ void reset(std::initializer_list<element_type>&& values_p) noexcept
	{
		this->operator=(std::move(values_p));
	}

	_FORCE_INLINE_ void reset(FE::resize_to&& new_array_size_p) noexcept
	{
		this->operator=(std::move(new_array_size_p));
	}

	_FORCE_INLINE_ size_t capacity() const noexcept
	{
		return this->m_smart_ptr_end - this->m_smart_ptr;
	}

	_CONSTEXPR20_ void swap(unique_ptr& in_out_other_p) noexcept
	{
		pointer l_temporary_smart_ptr = in_out_other_p.m_smart_ptr;
		pointer l_temporary_smart_ptr_end = in_out_other_p.m_smart_ptr_end;
		in_out_other_p.m_smart_ptr = this->m_smart_ptr;
		in_out_other_p.m_smart_ptr_end = this->m_smart_ptr_end;
		this->m_smart_ptr = l_temporary_smart_ptr;
		this->m_smart_ptr_end = l_temporary_smart_ptr_end;
	}

	_FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_FORCE_INLINE_ allocator_type& get_allocator() noexcept
	{
		return this->m_allocator;
	}

	_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return this->m_smart_ptr != nullptr;
	}

	_FORCE_INLINE_ bool operator!() const noexcept
	{
		return this->m_smart_ptr == nullptr;
	}

	_FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return *this->m_smart_ptr;
	}

	_FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}

	_FORCE_INLINE_ element_type& operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		FE_ASSERT(static_cast<index_t>(this->m_smart_ptr_end - this->m_smart_ptr) <= index_p, "${%s@0}: ${%s@1} exceeds the index boundary. ${%s@1} was ${%lu@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(index_p), &index_p);

		return this->m_smart_ptr[index_p];
	}


	_CONSTEXPR23_ _FORCE_INLINE_ boolean operator==(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr == nullptr_p;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ boolean operator!=(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr != nullptr_p;
	}

	_FORCE_INLINE_ boolean operator==(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const unique_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ FE::iterator<FE::contiguous_iterator<element_type>> begin() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}
	_FORCE_INLINE_ FE::iterator<FE::contiguous_iterator<element_type>> end() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr_end;
	}
	_FORCE_INLINE_ FE::const_iterator<FE::contiguous_iterator<element_type>> cbegin() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}
	_FORCE_INLINE_ FE::const_iterator<FE::contiguous_iterator<element_type>> cend() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr_end;
	}
	_FORCE_INLINE_ FE::reverse_iterator<FE::contiguous_iterator<element_type>> rbegin() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}
	_FORCE_INLINE_ FE::reverse_iterator<FE::contiguous_iterator<element_type>> rend() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr_end;
	}
	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<element_type>> crbegin() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}
	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<element_type>> crend() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr_end;
	}

private:
	_CONSTEXPR20_ void __copy_from_initializer_list(std::initializer_list<element_type>&& values_p) noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));

		if constexpr (FE::is_trivial<T>::value == FE::TYPE_TRIVIALITY::_TRIVIAL)
		{
			FE::memcpy<allocator_type::is_address_aligned>(this->m_smart_ptr, const_cast<pointer>(values_p.begin()), values_p.size() * sizeof(element_type));
		}
		else if constexpr (FE::is_trivial<T>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			count_t l_initializer_list_size = values_p.size();

			pointer l_initializer_list_iterator = const_cast<pointer>(values_p.begin());
			pointer l_smart_ptr_iterator = this->m_smart_ptr;
			for (var::count_t i = 0; i < l_initializer_list_size; ++i)
			{
				*l_smart_ptr_iterator = std::move(*l_initializer_list_iterator);
				++l_smart_ptr_iterator;
				++l_initializer_list_iterator;
			}
		}
	}

	_FORCE_INLINE_ void __reallocate(size_t new_count_p) noexcept
	{
		this->m_smart_ptr = this->m_allocator.reallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr, new_count_p);
		this->m_smart_ptr_end = this->m_smart_ptr + new_count_p;
	}
};

template<typename T, class Allocator = FE::new_delete_allocator<FE::aligned_allocator<typename std::remove_all_extents<T>::type>>>
_CONSTEXPR23_ _NODISCARD_ unique_ptr<typename std::remove_all_extents<T>::type[], Allocator> make_unique(size_t array_size_p) noexcept
{
	static_assert(std::is_array<T>::value == true, "static assertion failed: The typename T must be an array type");
	return unique_ptr<typename std::remove_all_extents<T>::type[], Allocator>(FE::reserve{ array_size_p });
}

template<typename T, class Allocator = FE::new_delete_allocator<FE::aligned_allocator<typename std::remove_all_extents<T>::type>>>
_CONSTEXPR23_ _NODISCARD_ unique_ptr<typename std::remove_all_extents<T>::type[], Allocator> make_unique(std::initializer_list<typename std::remove_all_extents<T>::type>&& values_p) noexcept
{
	static_assert(std::is_array<T>::value == true, "static assertion failed: The typename T must be an array type");
	return unique_ptr<typename std::remove_all_extents<T>::type[], Allocator>(std::move(values_p));
}








END_NAMESPACE
#endif