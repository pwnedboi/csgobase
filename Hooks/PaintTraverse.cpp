/*      PaintTraverse.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"


void PaintTraverse_hk(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce) {
    IMPL_HOOK("PaintTraverse");
    
    if(set.vis.noscope && !strcmp("HudZoom", pPanel->GetName(thisPanel)))
        return;
    paintVMT->GetOriginalMethod<oPaintTraverse>(PaintTraverseIndex)(thisptr, thisPanel, forceRepaint, allowForce);
    static VPANEL lastPanel = 0;
    
    if(!lastPanel) {
        if(strstr(pPanel->GetName(thisPanel), "FocusOverlayPanel")) {
            render->InitialiseFonts();
            lastPanel = thisPanel;
        }
    }
    
    if(thisPanel == lastPanel) {
        if(Global::localplayer) {
            visuals->drawPlayerESP();
            visuals->drawScopeLine();
            visuals->drawCrosshair();
        }
    }    
}
