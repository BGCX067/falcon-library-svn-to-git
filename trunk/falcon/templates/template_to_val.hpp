#ifndef _FALCON_TEMPLATES_TEMPLATE_TO_VAL_HPP
#define _FALCON_TEMPLATES_TEMPLATE_TO_VAL_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/typeof/typeof.hpp>
#endif

namespace falcon {
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template <template<class...> class _Temp>
	struct template_to_val
	{
		template<typename... _Args>
		struct filter
		{
			static const decltype(_Temp<_Args...>::value) value = _Temp<_Args...>::value;
		};
	};
#else
	template <template<class> class _Temp>
	struct template_to_val
	{
		template<typename _T>
		class filter
		{
			static const BOOST_TYPEOF(_Temp<_T>::value) value = _Temp<_T>::value;
		};
	};
#endif
}

#endif