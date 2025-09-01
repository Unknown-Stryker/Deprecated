//#ifndef _FE_CORE_SHARED_REF_HXX_
//#define _FE_CORE_SHARED_REF_HXX_
//// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
//#include <FE/core/prerequisites.h>
//
//
//
//
//BEGIN_NAMESPACE(FE::concurrency)
//
//
//template<typename T, class Alignment>
//class memory_block;
//
//
//template<typename T, class Alignment>
//struct control_block
//{
//	std::atomic<var::uint32> _ref_count = 0;
//	std::atomic_bool _is_being_used = false;
//	
//	FE::ref<T> _memory_block;
//};
//
//
//template <typename T, class Alignment = FE::align_CPU_L1_cache_line>
//class shared_ref final
//{
//	std::atomic<var::index_t> m_shared_key;
//
//	using memory_block_type = memory_block<T, Alignment>;
//
//public:
//	using value_type = T;
//	using pointer = value_type*;
//	using const_pointer = const pointer;
//	using reference = value_type&;
//	using const_reference = const reference;
//
//	_FORCE_INLINE_ shared_ref() noexcept : m_shared_key(memory_block_type::s_index_map::invalid_key_value) {}
//	
//	_FORCE_INLINE_ shared_ref(index_t shared_key_p) noexcept : m_shared_key(shared_key_p) 
//	{
//		if (this->m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value) { return; }
//
//		memory_block_type::s_index_map.find(this->m_shared_key.load())._ref_count.fetch_add(1);
//	}
//
//	_FORCE_INLINE_ ~shared_ref() noexcept
//	{
//		if (this->m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value) { return; }
//
//		control_block& l_value = memory_block_type::s_index_map.find(this->m_shared_key.load());
//		
//		l_value._ref_count.fetch_sub(1);
//
//		if (l_value._ref_count.load() == 0)
//		{
//			l_value._is_being_used.store(false);
//		}
//	}
//
//	_FORCE_INLINE_ shared_ref(const shared_ref& other_p) noexcept : m_shared_key(other_p.m_shared_key)
//	{
//		if (this->m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value) { return; }
//
//		memory_block_type::s_index_map.find(this->m_shared_key.load())._ref_count.fetch_add(1);
//	}
//
//	_FORCE_INLINE_ shared_ref(shared_ref&& rvalue_p) noexcept : m_shared_key(rvalue_p.m_shared_key.exchange(memory_block_type::s_index_map::invalid_key_value)) {}
//
//
//	_FORCE_INLINE_ shared_ref& operator=(const shared_ref& other_p) noexcept
//	{
//		if (other_p.m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value) { return; }
//		
//		this->m_shared_key.store(other_p.m_shared_key.load());
//
//		memory_block_type::s_index_map.find(this->m_shared_key.load())._ref_count.fetch_add(1);
//		return *this;
//	}
//
//	_FORCE_INLINE_ shared_ref& operator=(shared_ref&& rvalue_p) noexcept
//	{
//		this->m_shared_key = rvalue_p.m_shared_key.exchange(memory_block_type::s_index_map::invalid_key_value);
//		return *this;
//	}
//
//
//	_FORCE_INLINE_ boolean is_being_used() const noexcept
//	{
//		FE_ASSERT((this->m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value), "Error, the key value of a shared_ref instance is invalid.");
//		return memory_block_type::s_index_map.find(this->m_shared_key.load())._is_being_used.load();
//	}
//
//	_FORCE_INLINE_ void stop_using() noexcept
//	{
//		this->~shared_ref();
//	}
//
//	_FORCE_INLINE_  T* operator->() const noexcept
//	{
//		FE_ASSERT((this->m_shared_key.load() == memory_block_type::s_index_map::invalid_key_value), "Error, the key value of a shared_ref instance is invalid.");
//		return memory_block_type::s_index_map.find(this->m_shared_key.load())._memory_block.get();
//	}
//};
//
//
//END_NAMESPACE
//
//#endif
