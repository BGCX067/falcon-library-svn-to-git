#include <test/test.hpp>
#include <test/A.h>
#include <falcon/new.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/algorithm/algorithm.hpp>
#include "new.hpp"

void new_test() {
	std::stringstream ss;
	std::streambuf* oldbuf = std::cout.rdbuf(ss.rdbuf());
	{
		A* i = falcon::allocate<A>();
		A* keep = i;
		falcon::construct<>(i,4);
		CHECK_EQUAL_VALUE(ss.str(), "A(4)\n"); ss.str("");
		CHECK_EQUAL_VALUE(4, i->i);
		CHECK_EQUAL_VALUE(keep, i);
		falcon::reconstruct<>(i, 8);
		CHECK_EQUAL_VALUE(ss.str(), "~A\nA(8)\n"); ss.str("");
		CHECK_EQUAL_VALUE(8, i->i);
		CHECK_EQUAL_VALUE(keep, i);
		falcon::destroy<>(i);
		CHECK_EQUAL_VALUE(ss.str(), "~A\n"); ss.str("");
		falcon::deallocate<>(i);

		i = falcon::default_new<A>(20);
		CHECK_EQUAL_VALUE(ss.str(), "A(20)\n"); ss.str("");
		CHECK_EQUAL_VALUE(20, i->i);
		falcon::renew<>(i,7);
		CHECK_EQUAL_VALUE(ss.str(), "~A\nA(7)\n"); ss.str("");
		CHECK_EQUAL_VALUE(7, i->i);
		keep = i;
		falcon::reconstruct<>(i,9);
		CHECK_EQUAL_VALUE(ss.str(), "~A\nA(9)\n"); ss.str("");
		CHECK_EQUAL_VALUE(9, i->i);
		CHECK_EQUAL_VALUE(keep, i);
		falcon::default_delete<>(i);
		CHECK_EQUAL_VALUE(ss.str(), "~A\n"); ss.str("");
	}
	{
		A* i[5]/* = {0,0,0,0,0}*/;

		//falcon::algorithm::generate<>(i, falcon::default_new<A>);
		//falcon::algorithm::fill(range_access(i), 4);
		falcon::algorithm::generate<>(i, std::bind(falcon::default_new_wrapper<A>(), 4));
		CHECK_EQUAL_VALUE(ss.str(), "A(4)\nA(4)\nA(4)\nA(4)\nA(4)\n"); ss.str("");
		falcon::default_delete<>(falcon::begin(i), falcon::end(i));
		CHECK_EQUAL_VALUE(ss.str(), "~A\n~A\n~A\n~A\n~A\n");
	}
	std::cout.rdbuf(oldbuf);
}

FALCON_TEST_TO_MAIN(new_test)
