#include <string>
#include "fstypes.h"

std::string fs_entry_str(fs_entry& entry){
	return "DIR=" + std::to_string(entry.isDir) + " nameID=" + std::to_string(entry.nameID) + " parentID=" + std::to_string(entry.parentID);
}
