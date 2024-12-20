#ifndef _FE_CORE_STRING_VIEW_HXX_
#define _FE_CORE_STRING_VIEW_HXX_
/*
Copyright © from 2022 to present, UNKNOWN STRYKER. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <FE/framework/managed/ptr.hxx>

#include <FE/prerequisites.h>
#include <FE/algorithm/string.hxx>
#include <FE/algorithm/utility.hxx>
#include <FE/iterator.hxx>
#include <FE/type_traits.hxx>

// std
#include <optional>
#include <utility>




BEGIN_NAMESPACE(FE)


template<typename CharT, class Allocator, class Traits>
class basic_string;


template<typename CharT>
class basic_string_view final
{
	FE_NEGATIVE_STATIC_ASSERT(FE::is_char<CharT>::value == false, "CharT is not a valid character type");

	FE::ptr<CharT[]> m_watcher;
	var::index_t m_begin;
	var::index_t m_end;

public:
	using value_type = CharT;
	using pointer = CharT*;
	using const_pointer = const CharT*;
	using reference = CharT&;
	using const_reference = const CharT&;
	using const_iterator = FE::const_iterator<FE::contiguous_iterator<CharT>>;
	using iterator = FE::iterator<FE::contiguous_iterator<CharT>>;
	using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<CharT>>;
	using reverse_iterator = FE::reverse_iterator<FE::contiguous_iterator<CharT>>;
	using size_type = var::index_t;
	using length_type = var::index_t;
	using difference_type = ptrdiff;


	_FE_CONSTEXPR17_ basic_string_view() noexcept : m_watcher(), m_begin(), m_end() {}
	_FE_CONSTEXPR17_ basic_string_view(basic_string_view& other_p) noexcept : m_watcher(other_p.m_watcher), m_begin(other_p.m_begin), m_end(other_p.m_end) {}
	_FE_CONSTEXPR17_ basic_string_view(basic_string_view&& rvalue_p) noexcept : m_watcher(rvalue_p.m_watcher), m_begin(rvalue_p.m_begin), m_end(rvalue_p.m_end) 
	{
		rvalue_p.m_watcher.reset();
		rvalue_p.m_begin = 0;
		rvalue_p.m_end = 0;
	}

	_FE_CONSTEXPR20_ ~basic_string_view() noexcept {}

	template<class Allocator>
	_FE_CONSTEXPR20_ basic_string_view(const FE::exclusive_ptr<CharT[], Allocator>& source_p) noexcept : m_watcher(source_p), m_begin(), m_end()
	{
		if (this->m_watcher.is_expired() == true)
		{
			return;
		}

		this->m_end = algorithm::string::length(this->m_watcher.get());
	}

	_FE_CONSTEXPR20_ basic_string_view& operator=(basic_string_view& other_p) noexcept
	{
		if (other_p.m_watcher.is_expired() == true)
		{
			return *this;
		}

		this->m_watcher = other_p.m_watcher;
		this->m_begin = other_p.m_begin;
		this->m_end = other_p.m_end;

		return *this;
	}

	_FE_CONSTEXPR20_ basic_string_view& operator=(basic_string_view&& rvalue_p) noexcept
	{
		if (rvalue_p.m_watcher.is_expired() == true)
		{
			return *this;
		}

		this->m_watcher = rvalue_p.m_watcher;
		this->m_begin = rvalue_p.m_begin;
		this->m_end = rvalue_p.m_end;

		rvalue_p.m_watcher.reset();
		rvalue_p.m_begin = 0;
		rvalue_p.m_end = 0;

		return *this;
	}

	template<class Allocator>
	_FE_CONSTEXPR20_ basic_string_view& operator=(const FE::exclusive_ptr<CharT[], Allocator>& source_p) noexcept
	{
		if (source_p == nullptr)
		{
			return *this;
		}

		this->m_begin = 0;
		this->m_end = algorithm::string::length(source_p.get());
		this->m_watcher = source_p;
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ iterator begin() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return iterator{ l_pointer_to_string + this->m_begin };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ iterator end() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return iterator{ l_pointer_to_string + this->m_end };
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_iterator begin() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_iterator{ l_pointer_to_string + this->m_begin };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_iterator end() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_iterator{ l_pointer_to_string + this->m_end };
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_iterator cbegin() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_iterator{ l_pointer_to_string + this->m_begin };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_iterator cend() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_iterator{ l_pointer_to_string + this->m_end };
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ reverse_iterator rbegin() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return reverse_iterator{ (l_pointer_to_string + this->m_end) - 1 };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ reverse_iterator rend() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return reverse_iterator{ (l_pointer_to_string + this->m_begin) - 1 };
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reverse_iterator rbegin() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_reverse_iterator{ (l_pointer_to_string + this->m_end) - 1 };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reverse_iterator rend() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_reverse_iterator{ (l_pointer_to_string + this->m_begin) - 1 };
	}
	
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_reverse_iterator{ (l_pointer_to_string + this->m_end) - 1 };
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reverse_iterator crend() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return const_reverse_iterator{ (l_pointer_to_string + this->m_begin) - 1 };
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ reference operator[](index_t index_p) noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		FE_NEGATIVE_ASSERT(index_p >= this->m_end, "${%s@0}: ${%s@1} was ${%lu@2}, and the string capacity was ${%lu@3}", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(index_p), &index_p, &m_end);
		return l_pointer_to_string[index_p];
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reference operator[](index_t index_p) const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		FE_NEGATIVE_ASSERT(index_p >= this->m_end, "${%s@0}: ${%s@1} was ${%lu@2}, and the string capacity was ${%lu@3}", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(index_p), &index_p, &m_end);
		return l_pointer_to_string[index_p];
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ reference front() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return *(l_pointer_to_string + this->m_begin);
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reference front() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return *(l_pointer_to_string + this->m_begin);
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ reference back() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return *((l_pointer_to_string + this->m_end) - 1);
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_reference back() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return *((l_pointer_to_string + this->m_end) - 1);
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ pointer data() noexcept
	{
		pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return l_pointer_to_string + this->m_begin;
	}
	_FE_NODISCARD_ _FE_FORCE_INLINE_ const_pointer data() const noexcept
	{
		const_pointer l_pointer_to_string = this->m_watcher.operator->();
		FE_NEGATIVE_ASSERT(l_pointer_to_string == nullptr, "${%s@0}: ${%s@1} was nullptr.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(l_pointer_to_string));
		return l_pointer_to_string + this->m_begin;
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ length_type length() const noexcept
	{
		FE_NEGATIVE_ASSERT(this->m_end < this->m_begin, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_INVALID_ITERATOR), TO_STRING(this->m_begin), TO_STRING(this->m_end), &m_begin, &m_end);
		return this->m_end - this->m_begin; 
	}

	_FE_NODISCARD_ _FE_FORCE_INLINE_ length_type max_length() const noexcept { return FE::max_value<length_type> / sizeof(CharT); }
	_FE_NODISCARD_ _FE_FORCE_INLINE_ boolean is_empty() const noexcept { return this->m_begin == this->m_end; }
	_FE_NODISCARD_ _FE_FORCE_INLINE_ boolean is_valid() const noexcept { return !(this->m_watcher.is_expired()); }


	_FE_CONSTEXPR17_ void remove_prefix(const size_type count_p) noexcept
	{
		FE_NEGATIVE_ASSERT(this->m_begin >= this->m_end, "${%s@0}: Unable to shrink the front of an empty string view", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION));
		this->m_begin += count_p;
	}

	_FE_CONSTEXPR17_ void remove_suffix(const size_type count_p) noexcept
	{
		FE_NEGATIVE_ASSERT(this->m_begin >= this->m_end, "${%s@0}: Unable to shrink the back of an empty string view", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION));
		this->m_end -= count_p;
	}


	_FE_CONSTEXPR20_ void reset_range() noexcept
	{
		FE_NEGATIVE_ASSERT(this->m_watcher.is_expired() == true, "Assertion Failed: Cannot reset an empty string view.");

		this->m_begin = 0;
		this->m_end = algorithm::string::length(this->m_watcher.get());
	}
	
	_FE_CONSTEXPR20_ void swap(basic_string_view& in_out_other_p) noexcept
	{
		std::swap(*this, in_out_other_p);
	}


	_FE_CONSTEXPR20_ void copy(CharT* const out_out_dest_buffer_pointer_p, const size_type buffer_capacity_p, const size_type count_p, const size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(out_out_dest_buffer_pointer_p == nullptr, "${%s@0}: out_dest_string_buffer_p is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR));
		FE_NEGATIVE_ASSERT(count_p > this->length(), "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(count_p), TO_STRING(this->length()));

		algorithm::string::copy(out_out_dest_buffer_pointer_p, buffer_capacity_p, this->begin().operator->() + position_p, count_p);
	}

	template<class Allocator, class Traits>
	_FE_CONSTEXPR20_ void copy(basic_string<CharT, Allocator, Traits>& out_dest_string_buffer_p, _FE_MAYBE_UNUSED_ const size_type buffer_capacity_p, const size_type count_p, const size_type position_p = 0) const noexcept
	{
		pointer l_out_dest_string_buffer = out_dest_string_buffer_p.data();
		FE_NEGATIVE_ASSERT(l_out_dest_string_buffer == nullptr, "${%s@0}: out_dest_string_buffer_p is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR));
		FE_NEGATIVE_ASSERT(count_p > this->length(), "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(count_p), TO_STRING(this->length()));
		FE_NEGATIVE_ASSERT(count_p > buffer_capacity_p, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_BUFFER_OVERFLOW), TO_STRING(count_p), TO_STRING(buffer_capacity_p));

		algorithm::string::copy(l_out_dest_string_buffer, this->begin().operator->() + position_p, count_p);
	}
	
	_FE_NODISCARD_ _FE_CONSTEXPR20_ basic_string_view substr(const size_type position_p, const size_type count_p) noexcept
	{
		FE_NEGATIVE_ASSERT(this->m_watcher.is_expired() == true, "Assertion Failed: Cannot return a substring of an empty string view.");
		FE_NEGATIVE_ASSERT((this->m_begin + position_p + count_p) > this->m_end, "Assertion Failed: requested substring exceeded the string_view index boundary.");
		basic_string_view l_tmp_view;
		l_tmp_view = *this;
		l_tmp_view.m_begin = this->m_begin + position_p;
		l_tmp_view.m_end = this->m_begin + position_p + count_p;

		return l_tmp_view;
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean starts_with(const basic_string_view& other_p) const noexcept
	{
		if (other_p.is_empty() == true)
		{
			return false;
		}

		length_t l_other_string_length = other_p.length();

		if(this->length() < l_other_string_length)
		{
			FE_NEGATIVE_ASSERT(this->length() < l_other_string_length, "Assertion failure: the input string length cannot be greater than the visible string length.");
			return false;
		}

		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_begin, l_other_string_length },
			other_p.begin().operator->(), algorithm::string::range{other_p.m_begin, l_other_string_length}
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean starts_with(const CharT value_p) const noexcept
	{
		if(this->length() == 0)
		{
			FE_NEGATIVE_ASSERT(this->length() == 0, "Assertion failure: the string_view instance is empty and unable to proceed ends_with();");
			return false;
		}

		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_begin, this->m_begin + 1},
			&value_p, algorithm::string::range{ 0, 1 }
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean starts_with(const CharT* const string_p) const noexcept
	{
		FE_NEGATIVE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@0} is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(string_p));

		length_t l_input_string_length = algorithm::string::length(string_p);
		if(this->length() < l_input_string_length)
		{
			FE_NEGATIVE_ASSERT(this->length() < l_input_string_length, "Assertion failure: the input string length cannot be greater than the visible string length.");
			return false;
		}
		
		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_begin, l_input_string_length },
			string_p, algorithm::string::range{ 0, l_input_string_length }
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean ends_with(const basic_string_view& other_p) const noexcept
	{
		if (other_p.m_string_length == 0)
		{
			return false;
		}

		if(this->length() < other_p.m_string_length)
		{
			FE_NEGATIVE_ASSERT(this->length() < other_p.m_string_length, "Assertion failure: the input string length cannot be greater than the visible string length.");
			return false;
		}

		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_end - this->length(), this->m_end },
			other_p.begin().operator->(), algorithm::string::range{ other_p.m_end - other_p.length(), other_p.m_end }
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean ends_with(const CharT value_p) const noexcept
	{
		if(this->length() == 0)
		{
			FE_NEGATIVE_ASSERT(this->length() == 0, "Assertion failure: the string_view instance is empty and unable to proceed ends_with();");
			return false;
		}
		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_end - 1, this->m_end },
			&value_p, algorithm::string::range{ 0, 1 }
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean ends_with(const CharT* const string_p) const noexcept
	{
		FE_NEGATIVE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(string_p));
		
		length_t l_input_string_length = algorithm::string::length(string_p);
		FE_NEGATIVE_ASSERT(l_input_string_length == 0, "Assertion failure: the input string length is zero.");

		if(this->length() < l_input_string_length)
		{
			FE_NEGATIVE_ASSERT(this->length() < l_input_string_length, "Assertion failure: the input string length cannot be greater than the visible string length.");
			return false;
		}
		return algorithm::string::compare_ranged<CharT>(this->begin().operator->(), algorithm::string::range{ this->m_end - l_input_string_length, this->m_end },
			string_p, algorithm::string::range{ 0, l_input_string_length }
		);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean contains(const basic_string_view& other_p) const noexcept
	{
		if (other_p.is_empty() == true)
		{
			return false;
		}

		return (algorithm::string::find_the_first(this->begin().operator->(), other_p.begin().operator->())).has_value();
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean contains(const CharT value_p) const noexcept
	{
		return algorithm::string::find_the_first(this->begin().operator->(), value_p).has_value();
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ boolean contains(const CharT* const string_p) const noexcept
	{
		FE_NEGATIVE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR), TO_STRING(string_p));
		return (algorithm::string::find_the_first(this->begin().operator->(), string_p)).has_value();
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> find(const basic_string_view& other_p, size_type position_p = 0) const noexcept
	{
		if(position_p == 0)
		{
			position_p = other_p.m_begin;
		}

		if (other_p.is_empty() == true)
		{
			return std::nullopt;
		}

		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(position_p), TO_STRING(this->length()));

		return this->find(other_p.begin().operator->(), position_p);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> find(const CharT* const string_p, const size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(string_p == nullptr, "${%s@0}: string_p is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR));
		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));

		std::optional<algorithm::string::range> l_result = algorithm::string::find_the_first(this->begin().operator->() + position_p, string_p);

		if (l_result == std::nullopt)
		{
			return std::nullopt;
		}

		l_result->_begin += position_p;
		l_result->_end += position_p;
		return l_result;
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> find(const CharT value_p, const size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));
		FE_NEGATIVE_ASSERT(this->m_begin > position_p, "${%s@0}: position_p cannot be less than or equal to ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->m_begin));

		std::optional<algorithm::string::range> l_result = algorithm::string::find_the_first(this->begin().operator->() + position_p, value_p);
		
		if (l_result == std::nullopt)
		{
			return std::nullopt;
		}

		l_result->_begin += position_p;
		l_result->_end += position_p;
		return l_result;
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> rfind(const basic_string_view& other_p, const size_type position_p = 0) const noexcept
	{
		if (other_p.is_empty() == true)
		{
			return std::nullopt;
		}

		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));
		return this->rfind(other_p.begin().operator->(), position_p);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> rfind(const CharT* const string_p, size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(string_p == nullptr, "${%s@0}: string_p is nullptr", TO_STRING(ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_NULLPTR));
		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));
		if(position_p == 0)
		{
			position_p = this->m_end;
		}
		FE_NEGATIVE_ASSERT(this->m_begin >= position_p, "${%s@0}: position_p cannot be less than or equal to ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->m_begin));
		return algorithm::string::find_the_last_within_range(this->begin().operator->(), algorithm::string::range{this->m_begin, position_p}, string_p);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ std::optional<algorithm::string::range> rfind(const CharT value_p, size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));

		if(position_p == 0)
		{
			position_p = this->m_end;
		}
		FE_NEGATIVE_ASSERT(this->m_begin >= position_p, "${%s@0}: position_p cannot be less than or equal to ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->m_begin));
		return algorithm::string::find_the_last_within_range(this->begin().operator->(), algorithm::string::range{this->m_begin, position_p}, value_p);
	}

	_FE_NODISCARD_ _FE_CONSTEXPR20_ algorithm::string::count<CharT> count_chars(const CharT value_p, const size_type position_p = 0) const noexcept
	{
		FE_NEGATIVE_ASSERT(position_p > this->length(), "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(FE::ERROR_CODE::_FATAL_MEMORY_ERROR_1XX_ACCESS_VIOLATION), TO_STRING(this->length()));
		
		return algorithm::string::count_chars(this->begin().operator->() + position_p, value_p);
	}

	template<class Allocator, class Traits>
	_FE_CONSTEXPR20_ boolean operator==(const basic_string<CharT, Allocator, Traits>& string_p) const noexcept
	{
		return algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, string_p.c_str(), algorithm::string::range{ 0, string_p.length() });
	}
	_FE_CONSTEXPR20_ boolean operator==(basic_string_view& other_p) const noexcept
	{
		return algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, other_p.m_watcher.operator->(), algorithm::string::range{ other_p.m_begin, other_p.m_end });
	}
	_FE_CONSTEXPR20_ boolean operator==(const CharT* const string_p) const noexcept
	{
		return algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, string_p, algorithm::string::range{ 0, algorithm::string::length(string_p) });
	}
	_FE_CONSTEXPR20_ friend boolean operator==(const CharT* const string_p, basic_string_view& other_p) noexcept
	{
		return algorithm::string::compare_ranged<CharT>(other_p.m_watcher.operator->(), algorithm::string::range{ other_p.m_begin, other_p.m_end }, string_p, algorithm::string::range{0, algorithm::string::length(string_p)});
	}

	template<class Allocator, class Traits>
	_FE_CONSTEXPR20_ boolean operator!=(const basic_string<CharT, Allocator, Traits>& string_p) const noexcept
	{
		return !algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, string_p.c_str(), algorithm::string::range{ 0, string_p.length() });
	}
	_FE_CONSTEXPR20_ boolean operator!=(basic_string_view& other_p) const noexcept
	{
		return !algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, other_p.m_watcher.operator->(), algorithm::string::range{ other_p.m_begin, other_p.m_end });
	}
	_FE_CONSTEXPR20_ boolean operator!=(const CharT* const string_p) const noexcept
	{
		return !algorithm::string::compare_ranged<CharT>(this->m_watcher.operator->(), algorithm::string::range{ this->m_begin, this->m_end }, string_p, algorithm::string::range{ 0, algorithm::string::length(string_p) });
	}
	_FE_CONSTEXPR20_ friend boolean operator!=(const CharT* const string_p, basic_string_view& other_p) noexcept
	{
		return !algorithm::string::compare_ranged<CharT>(other_p.m_watcher.operator->(), algorithm::string::range{ other_p.m_begin , other_p.m_end }, string_p, algorithm::string::range{ 0, algorithm::string::length(string_p) });
	}
};


using string_view = basic_string_view<var::ASCII>;
using wstring_view = basic_string_view<var::wchar>;

#ifdef _FE_HAS_CXX20_
using string_view8 = basic_string_view<var::UTF8>;
#endif

using string_view16 = basic_string_view<var::UTF16>;
using string_view32 = basic_string_view<var::UTF32>;


template <typename T>
struct is_basic_string_view : std::false_type {};

template <typename T>
struct is_basic_string_view<FE::basic_string_view<T>> : std::true_type {};


template <typename T>
struct is_string_class<FE::basic_string_view<T>> : std::true_type {};


END_NAMESPACE
#endif
