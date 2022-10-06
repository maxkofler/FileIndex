#include "../t_fileIndex.h"

TEST(FileIndex, setCBFSEntryIndexed_debug){
	FUN();

	std::string funName = "FileIndex::CBFSEntryIndexed()";

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

static size_t calls_to_handler = 0;
void callback_handler(const std::string_view& name, size_t id, bool isDir){
	calls_to_handler++;
}

//Check if the callback works
TEST(FileIndex, setCBFSEntryIndexed_check){
	FUN();

	NamesDB db("FS-main");
	FS fs(&db);
	FileIndex index(&fs);

	index.setCBFSEntryIndexed(&callback_handler);
	ASSERT_EQ(&callback_handler, index._callback_indexed) << "The setCBFSEntryIndexed() function does not set the callback!";

	calls_to_handler = 0;
	index.index(".", false);

	ASSERT_TRUE(calls_to_handler > 0);

	index.removeCBFSEntryIndexed();
	ASSERT_EQ(nullptr, index._callback_indexed) << "The removeCBSFEntryIndexed() function does not remove the callback!";
}
