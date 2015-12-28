#ifndef _FALCON_CONTAINER_CONTAINER_WRAPPER
#define _FALCON_CONTAINER_CONTAINER_WRAPPER

#include <iterator>
#include <falcon/container/range_access_traits.hpp>

namespace falcon{

template<typename _Container, typename _Traits = range_access_traits<_Container> >
struct container_wrapper
{
	typedef _Container container_type;
	typedef typename _Traits::iterator iterator;

private:
	typedef std::iterator_traits<iterator> __type_traits;

public:
	typedef typename __type_traits::value_type value_type;
	typedef typename __type_traits::pointer pointer;
	typedef typename __type_traits::reference reference;


private:
	container_type& _container;


public:
	container_wrapper(container_type& container)
	: _container(container)
	{}

	container_wrapper(const container_wrapper& other)
	: _container(other._container)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	container_wrapper(container_type&&) = delete;
	container_wrapper& operator=(const container_wrapper& other) = delete;
#else
private:
	container_wrapper& operator=(const container_wrapper& other);
public:
#endif

	iterator begin() const
	{ return _Traits::begin(base()); }

	iterator end() const
	{ return _Traits::end(base()); }

	void swap(container_wrapper& other)
	{ std::swap(_container, other._container); }

	operator container_type&() const
	{ return base(); }

	container_type& base() const
	{ return _container; }
};

template<typename _Container, typename _Traits = _Container>
struct static_container_wrapper
{
	typedef _Container container_type;
	typedef typename _Traits::iterator iterator;

private:
	typedef std::iterator_traits<iterator> __type_traits;

public:
	typedef typename __type_traits::value_type value_type;
	typedef typename __type_traits::pointer pointer;
	typedef typename __type_traits::reference reference;


public:
	iterator begin() const
	{ return _Traits::begin(); }

	iterator end() const
	{ return _Traits::end(); }
};

}

#endif