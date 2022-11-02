#ifndef __FSTYPES_H__
#define __FSTYPES_H__

#ifdef _WIN32
    #define GNU_ATTRIBUTE_PACKED
    #define WINDOWS_PACKED_START #pragma pack(push, 1)
    #define WINDOWS_PACKED_STOP #pragma pack(pop)
#else
    #define GNU_ATTRIBUTE_PACKED __attribute__((packed))
    #define WINDOWS_PACKED_START
    #define WINDOWS_PACKED_STOP
#endif

WINDOWS_PACKED_START

/**
 * @brief	The base filesystem entry for the different filesystem types
 */
typedef struct fsentry_s {
    bool				isDir;
    size_t				nameID;
    size_t				parentID;
} GNU_ATTRIBUTE_PACKED fs_entry;

/**
 * @brief	An internal representation of a file in a filesystem tree
 */
typedef struct s_fs_file : public fsentry_s{
    s_fs_file(){
        isDir = false;
    }
} GNU_ATTRIBUTE_PACKED fs_file;

/**
 * @brief	An internal representation of a directory in a filesystem tree
 */
typedef struct s_fs_dir : public fsentry_s{
    s_fs_dir(){
        isDir = true;
    }
} GNU_ATTRIBUTE_PACKED fs_dir;

WINDOWS_PACKED_STOP

/**
 * @brief   Returns information about the fs_entry in string form
 * @param   entry       The entry to inform about
 */
std::string fs_entry_str(fs_entry& entry);

#endif
