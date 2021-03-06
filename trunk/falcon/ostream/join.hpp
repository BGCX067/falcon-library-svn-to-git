#ifndef _FALCON_OSTREAM_JOIN_HPP
#define _FALCON_OSTREAM_JOIN_HPP

#include <iosfwd>
#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/is_ios.hpp>
#include <falcon/type_traits/enable_if.hpp>

namespace falcon {

namespace ostream {

template<typename _CharT, typename _Traits, typename _ForwardIterator>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, _ForwardIterator first, _ForwardIterator last, const _CharT* glue, std::streamsize n)
{
	if (first == last)
		return os;
	const std::streamsize w = os.width();
	os << *first;
	if (w)
	{
		while (++first != last)
		{
			os.write(glue, n).width(w);
			os << *first;
		}
	}
	else
	{
		while (++first != last)
			os.write(glue, n) << *first;
	}
	return os;
}

template<typename _CharT, typename _Traits, typename _ForwardIterator>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, _ForwardIterator first, _ForwardIterator last, const _CharT* glue)
{
	return join(os, first, last, glue, static_cast<std::streamsize>(_Traits::length(glue)));
}

template<typename _CharT, typename _Traits, typename _ForwardIterator>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, _ForwardIterator first, _ForwardIterator last, _CharT glue = ',')
{
	return join(os, first, last, &glue, 1);
}

template<typename _CharT, typename _Traits, typename _Container>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, const _Container& container, const _CharT* glue)
{
	return join<>(os, begin(container), end(container), glue, static_cast<std::streamsize>(_Traits::length(glue)));
}

template<typename _CharT, typename _Traits, typename _Container>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, const _Container& container, const _CharT* glue, std::streamsize size)
{
	return join<>(os, begin(container), end(container), glue, size);
}

template<typename _CharT, typename _Traits, typename _Container>
std::basic_ostream<_CharT, _Traits>& join(std::basic_ostream<_CharT, _Traits>& os, const _Container& container, _CharT glue = ',')
{
	return join<>(os, begin(container), end(container), &glue, 1);
}


template<typename _CharT, typename _CharOrStringT, typename _ForwardIterator, bool _SpecifiedSize = false>
struct join_iterator_wrapper
{
	typedef _CharOrStringT value_type;
	typedef _ForwardIterator iterator_type;

	join_iterator_wrapper(iterator_type first, iterator_type last, value_type glue)
	: _glue(glue)
	, _first(first)
	, _last(last)
	{}

	value_type _glue;
	iterator_type _first;
	iterator_type _last;
};

template<typename _CharT, typename _CharOrStringT, typename _ForwardIterator>
struct join_iterator_wrapper<_CharT, _CharOrStringT, _ForwardIterator, true>
{
	typedef _CharOrStringT value_type;
	typedef _ForwardIterator iterator_type;

	join_iterator_wrapper(iterator_type first, iterator_type last, value_type glue, std::streamsize size)
	: _glue(glue)
	, _first(first)
	, _last(last)
	, _size(size)
	{}

	value_type _glue;
	iterator_type _first;
	iterator_type _last;
	std::streamsize _size;
};

template<typename _CharT, typename _Traits, typename _CharOrStringT, typename _ForwardIterator>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, join_iterator_wrapper<_CharT, _CharOrStringT, _ForwardIterator, false> wrapper)
{
	return join<>(os, wrapper._first, wrapper._last, wrapper._glue);
}

