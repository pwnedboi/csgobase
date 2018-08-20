/*      FrameStage.cpp
 *
 *
 *
 */

#include "main.h"

void FrameStage_hk(void* thisptr, ClientFrameStage_t curStage)
{
    IMPL_HOOK("FrameStageNotify");
    
    if(!Global::local)
        Global::local = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!Global::localWeapon && Global::local)
        Global::localWeapon = get_active_weapon(Global::local);
    
    
    
    if(Global::local)
    {
        // Run features
    }
    
    
    
    clientVMT->GetOriginalMethod<oFrameStage>(36)(thisptr, curStage);
}
