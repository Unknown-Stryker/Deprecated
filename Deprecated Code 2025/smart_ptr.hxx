#ifndef _FE_FRAMEWORK_SMART_PTR_HXX_
#define _FE_FRAMEWORK_SMART_PTR_HXX_
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
#include <FE/prerequisites.h>

#include <memory_resource>
#include <type_traits>
#include <utility>




BEGIN_NAMESPACE(FE)


struct memblock_metadata
{
    var::int32 observer_count; // Number of observers
    bool is_expired; // Expiration flag
    std::pmr::memory_resource* resource; // Memory resource pointer
};


enum struct RefType
{
    _Owner,
    _Observer
};


template <typename T, RefType Type>
class smart_ptr;


template <typename T>
class smart_ptr<T, RefType::_Owner>
{
    friend class smart_ptr<T, RefType::_Observer>;

    static_assert(std::is_array_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to an array.");
    static_assert(std::is_reference_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a reference type variable.");
    static_assert(std::is_const_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a const type variable.");
    
    /* - memblock view (offsets) -
    * 0 ~ sizeof(T): T object
	* sizeof(T) ~ sizeof(T) + 8: var::int64 observer_count
	* sizeof(T) + 8 ~ sizeof(T) + 16: std::pmr::memory_resource* resource
	* sizeof(T) + 16 ~ sizeof(T) + 17: bool is_expired
    */
    T* m_ptr;
	memblock_metadata* m_metadata;

public:
    smart_ptr() noexcept
        : m_ptr() {}

    template <typename... Arguments>
    smart_ptr(std::pmr::polymorphic_allocator<var::byte> resource_p, Arguments&&... arguments_p) noexcept
        : m_ptr()
    {
        m_ptr = (T*)resource_p.allocate(sizeof(T));
        FE_ASSERT(m_ptr != nullptr);
        new(m_ptr) T( std::forward<Arguments&&>(arguments_p)... );

        m_metadata = (memblock_metadata*)resource_p.allocate(sizeof(memblock_metadata));
        FE_ASSERT(m_metadata != nullptr);
        new(m_metadata) memblock_metadata( 0, false, resource_p.resource() );
    }

    ~smart_ptr() noexcept
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }
        FE_ASSERT(m_metadata != nullptr);

		// Call the destructor of T
        this->m_ptr->~T();

		FE_ASSERT(m_metadata->observer_count >= 0);

		// Nobody is observing this object, so we can safely deallocate it
        if (m_metadata->observer_count == 0)
        {
			// Deallocate the memblock bytes
            std::pmr::polymorphic_allocator<var::byte>{ m_metadata->resource }.deallocate( reinterpret_cast<var::byte*>(m_ptr), );
        }
        else
        {
            *l_expiration_flag = true; // Mark the object as expired, so that it can be deallocated later
        }
    }

    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;

    _FE_FORCE_INLINE_ smart_ptr(smart_ptr&& other_p) noexcept
        : m_ptr(other_p.m_ptr)
    {
        other_p.m_ptr = nullptr;
    }

    template <class Child>
    _FE_FORCE_INLINE_ smart_ptr(smart_ptr<Child, FE::RefType::_Owner>&& other_p) noexcept
        :   m_ptr( reinterpret_cast< std::remove_pointer_t<decltype(this)>&& >(other_p).m_ptr ),
            m_memblock_size(reinterpret_cast<std::remove_pointer_t<decltype(this)>&&>(other_p).m_memblock_size)
    {
        static_assert(std::is_base_of_v<T, Child>, "Static assertion failed: Child must be derived from T.");

        std::memset(&other_p, 0, sizeof(other_p));
    }

    _FE_FORCE_INLINE_ smart_ptr& operator=(smart_ptr&& other_p) noexcept
    {
        this->reset();
        this->m_ptr = other_p.m_ptr;
        other_p.m_ptr = nullptr;
        return *this;
    }

    template <class Child>
    _FE_FORCE_INLINE_ smart_ptr& operator=(smart_ptr<Child, FE::RefType::_Owner>&& other_p) noexcept
    {
		static_assert(std::is_base_of_v<T, Child>, "Static assertion failed: Child must be derived from T.");

        this->reset();
        this->m_ptr = reinterpret_cast<std::remove_pointer_t<decltype(this)>&&>(other_p).m_ptr;
        this->m_memblock_size = reinterpret_cast<std::remove_pointer_t<decltype(this)>&&>(other_p).m_memblock_size;
        std::memset(&other_p, 0, sizeof(other_p));
        return *this;
    }

    void reset() noexcept
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Call the destructor of T
        this->m_ptr->~T();

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));

        FE_ASSERT(*l_observer_count >= 0);

        // Retrieve a pointer to the memory resource pointer
        std::pmr::memory_resource** l_ptr_to_resource_ptr = reinterpret_cast<std::pmr::memory_resource**>(reinterpret_cast<var::byte*>(l_observer_count) + sizeof(var::int64));

        // Retrieve the expiration flag
        bool* l_expiration_flag = reinterpret_cast<bool*>(reinterpret_cast<var::byte*>(m_ptr) + m_memblock_size - 1);

        // Nobody is observing this object, so we can safely deallocate it
        if (*l_observer_count == 0)
        {
            // Destruct the observer count variable
            //l_observer_count->~var::int64();
            // Destruct the memory resource pointer
            // l_resource->~std::pmr::memory_resource*(); // MSVC won't compile.
            //l_expiration_flag->~bool();

            // Deallocate the memblock bytes
            std::pmr::polymorphic_allocator<var::byte>{ *l_ptr_to_resource_ptr }.deallocate(reinterpret_cast<var::byte*>(m_ptr), m_memblock_size);
        }
        else
        {
            *l_expiration_flag = true; // Mark the object as expired, so that it can be deallocated later
        }
        this->m_ptr = nullptr;
    }

    _FE_FORCE_INLINE_ void swap(smart_ptr& other_p) noexcept
    {
        std::swap(this->m_ptr, other_p.m_ptr);
    }

    _FE_FORCE_INLINE_ T* operator->() noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return m_ptr;
    }

    _FE_FORCE_INLINE_ const T* operator->() const noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return m_ptr;
    }

    _FE_FORCE_INLINE_ T& operator*() noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return *m_ptr;
    }

    _FE_FORCE_INLINE_ const T& operator*() const noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return *m_ptr;
    }
    
	_FE_FORCE_INLINE_ FE::boolean is_null() const noexcept
	{
		return (this->m_ptr == nullptr);
	}
};

