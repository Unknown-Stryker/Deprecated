#ifndef _FE_CORE_ALGORITHM_SEARCH_HXX_
#define _FE_CORE_ALGORITHM_SEARCH_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../types.h"
#include <optional>


BEGIN_NAMESPACE(FE::algorithm::search)


template<typename T, class iterator>
_FORCE_INLINE_ std::optional<T> linear_search(iterator& begin_iterator_ref_p, iterator& end_iterator_ref_p, const T& target_cref_p) noexcept
{
	while (begin_iterator_ref_p != end_iterator_ref_p)
	{
		if (*begin_iterator_ref_p == target_cref_p)
		{
			return target_cref_p;
		}
		++begin_iterator_ref_p;
	}

	return std::nullopt;
}


template<class contiguous_container, typename T>
_FORCE_INLINE_ std::optional<T> binary_search(const contiguous_container& container_cref_p, const T& target_cref_p) noexcept
{
	var::int64 l_low = 0;
	var::int64 l_high = container_cref_p.size() - 1;

	var::int64 l_mid = l_low + ((l_high - l_low) / 2);

	T l_mid_buffer = std::move(container_cref_p[l_mid]);

	if (l_mid_buffer == target_cref_p) { return l_mid_buffer; }


	while (l_low <= l_high)
	{
		if (l_mid_buffer < target_cref_p)
		{
			l_low = l_mid + 1;
		}
		else
		{
			l_high = l_mid - 1;
		}

		l_mid = l_low + ((l_high - l_low) / 2);

		l_mid_buffer = std::move(container_cref_p[l_mid]);

		if (l_mid_buffer == target_cref_p)
		{
			return l_mid_buffer;
		}
	}

	return std::nullopt;
}


END_NAMESPACE
#endif
