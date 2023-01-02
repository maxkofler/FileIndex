#ifndef __SQL_H__
#define __SQL_H__

#include <string>
#include <deque>
#include <mutex>

#ifdef SQLITE_VERSION
	#define SQL_TYPE sqlite3
#else
	#define SQL_TYPE void
#endif

struct SQL_res{
	int										code;
	std::deque<std::deque<std::string>>		result;
};

class SQL{

public:
	SQL(std::string sqlFile = "");
	~SQL();

	/**
	 * @brief	Executes an SQL command, false is returnes on error
	 * @param command						The command to execute
	 */
	SQL_res									exec(std::string command);

	/**
	 * @brief	Returns a string containing the last error thrown
	 */
	std::string								getError();

	/**
	 * @brief	Saves the contents of the currently loaded database into the supplied file
	 * @param	outFile						The file path to save to
	 */
	bool									save(std::string outFile);

	/**
	 * @brief	Closes the currently loaded database and loads a new one from the supplied file
	 * @param	inFile						The file to load from
	 */
	bool									load(std::string inFile);

private:
	/**
	 * @brief	The file the database lies in
	 */
	std::string								_sqlFile;

	/**
	 * @brief	The internal database
	 */
	SQL_TYPE*								_db = nullptr;

	/**
	 * @brief	The result of the last exec operation
	 */
	std::deque<std::deque<std::string>>		_sql_res;

	/**
	 * @brief	A mutex protectig the SQLite DB from simultaneous access
	 */
	std::mutex								_m_exec;

	/**
	 * @brief	The callback for the incoming data
	 * @param	argc						The amount of rows available
	 * @param	argv						The rows contents
	 * @param	rowName						The name (description) of the row
	 * @return	int
	 */
	int										sqlite3_callback(int argc, char **argv, char **rowName);

	/**
	 * @brief	The static version of the callback to call into the class callback
	 * @param	data						A pointer to the current SQL object (this)
	 * @param	argc						The amount of rows available
	 * @param	argv						The rows contents
	 * @param	rowName						The name (description) of the row
	 * @return	int
	 */
	static int								s_sqlite3_callback(void* data, int argc, char **argv, char **rowName);
};

#endif
