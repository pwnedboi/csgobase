/*      hooker.cpp
 *
 *  - Initialises interfaces
 *  - Initialises hooks
 *  - Initialises variables
 *
 */

#include "main.h"
#include "hooker.h"

/*
 *  init_interfaces
 *  Finds all interfaces
 */
void init_interfaces()
{
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client_panorama.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client_panorama.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pPrediction     = GetInterface<IPrediction>("./csgo/bin/osx64/client_panorama.dylib", "VClientPrediction");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client_panorama.dylib", "GameMovement");
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
}

/*
 *
 *
 */
void protect_addr(void* addr, int prot)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void*)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

/*
 *  init_hooks
 *  Finds pointers then initiliases VMT's and game functions
 */
void init_hooks()
{
    C_PatternScanner* scanner = C_PatternScanner::get();
    uintptr_t clientModePtr = scanner->get_pointer("client_panorama.dylib",(Byte*)CLIENTMODE_SIG, CLIENTMODE_MASK, 0xA) + 0x4;
    uintptr_t globalVarsPtr = scanner->get_pointer("client_panorama.dylib",(Byte*)GLOBALS_SIG, GLOBALS_MASK, 0x3) + 0x4;
    uintptr_t clanTagPtr    = scanner->get_pointer("engine.dylib",(Byte*)CLANTAG_SIG, CLANTAG_MASK, 0xB) + 0x4;
    uintptr_t sendPacketPtr = scanner->get_procedure("engine.dylib",(Byte*)SENDPACKET_SIG, SENDPACKET_MASK, 0x1) + 0x2;
    
    
    bSendPacket = reinterpret_cast<bool*>(sendPacketPtr);
    protect_addr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
    
    
    void* handle        = dlopen("./csgo/bin/osx64/client_panorama.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomSeed          = reinterpret_cast<RandomSeedFn>         (dlsym(handle, "RandomSeed"));
    RandomInt           = reinterpret_cast<RandomIntFn>          (dlsym(handle, "RandomInt"));
    RandomFloat         = reinterpret_cast<RandomFloatFn>        (dlsym(handle, "RandomFloat"));
    RandomFloatExp      = reinterpret_cast<RandomFloatExpFn>     (dlsym(handle, "RandomFloatExp"));
    RandomGaussianFloat = reinterpret_cast<RandomGaussianFloatFn>(dlsym(handle, "RandomGaussianFloat"));
    dlclose(handle);
    
    
    SetTag          = reinterpret_cast<SendClanTagFn>(clanTagPtr);
    pClientMode     = reinterpret_cast<IClientMode*>(clientModePtr);
    pGlobals        = *reinterpret_cast<CGlobalVarsBase**>(globalVarsPtr);
    
    
    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    surfaceVMT      = new VMT(pSurface);
    modelVMT        = new VMT(pModelRender);
    predictionVMT   = new VMT(pPrediction);
    materialVMT     = new VMT(pMatSystem);
}

/*
 *  hook_functions
 *  Applies the hooks
 */
void hook_functions()
{
    createmoveVMT->HookVM((void*)CreateMove_hk, CreateMoveIndex);
    createmoveVMT->ApplyVMT();
    
    paintVMT->HookVM((void*)PaintTraverse_hk, PaintTraverseIndex);
    paintVMT->ApplyVMT();

    clientVMT->HookVM((void*)KeyEvent_hk, KeyEventIndex);
    clientVMT->HookVM((void*)FrameStage_hk, FrameStageIndex);
    clientVMT->ApplyVMT();
    
    surfaceVMT->HookVM((void*)LockCursor_hk, LockCursorIndex);
    surfaceVMT->ApplyVMT();
    
    OpenGL_hk();
    
    print("Functions hooked", Color::Orange());
}

/*
 *  init_settings
 *  Initialises variables
 */
void init_settings()
{
    // Initialise variables here
    
    
    
}
