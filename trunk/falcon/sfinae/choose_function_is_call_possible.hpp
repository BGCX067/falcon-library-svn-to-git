#ifndef _FALCON_SFINAE_CHOOSE_FUNCTION_IS_CALL_POSSIBLE_HPP
#define _FALCON_SFINAE_CHOOSE_FUNCTION_IS_CALL_POSSIBLE_HPP

#include <falcon/sfinae/function_is_call_possible.hpp>
#include <falcon/sfinae/choose_type.hpp>

#define FALCON_CALL_CHOOSE_FUNCTION_IS_CALL_POSSIBLE(_FuncName, ...)\
	FALCON_CALL_CHOOSE_TYPE(FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName)<__VA_ARGS__>::value, _FuncName)

#define FALCON_CLASS_CHOOSE_FUNCTION_IS_CALL_POSSIBLE(_T, _FuncName, _TypeTrue, _TypeFalse)\
	FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(_FuncName);\
	FALCON_CLASS_CHOOSE_TYPE(_FuncName, _TypeTrue, _TypeFalse)

#endif
