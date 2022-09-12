#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "fs.h"

class FileIndex{

public:
    FileIndex(FS* fs);

    /**
     * @brief	Indexes the supplied path if it is a directory
     * @param	parent		The parent directory
     * @param	path		The path to index
     * @param	recursive	If this function should enter subdirectories (default: true)
     * @return	size_t      The amount of entries found
     */
    size_t                      index(fs_dir* parent, std::string path, bool recursive = true);

    /**
     * @brief   Returns the internal filesystem
     */
    FS*                         getFS();

private:

    /**
     * @brief   The filesystem to use
     */
    FS*                         _fs;

    size_t                      _indexedEntries = 0;

    /**
     * @brief	Indexes the supplied path blindly, no checks are made
     * @param	parent		The parent directory
     * @param	path		The path to index
     * @param	recursive	If this function should enter subdirectories (default: true)
     */
    void					index_blind(fs_dir* parent, std::string path, bool recursive = true);

};

#endif
