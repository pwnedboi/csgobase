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

int KeyEvent_hk(void* thisptr, int event_code, int keycode, const char* cur_binding)
{
    IMPL_HOOK("KeyEvent");
    
    if(event_code == PRESSED)
    {
        if(keycode == KEY_INSERT || keycode == KEY_LALT || keycode == KEY_RALT)
        {
            set.menu = !set.menu;
            pInputSystem->EnableInput(!set.menu);
        }
    }
    
    
    if(event_code == RELEASED)
    {
        
    }
    
    
    return clientVMT->GetOriginalMethod<oKeyEvent>(21)(thisptr, event_code, keycode, cur_binding);
}





