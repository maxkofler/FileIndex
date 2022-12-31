#ifndef __FSTYPES_H__
#define __FSTYPES_H__

#include <stdint.h>
#include <string>

/**
 * @brief	The base filesystem entry for the different filesystem types
 */
typedef struct fsentry_s {
    bool                isDir;
    uint64_t            id;
    std::string         name;
    uint64_t            nameID;
    uint64_t            parentID;
} fs_entry;

/**
 * @brief	An internal representation of a file in a filesystem tree
 */
typedef struct s_fs_file : public fsentry_s{
    s_fs_file(){
        isDir = false;
    }
} fs_file;

/**
 * @brief	An internal representation of a directory in a filesystem tree
 */
typedef struct s_fs_dir : public fsentry_s{
    s_fs_dir(){
        isDir = true;
    }
} fs_dir;

/**
 * @brief   Returns information about the fs_entry in string form
 * @param   entry       The entry to inform about
 */
std::string fs_entry_str(fs_entry& entry);

/**
 * @brief   Parses the fs_entry from the supplied strings
 * @param isDir
 * @param id
 * @param name
 * @param nameID
 * @param parentID
 * @return fs_entry
 */
fs_entry fs_entry_parse(std::string isDir, std::string id, std::string name, std::string nameID, std::string parentID);

#endif
