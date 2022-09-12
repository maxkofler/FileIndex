#ifndef __FS_H__
#define __FS_H__

#include "namesDB.h"
#include "fstypes.h"
#include "crate.h"
#include "dArray.h"

#ifndef FS_DEFAULT_CHUNK_SIZE
    #define FS_DEFAULT_CHUNK_SIZE 32
#endif

class FS{

public:
    /**
     * @brief   Creates a new filesystem
     * @param   db              The database to use, nullptr to create a new one
     * @param   useDirtyDB      Whether to use a dirty db that gets cleaned afterwards or accepts duplicates (default: false)
     */
    FS(NamesDB* db, bool useDirtyDB = false, size_t chunkSize = FS_DEFAULT_CHUNK_SIZE);

    ~FS();

    /**
     * @brief   Adds the supplied filesystem entry with the name
     * @param   name            The name to add
     * @param   entry           The entry to add
     */
    size_t                      add(const std::string& name, const fs_entry& entry);

    /**
     * @brief   Gets a pointer to the filesystem entry with the supplied id
     * @param   id              The id to get
     * @return  fs_entry*       nullptr if id out of bounds
     */
    fs_entry*                   getEntry(size_t id);

    /**
     * @brief   Returns a pointer to the main Database for this filesystem
     */
    NamesDB*                    getDB();

    /**
     * @brief   If this filesystem should use a dirty database
     */
    bool                        getUseDirtyDB();

    /**
     * @brief   Returns the dirty database if existing, else nullptr
     */
    NamesDB*                    getDirtyDB();

private:

    /**
     * @brief   The database that stores the names of the filesystem
     */
    NamesDB*                    _db = nullptr;

    /**
     * @brief   The amount of blocks to expand by default
     */
    size_t                      _chunkSize;

    /**
     * @brief   If this should use a dirty database
     */
    bool                        _useDirtyDB = false;

    /**
     * @brief   The dirty db that gets used
     */
    NamesDB*                    _dirtyDB = nullptr;

    /**
     * @brief   The array containing all the crates
     */
    DArray<crate_s<size_t>>     _crates;

    /**
     * @brief   The entries to build up the filesystem tree
     */
    DArray<fs_entry>            _entries;

};

#endif
