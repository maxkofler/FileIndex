#include "../t_namesDB.h"

TEST(NamesDB, clean_debug){
	FUN();

	std::string funName = "NamesDB::clean()";

	NamesDB* db;

	try{
		DEBUG_PREPARE_FAIL(funName);

		db = new NamesDB();
		db->clean();

		DEBUG_TEARDOWN_FAIL(funName);

		delete db;

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		DEBUG_TEARDOWN_FAIL(funName);
		delete db;
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		DEBUG_TEARDOWN_FAIL(funName);
		delete db;
		F_WRONGEXCEPTION(funName + " - debug");
	}
}
