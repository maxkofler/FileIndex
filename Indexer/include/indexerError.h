#ifndef __INDEXER_ERROR_H__
#define __INDEXER_ERROR_H__

#include "error.h"

#include <system_error>

namespace EC{
	enum ec{
		INDEXER_NOTDIR,
	};
}

class IndexerError : public Error{

public:
	IndexerError(std::string cause);

	std::string 			what();

private:
	std::string				_cause;

};

#endif