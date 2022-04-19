#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

class DebugException{
public:
	DebugException(std::string funName);
	std::string			what();
private:
	std::string			_funName;
};

/**
 * @brief	Is a context guard, as long as this is on the stack, the specified function will fail
 */
class Fun_Fail_Guard{
public:
	Fun_Fail_Guard(std::string funName);
	~Fun_Fail_Guard();
private:
	std::string			_funName;
};

#ifdef DEBUG
	bool function_should_fail(std::string funName);
	void prepare_fun_failure(std::string funName);
	void teardown_function_failure(std::string funName);

	#define DEBUG_FAIL_FUN(name) Fun_Fail_Guard functionFailGuard(name)

	#define DEBUG_PREPARE_FAIL(name) prepare_fun_failure(name)
	#define DEBUG_TEARDOWN_FAIL(name) teardown_function_failure(name)

	#define DEBUG_RET(name) if (function_should_fail(name)) return false
	#define DEBUG_EX(name) if (function_should_fail(name)) throw new DebugException(name)
#else
	#define DEBUG_RET(name)
	#define DEBUG_EX(name)
#endif


#endif
