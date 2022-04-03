#include "CustomObj.h"


// ========================================
// ======= Static Func Definitions ========
// ========================================

enum{
	
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + OBJ_MOKHA_VRAMOFF
	OBJ_MOKHA_VRAMOFF = 0x4800, 
	
	// Real Palette index: OBJ_MOKHA_PAL + 0x10
	OBJ_MOKHA_PAL = 0x3,
	
	
	// Obj config
	OBJ_MOKHA_XPOS = 0x6 * 0x10,
	OBJ_MOKHA_YPOS = 0x18 * 0x10,
};



static void ProcObjMokha_OnDraw(struct Proc_CustomObj* proc);
static void ProcObjMokha_OnUpdate(struct Proc_CustomObj* proc);





// ========================================
// ================ Main ==================
// ========================================


const static struct ProcCmd gProc_ObjMokha[] = {
	
	PROC_NAME	("FE8U_CUSTOM_OBJ"),

	PROC_CALL	(ProcObjMokha_OnDraw),
	PROC_REPEAT	(ProcObjMokha_OnUpdate),
	
	PROC_END,
	
};



void ProcObjMokha_OnDraw(struct Proc_CustomObj* proc){
	
	extern u16 Gfx_ObjMokha[];
	extern u16 Pal_ObjMokha[];
	
	// Gfx
	CopyDataWithPossibleUncomp( Gfx_ObjMokha, OBJ_VRAM0 + OBJ_MOKHA_VRAMOFF ); 
	
	// Pal
	ApplyPalettes(Pal_ObjMokha, OBJ_MOKHA_PAL + 0x10, 1);
	
	// Init timer
	proc->timer = 0;
	
}



void ProcObjMokha_OnUpdate(struct Proc_CustomObj* proc){
	
	
	
	proc->timer++;
	
	// for Obj blinking
	if( (proc->timer & 0x3F) < 0x20 )
		return;
	
	PutSprite(
		4, 
		OBJ_MOKHA_XPOS, 
		OBJ_MOKHA_YPOS,
		gObject_32x16, 
		OAM2_PAL(OBJ_MOKHA_PAL) + OAM2_LAYER(0b00) + OAM2_CHR(OBJ_MOKHA_VRAMOFF / 0x20));
		
	PutSprite(
		4, 
		OBJ_MOKHA_XPOS + 0x20, 
		OBJ_MOKHA_YPOS, 
		gObject_32x16, 
		OAM2_PAL(OBJ_MOKHA_PAL) + OAM2_LAYER(0b00) + OAM2_CHR(OBJ_MOKHA_VRAMOFF / 0x20 + 4));
		
	// pal: (pal << 12) & 0xF000
	// VRAM-offset: (offset & 0x3FF) * 0x20 + 0x6010000
	
	// for example: 
	// if par4 = 0xA440;
	
	// then pal-off = (0xA440 & 0xF000) >> 12 = 0xA, 
	// palette = 0x10 + 0xA = 0x1A;
	
	// VRAM-off = 0xA440 & 0x3FF = 0x40;
	// real VRAM dest = 0x06010000 + 0x40 * 0x20 = 0x6010800
	
		
}



// =======================================================
// ====================== GLOBAL =========================
// =======================================================

void StartProc_ObjMokha(ProcPtr parent){
	
	if( NULL == Proc_Find(gProc_ObjMokha) )
		Proc_Start(gProc_ObjMokha, parent);
	
}

void EndProc_ObjMokha(){
	
	Proc_EndEach(gProc_ObjMokha);
	
}
