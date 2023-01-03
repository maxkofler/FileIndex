#ifndef __FSTYPES_H__
#define __FSTYPES_H__

#include <stdint.h>
#include <string>
#include <deque>
#include <iostream>

/**
 * @brief	The base filesystem entry for the different filesystem types
 */
struct fsentry_s;

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

class FSEntry{
public:
    FSEntry(std::string isDir, std::string id, std::string name, std::string nameID, std::string parentID);
    FSEntry(bool isDir, uint64_t id, const std::string& name, uint64_t nameID, uint64_t parentID);

    bool                    isDir;
    uint64_t                id;
    std::string             name;
    uint64_t                nameID;
    uint64_t                parentID;
};

class FSDir : public FSEntry{
public:
    FSDir(std::string id, std::string name, std::string nameID, std::string parentID);
    FSDir(const FSEntry& other);
    FSDir(const FSEntry* other);
    ~FSDir();

    /**
     * @brief   Get a string describiong the members of this directory recursively
     * @param   depth       The starting depth
     */
    std::string getRecMembersString(size_t depth = 1);

    /**
     * @brief   All the Members of this directory
     */
    std::deque<FSEntry*>    members;
};

#endif
