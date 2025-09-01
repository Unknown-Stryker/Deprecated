    template <typename char_type, typename U = null_template_argument, typename ...arguments>
    void format_string_recursive(char_type* return_buffer_ptr_p, const char_type* string_format_ptr_p, U first_p = null_template_argument{}, arguments&&... arguments_p)
    {
        enum FORMAT_SPECIFIER_TABLE_INDEX
        {
            _BINARY = 98, _CHARACTER = 99,
            _SIGNED_INTEGER = 100, _UNSIGNED_INTEGER = 117,
            _FLOAT = 102, _HEXADECIMAL_ADDRESS = 112,
            _STRING = 115, _OBJECT = 111
        };

        FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, (internal::strlen(string_format_ptr_p) * sizeof(char_type)) > _512_BYTES_BIT_COUNT_, is_return_buffer_insufficient);
        FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, return_buffer_ptr_p == nullptr, is_return_buffer_nullptr);
        FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, string_format_ptr_p == nullptr, is_string_format_nullptr);

        constexpr static auto _FORMAT_SPECIFIER_LENGTH_ = 4;

        const char_type* l_string_format_begin_ptr = string_format_ptr_p;

        
        if (*string_format_ptr_p == _NULL_) _UNLIKELY_
        {
            return;
        }

        while ((*string_format_ptr_p != '{') && (*string_format_ptr_p != '%') && (*string_format_ptr_p != '}'))
        {
            ++string_format_ptr_p;
            if ((*string_format_ptr_p == '\0'))
            {
                break;
            }
        }

        int64 l_preface_text_bytes_to_copy = (string_format_ptr_p - l_string_format_begin_ptr) * sizeof(char_type);
        if (l_preface_text_bytes_to_copy)
        {
            std::memcpy(return_buffer_ptr_p, l_string_format_begin_ptr, l_preface_text_bytes_to_copy);
            std::cout << l_preface_text_bytes_to_copy << "\n";
            return_buffer_ptr_p += l_preface_text_bytes_to_copy;
        }

        //while ((*string_format_ptr_p == '{') && (string_format_ptr_p[1] != '%') && (*string_format_ptr_p != '\0'))
        //{
        //    ++string_format_ptr_p;
        //}
   
        if (*string_format_ptr_p == '{'/* && (string_format_ptr_p[1] == '%')*/)
        {
            ++string_format_ptr_p;
            if (*string_format_ptr_p == '%' && string_format_ptr_p[2] == '}')
            {
                switch (string_format_ptr_p[1])
                {
                case _BINARY:
                    _FALLTHROUGH_;
                case _CHARACTER:
                    _FALLTHROUGH_;
                case _SIGNED_INTEGER:
                    _FALLTHROUGH_;
                case _UNSIGNED_INTEGER:
                    _FALLTHROUGH_;
                case _FLOAT:
                    _FALLTHROUGH_;
                case _HEXADECIMAL_ADDRESS:
                    _FALLTHROUGH_;
                case _STRING:
                    _FALLTHROUGH_;
                case _OBJECT:
                {
                    const char_type* l_result_ptrc = FE::algorithm::string::any_to_string<char_type, U>(first_p);
                    int64 l_data_bytes_to_copy = internal::strlen(l_result_ptrc) * sizeof(char_type);
                    std::memcpy(return_buffer_ptr_p, l_result_ptrc, l_data_bytes_to_copy);

                    return_buffer_ptr_p += l_data_bytes_to_copy;

                    while ((*l_string_format_begin_ptr != '{') && (*l_string_format_begin_ptr != '}'))
                    {
                        ++l_string_format_begin_ptr;
                        if (*l_string_format_begin_ptr == '\0') _UNLIKELY_
                        {
                            break;
                        }
                    }
                    string_format_ptr_p += _FORMAT_SPECIFIER_LENGTH_;
                    l_string_format_begin_ptr += _FORMAT_SPECIFIER_LENGTH_;
                }
                    break;
                   
                default:
                    break;
                }
            }
        }

        var::int64 l_appendix_text_bytes_to_copy = ((string_format_ptr_p - l_string_format_begin_ptr) * sizeof(char_type));
        if (l_appendix_text_bytes_to_copy)
        {
            l_appendix_text_bytes_to_copy = ABS(l_appendix_text_bytes_to_copy - l_preface_text_bytes_to_copy);
            std::memcpy(return_buffer_ptr_p, l_string_format_begin_ptr, l_appendix_text_bytes_to_copy);
            std::cout << l_appendix_text_bytes_to_copy << "\n";
            return_buffer_ptr_p += l_appendix_text_bytes_to_copy;
        }
        format_string_recursive(return_buffer_ptr_p, string_format_ptr_p, first_p);
    }
