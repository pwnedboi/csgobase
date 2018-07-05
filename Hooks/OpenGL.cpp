/*      glHook.cpp
 *
 *
 *
 */

#include "main.h"
#include "menu.h"

#include "imgui.h"
#include "imgui_impl_sdl_gl2.h"

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>

#include <sys/types.h>
#include <mach/mach.h>
#include <mach/error.h>
#include <mach-o/dyld.h>
#include <mach/vm_types.h>
#include <mach-o/getsect.h>

namespace glHelper
{
    uintptr_t GetAbsoluteAddress( uintptr_t dwAddress, uintptr_t memoryPtr, uintptr_t startOffset, uintptr_t size)
    {
        uintptr_t signatureAddress = memoryPtr + startOffset;
        uintptr_t fileOffset = signatureAddress - dwAddress;
        uintptr_t offset = *reinterpret_cast<uint32_t*>(signatureAddress);
        return dwAddress + (offset + fileOffset) + size;
    }
    
    string getFileNameFromPath(const string& path)
    {
        int pos = (int)path.length();
        while (pos && path[pos] != '/')
            --pos;
        return path.substr(pos + 1);
    }
    
    class module
    {
    public:
        
        module(const string& name) : m_start(0) , m_size(0)
        {
            bool found = false;
            unsigned int imageCount = _dyld_image_count();
            for (int i = 0; i < imageCount; i++)
            {
                mach_header* header = (mach_header*)_dyld_get_image_header(i);
                
                const char* imageName = _dyld_get_image_name(i);
                if (!imageName)
                    continue;
                
                string shortName = getFileNameFromPath(string(imageName));
                if (shortName != name)
                    continue;
                
                struct stat sb;
                if (stat(imageName, &sb))
                    break;
                
                found    = true;
                m_start  = (void*)header;
                m_size   = (unsigned int)sb.st_size;
                m_header = header;
                m_name   = shortName;
                m_path   = string(imageName);
                m_handle = dlopen(imageName, RTLD_GLOBAL | RTLD_LAZY);
                break;
            }
        }
        
        void* start() const
        {
            return m_start;
        }
        
        unsigned int size() const
        {
            return m_size;
        }
        
        std::string name() const
        {
            return m_name;
        }
        
        std::string path() const
        {
            return m_path;
        }
        
        mach_header* machHeader() const
        {
            return m_header;
        }
        
        void* handle() const
        {
            return m_handle;
        }
        
        template <typename Fn>
        Fn getSymbol(const char* name) const
        {
            return (Fn)dlsym(handle(), name);
        }
        
    private:
        
        void* m_start;
        unsigned int m_size;
        string m_name;
        string m_path;
        mach_header* m_header;
        void* m_handle;
        
    };
}

void SDLCALL SDL_GetWindowSize(SDL_Window* window, int* w, int* h)
{
    typedef void (*currFn)(SDL_Window*, int*, int*);
    static currFn SDL_GetWindowSizeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetWindowSize"));
    return SDL_GetWindowSizeFn(window, w, h);
}

void SDLCALL SDL_WarpMouseInWindow(SDL_Window* window, int x, int y)
{
    typedef void (*currFn)(SDL_Window*, int, int);
    static currFn SDL_WarpMouseInWindowFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_WarpMouseInWindow"));
    return SDL_WarpMouseInWindowFn(window, x, y);
}

char* SDLCALL SDL_GetClipboardText(void)
{
    typedef char* (*currFn)(void);
    static currFn SDL_GetClipboardTextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetClipboardText"));
    return SDL_GetClipboardTextFn();
}

void SDLCALL SDL_GL_GetDrawableSize(SDL_Window* window, int* w, int* h)
{
    typedef void (*currFn)(SDL_Window*, int*, int*);
    static currFn SDL_GL_GetDrawableSizeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_GetDrawableSize"));
    return SDL_GL_GetDrawableSizeFn(window, w, h);
}

Uint32 SDLCALL SDL_GetTicks(void)
{
    typedef Uint32 (*currFn)(void);
    static currFn SDL_GetTicksFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetTicks"));
    return SDL_GetTicksFn();
}

Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window* window)
{
    typedef Uint32 (*currFn)(SDL_Window*);
    static currFn SDL_GetWindowFlagsFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetWindowFlags"));
    return SDL_GetWindowFlagsFn(window);
}

int SDLCALL SDL_ShowCursor(int toggle)
{
    typedef int (*currFn)(int);
    static currFn SDL_ShowCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_ShowCursor"));
    return SDL_ShowCursorFn(toggle);
}

int SDLCALL SDL_SetClipboardText(const char* text)
{
    typedef int (*currFn)(const char*);
    static currFn SDL_SetClipboardTextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetClipboardText"));
    return SDL_SetClipboardTextFn(text);
}

Uint32 SDLCALL SDL_GetMouseState(int* x, int* y)
{
    typedef Uint32 (*currFn)(int*, int*);
    static currFn SDL_GetMouseStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetMouseState"));
    return SDL_GetMouseStateFn(x, y);
}

SDL_Keymod SDLCALL SDL_GetModState(void)
{
    typedef SDL_Keymod (*currFn)(void);
    static currFn SDL_GetModStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetModState"));
    return SDL_GetModStateFn();
}

SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void)
{
    typedef SDL_GLContext (*currFn)(void);
    static currFn SDL_GL_GetCurrentContextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_GetCurrentContext"));
    return SDL_GL_GetCurrentContextFn();
}

SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window* window)
{
    typedef SDL_GLContext (*currFn)(SDL_Window*);
    static currFn SDL_GL_CreateContextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_CreateContext"));
    return SDL_GL_CreateContextFn(window);
}

int SDLCALL SDL_GL_MakeCurrent(SDL_Window* window, SDL_GLContext context)
{
    typedef int (*currFn)(SDL_Window*, SDL_GLContext);
    static currFn SDL_GL_MakeCurrentFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_MakeCurrent"));
    return SDL_GL_MakeCurrentFn(window, context);
}

Uint64 SDLCALL SDL_GetPerformanceFrequency(void)
{
    typedef Uint64 (*currFn)(void);
    static currFn SDL_GetPerformanceFrequencyFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetPerformanceFrequency"));
    return SDL_GetPerformanceFrequencyFn();
}

Uint64 SDLCALL SDL_GetPerformanceCounter(void)
{
    typedef Uint64 (*currFn)(void);
    static currFn SDL_GetPerformanceCounterFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetPerformanceCounter"));
    return SDL_GetPerformanceCounterFn();
}

int SDLCALL SDL_CaptureMouse(SDL_bool enabled)
{
    typedef int (*currFn)(SDL_bool);
    static currFn SDL_CaptureMouseFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_CaptureMouse"));
    return SDL_CaptureMouseFn(enabled);
}

void SDLCALL SDL_SetCursor(SDL_Cursor* cursor)
{
    typedef void (*currFn)(SDL_Cursor*);
    static currFn SDL_SetCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetCursor"));
    SDL_SetCursorFn(cursor);
}

void SDLCALL SDL_FreeCursor(SDL_Cursor* cursor)
{
    typedef void (*currFn)(SDL_Cursor*);
    static currFn SDL_FreeCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_FreeCursor"));
    return SDL_FreeCursorFn(cursor);
}

SDL_Cursor* SDLCALL SDL_CreateSystemCursor(SDL_SystemCursor id)
{
    typedef SDL_Cursor* (*currFn)(SDL_SystemCursor);
    static currFn SDL_CreateSystemCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_CreateSystemCursor"));
    return SDL_CreateSystemCursorFn(id);
}

int SDLCALL SDL_PollEvent(SDL_Event* event)
{
    typedef int (*currFn)(SDL_Event*);
    static currFn SDL_PollEventFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_PollEvent"));
    return SDL_PollEventFn(event);
}

int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value)
{
    typedef int (*currFn)(SDL_GLattr, int);
    static currFn SDL_GL_SetAttributeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_SetAttribute"));
    return SDL_GL_SetAttributeFn(attr, value);
}

int SDLCALL SDL_SetRelativeMouseMode(SDL_bool enabled)
{
    typedef int (*currFn)(SDL_bool);
    static currFn SDL_SetRelativeMouseModeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetRelativeMouseMode"));
    return SDL_SetRelativeMouseModeFn(enabled);
}

const Uint8* SDLCALL SDL_GetKeyboardState(int* numkeys)
{
    typedef Uint8* (*currFn)(int*);
    static currFn SDL_GetKeyboardStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetKeyboardState"));
    return SDL_GetKeyboardStateFn(numkeys);
}

SDL_bool SDLCALL SDL_SetHint(const char* name, const char* value)
{
    typedef SDL_bool (*currFn)(const char*, const char*);
    static currFn SDL_SetHintFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetHint"));
    return SDL_SetHintFn(name, value);
}

int SDLCALL SDL_Init(Uint32 flags)
{
    typedef int (*currFn)(Uint32);
    static currFn SDL_InitFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_Init"));
    return SDL_InitFn(flags);
}


uintptr_t* swapwindow_ptr = nullptr;
uintptr_t swapwindow_original = NULL;

static SDL_GLContext context = NULL;
void SwapWindow(SDL_Window* window)
{
    static void (*oSDL_GL_SwapWindow)(SDL_Window*)= reinterpret_cast<void (*)(SDL_Window*)>(swapwindow_original);
    static SDL_GLContext original_context = SDL_GL_GetCurrentContext();
    
    if(!context)
    {
        context = SDL_GL_CreateContext(window);
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplSdlGL2_Init(window);
        
        // Initialise the menu style
        menu->setup_style();
    }
    
    SDL_GL_MakeCurrent(window, context);
    ImGui_ImplSdlGL2_NewFrame(window);
    
    
    
    if(set.menu)
    {
        menu->render();
    }
    
    // Draw the mouse
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
    uintptr_t swapwindowFn  = reinterpret_cast<uintptr_t>(dlsym(RTLD_DEFAULT, "SDL_GL_SwapWindow"));
    uintptr_t sdllib        = reinterpret_cast<uintptr_t>(glHelper::module::module("libSDL2-2.0.0.dylib").start());
    swapwindow_ptr          = reinterpret_cast<uintptr_t*>(glHelper::GetAbsoluteAddress(sdllib, swapwindowFn, 0xF, 0x4));
    swapwindow_original     = *swapwindow_ptr;
    *swapwindow_ptr         = reinterpret_cast<uintptr_t>(&SwapWindow);
}
