/*      PaintTraverse.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"


void PaintTraverse_hk(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce) {
    IMPL_HOOK("PaintTraverse");
    paintVMT->GetOriginalMethod<oPaintTraverse>(PaintTraverseIndex)(thisptr, thisPanel, forceRepaint, allowForce);
    static VPANEL lastPanel = 0;
    
    if(!lastPanel) {
        if(strstr(pPanel->GetName(thisPanel), "FocusOverlayPanel")) {
            lastPanel = thisPanel;
        }
    }
    
    if(thisPanel == lastPanel) {
        //visuals->draw_player_esp();
    }    
}
