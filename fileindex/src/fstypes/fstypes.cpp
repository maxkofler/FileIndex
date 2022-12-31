#include <string>
#include "fstypes.h"

std::string fs_entry_str(fs_entry& entry){
	return 	"DIR=" + std::to_string(entry.isDir) +
			" id=" + std::to_string(entry.id) +
			" name=" + entry.name +
			" nameID=" + std::to_string(entry.nameID) +
			" parentID=" + std::to_string(entry.parentID);
}

fs_entry fs_entry_parse(std::string isDir, std::string id, std::string name, std::string nameID, std::string parentID){
	fs_entry e;

	e.isDir = std::stoi(isDir);
	e.id = std::stoi(id);
	e.name = name;
	e.nameID = std::stoi(nameID);
	e.parentID = std::stoi(parentID);

	return e;
}
