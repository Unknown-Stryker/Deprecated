#pragma once
#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include"typeinfo.h"
using typeinfo::compare_data_types;
using typeinfo::GET_type_name;
using typeinfo::TYPE_COMPARISON_RESULT;

#include "string.h"
using memory::string;

const index AUTO_INSERTION_FAILURE = 18446744073709551615;


template <typename T>
class dynamic_array
{
	struct element
	{
		T m_data;
		string m_tag;

		element();
		element(T data_p);
		~element();
	};


	bool* m_Is_it_valid;
	element* m_allocator;

	element* m_array_pointer;

	length m_array_size;
	length m_capacity;

	// miscellaneous
	length m_divider;

	index m_emplace_back_idx;
	index m_iterate_idx;

	T null;

public:
	dynamic_array(length initial_length_param = 10);
	dynamic_array(length initial_length_param, T initial_val_param);
	~dynamic_array();

	length GET_total_length()  const;

	length GET_capacity()  const;
	void SET_capacity_by_percent(length Percent_Param = 50);
	length GET_number_of_valid_elements() const;
	string GET_tag(index Index_param)  const;

	void extend();
	void resize(length Size_param);

	// Exclusively Avaliable for m_array_pointer Types
	void shrink_to_fit();

	void insert(index Index_param, T Data_param);
	void insert(index Index_param, T Data_param, string Tag_param);
	void insert(index Index_param, string Tag_param);

	void emplace_back(T Data_param);
	void emplace_back(T Data_param, string Tag_param);
	T& Iterate();

	T& operator[](index Index_param);
	T& operator[](string Tag_param);
	dynamic_array& get_instance();

	static void swap(dynamic_array& A, dynamic_array& B);

	T* copy_primitive_array();
	element* copy_array();
};


template<typename T>
inline dynamic_array<T>::element::element() : m_data(), m_tag("\0")
{
}

template<typename T>
inline dynamic_array<T>::element::element(T data_param) : m_data(data_param), m_tag("\0")
{
}

template<typename T>
inline dynamic_array<T>::element::~element()
{
}


template<typename T>
inline dynamic_array<T>::dynamic_array(length initial_length_param)
	: m_array_pointer(nullptr), m_allocator(nullptr), m_Is_it_valid(nullptr), m_array_size(initial_length_param), m_capacity(initial_length_param), m_divider(2), m_emplace_back_idx(0), m_iterate_idx(0), null()
{
	if (initial_length_param < 10)
	{
		initial_length_param = 10;
	}
	this->m_array_pointer = new element[initial_length_param];
}

template<typename T>
inline dynamic_array<T>::dynamic_array(length initial_length_param, T initial_val_param)
{
	if (initial_length_param < 10)
	{
		initial_length_param = 10;
	}
	this->m_array_pointer = new element[initial_length_param]{ initial_val_param };
}

template<typename T>
inline dynamic_array<T>::~dynamic_array()
{
	delete[] this->m_array_pointer;
}

template<typename T>
inline length dynamic_array<T>::GET_total_length() const
{
	if (this != nullptr)
	{
		return this->m_array_size;
	}
	return 0;
}

template<typename T>
inline length dynamic_array<T>::GET_capacity()  const
{
	return this->m_capacity;
}

template<typename T>
inline void dynamic_array<T>::SET_capacity_by_percent(length Percent_Param)
{
	m_divider = 100 / Percent_Param;
	this->m_capacity = this->m_array_size / m_divider;
}

template<typename T>
inline length dynamic_array<T>::GET_number_of_valid_elements() const
{
	return this->m_emplace_back_idx;
}

template<typename T>
inline string dynamic_array<T>::GET_tag(index Index_param)  const
{
	return this->m_array_pointer[Index_param].m_tag;
}

template<typename T>
inline void dynamic_array<T>::extend()
{
	if (this->m_array_pointer == nullptr) { return; }


	this->m_allocator = new element[this->m_array_size + this->m_capacity] {};

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
#pragma warning (disable : 6385)
		this->m_allocator[idx] = this->m_array_pointer[idx];
	}

	delete[] this->m_array_pointer;

	this->m_array_pointer = this->m_allocator;

	this->m_array_size = this->m_array_size + this->m_capacity;

	this->m_allocator = nullptr;

	this->m_capacity = this->m_array_size / this->m_divider;
}

template<typename T>
inline void dynamic_array<T>::resize(length Size_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}


	this->m_allocator = new element[Size_param];

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		this->m_allocator[idx] = this->m_array_pointer[idx];
	}

	delete[] this->m_array_pointer;

	this->m_array_pointer = this->m_allocator;

	this->m_allocator = nullptr;

	this->m_array_size = Size_param;

	this->m_capacity = this->m_array_size / this->m_divider;
}

