#include "../t_fileIndex.h"

TEST(FileIndex, FileIndex_debug){
	FUN();

	std::string funName = "FileIndex::FileIndex()";

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

//Tests if the mechanism for setting the internal database works correctly
TEST(FileIndex, FileIndex_setDB){
	FUN();

	NamesDB externalDB;

	{
		FileIndex index;
		ASSERT_NE(index._db, nullptr);
		ASSERT_NE(index._db, &externalDB);
		ASSERT_FALSE(index._externalDB);
	}

	{
		FileIndex index(&externalDB);
		ASSERT_EQ(index._db, &externalDB);
		ASSERT_TRUE(index._externalDB);
	}
}
