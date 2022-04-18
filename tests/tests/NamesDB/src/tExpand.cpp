#include "../t_namesDB.h"

#include <fstream>

#include "namesDB.h"

TEST(NamesDB, expand_general){
	FUN();

	NamesDB db;

	ASSERT_TRUE(db.expand());
}
