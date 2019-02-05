/*      CreateMove.cpp
 *
 *
 *
 */

#include "main.h"

bool CreateMove_hk(void* thisptr, float flSampleInput, CUserCmd* cmd)
{
    IMPL_HOOK("CreateMove");
    
    createmoveVMT->GetOriginalMethod<oCreateMove>(CreateMoveIndex)(thisptr, flSampleInput, cmd);
    
    if(!cmd)
        return false;
    
    if(!cmd->command_number)
        return false;
    
    if(!bSendPacket)
        return false;
    
    Global::cmd = cmd;
    
    
    // run features
    // clamp angles
    // all that
    
    
    return false;
}
