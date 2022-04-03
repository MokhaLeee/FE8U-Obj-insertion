// =================================
// C-Lib: https://github.com/MokhaLeee/FE-CLib-Mokha.git

#include "gbafe.h"
// =================================

struct Proc_CustomObj{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 timer;
	
};


// Debug
void Debug_OnPutTestObjs(ProcPtr);
void Debug_OnRemoveTestObjs();


// Obj "Mokha"
void StartProc_ObjMokha(ProcPtr);
void EndProc_ObjMokha();


// Obj Window
void Draw_ObjWindow(ProcPtr);
void Remove_ObjMokha();
