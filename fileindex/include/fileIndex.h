#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "fs.h"

class FileIndex{

public:
    FileIndex(FS* fs);

    /**
     * @brief	Indexes the supplied path if it is a directory
     * @param	path		    The path to index
     * @param	recursive	    If this function should enter subdirectories (default: true)
     * @return	size_t          The amount of entries found
     */
    size_t                      index(std::string path, bool recursive = true);

    /**
     * @brief   Adds the supplied entry to the internal FS
     * @param   name            The name of the entry
     * @param   entry           The entry to add
     * @return  size_t          The id of the added entry
     */
    size_t                      add(std::string& name, fs_entry entry);

    /**
     * @brief   Returns the internal filesystem
     */
    FS*                         getFS();

    /**
     * @brief   Adds a callback that gets called every time the index() function finds a filesystem entry
     * @param   callback        The callback function
     *  @param  path            A const std::string_view& for passing the path of the entry
     *  @param  id              The id of the indexed entry
     *  @param  isDir           True if the entry is a directory
     */
    void                        setCBFSEntryIndexed(void (*callback)(const std::string_view& path, size_t id, bool isDir));

    /**
     * @brief   Removes the previously set callback for every indexed fs entry
     */
    void                        removeCBFSEntryIndexed();

#ifndef FRIEND_FILEINDEX
private:
#endif

    /**
     * @brief   The filesystem to use
     */
    FS*                         _fs;

    /**
     * @brief   The amount of indexed fs entries in this index
     */
    size_t                      _indexedEntries = 0;

    /**
     * @brief   The callback for every fs entry found
     * @param   path            A const std::string_view& for passing the path of the entry
     * @param   id              The id of the indexed entry
     * @param   isDir           True if the entry is a directory
     */
    void                        (*_callback_indexed)(const std::string_view& path, size_t id, bool isDir) = nullptr;

    /**
     * @brief   Indexes the supplied path blindly, no checks are made
     * @param   parentID        The ID of the parent directory
     * @param   path            The path to index
     * @param   recursive       If this function should enter subdirectories (default: true)
     */
    void                        index_blind(size_t parentID, std::string path, bool recursive = true);

};

#endif
