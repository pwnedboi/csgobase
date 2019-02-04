/*      PaintTraverse.cpp
 *
 *
 *
 */

#include "main.h"
#include "../Hacks/visuals.h"


void PaintTraverse_hk(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce) {
    IMPL_HOOK("PaintTraverse");
    if (set.visuals.enabled && !strcmp("HudZoom", pPanel->GetName(thisPanel)))
        return;
    
    paintVMT->GetOriginalMethod<oPaintTraverse>(PaintTraverseIndex)(thisptr, thisPanel, forceRepaint, allowForce);
    static VPANEL lastPanel = 0;
    
    if(!lastPanel) {
        if(strstr(pPanel->GetName(thisPanel), "FocusOverlayPanel")) {
            lastPanel = thisPanel;
        }
    }
    
    if(thisPanel == lastPanel) {
        visuals->draw_player_esp();
    }    
}
