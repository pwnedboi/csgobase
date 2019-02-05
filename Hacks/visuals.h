/*
 *  visuals.h
 */
#pragma once

class CVisuals
{
private:
    void drawHealthBar(int x, int y, int w, int h, int health);
    void drawArmorBar();
public:

    void drawPlayerESP();
    void drawScopeLine();
    void drawCrosshair();
    
};

extern CVisuals* visuals;
