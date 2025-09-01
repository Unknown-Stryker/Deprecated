#ifndef _FE_CORE_PARALLEL_PROXY_TABLE_IMPLEMENTATION_HXX_
#define _FE_CORE_PARALLEL_PROXY_TABLE_IMPLEMENTATION_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "proxy_table.interface.hxx"
#include "../../memory/allocator/allocator.implementation.hxx"
#include "../../macros/attributes.h"


// this class will be replaced with concurrent_hash_map


BEGIN_NAMESPACE(FE::parallel)


template<typename T, class allocator>
std::atomic< volatile proxy_ptr<T, allocator>* > proxy_table<T, allocator>::s_null;


template<typename T, class allocator>
_FORCE_INLINE_ std::atomic<volatile proxy_ptr<T, allocator>* >& proxy_table<T, allocator>::operator[](index_t idx_p) noexcept
{
	if (this->m_array_total_length.load(std::memory_order_relaxed) < idx_p)
#if _HAS_CXX20
		_UNLIKELY_
#endif
	{
		exception::handle_exceptions(	true,
										FE::_LOG_EXCEPTION_HISTORY_,
										"FATAL ERROR!: index out of range.",
										_EXCEPTION_ORIGIN_
										);
		return proxy_table<T, allocator>::s_null;
	}

	return this->m_pointer_array_ptr.load(std::memory_order_acquire)[idx_p];
}

template<typename T, class allocator>
_FORCE_INLINE_ std::atomic< volatile proxy_ptr<T, allocator>* >* proxy_table<T, allocator>::emplace_back(proxy_ptr<T, allocator>* const indirect_ptrc_p) noexcept
{
	while (this->m_is_quick_access_ptr_on_update.load(std::memory_order_acquire) == true) {}

	if (this->m_element_count.load(std::memory_order_acquire) < this->m_array_total_length.load(std::memory_order_acquire))
#if _HAS_CXX20
		_LIKELY_
#endif
	{
		std::atomic< volatile proxy_ptr<T, allocator>* >*l_buffer_ptr = &(this->m_pointer_array_ptr.load(std::memory_order_acquire)[this->m_element_count.load(std::memory_order_acquire)]);
	this->m_pointer_array_ptr.load(std::memory_order_acquire)[this->m_element_count.load(std::memory_order_acquire)] = indirect_ptrc_p;
		++this->m_element_count;

		return l_buffer_ptr;
	}

		exception::handle_exceptions(	true,
										FE::_ABORT_IMMEDIATELY_,
										"FATAL ERROR!: out of capacity, returning nullptr.",
										_EXCEPTION_ORIGIN_
										);
	return nullptr;
}

template<typename T, class allocator>
_FORCE_INLINE_ void proxy_table<T, allocator>::reserve(uint64 new_size_p) noexcept
{
	this->m_is_quick_access_ptr_on_update.store(true);

	exception::handle_exceptions(	IF(new_size_p == 0),
									FE::_ABORT_IMMEDIATELY_,
									"void proxy_table<T, allocator>::reserve(uint64 new_size_p) noexcept; uint64 new_size_p is zero, which is invalid.",
									_EXCEPTION_ORIGIN_
									);

	const std::lock_guard<std::mutex> lock(this->m_lock);

	std::atomic<std::atomic<volatile proxy_ptr<T, allocator>*>*> l_ptr = FE::memory::trackable_realloc(	this->m_pointer_array_ptr.load(std::memory_order_relaxed),
																							this->m_array_total_length.load(),
																							sizeof(volatile proxy_ptr<T, allocator>*),
																							this->m_array_total_length.load() + new_size_p,
																							sizeof(volatile proxy_ptr<T, allocator>*)
																							);
																			
	this->m_pointer_array_ptr = l_ptr.exchange(nullptr);

	this->m_array_total_length.store(this->m_array_total_length.load(std::memory_order_relaxed) + new_size_p);

	FE::memory::memset_s( this->m_pointer_array_ptr.load(std::memory_order_relaxed), NULL, this->m_array_total_length.load(std::memory_order_relaxed), sizeof(volatile proxy_ptr<T, allocator>*) );

	for (var::uint64 idx = 0; idx < this->m_element_count.load(std::memory_order_acquire); ++idx)
	{
		if (this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx] != nullptr)
		{
			this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx].load()->m_quick_access_ptr.store(&(this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx]));
		}
	}

	this->m_is_quick_access_ptr_on_update.store(false);
}

