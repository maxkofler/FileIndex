#ifndef __FS_ERROR_H__
#define __FS_ERROR_H__

#include "error.h"

#include <system_error>

class FSError : public Error{

public:
	FSError(std::string cause);

	std::string 			what();

private:
	std::string				_cause;

};

#endif