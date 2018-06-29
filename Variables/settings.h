/*
 *  settings.h
 */
#pragma once

#include "imgui.h" // ImVec4

struct CSettings
{
    bool menu = false;
    
    struct
    {
        
    }aimbot;
    
    struct
    {
        bool enabled = false;
    }visuals;
    
    struct
    {
        
    }misc;
    
    struct
    {
        ImVec4 box;
    }colors;
    
    struct
    {
        
    }keys;
    
};

extern CSettings set;
