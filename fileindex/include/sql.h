#ifndef __SQL_H__
#define __SQL_H__

#include <string>

#ifdef SQLITE_VERSION
	#define SQL_TYPE sqlite3
#else
	#define SQL_TYPE void
#endif

class SQL{

public:
	SQL(std::string sqlFile);
	~SQL();

	/**
	 * @brief	Executes an SQL command, false is returnes on error
	 * @param command		The command to execute
	 */
	bool					exec(std::string command);

	/**
	 * @brief	Returns a string containing the last error thrown
	 */
	std::string				getError();

private:
	/**
	 * @brief	The file the database lies in
	 */
	std::string				_sqlFile;

	/**
	 * @brief	The internal database
	 */
	SQL_TYPE*				_db = nullptr;

};

#endif
