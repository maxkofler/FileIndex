#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "directory.h"

#include <list>
#include <string>
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

	/**
	 * @brief	Checks if the supplied path is a directory
	 * @param	path						The path to check
	 * @param	isCritical					If a fs error should throw an exception (depends on _failOnError too, default: true)
	 */
	bool									isDirectory(std::string path, bool isCritical = true);

	/**
	 * @brief	Checks if the supplied path is a symlink
	 * @param	path						The path to check
	 * @param	isCritical					If a fs error should throw an exception (depends on _failOnError too, default: true)
	 */
	bool									isSymlink(std::string path, bool isCritical = true);

private:
	Directory*								_rootDir;

	bool									_failOnError = false;

	void									iterate(Directory* dir);

};

#endif