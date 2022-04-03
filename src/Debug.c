#include "CustomObj.h"


void Debug_OnPutTestObjs(ProcPtr proc){
	
	StartProc_ObjMokha(proc);
	Draw_ObjWindow(proc);
	
}


void Debug_OnRemoveTestObjs(){
	
	EndProc_ObjMokha();
	Remove_ObjMokha();
	
}
