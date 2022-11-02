#ifndef __FS_H__
#define __FS_H__

#include "namesDB.h"
#include "fstypes.h"
#include "crate.h"
#include "dArray.h"

#include <deque>
#include <ostream>
#include <istream>

#ifndef FS_DEFAULT_CHUNK_SIZE
    #define FS_DEFAULT_CHUNK_SIZE 32
#endif

#define FS_ROOT_PARENTID UINT64_MAX

class FS{

public:
    /**
     * @brief   Creates a new filesystem
     * @param   db              The database to use, nullptr to create a new one
     * @param   chunkSize       The size of the chunks allocated
     */
    FS(NamesDB<fs_entry>* db, size_t chunkSize = FS_DEFAULT_CHUNK_SIZE);

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
     * @brief   Returns a deque describing the path to the supplied entry, starting with the root
     * @param   id              The id of the entry
     * @param   path            A reference to the path to append to
     */
    void                        getEntryPath(size_t id, std::deque<fs_entry>& path);

    /**
     * @brief   Returns a string describing the path to the supplied entry
     * @param   id              The id of the entry
     * @return  std::string
     */
    std::string                 getEntryPathString(size_t id);

    /**
     * @brief   Returns a pointer to the main Database for this filesystem
     */
    NamesDB<fs_entry>*          getDB();

    /**
	 * @brief	Exports this filesystems contents to the supplied stream
	 * @param	outStream		The stream to export to
	 */
	void						exportFS(std::ostream& outStream);

	/**
	 * @brief	Imports the contents of this filesystem form the supplied stream
	 * @note	This clears the contents of this filesystem
	 * @param	inStream		The stream to import from
	 */
	bool						importFS(std::istream& inStream);

#ifndef FRIEND_FS
private:
#endif

    /**
     * @brief   The database that stores the names of the filesystem
     */
    NamesDB<fs_entry>*          _db = nullptr;

    /**
     * @brief   The amount of blocks to expand by default
     */
    size_t                      _chunkSize;

    /**
     * @brief   The entries to build up the filesystem tree
     */
    //DArray<fs_entry>            _entries;

};

#endif
