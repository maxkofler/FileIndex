#ifndef __FSCRATE_H__
#define __FSCRATE_H__

#include <stdint.h>

#include "fstypes.h"

/**
 * @brief	A crate holding all fsentries with the same name
 */
typedef struct s_fs_crate {
	uint32_t	count;
	fs_entry**	entries = nullptr;
} fs_crate;

/**
 * @brief	Expands the supplied crate by the specified amount of entries
 * @param	crate		The crate to expand
 * @param	amount		The amount of entries to make space for
 * @return	uint32_t	The new size of the crate, 0 on failure
 */
uint32_t 	FSCrate_expand(fs_crate* crate, uint32_t amount = 1);

/**
 * @brief	Adds the supplied fs_entry to the supplied crate
 * @param	crate		The crate that the new entry gets added to
 * @param	entry		The new entry to add
 * @return	uint32_t	The new size of the crate, 0 on failure
 */
uint32_t	FSCrate_add(fs_crate* crate, fs_entry* entry);

/**
 * @brief	Adds the supplied array of fs_entries to the supplied crate
 * @param	crate		The crate that the new entries get added to
 * @param	entries		A pointer to an array containing the new entries to add
 * @param	amount		The amount of new entries to add
 * @return	uint32_t	The new size of the crate, 0 on failure
 */
uint32_t	FSCrate_add(fs_crate* crate, fs_entry** entries, uint32_t amount);

#endif
