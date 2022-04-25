#include "../t_namesDB.h"

TEST(NamesDB, get_debug){
	FUN();

	std::string funName = "NamesDB::get()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.get(db.add("NewEntry", nullptr));

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

//Tests if get() reacts correctly to a id that is out of bounds
TEST(NamesDB, get_id_out_of_range){
	FUN();

	NamesDB db;

	EXPECT_EQ(nullptr, db.get(0));
	EXPECT_EQ(nullptr, db.get(1));
	EXPECT_EQ(nullptr, db.get(3498023));

	db.add("Name", nullptr);

	EXPECT_EQ(nullptr, db.get(1));
}

TEST(NamesDB, get_correct_return){
	FUN();

	std::string name = "This is my name!";
	std::string name2 = "This is a second name!";

	NamesDB db;

	size_t id = db.add(name, &name);
	size_t id2 = db.add(name2, &name2);

	EXPECT_EQ(&name, db.get(id));
	EXPECT_EQ(&name2, db.get(id2));
}

TEST(NamesDB, get_empty){
	FUN();

	NamesDB db;

	EXPECT_EQ(nullptr, db.get(0));
}
