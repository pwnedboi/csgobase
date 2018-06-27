/*      PaintTraverse.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"


void PaintTraverse_hk(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce)
{
    IMPL_HOOK("PaintTraverse");
    
    paintVMT->GetOriginalMethod<oPaintTraverse>(42)(thisptr, thisPanel, forceRepaint, allowForce);
    static VPANEL lastPanel = 0;
    
    
    if(!lastPanel)
    {
        if(strstr(pPanel->GetName(thisPanel), "FocusOverlayPanel"))
        {
            render->InitialiseFonts();
            lastPanel = thisPanel;
        }
    }
    
    
    if(thisPanel == lastPanel)
    {
        if(Global::local)
        {
            visuals->drawPlayerESP();
        }
        
        
        render->drawString(13, 21, Color::PastelPink(), menufont, "csgobase");
    }    
}
