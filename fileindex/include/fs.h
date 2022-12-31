#ifndef __FS_H__
#define __FS_H__

#include "sql.h"

#include <deque>
#include <ostream>
#include <istream>

class FS{

public:
    FS(SQL& sql);
    ~FS();

    /**
     * @brief   Adds the supplied filesystem entry with the name
     * @param   path            The path to add
     */
    bool                        add(const std::string& path);

#ifndef FRIEND_FS
private:
#endif

    /**
     * @brief   The SQL wrapper for the core filesystem database
     */
    SQL&                        _sql;
};

#endif
