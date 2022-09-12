#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "fs.h"

class FileIndex{

public:
    FileIndex(FS* fs);

    /**
     * @brief	Indexes the supplied path if it is a directory
     * @param	path		The path to index
     * @param	recursive	If this function should enter subdirectories (default: true)
     * @return	size_t      The amount of entries found
     */
    size_t                      index(std::string path, bool recursive = true);

    /**
     * @brief   Adds the supplied entry to the internal FS
     * @param   name        The name of the entry
     * @param   entry       The entry to add
     * @return  size_t      The id of the added entry
     */
    size_t                      add(std::string& name, fs_entry entry);

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
     * @brief   Indexes the supplied path blindly, no checks are made
     * @param   parentID        The ID of the parent directory
     * @param   path            The path to index
     * @param   recursive       If this function should enter subdirectories (default: true)
     */
    void                        index_blind(size_t parentID, std::string path, bool recursive = true);

};

#endif
