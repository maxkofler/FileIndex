#ifndef __FS_H__
#define __FS_H__

#include "namesDB.h"
#include "fstypes.h"

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

    /**
     * @brief   Adds the supplied filesystem entry with the name
     * @param   name            The name to add
     * @param   entry           The entry to add
     */
    void                        add(const std::string& name, const fs_entry& entry);

    /**
     * @brief   Expands the internal database by the supplied amount
     * @param   amount          The amount of entries to expand (0 for default)
     */
    void                        expand(size_t amount = 0);

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
     * @brief   The entries to build up the filesystem tree
     */
    fs_entry*                   _entries = nullptr;

    /**
     * @brief   The amount of entry places used
     */
    size_t                      _count_entries = 0;

    /**
     * @brief   The size of the entries array
     */
    size_t                      _size_entries = 0;

};

#endif
