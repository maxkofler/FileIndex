#include "log.h"
#include "fsError.h"

FSError::FSError(std::string cause){
	_cause = cause;
}

std::string FSError::what(){
	return _cause;
}
