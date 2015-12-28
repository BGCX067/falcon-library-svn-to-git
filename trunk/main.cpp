// #include <iostream>
// #include <falcon/unused_variable.hpp>
// #ifdef __GXX_EXPERIMENTAL_CXX0X__
// # include <falcon/c++0x/syntax.hpp>
// #else
// # define CPP0X(...)
// #endif
//
// using falcon::unused_variable;
// using falcon::unused_variables;

/*void f(int a)
{
	std::cout << a << ' ';
}

double f2(int i, double d)
{
	std::cout << i << ' ' << d << std::endl;
	return d+i;
}*/

// #include "falcon/test/utility/store_if.cpp"
// #include <falcon/test/all_tests.cpp>
// #include <falcon/test/iterator.cpp>
// #include <falcon/test/java_iterator.cpp>
#include "test/all_tests.hpp"

int main()
{
	all_tests();

	return 0;
}
