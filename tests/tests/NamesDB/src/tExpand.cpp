#include "../t_namesDB.h"

#include <fstream>

#include "namesDB.h"

/**
 * @brief	Tests if the constructor calls expand
 */
TEST(NamesDB, expand_constructor){
	FUN();

	std::string fun_name = "NamesDB::expand()";

	try{
		DEBUG_FAIL_FUN(fun_name);

		NamesDB db;

		F_NOTHROW(fun_name + " - debug");
	} catch (DebugException* e){
		if (e->what() != fun_name){
			F_WRONGTHROW(fun_name, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(fun_name + " - debug");
	}
}

TEST(NamesDB, expand_general){
	FUN();

	NamesDB db;

	ASSERT_TRUE(db.expand());
}

/**
 * @brief	Tests the correct expansion if the _names field is empty, typically at constructor
 */
TEST(NamesDB, expand_zero){
	FUN();

	NamesDB db;

	delete db._entries;
	db._entries = nullptr;

	db.expand(1);

	ASSERT_NE(nullptr, db._entries);
}
