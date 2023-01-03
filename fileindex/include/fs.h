#ifndef __FS_H__
#define __FS_H__

#include "sql.h"
#include "fstypes.h"

#include <deque>
#include <ostream>
#include <istream>

#include <stdint.h>

class FS{

public:
    FS(SQL& sql);
    ~FS();

    /**
     * @brief   Adds the supplied filesystem entry with the name
     * @param   fsEntry         The filesystem entry to add (id and nameID gets filled in)
     */
    bool                        add(fs_entry& entry);

    /**
     * @brief   Searches the filesystem for the searched string
     * @param   search          The string to search for
     * @param   matchCase       If the search casing has to match
     * @param   exact           If the string has to match exactly
     * @return  std::deque<fs_entry>
     */
    std::deque<fs_entry>        search(const std::string& search, bool matchCase = false, bool exact = false);

    /**
     * @brief   Searches the filesystem for the searched string
     * @param   search          The string to search for
     * @param   matchCase       If the search casing has to match
     * @param   exact           If the string has to match exactly
     * @return  std::deque<std::shared_ptr<FSDir>>  The root handles
     */
    std::deque<std::shared_ptr<FSDir>> searchTree(const std::string& search, bool matchCase = false, bool exact = false);

    /**
     * @brief   Resolves all upper fs_entries of the supplied entry (The parent directories)
     * @param   entry           The entry to process
     * @return  std::deque<fs_entry>
     */
    std::deque<fs_entry>        getPath(fs_entry& entry);

    /**
     * @brief   Returns the whole path for the supplied entry
     * @param   entry           The entry to process
     * @return  std::string
     */
    std::string                 getPathString(fs_entry& entry);

    /**
     * @brief   Returns a deque containing all the root entries (where parentID=0)
     */
    std::deque<fs_entry>        getRoots();

    /**
     * @brief   Queries the database for the complete entry according to the supplied id
     * @param   id              The ID of the searched entry
     * @return  fs_entry        id = 0 on error
     */
    fs_entry                    getEntryByID(uint64_t id);

    /**
     * @brief   Returns a reference to the used SQL object
     */
    SQL&                        getSQL(){return _sql;}

    /**
     * @brief   Creates the SQL tables needed for the filesystem to work
     */
    void                        createTables();

#ifndef FRIEND_FS
private:
#endif

    /**
     * @brief   The SQL wrapper for the core filesystem database
     */
    SQL&                        _sql;
};

#endif
