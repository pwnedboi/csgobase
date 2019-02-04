/*      glHook.cpp
 *
 *
 *
 */

#include "main.h"
#include "util_sdl.h"

#include "menu.h"
#include "visuals.h"

#include "imgui.h"
#include "imgui_impl_sdl_gl2.h"

uintptr_t  oSwapWindow = NULL;
uintptr_t* pSwapWindow = nullptr;

void SwapWindow_hk(SDL_Window* window)
{
    static SDL_GLContext context = NULL;
    static void (*oSDL_GL_SwapWindow)(SDL_Window*)= reinterpret_cast<void (*)(SDL_Window*)>(oSwapWindow);
    static SDL_GLContext original_context = SDL_GL_GetCurrentContext();
    
    if(!context)
    {
        context = SDL_GL_CreateContext(window);
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplSdlGL2_Init(window);
        
        /*
         *  Init the menu
         */
        menu->init();
        
        /*
         *  Init the fonts
         */
        render->init_fonts();
    }
    
    SDL_GL_MakeCurrent(window, context);
    
    /*
     *  Disable vsync
     */
    if(SDL_GL_SetSwapInterval(0) < 0)
        print("Unable to disable vsync!");
    
    ImGui_ImplSdlGL2_NewFrame(window);
    
    
    /*
     *  Draw everything between start and finish
     */
    render->start();
    
    
    /*
     *  Should probably use pEngine->IsInGame
     */
    if(pEngine->IsInGame())
    {
        if(set.visuals.enabled) // Might need to remove
        visuals->draw_player_esp();
        
    }
    
    render->finish();
    
    
    /*
     *  Draw the menu
     */
    if(set.menu)
        menu->display();
    
    /*
     *  Draw the mouse
     */
    static ImGuiIO& io = ImGui::GetIO();
    io.MouseDrawCursor = set.menu;

    
    
    ImGui::Render();
    ImGui_ImplSdlGL2_RenderDrawData(ImGui::GetDrawData());
    
    
    
    oSDL_GL_SwapWindow(window);
    SDL_GL_MakeCurrent(window, original_context);
    glFlush();
}

void OpenGL_hk()
{
    GLHelper::module mod("libSDL2-2.0.0.dylib");
    
    uintptr_t SwapWindowFn  = reinterpret_cast<uintptr_t>(dlsym(RTLD_DEFAULT, "SDL_GL_SwapWindow"));
    uintptr_t sdl_lib       = reinterpret_cast<uintptr_t>(mod.start());
    pSwapWindow             = reinterpret_cast<uintptr_t*>(GLHelper::get_absolue_address(sdl_lib, SwapWindowFn, 0xF, 0x4));
    oSwapWindow             = *pSwapWindow;
    *pSwapWindow            = reinterpret_cast<uintptr_t>(&SwapWindow_hk);
}
