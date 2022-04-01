#include "CustomObj.h"

void AtMenuEnd_8096294(ProcPtr proc){
	
	extern void sub_8096294(ProcPtr);
	
	EndProc_CustomObj();
	sub_8096294(proc);
}