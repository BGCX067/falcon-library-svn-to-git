#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/contain_range_access.hpp>
#include "range_access.hpp"

void range_access_test()
{
	using falcon::contain_range_access_iterator;
	using falcon::contain_range_access_reverse_iterator;

	STATIC_CHECK_VALUE(false, contain_range_access_iterator<int>);
	STATIC_CHECK_VALUE(true, contain_range_access_iterator<int[5]>);
	STATIC_CHECK_VALUE(false, contain_range_access_reverse_iterator<int>);
	STATIC_CHECK_VALUE(true, contain_range_access_reverse_iterator<int[5]>);

	typedef std::vector<int> container;
	typedef typename container::iterator iterator;
	typedef std::vector<container> w_container;
	typedef typename w_container::iterator w_iterator;

	CHECK_TYPE(iterator, falcon::range_access_iterator<container>);
	CHECK_TYPE(w_iterator, falcon::range_access_iterator<w_container>);

	STATIC_CHECK_VALUE(true, contain_range_access_iterator<container>);
	STATIC_CHECK_VALUE(true, contain_range_access_reverse_iterator<container>);

	STATIC_CHECK_VALUE(true, contain_range_access_iterator<w_container>);
	STATIC_CHECK_VALUE(true, contain_range_access_reverse_iterator<w_container>);

	STATIC_CHECK_VALUE(false, contain_range_access_iterator<iterator>);
	STATIC_CHECK_VALUE(false, contain_range_access_reverse_iterator<w_iterator>);
}
FALCON_TEST_TO_MAIN(range_access_test)
