#ifndef _FALCON_LITERAL_STDDEF_HPP
#define _FALCON_LITERAL_STDDEF_HPP

#include <falcon/literal/detail/literal_support.hpp>

#include <cstdint>

namespace falcon {
namespace literal {
namespace numeric {

#define FALCON_USER_DEFINED_STDINT_LITERAL(suffix)\
	constexpr suffix##_t operator "" _##suffix(unsigned long long n)\
	{ return static_cast<suffix##_t>(n); }

#define FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(suffix)\
	FALCON_USER_DEFINED_STDINT_LITERAL(suffix)\
	FALCON_USER_DEFINED_STDINT_LITERAL(u##suffix)

#define FALCON_USER_DEFINED_STDINT_LITERAL_UTILS(suffix)\
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(suffix##8)\
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(suffix##16)\
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(suffix##32)\
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(suffix##64)

	FALCON_USER_DEFINED_STDINT_LITERAL_UTILS(int)
	FALCON_USER_DEFINED_STDINT_LITERAL_UTILS(int_fast)
	FALCON_USER_DEFINED_STDINT_LITERAL_UTILS(int_least)
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(intmax)
	FALCON_USER_DEFINED_STDINT_LITERAL_PAIR(intptr)

#undef FALCON_USER_DEFINED_STDINT_LITERAL_UTILS
#undef FALCON_USER_DEFINED_STDINT_LITERAL_PAIR
#undef FALCON_USER_DEFINED_STDINT_LITERAL

}
}
}

#endif