template<typename T, class allocator>
_FORCE_INLINE_ void proxy_table<T, allocator>::sort() const noexcept
{
	if (this->m_lock.try_lock() == false) { return; }
	
	this->m_is_quick_access_ptr_on_update.store(true);

	volatile proxy_ptr<T, allocator>* l_buffer = nullptr;
	auto l_progress = this->m_pointer_array_ptr.load(std::memory_order_relaxed);

	static var::boolean l_did_once = false;

	for (auto it = this->m_pointer_array_ptr.load(std::memory_order_relaxed); it != &(this->m_pointer_array_ptr.load(std::memory_order_relaxed)[this->m_element_count.load(std::memory_order_acquire)]); it += 1)
	{
		if (*it == nullptr)
		{
			if (l_did_once == false)
			{
				l_did_once = true;
				l_progress = it;
			}
			for (; l_progress != &(this->m_pointer_array_ptr.load(std::memory_order_relaxed)[this->m_element_count.load(std::memory_order_acquire)]); l_progress += 1)
			{
				if (*l_progress != nullptr)
				{
					l_buffer = *l_progress;
					*l_progress = nullptr;
					break;
				}
			}
			*it = l_buffer;
			l_buffer = nullptr;
		}
	}

	l_did_once = false;

	for (var::uint64 idx = 0; idx < this->m_element_count.load(); ++idx)
	{
		if (this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx] != nullptr)
		{
			this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx].load(std::memory_order_relaxed)->m_quick_access_ptr.store(&(this->m_pointer_array_ptr.load(std::memory_order_relaxed)[idx]));
		}
	}
	this->m_is_quick_access_ptr_on_update.store(false, std::memory_order_release);

	this->m_lock.unlock();
}

template<typename T, class allocator>
_FORCE_INLINE_ void proxy_table<T, allocator>::shrink_to_fit() noexcept
{
	this->sort();

	if (this->m_lock.try_lock() == false) { return; }

	this->m_is_quick_access_ptr_on_update.store(true, std::memory_order_release);

	var::uint64 l_number_of_valid_elements = 0;

	for (var::uint64 idx = 0; idx < this->m_element_count.load(std::memory_order_relaxed); ++idx)
	{
		if (this->m_pointer_array_ptr.load(std::memory_order_acquire)[idx] != nullptr)
		{
			++l_number_of_valid_elements;
		}
	}

	if (l_number_of_valid_elements == 0) { return; }

	std::atomic<std::atomic<volatile proxy_ptr<T, allocator>*>*> l_ptr = FE::memory::trackable_realloc(	this->m_pointer_array_ptr.load(std::memory_order_relaxed),
																							this->m_array_total_length.load(std::memory_order_relaxed),
																							sizeof(volatile proxy_ptr<T, allocator>*),
																							l_number_of_valid_elements,
																							sizeof(volatile proxy_ptr<T, allocator>*)
																							);
																			
	this->m_pointer_array_ptr = l_ptr.exchange(nullptr);
	this->m_array_total_length.store(l_number_of_valid_elements, std::memory_order_release);
	this->m_element_count.store(l_number_of_valid_elements, std::memory_order_release);

	this->m_is_quick_access_ptr_on_update.store(false, std::memory_order_release);

	this->m_lock.unlock();
}


END_NAMESPACE


#endif
