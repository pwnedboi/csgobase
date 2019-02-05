#pragma once

typedef void(*oPaintTraverse)   (void*, VPANEL panel, bool forceRepaint, bool allowForce);
typedef bool(*oCreateMove)      (void*, float flSampleInput, CUserCmd* cmd);
typedef int (*oKeyEvent)        (void*, int, int, const char*);
typedef void(*oLockCursor)      (void*);
typedef void(*oFrameStage)      (void*, ClientFrameStage_t);
typedef void(*oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);


bool CreateMove_hk(void* thisptr, float flSampleInput, CUserCmd* cmd);
void PaintTraverse_hk(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce);
void FrameStage_hk(void* thisptr, ClientFrameStage_t curStage);
void DrawModelExecute_hk(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld);
int  KeyEvent_hk(void* thisptr, int eventcode, int keycode, const char* currentbinding);
void LockCursor_hk(void* thisptr);
void OpenGL_hk();

extern bool* bSendPacket;

namespace Global
{
    extern CUserCmd*     cmd;
    extern C_BasePlayer* localplayer;
    extern C_BaseCombatWeapon* localWeapon;
}

// Paint VMT
#define PaintTraverseIndex 42
// CreatmoveVMT
#define CreateMoveIndex 25
#define OverrideViewIndex 19
// ClientVMT
#define KeyEventIndex 21
#define FrameStageIndex 37
// SurfaceVMT
#define LockCursorIndex 67
// ModelVMT
#define DrawModelExecuteIndex 21
// PredVMT
#define RunCommandIndex 20
// GameEventVMT
#define FireEventClientSideIndex 36
#define FireEventIndex 9
