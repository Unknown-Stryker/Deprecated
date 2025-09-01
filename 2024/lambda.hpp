
#include <memory>
#include <iostream>
#include <cstddef>


template <typename ReturnType = void, typename... Arguments>
class lambda;

template <typename ReturnType, typename... Arguments>
class lambda<ReturnType (Arguments...)>
{
    class __impl_base 
    {
    public:
        virtual ~__impl_base() noexcept = default;

        virtual inline void __copy_construct(__impl_base* const dest_p, const __impl_base* const source_p)  noexcept = 0;
        virtual inline ReturnType __invoke(Arguments&&... arguments_p) noexcept = 0;
    };

    template <typename Callable>
    class __impl : __impl_base 
    {
        Callable m_task;
    public:
        __impl(Callable&& task_p) noexcept 
            : m_task( std::forward<Callable>(task_p) ) {}

        virtual inline void __copy_construct(__impl_base* const dest_p, const __impl_base* const source_p)  noexcept override
       {
           const __impl* const l_source = static_cast<const __impl* const>(source_p);
           __impl* const l_dest = static_cast<__impl* const>(dest_p);
           new(l_dest) __impl(*l_source);
       }

        virtual inline ReturnType __invoke(Arguments&&... arguments_p) noexcept override 
        { 
            if constexpr (std::is_same<ReturnType, void>::value == true)
            {
                this->m_task( std::forward<Arguments>(arguments_p)... ); 
            }
            else if constexpr (std::is_same<ReturnType, void>::value == false)
            {
                return this->m_task( std::forward<Arguments>(arguments_p)... );
            }
        }
    };

    std::uint8_t m_memory[23];
    bool m_is_valid;
    __impl_base* m_impl;

public:
    lambda() noexcept
        : m_memory{}, m_is_valid(false), m_impl( reinterpret_cast<__impl_base*>(m_memory) ) {}

    ~lambda() noexcept
    {
        if(this->m_is_valid == true)
        {
            this->m_impl->~__impl_base();
        }
    }

    lambda(const lambda& other_p) noexcept
        : m_memory{}, m_is_valid(true), m_impl( reinterpret_cast<__impl_base*>(m_memory) ) 
    {
        other_p.__copy_construct(this->m_impl, other_p.m_impl);
    }

    lambda& operator=(const lambda& other_p) noexcept
    {
        if(this->m_is_valid == true)
        {
            this->m_impl->~__impl_base();
        }
        other_p.__copy_construct(this->m_impl, other_p.m_impl);
        this->m_is_valid = true;
    }


    template <typename Callable>
    lambda(Callable&& task_p) noexcept 
        : m_memory{}, m_is_valid(true), m_impl( reinterpret_cast<__impl_base*>(m_memory) ) 
    {
        static_assert(sizeof(m_memory) > sizeof(__impl<Callable>), "Static Assertion failed: the memory for the lambda object is insufficient.");
        new(this->m_impl) __impl<Callable>( std::forward<Callable>(task_p) );
    }


    template <typename Callable>
    lambda& operator=(Callable&& task_p) noexcept
    {
        static_assert(sizeof(m_memory) > sizeof(__impl<Callable>), "Static Assertion failed: the memory for the lambda object is insufficient.");
        if(this->m_is_valid == true)
        {
            this->m_impl->~__impl_base();
        }
        new(this->m_impl) __impl<Callable>( std::forward<Callable>(task_p) );
    }

    
    inline ReturnType operator()(Arguments&&... arguments_p) noexcept 
    {
        assert((this->m_impl != nullptr));
        if constexpr (std::is_same<ReturnType, void>::value == true)
        {
            this->m_impl->__invoke( std::forward<Arguments>(arguments_p)... ); 
        }
        else if constexpr (std::is_same<ReturnType, void>::value == false)
        {
            return this->m_impl->__invoke( std::forward<Arguments>(arguments_p)... );
        }
    }


    lambda(lambda&&) noexcept = delete;
    lambda& operator=(lambda&&) noexcept = delete;
};