template<typename T>
inline void dynamic_array<T>::shrink_to_fit()
{
	if (this == nullptr) { return; }

	else if (this->m_array_pointer == nullptr) { return; }

	else if (typeinfo::Is_it__ptr(this->m_array_pointer[0].m_data) == false) { return; }

	length is_it_new = 0;
	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		if (this->m_array_pointer[idx].m_data == nullptr)
		{
			++is_it_new;
		}
	}

	if (is_it_new == this->m_array_size) { return; }

	else if (is_it_new == 0) { return; }



	// CODE STARTS HERE

	// Allocate Authenticator
	this->m_Is_it_valid = new bool[this->m_array_size];

	// Mark Valid Pointers
	length valid_elements = 0;
	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		if (this->m_array_pointer[idx].m_data != nullptr)
		{
			this->m_Is_it_valid[idx] = true;
			++valid_elements;
		}
	}

	// Allocate New dynamic_array
	this->m_allocator = new element[valid_elements];
	index alloctr_idx = 0;

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		if (this->m_Is_it_valid[idx] == true)
		{
			this->m_allocator[alloctr_idx].m_data = this->m_array_pointer[idx].m_data;
			++alloctr_idx;
		}
	}

	delete[] this->m_array_pointer;
	this->m_array_pointer = this->m_allocator;
	this->m_array_size = valid_elements;
	this->m_allocator = nullptr;
	delete[] this->m_Is_it_valid;
	this->m_Is_it_valid = nullptr;
}


template<typename T>
inline void dynamic_array<T>::insert(index Index_param, T Data_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (Index_param < this->m_array_size)
	{
		this->m_array_pointer[Index_param].m_data = Data_param;
		return;
	}

	for (; this->m_array_size <= Index_param; this->extend()) {}

	if (this->m_array_size > Index_param)
	{
		this->insert(Index_param, Data_param);
	}
}

template<typename T>
inline void dynamic_array<T>::insert(index Index_param, T Data_param, string Tag_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (Index_param < this->m_array_size)
	{
		this->m_array_pointer[Index_param].m_data = Data_param;
		this->m_array_pointer[Index_param].m_tag = Tag_param;
		return;
	}

	for (; this->m_array_size <= Index_param; this->extend()) {}

	if (this->m_array_size > Index_param)
	{
		this->insert(Index_param, Data_param, Tag_param);
	}
}

template<typename T>
inline void dynamic_array<T>::insert(index Index_param, string Tag_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (Index_param < this->m_array_size)
	{
		this->m_array_pointer[Index_param].m_tag = Tag_param;
		return;
	}

	for (; this->m_array_size <= Index_param; this->extend()) {}

	if (this->m_array_size > Index_param)
	{
		this->insert(Index_param, Tag_param);
	}
}


template<typename T>
inline void dynamic_array<T>::emplace_back(T Data_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (this->m_emplace_back_idx >= this->m_array_size)
	{
		this->insert(this->m_emplace_back_idx, Data_param);
		++this->m_emplace_back_idx;
		return;
	}

	this->m_array_pointer[this->m_emplace_back_idx].m_data = Data_param;

	++this->m_emplace_back_idx;

}

template<typename T>
inline void dynamic_array<T>::emplace_back(T Data_param, string Tag_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (this->m_emplace_back_idx >= this->m_array_size)
	{
		this->insert(this->m_emplace_back_idx, Data_param, Tag_param);
		++this->m_emplace_back_idx;
		return;
	}

	this->m_array_pointer[this->m_emplace_back_idx].m_data = Data_param;
	this->m_array_pointer[this->m_emplace_back_idx].m_tag = Tag_param;

	++this->m_emplace_back_idx;
}

template<typename T>
inline T& dynamic_array<T>::Iterate()
{
	if (this->m_array_pointer == nullptr)
	{
		return;
	}

	if (this->m_iterate_idx >= this->m_array_size)
	{
		this->m_iterate_idx = 0;
	}

	++this->m_iterate_idx;
	return this->m_array_pointer[this->m_iterate_idx - 1].m_data;
}


template<typename T>
inline T& dynamic_array<T>::operator[](index Index_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return null;
	}

	return this->m_array_pointer[Index_param].m_data;
}

template<typename T>
inline T& dynamic_array<T>::operator[](string Tag_param)
{
	if (this->m_array_pointer == nullptr)
	{
		return null;
	}

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		if (this->m_array_pointer[idx].m_tag == Tag_param)
		{
			return this->m_array_pointer[idx].m_data;
		}
	}

	return this->null;
}


template<typename T>
inline dynamic_array<T>& dynamic_array<T>::get_instance()
{
	return *this;
}

template<typename T>
inline void dynamic_array<T>::swap(dynamic_array& A, dynamic_array& B)
{
	dynamic_array Temporary = A;

	A = B;

	B = Temporary;
}

template<typename T>
inline T* dynamic_array<T>::copy_primitive_array()
{
	if (this->m_array_pointer == nullptr) { return nullptr; }

	T* new_array = new T[this->m_array_size];

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		new_array[idx] = this->m_array_pointer[idx].m_data;
	}

	return new_array;
}

template<typename T>
inline dynamic_array<T>::element* dynamic_array<T>::copy_array()
{
	if (this->m_array_pointer == nullptr) { return nullptr; }

	element* new_array = new element[this->m_array_size];

	for (index idx = 0; idx < this->m_array_size; ++idx)
	{
		new_array[idx] = this->m_array_pointer[idx];
	}

	return new_array;
}
#endif