#include "CustomObj.h"


// ========================================
// ======= Static Func Definitions ========
// ========================================

enum{
	
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + WINDOW_OBJ_VRAMOFF
	WINDOW_OBJ_VRAMOFF = 0x5000, 
	
	// Real Palette index: WINDOW_OBJ_PAL + 0x10
	WINDOW_OBJ_PAL = 0x4,
	
	
	// Window config
	WINDOW_XPOS = 0x0B * 0x8,
	WINDOW_YPOS = 0x0F * 0x8,
	WINDOW_LENGTH = 0x8,
	WINDOW_HEIGHT = 0x3,
};


static void ProcObjWindow_OnDraw(struct Proc_CustomObj* proc);
static void ProcObjWindow_OnUpdate(int x, int y, int len, int h);





// ========================================
// ================ Main ==================
// ======================================== 


void ProcObjWindow_OnDraw(struct Proc_CustomObj* proc){
	
	extern u16 Gfx_ObjWindow[];
	extern u16 Pal_ObjWindow[];
	
	CopyDataWithPossibleUncomp(Gfx_ObjWindow, OBJ_VRAM0 + WINDOW_OBJ_VRAMOFF);
	ApplyPalettes(Pal_ObjWindow, WINDOW_OBJ_PAL + 0x10, 1);
	
}
void ProcObjWindow_OnUpdate(){
	
	static void (*UpdateObjWindow)(int x, int y, int len, int h, int oma2) = (const void*) 0x809A31D;
	
	UpdateObjWindow(
		WINDOW_XPOS,
		WINDOW_YPOS,
		WINDOW_LENGTH,
		WINDOW_HEIGHT,
		OAM2_PAL(WINDOW_OBJ_PAL) +
			OAM2_LAYER(0b01)+
			OAM2_CHR(WINDOW_OBJ_VRAMOFF / 0x20)
	);
	
}



// =======================================================
// ====================== GLOBAL =========================
// =======================================================

void Draw_ObjWindow(ProcPtr proc){
	
	extern void StartParallelWorker(void* func, ProcPtr);
	
	ProcObjWindow_OnDraw(proc);
	
	StartParallelWorker(ProcObjWindow_OnUpdate, proc);
	
}

void Remove_ObjMokha(){
	
	extern ProcPtr GetParallelWorker(void* func);
	
	Proc_End( GetParallelWorker(ProcObjWindow_OnUpdate) );
	
}

