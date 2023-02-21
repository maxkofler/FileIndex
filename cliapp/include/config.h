#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

typedef struct config_s {
	bool				ok = false;
	uint8_t				verbosity = 0;
	std::string			indexPath = "./";
	std::string			databasePath = "fs.sql";
} config_t;

/**
 * @brief	Parses the supplied CLI arguments to the resulting congfig_t
 * @param	argc		The argument count
 * @param	argv		The vector of arguments supplied
 * @return	config_t	The parsed config
 */
config_t parseFromCLI(int argc, char** argv);

/**
 * @brief	Apply the supplied configuration
 * @param	conf		The config to apply
 */
void applyConfig(config_t conf);

#endif
