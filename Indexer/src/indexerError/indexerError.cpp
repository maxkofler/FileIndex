#include "log.h"
#include "indexerError.h"

IndexerError::IndexerError(std::string cause){
	_cause = cause;
}

std::string IndexerError::what(){
	return _cause;
}
