#include "../t_fileIndex.h"

TEST(FileIndex, FileIndex_debug){
	FUN();

	std::string funName = "FileIndex::FileIndex()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db("FS-main");
		FS fs(&db);
		FileIndex index(&fs);

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}
