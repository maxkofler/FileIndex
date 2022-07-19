#include "../t_fileIndex.h"


TEST(FileIndex, Index_Indexing){
	FUN();

	std::string indexDir = ".";

	FileIndex indexer;

	fs_dir* root = new fs_dir;
	
	root->nameID = indexer.getDB()->add(indexDir, root);


	ASSERT_NE(0, indexer.index(root, indexDir));
}
