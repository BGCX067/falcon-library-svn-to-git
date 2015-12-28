#ifndef _FALCON_ITERATOR_RANGE_ACCESS_HPP
#define _FALCON_ITERATOR_RANGE_ACCESS_HPP

#include <iterator>
#include <falcon/type_traits/declval.hpp>

#ifdef __GXX_EXPERIMENTAL_CXX0X__

namespace falcon {
	using std::begin;
	using std::end;

	template<class _Container>
	inline auto rbegin(_Container& cont)
	-> decltype(cont.rbegin())
	{ return cont.rbegin(); }

	template<class _Container>
	inline auto rbegin(const _Container& cont)
	-> decltype(cont.rbegin())
	{ return cont.rbegin(); }

	template<class _Container>
	inline auto rend(_Container& cont)
	-> decltype(cont.rend())
	{ return cont.rend(); }

	template<class _Container>
	inline auto rend(const _Container& cont)
	-> decltype(cont.rend())
	{ return cont.rend(); }

	template<class _Container>
	inline auto cbegin(const _Container& cont)
	-> decltype(begin(cont))
	{ return begin(cont); }

	template<class _Container>
	inline auto cend(const _Container& cont)
	-> decltype(end(cont))
	{ return end(cont); }

	template<class _Container>
	inline auto crbegin(const _Container& cont)
	-> decltype(rbegin(cont))
	{ return rbegin(cont); }

	template<class _Container>
	inline auto crend(const _Container& cont)
	-> decltype(rend(cont))
	{ return rend(cont); }
}

#else

# include <cstddef>
# include <falcon/sfinae/choose_has_type.hpp>

namespace falcon {

	template <typename _Container>
	class range_access_iterator
	{
		FALCON_CLASS_CHOOSE_HAS_TYPE(_Container, iterator, typename _Container::const_iterator);

	public:
		typedef FALCON_CALL_CHOOSE_HAS_TYPE(_Container, iterator) type;
	};

	template <typename _T, std::size_t _N>
	struct range_access_iterator<_T[_N]>
	{
		typedef _T* type;
	};

	template <typename _Container>
	class range_access_iterator<const _Container>
	{
		FALCON_CLASS_CHOOSE_HAS_TYPE(_Container, const_iterator, typename _Container::iterator);

	public:
		typedef FALCON_CALL_CHOOSE_HAS_TYPE(_Container, const_iterator) type;
	};

	template <typename _Container>
	struct range_access_reverse_iterator
	{
		FALCON_CLASS_CHOOSE_HAS_TYPE(_Container, reverse_iterator, typename _Container::const_reverse_iterator);

	public:
		typedef FALCON_CALL_CHOOSE_HAS_TYPE(_Container, reverse_iterator) type;
	};

	template <typename _T, std::size_t _N>
	struct range_access_reverse_iterator<_T[_N]>
	{
		typedef _T* type;
	};

	template <typename _Container>
	class range_access_reverse_iterator<const _Container>
	{
		FALCON_CLASS_CHOOSE_HAS_TYPE(_Container, const_reverse_iterator, typename _Container::reverse_iterator);

	public:
		typedef FALCON_CALL_CHOOSE_HAS_TYPE(_Container, const_reverse_iterator) type;
	};

	template<typename _Container>
	inline typename range_access_iterator<_Container>::type begin(_Container& cont)
	{ return cont.begin(); }

	template<typename _Container>
	inline typename range_access_iterator<_Container>::type end(_Container& cont)
	{ return cont.end(); }

	template<class _Tp, size_t _Nm>
	inline _Tp* begin(_Tp (&arr)[_Nm])
	{ return arr; }

	template<class _Tp, size_t _Nm>
	inline _Tp* end(_Tp (&arr)[_Nm])
	{ return arr + _Nm; }

	template<typename _Container>
	inline typename range_access_reverse_iterator<_Container>::type rbegin(_Container& cont)
	{ return cont.rbegin(); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<_Container>::type rend(_Container& cont)
	{ return cont.rend(); }

	template<typename _Container>
	inline typename range_access_iterator<const _Container>::type cbegin(const _Container& cont)
	{ return begin(cont); }

	template<typename _Container>
	inline typename range_access_iterator<const _Container>::type cend(const _Container& cont)
	{ return end(cont); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<const _Container>::type crbegin(const _Container& cont)
	{ return rbegin(cont); }

	template<typename _Container>
	inline typename range_access_reverse_iterator<const _Container>::type crend(const _Container& cont)
	{ return rend(cont); }
}
#endif

namespace falcon {
	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<_Tp*> rbegin(_Tp (&arr)[_Nm])
	{ return std::reverse_iterator<_Tp*>(begin(arr)); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<_Tp*> rend(_Tp (&arr)[_Nm])
	{ return std::reverse_iterator<_Tp*>(end(arr)); }

	template<class _Tp, size_t _Nm>
	inline const _Tp* cbegin(const _Tp (&arr)[_Nm])
	{ return begin(arr); }

	template<class _Tp, size_t _Nm>
	inline const _Tp* cend(const _Tp (&arr)[_Nm])
	{ return begin(arr); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<const _Tp*> crbegin(const _Tp (&arr)[_Nm])
	{ return rbegin(arr); }

	template<class _Tp, size_t _Nm>
	inline std::reverse_iterator<const _Tp*> crend(const _Tp (&arr)[_Nm])
	{ return rbegin(arr); }
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__

# include <type_traits>

namespace falcon {
	template <typename _Container>
	struct range_access_iterator
	{
		typedef decltype(begin(std::declval<_Container&>())) type;
	};

	template <typename _Container>
	struct range_access_reverse_iterator
	{
		typedef decltype(rbegin(std::declval<_Container&>())) type;
	};
}
#endif

namespace falcon {

	template <typename _T>
	struct range_access_subtype
	{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		typedef decltype(*begin(declval<_T&>())) type;
#else
		typedef typename std::iterator_traits<typename range_access_iterator<_T>::type>::value_type type;
#endif
	};

}

#endif