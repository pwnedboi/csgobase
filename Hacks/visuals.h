/*
 *  visuals.h
 */
#pragma once

class C_Visuals
{
private:
    
    void draw_esp_box(int x, int y, int w, int h, ImColor col);
    
public:
    
    void draw_player_esp();
    
};

extern C_Visuals* visuals;
