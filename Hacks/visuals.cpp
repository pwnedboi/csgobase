/*      visuals.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"

CVisuals* visuals = new CVisuals();

void CVisuals::drawCrosshair() {
    if(!set.vis.crosshair || !Global::localplayer || (Global::localplayer && Global::localplayer->IsScoped()))
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    int cx = w / 2;
    int cy = h / 2;
    int length = set.vis.crosshairlength;
    Color col = ImVecToColor(set.colors.crosshair);
    
    render->drawLine(cx - length, cy, cx + length, cy, col);
    render->drawLine(cx, cy - length, cx, cy + length, col);
}

void CVisuals::drawScopeLine() {
    if(!set.vis.noscope || !Global::localplayer || (Global::localplayer && !Global::localplayer->IsScoped()))
        return;
    
    if(*Global::localWeapon->GetItemDefinitionIndex() == WEAPON_AUG || *Global::localWeapon->GetItemDefinitionIndex() == WEAPON_SG556)
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    render->drawLine(w / 2, 0, w / 2, h, Color::Black());
    render->drawLine(0, h / 2, w, h / 2, Color::Black());
    
}

void CVisuals::drawHealthBar(int x, int y, int w, int h, int health) {
    int Red = 255 - (health*2.55);
    int Green = health*2.55;
    
    int hw = h - ((h) * health) / 100;
    render->drawBoxFilled(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    render->drawBoxFilled(x, y + hw - 1, w, h - hw + 2, Color(Red, Green, 0, 180));
    render->drawBoxOutline(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
}

void CVisuals::drawPlayerESP() {
    if(!set.vis.enabled)
        return;
    
    for(int i = 0; i < 64; i++) {
        C_BasePlayer* player = (C_BasePlayer*)pEntList->GetClientEntity(i);
        
        if(!player)
            continue;
        if(player->IsPlayer())
            continue;
        if(!player->IsAlive())
            continue;
        if(player->IsDormant())
            continue;
        if(player->GetTeam() != 2 && player->GetTeam() != 3)
            continue;
        
        bool visible = IsPlayerVisible(player);
        
        Color col = [&]() -> Color {
            if(player->GetTeam() == 3)
                return visible ? ImVecToColor(set.colors.box) : ImVecToColor(set.colors.box_ign);
            else if(player->GetTeam() == 2)
                return visible ? ImVecToColor(set.colors.box) : ImVecToColor(set.colors.box_ign);
        }();
        
        box_t box;
        
        if(get_box(player, box)) {
            if(set.vis.box) {
            render->drawBoxOutline(box.x, box.y, box.w, box.h, col);
                if(set.vis.name) {
            string to_draw = string(player->GetName()) + " / " + to_string(player->GetHealth());
            render->drawString(box.x + box.w / 2, box.y + box.h + 5, Color::White(), espfont, to_draw.c_str(), true);
                }
            }
        }
    }
}
