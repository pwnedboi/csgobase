/*      visuals.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"

C_Visuals* visuals = new C_Visuals();

/*
 *  draw_esp_box
 *  Draws an esp box
 */
void C_Visuals::draw_esp_box(int x, int y, int w, int h, ImColor col)
{
    /*
     *  The first 2 boxes are the border for the esp
     */
    render->draw_box(x - 1, y - 1, w + 2, h + 2, IM_COL32_BLACK);
    render->draw_box(x + 1, y + 1, w - 2, h - 2, IM_COL32_BLACK);
    render->draw_box(x, y, w, h, col);
}

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
        bool visible = is_player_visible(player);
        
        // Just an example of what to do
        ImColor col(set.colors.box);
        
                
        box_t box;
        
        if(!get_box(player, box))
            continue;
        
        // Draw the players name and heath, ect : pwned / 100
        string to_draw = string(player->GetName()) + " / " + to_string(player->GetHealth());
        render->draw_string(box.x + box.w / 2, box.y + box.h + 5, to_draw.c_str(), Fonts::small, IM_COL32_WHITE, true);
        
        this->draw_esp_box(box.x, box.y, box.w, box.h, col);
    }
}
