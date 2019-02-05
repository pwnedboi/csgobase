/*      FrameStage.cpp
 *
 *
 *
 */

#include "main.h"

void FrameStage_hk(void* thisptr, ClientFrameStage_t curStage)
{
    IMPL_HOOK("FrameStageNotify");
    
    if(!Global::localplayer)
        Global::localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!Global::localWeapon && Global::localplayer)
        Global::localWeapon = GetActiveWeapon(Global::localplayer);
    
    
    
    if(Global::localplayer)
    {
        // Run features
    }
    
    
    
    clientVMT->GetOriginalMethod<oFrameStage>(FrameStageIndex)(thisptr, curStage);
}
