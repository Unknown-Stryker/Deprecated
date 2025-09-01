// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include "../runtime_exception.hpp"

#include "../algorithm/string.hxx"
#include "../fstring.hxx"
#include "../thread.hpp"
#include "../clock.hpp"

#include <cwchar>
#include <fstream>
#include <filesystem>


constexpr auto _FILE_NAME_MAX_LENGTH_ = 8000;
constexpr auto _MAX_THRED_ID_DIGIT_LENGTH_ = 24;


thread_local ::std::ofstream FE::exception::tl_s_exception_reporter;

thread_local ::FE::clock FE::exception::tl_s_clock;

thread_local ::std::unique_ptr<FE::exception::char_type[]> FE::exception::tl_s_source_code_line_info_buffer(new FE::exception::char_type[_LINE_INFO_BUFFER_SIZE_] {(FE::exception::char_type)'\0'});

thread_local ::std::unique_ptr<FE::exception::char_type[]> FE::exception::tl_s_full_debug_info_buffer(new FE::exception::char_type[_FULL_DEBUG_INFO_BUFFER_SIZE_] {(FE::exception::char_type)'\0'});


void FE::exception::__construct_exception_on_main_thread() noexcept
{
    ::std::filesystem::path l_directory_name = ::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs\0";
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }
#if _WINDOWS_64BIT_OS_ == 1
    ::FE::fwstring<_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_> l_date_info_wstring; 
    ::std::mbstowcs(l_date_info_wstring.begin(), exception::tl_s_clock.get_current_local_time(), _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);

    if (::FE::algorithm::string::strlen((::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs\\thread \0").c_str()) >= _FILE_NAME_MAX_LENGTH_ - _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_) { ::abort(); }
    
    ::FE::fwstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs\\thread \0").c_str();
    
    ::FE::algorithm::string::concatenate_strings<::FE::fwstring<_FILE_NAME_MAX_LENGTH_>::value_type>
    (
        l_exception_history_file_name.begin(),
        _FILE_NAME_MAX_LENGTH_, 
        {
            L"main() @ ",
            l_date_info_wstring.c_str(),
            L".txt" 
        }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#elif _LINUX_64BIT_OS_ == 1
    if (::FE::algorithm::string::strlen((::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs/thread \0").c_str()) >= _FILE_NAME_MAX_LENGTH_ - _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_) { ::abort(); }

    ::FE::fstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs/thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fstring<_FILE_NAME_MAX_LENGTH_>::value_type>
    (
        l_exception_history_file_name.begin(),
        _FILE_NAME_MAX_LENGTH_, 
        {
            "main() @ ",
            exception::tl_s_clock.get_current_local_time(),
            ".txt" 
        }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#endif
}

void FE::exception::__destruct_exception() noexcept // It needs some adjustments to ensure the function invocation.
{
    if (exception::tl_s_exception_reporter.is_open() == true)
    {
        exception::tl_s_exception_reporter << "\n}\n[END OF HISTORY]";

        exception::tl_s_exception_reporter.close();
    }
}


void FE::exception::__construct_exception(::FE::thread& thread_ref_p) noexcept
{
    ::std::filesystem::path l_directory_name = ::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs\0";
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }
#if _WINDOWS_64BIT_OS_ == 1
    ::FE::fwstring<_MAX_THRED_ID_DIGIT_LENGTH_> l_thread_id;
    ::swprintf(l_thread_id.begin(), _MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", thread_ref_p.get_id()); // hashed thread-ids from std::hash are too long and hard to read 
    
    ::FE::fwstring<_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_> l_date_info_wstring;
    ::std::mbstowcs(l_date_info_wstring.begin(), exception::tl_s_clock.get_current_local_time(), _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
    
    ::FE::fwstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs\\thread \0").c_str();
   
    ::FE::algorithm::string::concatenate_strings<::FE::fwstring<_FILE_NAME_MAX_LENGTH_>::value_type>
    (
        l_exception_history_file_name.begin(),
        _FILE_NAME_MAX_LENGTH_, 
        { 
            l_thread_id.c_str(), 
            L" @ ", 
            l_date_info_wstring.c_str(),
            L".txt" 
        }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#elif _LINUX_64BIT_OS_ == 1
    ::FE::fstring<_MAX_THRED_ID_DIGIT_LENGTH_> l_thread_id;
    snprintf(l_thread_id.begin(), _MAX_THRED_ID_DIGIT_LENGTH_, "%llu", thread_ref_p.get_id());

    ::FE::fstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-API-Exception-History-Logs/thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fstring<_FILE_NAME_MAX_LENGTH_>::value_type>
        (
            l_exception_history_file_name.begin(),
            _FILE_NAME_MAX_LENGTH_,
            {
                l_thread_id.c_str(),
                " @ ",
                exception::tl_s_clock.get_current_local_time(),
                ".txt"
            }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#endif
}


bool FE::exception::handle_exceptions(const bool expression_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept
{
    switch ( static_cast<int>(expression_p) )
    {
    case 0:
        return false;
    default:
        break;
    }


    ::snprintf(exception::tl_s_source_code_line_info_buffer.get(), _LINE_INFO_BUFFER_SIZE_, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<char>
    (
        exception::tl_s_full_debug_info_buffer.get(), 
        _FULL_DEBUG_INFO_BUFFER_SIZE_, 
        { 
            "time: ", exception::tl_s_clock.get_current_local_time(), "\n", 
            "error message: ", message_ptr_p, "\n", 
            "file directory: ", file_name_ptr_p, "\n",
            "function: ", function_name_ptr_p, "\n",
            "line: ", exception::tl_s_source_code_line_info_buffer.get()
        }
    );


    switch (runtime_exception_mode_p)
    {
    case _LOG_EXCEPTION_HISTORY_: // store exception logs in a global container and write  exception history file right before the unsafe_end of the application.  
        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);
    break;


    case _ABORT_IMMEDIATELY_:
        FE::algorithm::string::strcat<char>( exception::tl_s_full_debug_info_buffer.get(), _FULL_DEBUG_INFO_BUFFER_SIZE_, "\nabort() HAS BEEN CALLED.", ::FE::algorithm::string::strlen("\tabort() HAS BEEN CALLED.") );
        
        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);

        ::abort(); // aborts the entire processes of the application.


    case _EXIT_WITH_CODE_:
        // store exit code
        ::snprintf(exception::tl_s_source_code_line_info_buffer.get(), _LINE_INFO_BUFFER_SIZE_, "%d", exit_code_p);

        ::FE::algorithm::string::concatenate_strings<char>
        (
            exception::tl_s_full_debug_info_buffer.get(),
            _FULL_DEBUG_INFO_BUFFER_SIZE_,
            {
                "\nexit() HAS BEEN CALLED with exit code: ", exception::tl_s_source_code_line_info_buffer.get()
            }
        );

        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);

        ::exit(exit_code_p);
    }

    return true;
}