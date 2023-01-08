#ifndef __FSTYPES_H__
#define __FSTYPES_H__

#include <stdint.h>
#include <string>
#include <deque>
#include <iostream>
#include <memory>

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
std::string fs_entry_str(const fs_entry& entry);

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

class FSDir;

class FSEntry{
public:
    FSEntry(FSDir* parent, std::string isDir, std::string id, std::string name, std::string nameID, std::string parentID);
    FSEntry(FSDir* parent, bool isDir, uint64_t id, const std::string& name, uint64_t nameID, uint64_t parentID);

    /**
     * @brief   Returns a shared_ptr to the child with the id, else nullptr
     * @param   id              The if of the child
     */
    std::shared_ptr<FSEntry>    child(size_t id);

    /**
     * @brief   Returns the amount of children this FSEntry has, if this is a FSDir, else 0
     */
    size_t                      childCount();

    /**
     * @brief   Returns the index this FSEntry is in its parent, else 0
     */
    size_t                      childNumber();

    bool                        isDir;
    uint64_t                    id;
    std::string                 name;
    uint64_t                    nameID;
    FSDir*                      parent;
    uint64_t                    parentID;
};

class FSDir : public FSEntry{
public:
    FSDir(FSDir* parent, std::string id, std::string name, std::string nameID, std::string parentID);
    FSDir(const FSEntry& other);
    FSDir(const FSEntry* other);

    /**
     * @brief   Get a string describiong the children of this directory recursively
     * @param   depth           The starting depth
     */
    std::string                 getRecChildrenString(size_t depth = 1);

    /**
     * @brief   Sorts all the children of all subdirectories alphabetically
     */
    void                        sortChildrenRec();

    /**
     * @brief   All the children of this directory
     */
    std::deque<std::shared_ptr<FSEntry>> children;
};

#endif
