/*      macOS CS:GO base
 *         pwned#5530
 *
 *
 *  Notes
 *  - Use osxinj to inject
 *  - IMPL_HOOK just prints "hook_name hooked" to console
 *  - The print() function prints to console, args : string, color = Pastel pink, prefix = "debug"
 *
 *
 *
 *
 *
 *
 */

#include "main.h"
#include "Interfaces/Hooker.h"


namespace Global
{
    CUserCmd*     cmd;
    C_BasePlayer* localplayer;
    C_BaseCombatWeapon* localWeapon;
}


int __attribute__((constructor)) Init()
{
    init_interfaces();
    
    init_hooks();
    
    hook_functions();
    
    get_offsets();
    
    init_settings();
    
    return EXIT_SUCCESS;
}
