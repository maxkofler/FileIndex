#include "log.h"
#include "fs.h"
#include "fsError.h"

#include <filesystem>

bool FS::is(entry_type type, std::string path, bool isCritical){
	FUN();

	std::error_code ec;
	bool isTrue = false;

	switch (type){
	case ENTRY_DIRECTORY:
		isTrue = std::filesystem::is_directory(path, ec);
		break;

	case ENTRY_SYMLINK:
		isTrue = std::filesystem::is_symlink(path, ec);
		break;

	default:
		if (isCritical)
			throw new FSError("Tried to determine unknown fs entry type");

		LOGE("Tried to determine unknown fs entry type");
		return false;
	}

	if (ec){
		if (isCritical)
			throw new FSError("FS error while checking " + path + ": " + ec.message());
		else
			LOGE("FS error while checking " + path + ": " + ec.message());
	}

	return isTrue;
}