template<typename _CharT, typename _Traits, typename _CharOrStringT, typename _ForwardIterator>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, join_iterator_wrapper<_CharT, _CharOrStringT, _ForwardIterator, true> wrapper)
{
	return join<>(os, wrapper._first, wrapper._last, wrapper._glue, wrapper._size);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _ForwardIterator>
#else
template<typename _CharT, typename _ForwardIterator>
#endif
join_iterator_wrapper<_CharT, const _CharT*, _ForwardIterator> join(_ForwardIterator first, _ForwardIterator last, const _CharT* glue)
{
	return join_iterator_wrapper<_CharT, const _CharT*, _ForwardIterator>(first, last, glue);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _ForwardIterator>
#else
template<typename _CharT, typename _ForwardIterator>
#endif
join_iterator_wrapper<_CharT, _CharT, _ForwardIterator> join(_ForwardIterator first, _ForwardIterator last, _CharT glue = ',')
{
	return join_iterator_wrapper<_CharT, _CharT, _ForwardIterator>(first, last, glue);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _ForwardIterator>
#else
template<typename _CharT, typename _ForwardIterator>
#endif
join_iterator_wrapper<_CharT, const _CharT*, _ForwardIterator, true> join(_ForwardIterator first, _ForwardIterator last, const _CharT* glue, std::streamsize size)
{
	return join_iterator_wrapper<_CharT, const _CharT*, _ForwardIterator, true>(first, last, glue, size);
}


template<typename _CharT, typename _CharOrStringT, typename _Container, bool _SpecifiedSize = false>
struct join_wrapper
{
	typedef _CharOrStringT value_type;
	typedef const _Container& container_type;

	join_wrapper(container_type container, value_type glue)
		: _glue(glue)
		, _container(container)
	{}

	value_type _glue;
	container_type _container;
};

template<typename _CharT, typename _CharOrStringT, typename _Container>
struct join_wrapper<_CharT, _CharOrStringT, _Container, true>
{
	typedef _CharOrStringT value_type;
	typedef const _Container& container_type;

	join_wrapper(container_type container, value_type glue, std::streamsize size)
		: _glue(glue)
		, _container(container)
		, _size(size)
	{}

	value_type _glue;
	container_type _container;
	std::streamsize _size;
};

template<typename _CharT, typename _Traits, typename _CharOrStringT, typename _Container>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, join_wrapper<_CharT, _CharOrStringT, _Container, false> wrapper)
{
	return join<>(os, begin(wrapper._container), end(wrapper._container), wrapper._glue);
}

template<typename _CharT, typename _Traits, typename _CharOrStringT, typename _Container>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, join_wrapper<_CharT, _CharOrStringT, _Container, true> wrapper)
{
	return join<>(os, begin(wrapper._container), end(wrapper._container), wrapper._glue, wrapper._size);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _Container>
#else
template<typename _CharT, typename _Container>
#endif
join_wrapper<_CharT, const _CharT*, _Container> join(const _Container& container, const _CharT* glue)
{
	return join_wrapper<_CharT, const _CharT*, _Container>(container, glue);
}

template<typename _CharT, typename _Container, bool = is_ostream<_Container>::value>
struct __dispatch_join
{
	typedef void __result_type;
	static void __join(_Container& os, const _CharT& cont)
	{
		join(static_cast<std::basic_ostream<typename _Container::char_type, typename _Container::traits_type>&>(os), cont);
	}
};

template<typename _CharT, typename _Container>
struct __dispatch_join<_CharT, _Container, false>
{
	typedef join_wrapper<_CharT, _CharT, _Container> __result_type;
	static __result_type __join(const _Container& container, _CharT glue)
	{
		return __result_type(container, glue);
	}
};

template<typename _CharT, std::size_t _N, typename _Container>
struct __dispatch_join<_CharT[_N], _Container, false>
{
	typedef join_wrapper<_CharT, const _CharT*, _Container> __result_type;
	static __result_type __join(const _Container& container,
								const _CharT* glue)
	{
		return __result_type(container, glue);
	}
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _Container>
#else
template<typename _CharT, typename _Container>
#endif
typename __dispatch_join<_CharT, _Container>::__result_type
join(_Container& container, const _CharT& glue = ',')
{
	return __dispatch_join<_CharT, _Container>::__join(container, glue);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _Container>
#else
template<typename _CharT, typename _Container>
#endif
join_wrapper<_CharT, _CharT, _Container> join(const _Container& container)
{
	return join_wrapper<_CharT, _CharT, _Container>(container, ',');
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _CharT = char, typename _Container>
#else
template<typename _CharT, typename _Container>
#endif
typename enable_if<!is_ostream<_Container>::value, join_wrapper<_CharT, const _CharT*, _Container, true>>::type
join(const _Container& container, const _CharT* glue, std::streamsize size)
{
	return join_wrapper<_CharT, const _CharT*, _Container, true>(container, glue, size);
}

}

}

#endif
