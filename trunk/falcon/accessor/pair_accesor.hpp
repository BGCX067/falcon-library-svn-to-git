#ifndef _FALCON_ACCESSOR_PAIR_ACCESOR_HPP
#define _FALCON_ACCESSOR_PAIR_ACCESOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _PairT>
struct first_accessor
{
	typedef _PairT pair_type;
	typedef typename pair_type::first_type value_type;

	value_type& operator()(pair_type& pair) const
	{
		return pair.first;
	}

	CPP_USE_CONSTEXPR value_type& operator()(const pair_type& pair) const
	{
		return pair.first;
	}
};

template <typename _PairT>
struct second_accessor
{
	typedef _PairT pair_type;
	typedef typename pair_type::second_type value_type;

	value_type& operator()(pair_type& pair) const
	{
		return pair.second;
	}

	CPP_USE_CONSTEXPR value_type& operator()(const pair_type& pair) const
	{
		return pair.second;
	}
};

}

#endif