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
    }visuals;
    
    struct CMisc
    {
        
    }misc;
    
    struct CColors
    {
        ImVec4 box;
    }colors;
    
    struct CKeys
    {
        
    }keys;
    
};

extern CSettings set;
