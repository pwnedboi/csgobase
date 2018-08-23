/*      macOS CS:GO base
 *         pwned#5530
 *
 *
 *  Notes
 *  - Use osxinj to inject
 *  - IMPL_HOOK just prints "hook_name hooked" to console
 *  - The print() function prints to console, args : string, color = Pastel pink, prefix = "debug"
 *  - Install the fonts into /Library/Fonts/ and not ~/Library/Fonts/
 *
 *
 *
 *
 *
 */

#include "main.h"
#include "hooker.h"


int __attribute__((constructor)) main()
{
    init_interfaces();
    
    init_hooks();
    
    hook_functions();
    
    get_offsets();
    
    init_settings();
    
    return EXIT_SUCCESS;
}



