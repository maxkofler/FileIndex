#include "../t_namesDB.h"

#include <fstream>

#include "namesDB.h"

TEST(NamesDB, NamesDB_constructor_default_blocksize){
	FUN();

	NamesDB db;

	ASSERT_EQ(1024, db._blockSize);
}

TEST(NamesDB, NamesDB_constructor_specified_blocksize){
	FUN();

	NamesDB db(100234);

	ASSERT_EQ(100234, db._blockSize);
}
