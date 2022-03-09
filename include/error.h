#ifndef __ERROR_H__
#define __ERROR_H__

class Error{

public:
	virtual std::string					what() = 0;

};

#endif