#ifndef __INDEXER_H__
#define __INDEXER_H__

#include <list>
#include <string>
#include <filesystem>
#include <ostream>

class Indexer{

public:
	/**
	 * @brief	Contructor
	 * @param	out							An output stream to write the files to line by line
	 */
	Indexer(std::ostream& out);

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
	std::ostream&							_out;
	std::list<std::string>					_entries;

	bool									_failOnError = false;

	void									iterate(std::filesystem::directory_entry entry);

};

#endif