/*      KeyEvent.cpp
 *
 *
 *
 *
 */
#include "main.h"
#include "menu.h"

enum
{
    PRESSED  = 0,
    RELEASED = 1,
};

int KeyEvent_hk(void* thisptr, int eventCode, int keycode, const char* curBinding)
{
    IMPL_HOOK("KeyEvent");
    
    if(eventCode == PRESSED)
    {
        if(keycode == KEY_INSERT || keycode == KEY_LCONTROL)
        {
            set.menu = !set.menu;
            pEngine->ExecuteClientCmd(string("cl_mouseenable " + to_string(!set.menu)).c_str());
        }
    }
    
    
    if(eventCode == RELEASED)
    {
        
    }
    
    
    return clientVMT->GetOriginalMethod<oKeyEvent>(20)(thisptr, eventCode, keycode, curBinding);
}





