#pragma once

#include "main.h"

class C_Menu
{
private:
    
    enum MenuTab
    {
        Aimbot,
        Visuals,
        Misc,
        Colors,
    };
    
    ImGuiIO     io;
    C_Renderer* draw;
    
private:
    
    void add_checkbox(int x, int y, const char* label, bool* value);
    
public:
    
    C_Menu();
    ~C_Menu();
    
    void init();
    
    void display();
    
};

extern C_Menu* menu;
