/*
 *  util_sdl.h
 */
#pragma once

#include <sys/types.h>
#include <mach/mach.h>
#include <mach/error.h>
#include <mach-o/dyld.h>
#include <mach/vm_types.h>
#include <mach-o/getsect.h>

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>

/*
 *  SDL2 functions
 */
Uint32 SDLCALL SDL_GetTicks(void);
Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window* window);
Uint32 SDLCALL SDL_GetMouseState(int* x, int* y);
Uint64 SDLCALL SDL_GetPerformanceFrequency(void);
Uint64 SDLCALL SDL_GetPerformanceCounter(void);
const Uint8* SDLCALL SDL_GetKeyboardState(int* numkeys);
int SDLCALL SDL_ShowCursor(int toggle);
int SDLCALL SDL_SetClipboardText(const char* text);
int SDLCALL SDL_GL_MakeCurrent(SDL_Window* window, SDL_GLContext context);
int SDLCALL SDL_CaptureMouse(SDL_bool enabled);
int SDLCALL SDL_PollEvent(SDL_Event* event);
int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value);
int SDLCALL SDL_SetRelativeMouseMode(SDL_bool enabled);
int SDLCALL SDL_Init(Uint32 flags);
int SDLCALL SDL_GL_SetSwapInterval(int interval);
void SDLCALL SDL_GetWindowSize(SDL_Window* window, int* w, int* h);
void SDLCALL SDL_WarpMouseInWindow(SDL_Window* window, int x, int y);
void SDLCALL SDL_GL_GetDrawableSize(SDL_Window* window, int* w, int* h);
void SDLCALL SDL_SetCursor(SDL_Cursor* cursor);
void SDLCALL SDL_FreeCursor(SDL_Cursor* cursor);
char* SDLCALL SDL_GetClipboardText(void);
SDL_bool SDLCALL SDL_SetHint(const char* name, const char* value);
SDL_Keymod SDLCALL SDL_GetModState(void);
SDL_Cursor* SDLCALL SDL_CreateSystemCursor(SDL_SystemCursor id);
SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void);
SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window* window);

/*
 *  GLHelper
 *  Helps with hooking SDL
 */
namespace GLHelper
{
    inline uintptr_t get_absolue_address(uintptr_t dwAddress, uintptr_t memoryPtr, uintptr_t startOffset, uintptr_t size)
    {
        uintptr_t signatureAddress = memoryPtr + startOffset;
        uintptr_t fileOffset = signatureAddress - dwAddress;
        uintptr_t offset = *reinterpret_cast<uint32_t*>(signatureAddress);
        return dwAddress + (offset + fileOffset) + size;
    }
    
    inline string get_file_from_path(const string& path)
    {
        return string(find_if(path.rbegin(), path.rend(), [=](char ch) { return ch == '/'; }).base(), path.end());
    }
    
    class module
    {
    private:
        
        void* m_start;
        unsigned int m_size;
        string m_name;
        string m_path;
        mach_header* m_header;
        void* m_handle;
        
    public:
        
        module(const string& name) : m_start(0) , m_size(0), m_name(name)
        {
            bool found = false;
            unsigned int imageCount = _dyld_image_count();
            for (int i = 0; i < imageCount; i++)
            {
                mach_header* header = (mach_header*)_dyld_get_image_header(i);
                
                const char* imageName = _dyld_get_image_name(i);
                if (!imageName)
                    continue;
                
                string shortName = get_file_from_path(string(imageName));
                if (shortName != m_name)
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
        
        template <typename Fn>
        Fn getSymbol(const char* name) const
        {
            return (Fn)dlsym(this->m_handle, name);
        }
        
        void* start() const { return this->m_start; }
        
    };
}
