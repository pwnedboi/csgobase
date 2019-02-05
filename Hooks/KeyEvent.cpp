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

int KeyEvent_hk(void* thisptr, int eventCode, int keycode, const char* curBinding) {
    IMPL_HOOK("KeyEvent");
    
    if(eventCode == PRESSED) {
        if(keycode == KEY_LALT) {
            set.menu = !set.menu;
            pInputSystem->EnableInput(!set.menu);
        }
    }
    
    if(eventCode == RELEASED) {
        
    }
    
    return clientVMT->GetOriginalMethod<oKeyEvent>(KeyEventIndex)(thisptr, eventCode, keycode, curBinding);
}





