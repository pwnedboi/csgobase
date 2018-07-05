/*      visuals.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"

C_Visuals* visuals = new C_Visuals();

/*
 *  draw_player_esp
 *  Draws esp and visuals for each player
 */
void C_Visuals::draw_player_esp()
{
    if(!set.visuals.enabled)
        return;
    
    for(int i = 0; i < 64; i++)
    {
        C_BasePlayer* player = (C_BasePlayer*)pEntList->GetClientEntity(i);
        
        if(!player)
            continue;
        
        if(!player->IsPlayer())
            continue;
        
        if(!player->IsAlive())
            continue;
        
        if(player->IsDormant())
            continue;
        
        int  team = player->GetTeam();
        bool visible = IsPlayerVisible(player);
        
        // Just an example of what to do
        Color col = ImVecToColor(set.colors.box);
        
                
        box_t box;
        
        if(!get_box(player, box))
            continue;
        
        // Draw the players name and heath, ect : pwned / 100
        string to_draw = string(player->GetName()) + " / " + to_string(player->GetHealth());
        render->draw_string(box.x + box.w / 2, box.y + box.h + 5, Color::White(), espfont, to_draw.c_str(), true);
        
        Vector head_out, head_pos = GetHitboxPosition(player, HITBOX_NECK);
        if(WorldToScreen(head_pos, head_out))
            render->draw_box_filled(head_pos.x, head_pos.y, 2, 2, col);
    }
}
