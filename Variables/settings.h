/*
 *  settings.h
 */
#pragma once

#include "imgui.h" // ImVec4

struct CSettings
{
    bool menu = false;
    
    struct CCombo
    {
        
    }combo;
    
    struct CAimbot
    {
        
    }aimbot;
    
    struct CVisuals
    {
        bool enabled = false;
        bool box = false;
        bool name = false;
        // Misc
        bool noscope = false;
        bool crosshair = false;
        int crosshairlength = 0;
    }vis;
    
    struct CMisc
    {
        
    }misc;
    
    struct CColors
    {
        ImVec4 box;
        ImVec4 box_ign;
        ImVec4 crosshair;
    }colors;
    
    struct CKeys
    {
        
    }keys;
    
};

extern CSettings set;
