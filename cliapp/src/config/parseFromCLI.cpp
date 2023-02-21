#include "log.h"
#include "config.h"

#include <args.hxx>

static args::ArgumentParser parser("FileIndex CLI", "A cli tool for indexing the filesystem and doing quick lookups");

config_t parseFromCLI(int argc, char** argv){
	FUN();
	config_t conf;

	args::HelpFlag f_help(parser, "help", "Display this help menu", {'h', "help"});
	args::ValueFlag<int> f_verbosity(parser, "verbosity", "The verbosity level to use (0, 1, 2, 3)", {"verbosity", 'V'});
	args::ValueFlag<std::string> f_database(parser, "database", "The database file to use (does not have to exist)", {"database", 'd'});
	args::Positional<std::string> f_path(parser, "parse directory", "The directory path to be indexed");
	//args::Flag f_(parser, "short", "long", {'f'});
	//args::ValueFlag<std::string> f_(parser, "short", "long", {"option"});
	//args::Positional<std::string> a_(parser, "short", "long");
	//args::PositionalList<std::string> a_(parser, "short", "long");

	try{
		parser.ParseCLI(argc, argv);
	} catch (const args::Completion& e) {
		LOGE(e.what());
		conf.ok = false;
		return conf;
	} catch (const args::Help&) {
		std::cout << parser;
		conf.ok = false;
		return conf;
	} catch (const args::ParseError& e) {
		LOGE(std::string("Failed to parse options: ") + std::string(e.what()));
		std::cerr << parser;
		conf.ok = false;
		return conf;
	}

	if (f_verbosity){
		conf.verbosity = args::get(f_verbosity);
	}

	if (f_path)
		conf.indexPath = args::get(f_path);

	if (f_database)
		conf.databasePath = args::get(f_database);

	conf.ok = true;
	return conf;
}
