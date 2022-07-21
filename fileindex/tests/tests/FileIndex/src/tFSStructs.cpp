#include "../t_fileIndex.h"

TEST(FileIndex, FSEntry_Structs){
	FUN();

	fs_dir dir;
	fs_file file;

	ASSERT_TRUE(dir.isDir);
	ASSERT_FALSE(file.isDir);

	//Now try casting them around to check for SEGFAULTS
	
	fs_entry* dirP = &dir;
	fs_entry* fileP = &file;

	ASSERT_TRUE(dirP->isDir);
	ASSERT_FALSE(fileP->isDir);

}

TEST(FileIndex, FSEntry_Structs_FSTree){
	FUN();

	fs_dir root;
	
	fs_dir childDir;
	childDir.parent = &root;

	fs_file childFile;
	childFile.parent = &childDir;

	fs_entry* childDirP = &childDir;
	fs_entry* childFileP = &childFile;
	
	ASSERT_EQ(&root, childDirP->parent);
	ASSERT_EQ(&childDir, childFileP->parent);
}
