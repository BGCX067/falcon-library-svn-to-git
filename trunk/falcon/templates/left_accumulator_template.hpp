#ifndef _FALCON_TEMPLATES_LEFT_ACCUMULATOR_TEMPLATE_HPP
#define _FALCON_TEMPLATES_LEFT_ACCUMULATOR_TEMPLATE_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/typeof/typeof.hpp>
#endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<template<class...> class _Temp, typename... _LeftArgs>
	struct template_left_accumulator
	{
		template<typename... _Args>
		struct value_wrapper
		{
			static const decltype(_Temp<_LeftArgs..., _Args...>::value) value = _Temp<_LeftArgs..., _Args...>::value;
		};

		template<typename... _Args>
		struct type_wrapper
		{
			typedef typename _Temp<_LeftArgs..., _Args...>::type type;
		};
	};
#else
	template<template<class, class> class _Template, typename _LeftArg>
	struct template_left_accumulator
	{
		template<typename _T>
		class value_wrapper
		{
			static const BOOST_TYPEOF((_Template<_LeftArg, _T>::value)) value = _Template<_LeftArg, _T>::value;
		};

		template<typename _T>
		struct type_wrapper
		{
			typedef typename _Template<_LeftArg, _T>::type type;
		};
	};
#endif

}

#endif