#include "../t_namesDB.h"

TEST(NamesDB, add_debug){
	FUN();

	std::string funName = "NamesDB::add()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.add("NewEntry", nullptr);

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

//Just adds a name to a db, this should NEVER fail
TEST(NamesDB, add_normal){
	FUN();

	NamesDB db;
	db.add("MyName", &db);
}

//Adds loads of names to the database
TEST(NamesDB, add_loads_of_names){
	FUN();

	NamesDB db;

	try{
		for(size_t i = 0; i < 100000; i++)
			db.add("Name" + std::to_string(i), nullptr);
	} catch (std::bad_alloc& ba){
		FAIL() << "Adding of loads of entries failed with bad_alloc exception: " + std::string(ba.what());
	} catch (...) {
		FAIL() << "Failed to add loads of entries with exception";
	}
}

//Checks if the return value of add() is the correct id
TEST(NamesDB, add_return){
	FUN();

	NamesDB db;
	ASSERT_EQ(0, db.add("OneName", nullptr));
	ASSERT_EQ(1, db.add("SecondName", nullptr));
}

//Checks if the calling of add() expands the database
TEST(NamesDB, add_expand){
	FUN();

	std::string funName = "NamesDB::expand()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db(1);
		db.add("Name", nullptr);

		FAIL() << "NamesDB::add() does not call expand to extend its database";
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}
