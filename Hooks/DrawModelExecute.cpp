/*      DrawModelExecute.cpp
 *
 *
 *
 */

#include "main.h"

void DrawModelExecute_hk(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld)
{
    IMPL_HOOK("DrawModelExecute");
    
    if(model_info.pModel && set.visuals.enabled)
    {
        // example of what to do
        // visuals->renderPlayerChams(thisptr, context, state, model_info, pCustomBoneToWorld);
    }
    
    modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
