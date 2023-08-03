template<class container, typename T>
_FORCE_INLINE_ void push_target_values_to_back(container& container_in_out_ref_p, const T& target_value_cref_p) noexcept
{
	auto l_begin_of_container = container_in_out_ref_p.begin();
	auto l_end_of_container = container_in_out_ref_p.end();
	--l_end_of_container;

	while (l_begin_of_container < l_end_of_container)
	{
		if (*l_end_of_container == target_value_cref_p)
		{
			--l_end_of_container;
			continue;
		}

		if (*l_begin_of_container != target_value_cref_p)
		{
			++l_begin_of_container;
			continue;
		}

		if (*l_begin_of_container == target_value_cref_p)
		{
			utility::swap<T>(*l_begin_of_container, *l_end_of_container);
		}
	}
}


template<class container, typename T>
_FORCE_INLINE_ void push_target_values_to_front(container& container_in_out_ref_p, const T& target_value_cref_p) noexcept
{
	auto l_begin_of_container = container_in_out_ref_p.begin();
	auto l_end_of_container = container_in_out_ref_p.end();
	--l_end_of_container;

	while (l_begin_of_container < l_end_of_container)
	{
		if (*l_end_of_container != target_value_cref_p)
		{
			--l_end_of_container;
			continue;
		}

		if (*l_begin_of_container == target_value_cref_p)
		{
			++l_begin_of_container;
			continue;
		}

		if (*l_end_of_container == target_value_cref_p)
		{
			utility::swap<T>(*l_begin_of_container, *l_end_of_container);
		}
	}
}
