#include "../t_.h"

#include <fstream>

TEST(, _debug){
	FUN();

	try{
		DEBUG_FAIL_FUN("");



		F_NOTHROW(" - debug")
	} catch (DebugException* e){

	} catch (...){
		F_WRONGEXCEPTION(" - debug");
	}
}

TEST(, ){
	FUN();

}
