#ifndef __INDEXER_ERROR_H__
#define __INDEXER_ERROR_H__

#include "error.h"

#include <system_error>

class IndexerError : public Error{

public:
	IndexerError(std::string cause);

	std::string 			what();

private:
	std::string				_cause;

};

#endif