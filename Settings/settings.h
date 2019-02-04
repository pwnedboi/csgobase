/*
 *  settings.h
 */
#pragma once

#include "imgui.h" // ImVec4

struct C_Settings
{
    bool menu = false;
    
    struct
    {
        
    }aimbot;
    
    struct
    {
        bool enabled = true;
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
    
    struct
    {
        bool checkbox = false;
        int islider = 0;
        float fslider = 0.f;
    }test;
};
