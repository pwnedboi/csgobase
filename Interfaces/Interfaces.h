// =============== Interfaces.h =============== \\
//
//  - For defining interfaces
//
#pragma once

extern ICvar*               pCvar;
extern IPanel*              pPanel;
extern ISurface*            pSurface;
extern IBaseClientDLL*      pClient;
extern IClientEntityList*   pEntList;
extern IVDebugOverlay*      pOverlay;
extern IEngineClient*       pEngine;
extern IVModelInfo*         pModelInfo;
extern IEngineTrace*        pEngineTrace;
extern IClientMode*         pClientMode;
extern CGlobalVarsBase*     pGlobals;
extern IInputSystem*        pInputSystem;
extern CInput*              pInput;
extern IMaterialSystem*     pMatSystem;
extern IVModelRender*       pModelRender;
extern IPrediction*         pPrediction;
extern IGameMovement*       pGameMovement;
extern IMoveHelper*         pMoveHelper;
extern IPhysicsSurfaceProps*pPhysics;



extern CMoveData*           MoveData;
extern SendClanTagFn        SetTag;


extern RandomSeedFn         RandomSeed;
extern RandomFloatFn        RandomFloat;
extern RandomFloatExpFn     RandomFloatExp;
extern RandomIntFn          RandomInt;
extern RandomGaussianFloatFn RandomGaussianFloat;


extern VMT* paintVMT;
extern VMT* createmoveVMT;
extern VMT* clientVMT;
extern VMT* modelVMT;
extern VMT* vguiVMT;
extern VMT* materialVMT;
extern VMT* gameeventVMT;
extern VMT* predictionVMT;
extern VMT* surfaceVMT;
