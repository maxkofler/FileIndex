#include "../t_namesDB.h"

TEST(NamesDB, searchFirst_debug){
	FUN();

	std::string funName = "NamesDB::searchFirst()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.searchFirst("noName", false);

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

	void* wrongpointer = (void*) &name;

	NamesDB db;

	size_t id = db.add(name, &db);
	size_t id2 = db.add(name2, wrongpointer);

	{
		namesDB_searchRes res = db.searchFirst(name, false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		ASSERT_EQ(&db, res.data);
		ASSERT_EQ(0, res.id);
	}

	{
		namesDB_searchRes res = db.searchFirst(name2, false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		ASSERT_EQ(wrongpointer, res.data);
		ASSERT_EQ(1, res.id);
	}
}

//Tests if searchFirst() finds a name that is scattered throughout a string
TEST(NamesDB, searchFirst_find_scattered_name){
	FUN();

	std::string name = "SomeRandomName";

	void* wrongpointer = (void*) &name;

	NamesDB db;

	size_t id = db.add(name, &db);

	ASSERT_NE(0, db.searchFirst("Content", false).code) << "Could not find the entry";
}

//Tests if searchFirst() finds a similar string, what it should not do
TEST(NamesDB, searchFirst_similar){
	FUN();

	std::string contentWrong = "myContentIsWrong";
	std::string contentTrue = "Content";

	NamesDB db;

	void* wrongpointer = (void*) &contentWrong;

	size_t idW = db.add(contentWrong, wrongpointer);
	size_t idT = db.add(contentTrue, &db);

	{	//Check if the search find the wrong entry
		namesDB_searchRes res = db.searchFirst("Content", false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		EXPECT_NE(&db, res.data) << "Found the wrong item that was similar";
	}

	{	//Check if the search for "myContent" works correctly
		namesDB_searchRes res = db.searchFirst("myContent", false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		EXPECT_EQ(wrongpointer, res.data) << "Found the wrong item that was similar";
	}

}

TEST(NamesDB, searchFirst_find_content_start){
	FUN();

	std::string content = "Content";
	std::string name = content + "IsHere";

	NamesDB db;

	size_t id = db.add(name, &db);

	namesDB_searchRes res = db.searchFirst(content, false);

	ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the required string";
	ASSERT_EQ(0, res.code) << "Other error";
	ASSERT_EQ(&db, res.data) << "Found the wrong entry";
}

TEST(NamesDB, searchFirst_find_content_middle){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWith" + content + "IsHere";

	NamesDB db;

	size_t id = db.add(name, &db);

	namesDB_searchRes res = db.searchFirst(content, false);

	ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the required string";
	ASSERT_EQ(0, res.code) << "Other error";
	ASSERT_EQ(&db, res.data) << "Found the wrong entry";
}

TEST(NamesDB, searchFirst_find_content_end){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWithLoadsOfCharactersAndTheContentIsAtTheEnd" + content;

	NamesDB db;

	size_t id = db.add(name, &db);

	namesDB_searchRes res = db.searchFirst(content, false);

	ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the required string";
	ASSERT_EQ(0, res.code) << "Other error";
	ASSERT_EQ(&db, res.data) << "Found the wrong entry";
}

//Tests if the argument "search_start" works
TEST(NamesDB, searchFirst_find_from_start_index){
	FUN();

	std::string searchedString = "Content";
	std::string otherString = "Some random entry in the database...";

	NamesDB db;

	void* firstPointer = (void*) 1;
	void* secondPointer = (void*) 2;

	db.add(searchedString, firstPointer);
	db.add(otherString, nullptr);
	db.add(searchedString, secondPointer);

	{
		namesDB_searchRes res = db.searchFirst(searchedString, false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		ASSERT_EQ(firstPointer, res.data) << "searchFirst() could not find the first occurence";
		ASSERT_EQ(0, res.id);
	}

	{
		namesDB_searchRes res = db.searchFirst(searchedString, false);

		ASSERT_NE(SEARCHRES_NOTFOUND, res.code) << "Could not find the entry";
		ASSERT_EQ(0, res.code) << "Other error";
		ASSERT_EQ(firstPointer, res.data) << "searchFirst() could not find the second occurence";
		ASSERT_EQ(0, res.id);
	}

}
