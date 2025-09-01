#include <FE/miscellaneous/configuration.h>
#include <FE/miscellaneous/undefine_max_min.h>


#include <FE/miscellaneous/define_max_min.h>
#include <vector>
#include <list>
#include <deque>
#include <FE/core/runtime_exception.hpp>
#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/heap_utilization.hpp>
#include <FE/core/allocator_adaptors.hxx>
#include <FE/core/function.hxx>

#include <FE/core/thread.hpp>
#include <FE/core/private/launch.hpp>
#include <FE/miscellaneous/private/macro_restrictions.h>
#include <iostream>


int main(void) noexcept
{

    {
        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        std::vector<std::string, FE::standard_c_style_allocator<std::string>> l_vector;

        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        std::list<std::string, FE::standard_c_style_allocator<std::string>> l_list;

        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        std::deque<std::string, FE::standard_c_style_allocator<std::string>> l_deque;

        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        l_vector.reserve(10);
        l_vector.emplace_back("adaptor");

        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        l_list.emplace_back("hi");

        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
        l_deque.emplace_back("allocator");


        std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;
    }

    std::cout << FE::heap_utilization<std::string>::query_all_data()._thread_local_total_bytes << std::endl;


    return 0;
}