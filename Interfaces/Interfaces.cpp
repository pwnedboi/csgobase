/*      Interfaces.cpp
 *
 *  Defines interfaces
 *
 */

#include "main.h"

ICvar*              pCvar;
IPanel*             pPanel;
ISurface*           pSurface;
IBaseClientDLL*     pClient;
IClientEntityList*  pEntList;
IVDebugOverlay*     pOverlay;
IEngineClient*      pEngine;
IVModelInfo*        pModelInfo;
IEngineTrace*       pEngineTrace;
IClientMode*        pClientMode;
CGlobalVarsBase*    pGlobals;
IInputSystem*       pInputSystem;
CInput*             pInput;
IMaterialSystem*    pMatSystem;
IVModelRender*      pModelRender;
IPrediction*        pPrediction;
IGameMovement*      pGameMovement;
IMoveHelper*        pMoveHelper;
IPhysicsSurfaceProps*pPhysics;


CMoveData*           MoveData;
SendClanTagFn        SetTag;


RandomSeedFn          RandomSeed;
RandomFloatFn         RandomFloat;
RandomFloatExpFn      RandomFloatExp;
RandomIntFn           RandomInt;
RandomGaussianFloatFn RandomGaussianFloat;


VMT* paintVMT;
VMT* createmoveVMT;
VMT* clientVMT;
VMT* modelVMT;
VMT* vguiVMT;
VMT* materialVMT;
VMT* gameeventVMT;
VMT* predictionVMT;
VMT* surfaceVMT;
