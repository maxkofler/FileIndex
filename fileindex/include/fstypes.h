#ifndef __FSTYPES_H__
#define __FSTYPES_H__

#ifdef _WIN32
    #define GNU_ATTRIBUTE_PACKED
#else
    #define GNU_ATTRIBUTE_PACKED __attribute__((packed))
#endif

#ifdef _WIN32
	#pragma pack(push, 1)
#endif
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

#ifdef _WIN32
	#pragma pack(pop)
#endif

/**
 * @brief   Returns information about the fs_entry in string form
 * @param   entry       The entry to inform about
 */
std::string fs_entry_str(fs_entry& entry);

#endif
