#ifndef __FSTYPES_H__
#define __FSTYPES_H__

/**
 * @brief	The base filesystem entry for the different filesystem types
 */
typedef struct fsentry_s {
    bool				isDir;
    size_t				nameID;
    size_t				parentID;
} __attribute__((packed)) fs_entry;

/**
 * @brief	An internal representation of a file in a filesystem tree
 */
typedef struct s_fs_file : public fsentry_s{
    s_fs_file(){
        isDir = false;
    }
} __attribute__((packed)) fs_file;

/**
 * @brief	An internal representation of a directory in a filesystem tree
 */
typedef struct s_fs_dir : public fsentry_s{
    s_fs_dir(){
        isDir = true;
    }
} __attribute__((packed)) fs_dir;

#endif
