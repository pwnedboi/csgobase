/*      global.cpp
 *
 *
 *
 */

#include "main.h"

namespace Global
{
    CUserCmd*     cmd;
    C_BasePlayer* localplayer;
    C_BaseCombatWeapon* localWeapon;
}

C_Settings set;

bool* bSendPacket   = nullptr;

/*
 *  Interfaces
 */
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
CMoveData*           pMoveData;

/*
 *  Game Functions
 */
SendClanTagFn         SetTag;
RandomSeedFn          RandomSeed;
RandomFloatFn         RandomFloat;
RandomFloatExpFn      RandomFloatExp;
RandomIntFn           RandomInt;
RandomGaussianFloatFn RandomGaussianFloat;

/*
 *  VMT
 */
VMT* paintVMT;
VMT* createmoveVMT;
VMT* clientVMT;
VMT* modelVMT;
VMT* vguiVMT;
VMT* materialVMT;
VMT* gameeventVMT;
VMT* predictionVMT;
VMT* surfaceVMT;
