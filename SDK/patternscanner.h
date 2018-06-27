#pragma once

struct MemoryModule
{
    off_t       length;
    uint64_t    address;
    char*       path;
    string fullpath;
    Byte*       buffer = nullptr;
};

struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};

class PatternScanner
{
public:
    
    static PatternScanner* get()
    {
        if(!_instance)
        {
            _instance = new PatternScanner();
        }
        return _instance;
    }
    
    PatternScanner();
    
    string    Basename(string const& pathname);
    string    GetModulePath(string imageName);
    
    bool      Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask);
    
    uintptr_t FindPattern(uintptr_t dwAddress, off_t dwLen, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    uintptr_t GetPointer(string imageName, unsigned char* bMask, const char* szMask, uint32_t start);
    uintptr_t GetProcedure(string imageName, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    uintptr_t GetBaseAddress(string imageName);
    
private:
    
    void LoadModules();
    map<string, MemoryModule> loaded_modules;
    
    static PatternScanner* _instance;
    
};

