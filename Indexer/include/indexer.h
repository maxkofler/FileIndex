#ifndef __INDEXER_H__
#define __INDEXER_H__

#include <list>
#include <string>
#include <filesystem>

class Indexer{

public:
	Indexer();

	/**
	 * @brief	Indexes the supplied directory
	 * @param	directory					The directory to index
	 * @param	failOnError					Whether to fail on error or not (default: true)
	 */
	bool									index(std::string directory, bool failOnError = true);

	/**
	 * @brief	Clears the entries contained
	 */
	void									clear();

private:
	std::list<std::string>					_entries;

	bool									_failOnError = false;

	void									iterate(std::filesystem::directory_entry entry);

};

#endif