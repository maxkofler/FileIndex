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
     * @param   rootName        The name of the root, the supplied directory should be indexed into
     * @return	size_t          The amount of entries found
     */
    size_t                      index(std::string path, bool recursive = true, std::string rootName = "");

    /**
     * @brief   Adds the supplied entry to the internal FS
     * @param   path            The path of the entry
     */
    bool                        add(std::string& path);

    /**
     * @brief   Returns the internal filesystem
     */
    FS*                         getFS();

    /**
     * @brief   Adds a callback that gets called every time the index() function finds a filesystem entry
     * @param   callback        The callback function
     *  @param  udata           A pointer for user data
     *  @param  path            A const std::string_view& for passing the path of the entry
     *  @param  isDir           True if the entry is a directory
     * @param   udata           The user data to supply on every call
     */
    void                        setCBFSEntryIndexed(void (*callback)(const std::string_view& path, bool isDir, void* udata), void* udata);

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
     * @param   isDir           True if the entry is a directory
     */
    void                        (*_callback_indexed)(const std::string_view& path, bool isDir, void* udata) = nullptr;

    /**
     * @brief   The user data to return when the callback gets called
     */
    void*                       _callback_udata = nullptr;

    /**
     * @brief   Indexes the supplied path blindly, no checks are made
     * @param   relPath         The relative path to the root (the crate name too): myCrate/etc/ -> /etc/
     * @param   path            The path to index
     * @param   recursive       If this function should enter subdirectories (default: true)
     */
    void                        index_blind(const std::string& relPath, const std::string& path, bool recursive = true);

};

#endif