template <typename T>
class smart_ptr<T, RefType::_Observer>
{
	static_assert(std::is_array_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to an array.");
    static_assert(std::is_reference_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a reference type variable.");
    static_assert(std::is_const_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a const type variable.");

    T* m_ptr;

public:
    _FE_FORCE_INLINE_ smart_ptr() noexcept
		: m_ptr() {}

    smart_ptr(const smart_ptr<T, RefType::_Owner>& target_p) noexcept
        : m_ptr(target_p.m_ptr)
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
		++(*l_observer_count); // Increment the observer count
    }

    template<class Polymorphic>
    smart_ptr(const smart_ptr<Polymorphic, RefType::_Owner>& target_p) noexcept
        : m_ptr(reinterpret_cast<const smart_ptr<T, RefType::_Owner>&>(target_p).m_ptr)
    {
        static_assert(std::is_base_of_v<T, Polymorphic> || std::is_base_of_v<Polymorphic, T>, "Static assertion failed: the template argument Polymorphic is not polymorphic.");
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        ++(*l_observer_count); // Increment the observer count
    }

    smart_ptr& operator=(const smart_ptr<T, RefType::_Owner>& target_p) noexcept
    {
        this->m_ptr = target_p.m_ptr;

        if (this->m_ptr == nullptr)
        {
            return *this;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        ++(*l_observer_count); // Increment the observer count
        return *this;
    }

    template<class Polymorphic>
    smart_ptr& operator=(const smart_ptr<Polymorphic, RefType::_Owner>& target_p) noexcept
    {
        this->m_ptr = target_p.m_ptr;

        if (this->m_ptr == nullptr)
        {
            return *this;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        ++(*l_observer_count); // Increment the observer count
        return *this;
    }

    ~smart_ptr() noexcept
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        --(*l_observer_count); // Decrement the observer count
        FE_ASSERT(*l_observer_count >= 0);

        // Retrieve a pointer to the memory resource pointer
        std::pmr::memory_resource** l_ptr_to_resource_ptr = reinterpret_cast<std::pmr::memory_resource**>(reinterpret_cast<var::byte*>(l_observer_count) + sizeof(var::int64));

        // Retrieve the expiration flag
        bool* l_expiration_flag = reinterpret_cast<bool*>(reinterpret_cast<var::byte*>(m_ptr) + smart_ptr<T, RefType::_Owner>::memblock_size - 1);

        if ((*l_expiration_flag) == true)
        {
            // Nobody is observing this object, so we can safely deallocate it
            if (*l_observer_count == 0)
            {
                // Call the destructor of T
                this->m_ptr->~T();

                // Destruct the observer count variable
                //l_observer_count->~var::int64();
                // Destruct the memory resource pointer
                // l_resource->~std::pmr::memory_resource*(); // MSVC won't compile.
                //l_expiration_flag->~bool();

                // Deallocate the memblock bytes
                std::pmr::polymorphic_allocator<var::byte>{ *l_ptr_to_resource_ptr }.deallocate(reinterpret_cast<var::byte*>(m_ptr), smart_ptr<T, RefType::_Owner>::memblock_size);
            }
        }
    }

    _FE_FORCE_INLINE_ smart_ptr(const smart_ptr& other_p) noexcept
        : m_ptr(other_p.m_ptr)
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        ++(*l_observer_count); // Increment the observer count
    }

    _FE_FORCE_INLINE_ smart_ptr& operator=(const smart_ptr& other_p) noexcept
    {
        this->m_ptr = other_p.m_ptr;

        if (this->m_ptr == nullptr)
        {
            return *this;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        ++(*l_observer_count); // Increment the observer count
        return *this;
    }

    _FE_FORCE_INLINE_ smart_ptr(smart_ptr&& other_p) noexcept
        : m_ptr(other_p.m_ptr)
    {
        other_p.m_ptr = nullptr;
    }

    _FE_FORCE_INLINE_ smart_ptr& operator=(smart_ptr&& other_p) noexcept
    {
        this->m_ptr = other_p.m_ptr;
        other_p.m_ptr = nullptr;
        return *this;
    }

    void reset() noexcept
    {
        if (this->m_ptr == nullptr)
        {
            return;
        }

        // Retrieve the observer count variable
        var::int64* l_observer_count = reinterpret_cast<var::int64*>(reinterpret_cast<var::byte*>(m_ptr) + sizeof(T));
        --(*l_observer_count); // Decrement the observer count
        FE_ASSERT(*l_observer_count >= 0);

        // Retrieve a pointer to the memory resource pointer
        std::pmr::memory_resource** l_ptr_to_resource_ptr = reinterpret_cast<std::pmr::memory_resource**>(reinterpret_cast<var::byte*>(l_observer_count) + sizeof(var::int64));

        // Retrieve the expiration flag
        bool* l_expiration_flag = reinterpret_cast<bool*>(reinterpret_cast<var::byte*>(m_ptr) + smart_ptr<T, RefType::_Owner>::memblock_size - 1);

        if ((*l_expiration_flag) == true)
        {
            // Nobody is observing this object, so we can safely deallocate it
            if (*l_observer_count == 0)
            {
                // Call the destructor of T
                this->m_ptr->~T();

                // Destruct the observer count variable
                //l_observer_count->~var::int64();
                // Destruct the memory resource pointer
                // l_resource->~std::pmr::memory_resource*(); // MSVC won't compile.
                //l_expiration_flag->~bool();

                // Deallocate the memblock bytes
                std::pmr::polymorphic_allocator<var::byte>{ *l_ptr_to_resource_ptr }.deallocate(reinterpret_cast<var::byte*>(m_ptr), smart_ptr<T, RefType::_Owner>::memblock_size);
            }
        }
        this->m_ptr = nullptr;
    }

    _FE_FORCE_INLINE_ void swap(smart_ptr& other_p) noexcept
    {
        std::swap(this->m_ptr, other_p.m_ptr);
    }

    _FE_FORCE_INLINE_ T* operator->() noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return m_ptr;
    }

    _FE_FORCE_INLINE_ const T* operator->() const noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return m_ptr;
    }

    _FE_FORCE_INLINE_ T& operator*() noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return *m_ptr;
    }

    _FE_FORCE_INLINE_ const T& operator*() const noexcept
    {
        FE_ASSERT(m_ptr != nullptr);
        return *m_ptr;
    }

    _FE_FORCE_INLINE_ FE::boolean is_expired() const noexcept
    {
        // Retrieve the expiration flag
        bool* l_expiration_flag = reinterpret_cast<bool*>(reinterpret_cast<var::byte*>(m_ptr) + smart_ptr<T, RefType::_Owner>::memblock_size - 1);
        return ((this->m_ptr == nullptr) || (*l_expiration_flag == true));
    }
};

template <typename T, typename... Arguments>
_FE_FORCE_INLINE_ smart_ptr<std::remove_all_extents_t<T>, RefType::_Owner> gcnew(std::pmr::memory_resource* resource_p = std::pmr::get_default_resource(), Arguments&&... arguments_p) noexcept
{
    static_assert(std::is_reference_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a reference type variable.");
    static_assert(std::is_const_v<T> == false, "Static assertion failed: smart_ptr cannot hold a pointer to a const type variable.");
    return smart_ptr<std::remove_all_extents_t<T>, RefType::_Owner>(resource_p, std::forward<Arguments>(arguments_p)...);
}


END_NAMESPACE
#endif
