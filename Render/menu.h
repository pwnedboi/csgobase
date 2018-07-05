#pragma once

#include "main.h"

class C_Menu
{
private:
    
    enum
    {
        AIMBOT,
        VISUALS,
        MISC,
        COLOUR,
    };
    
public:
    
    void render();
    void setup_style();
    
};

extern C_Menu* menu;
