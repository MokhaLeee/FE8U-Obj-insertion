#include "CustomObj.h"


// ========================================
// ======= Static Func Definitions ========
// ========================================

enum{
	
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + CUSTOME_OBJ_VRAMOFF
	CUSTOME_OBJ_VRAMOFF = 0x4800, 
	
	// Real Palette index: CUSTOME_OBJ_PALID + 0x10
	CUSTOME_OBJ_PALID = 0x3,
};


struct Proc_CustomObj{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 timer;
	
};


static void ProcCustomObj_OnDraw(struct Proc_CustomObj* proc);
static void ProcCustomObj_OnUpdate(struct Proc_CustomObj* proc);





// ========================================
// ================ Main ==================
// ========================================


const static struct ProcCmd gProc_PrepSkillPutObj[] = {
	
	PROC_NAME	("FE8U_CUSTOM_OBJ"),

	PROC_CALL	(ProcCustomObj_OnDraw),
	PROC_REPEAT	(ProcCustomObj_OnUpdate),
	
	PROC_END,
	
};



void ProcCustomObj_OnDraw(struct Proc_CustomObj* proc){
	
	extern u16 Gfx_ObjGfx[];
	extern u16 Pal_ObjGfx[];
	
	// Gfx
	CopyDataWithPossibleUncomp( Gfx_ObjGfx, OBJ_VRAM0 + CUSTOME_OBJ_VRAMOFF ); 
	
	// Pal
	ApplyPalettes(Pal_ObjGfx, CUSTOME_OBJ_PALID + 0x10, 1);
	
	// Init timer
	proc->timer = 0;
	
}



void ProcCustomObj_OnUpdate(struct Proc_CustomObj* proc){
	
	
	
	proc->timer++;
	
	// for Obj blinking
	if( (proc->timer & 0x3F) < 0x20 )
		return;
	
	PutSprite(
		4, 
		0x6 * 0x10, 
		0x18 * 0x10, 
		gObject_32x16, 
		OAM2_PAL(CUSTOME_OBJ_PALID) + CUSTOME_OBJ_VRAMOFF / 0x20);
		
	PutSprite(
		4, 
		0x8 * 0x10, 
		0x18 * 0x10, 
		gObject_32x16, 
		OAM2_PAL(CUSTOME_OBJ_PALID) + CUSTOME_OBJ_VRAMOFF / 0x20 + 4);
	
	
}



// =======================================================
// ====================== GLOBAL =========================
// =======================================================

void StartProc_CustomObj(ProcPtr parent){
	
	if( NULL == Proc_Find(gProc_PrepSkillPutObj) )
		Proc_Start(gProc_PrepSkillPutObj, parent);
	
}

void EndProc_CustomObj(){
	
	Proc_EndEach(gProc_PrepSkillPutObj);
	
}
