#include "log.h"
#include "config.h"

void applyConfig(config_t conf){
	FUN();

	switch(conf.verbosity){
	case 0:
		hlog->setLevel(Log::U);
		break;

	case 1:
		LOGU("Using verbose logging");
		hlog->setLevel(Log::I);
		break;

	case 2:
		LOGU("Using superverbose logging");
		hlog->setLevel(Log::D);
		break;

	case 3:
		LOGU("Using ultraverbose logging");
		hlog->setLevel(Log::MEM);
		break;

	default:
		LOGUE("Invalid verbosity " + std::to_string(conf.verbosity) + "/{0, 1, 2, 3}");
	}
}
