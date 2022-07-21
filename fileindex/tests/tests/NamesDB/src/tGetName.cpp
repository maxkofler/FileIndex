#include "../t_namesDB.h"

TEST(NamesDB, getName_debug){
	FUN();

	std::string funName = "NamesDB::getName()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.getName(db.add("NewEntry", nullptr));

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
TEST(NamesDB, getName_id_out_of_range){
	FUN();

	NamesDB db;

	EXPECT_TRUE(db.getName(0).empty());
	EXPECT_TRUE(db.getName(1).empty());
	EXPECT_TRUE(db.getName(9281456).empty());

	db.add("Name", nullptr);

	EXPECT_FALSE(db.getName(0).empty());
	EXPECT_TRUE(db.getName(1).empty());
}

TEST(NamesDB, getName_correct_return){
	FUN();

	std::string name = "This is my name!";
	std::string name2 = "This is a second name!";

	NamesDB db;

	size_t id = db.add(name, &name);
	size_t id2 = db.add(name2, &name2);

	EXPECT_EQ(name, db.getName(id));
	EXPECT_EQ(name2, db.getName(id2));
}

TEST(NamesDB, getName_empty){
	FUN();

	NamesDB db;

	EXPECT_TRUE(db.getName(0).empty());
}
