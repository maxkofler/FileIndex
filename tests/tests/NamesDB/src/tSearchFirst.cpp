#include "../t_namesDB.h"

TEST(NamesDB, searchFirst_debug){
	FUN();

	std::string funName = "NamesDB::searchFirst()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.searchFirst("noName");

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

TEST(NamesDB, searchFirst_find_name){
	FUN();

	std::string name = "SomeRandomName";
	std::string name2 = "SomeOtherRandomName2";

	NamesDB db;

	size_t id = db.add(name, &db);
	size_t id2 = db.add(name2, nullptr);

	ASSERT_NE(nullptr, db.searchFirst(name));
	ASSERT_EQ(&db, db.searchFirst(name)->entry);

	ASSERT_NE(nullptr, db.searchFirst(name2));
	ASSERT_EQ(nullptr, db.searchFirst(name2)->entry);
}

//Tests if searchFirst() finds a similar string, what it should not do
TEST(NamesDB, searchFirst_similar){
	FUN();

	std::string contentWrong = "myContentIsWrong";
	std::string contentTrue = "Content";

	NamesDB db;

	size_t idW = db.add(contentWrong, nullptr);
	size_t idT = db.add(contentTrue, &db);

	{	//Check if the search find the wrong entry
		entry_namesDB* res = db.searchFirst("Content");

		ASSERT_NE(nullptr, res) << "Could not find the required string";
		EXPECT_NE(&db, res->entry) << "Found the wrong item that was similar";
	}

	{	//Check if the search for "myContent" works correctly
		entry_namesDB* res = db.searchFirst("myContent");

		ASSERT_NE(nullptr, res) << "Could not find the required string";
		EXPECT_EQ(nullptr, res->entry) << "Found the wrong item that was similar";
	}

}

TEST(NamesDB, searchFirst_find_content_start){
	FUN();

	std::string content = "Content";
	std::string name = content + "IsHere";

	NamesDB db;

	size_t id = db.add(name, &db);

	ASSERT_NE(nullptr, db.searchFirst(content)) << "Could not find the required string";
	ASSERT_EQ(&db, db.searchFirst(content)->entry) << "Found the wrong entry";
}

TEST(NamesDB, searchFirst_find_content_middle){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWith" + content + "IsHere";

	NamesDB db;

	size_t id = db.add(name, &db);

	ASSERT_NE(nullptr, db.searchFirst(content)) << "Could not find the required string";
	ASSERT_EQ(&db, db.searchFirst(content)->entry) << "Found the wrong entry";	//FAILS BECAUSE IMPLEMENTATION IS FLAWED!
}

TEST(NamesDB, searchFirst_find_content_end){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWithLoadsOfCharactersAndTheContentIsAtTheEnd" + content;

	NamesDB db;

	size_t id = db.add(name, &db);

	ASSERT_NE(nullptr, db.searchFirst(content)) << "Could not find the required string";
	ASSERT_EQ(&db, db.searchFirst(content)->entry) << "Found the wrong entry";	//FAILS BECAUSE IMPLEMENTATION IS FLAWED!
}
