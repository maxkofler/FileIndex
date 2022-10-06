#include "../t_fileIndex.h"

TEST(FileIndex, setCBFSEntryIndexed_debug){
	FUN();

	std::string funName = "FileIndex::CBFSEntryIndexed()";

	try{
		DEBUG_FAIL_FUN(funName);

		FileIndex index;

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}