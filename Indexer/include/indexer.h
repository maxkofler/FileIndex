#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "directory.h"

#include <list>
#include <string>
#include <filesystem>
#include <ostream>

class Indexer{

public:
	/**
	 * @brief	Contructor
	 * @param	rootDir						The root directory filesystem entry
	 */
	Indexer(Directory* rootDir);

	/**
	 * @brief	Indexes the supplied directory
	 * @param	failOnError					Whether to fail on error or not (default: true)
	 */
	bool									index(bool failOnError = true);

private:
	Directory*								_curDir;

	bool									_failOnError = false;

	void									iterate(std::filesystem::directory_entry entry);

};

#endif