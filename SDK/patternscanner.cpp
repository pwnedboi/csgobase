// =============== patternscanner.cpp =============== \\
//
//  -
//  -
//  -
//

#include "main.h"
#include "patternscanner.h"

PatternScanner* PatternScanner::_instance = nullptr;

PatternScanner::PatternScanner()
{
    LoadModules();
}

string PatternScanner::Basename(string const& pathname)
{
    return string(find_if(pathname.rbegin(), pathname.rend(), MatchPathSeparator()).base(), pathname.end());
}

void PatternScanner::LoadModules()
{
    struct task_dyld_info dyld_info;
    vm_address_t address = 0;
    mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;
    
    if (task_info(current_task(), TASK_DYLD_INFO, (task_info_t)&dyld_info, &count) == KERN_SUCCESS)
    {
        address = (vm_address_t)dyld_info.all_image_info_addr;
    }
    
    struct dyld_all_image_infos *dyldaii;
    mach_msg_type_number_t size = sizeof(dyld_all_image_infos);
    vm_offset_t readMem;
    kern_return_t kr = vm_read(current_task(), address, size, &readMem, &size);
    
    if (kr != KERN_SUCCESS)
        return;
    
    dyldaii = (dyld_all_image_infos *) readMem;
    int imageCount = dyldaii->infoArrayCount;
    mach_msg_type_number_t dataCnt = imageCount * 24;
    struct dyld_image_info *g_dii = NULL;
    g_dii = (struct dyld_image_info *) malloc (dataCnt);
    // 32bit bs 64bit
    kern_return_t kr2 = vm_read(current_task(), (vm_address_t)dyldaii->infoArray, dataCnt, &readMem, &dataCnt);
    if (kr2)
    {
        free(g_dii);
        return;
    }
    
    struct dyld_image_info *dii = (struct dyld_image_info *) readMem;
    
    for (int i = 0; i < imageCount; i++)
    {
        dataCnt = 1024;
        vm_read(current_task(), (vm_address_t)dii[i].imageFilePath, dataCnt, &readMem, &dataCnt);
        char *imageName = (char *)readMem;
        
        if (imageName)
        {
            g_dii[i].imageFilePath = strdup(imageName);
        }
        else
        {
            g_dii[i].imageFilePath = NULL;
        }
        
        g_dii[i].imageLoadAddress = dii[i].imageLoadAddress;
        
        MemoryModule memoryModule;
        struct stat st;
        stat(imageName, &st);
        
        memoryModule.address = (vm_address_t)dii[i].imageLoadAddress;
        memoryModule.length = st.st_size;
        memoryModule.path = imageName;
        memoryModule.fullpath = g_dii[i].imageFilePath;
        
        loaded_modules[Basename(imageName)] = memoryModule;
    }
    
    free(g_dii);
    
}

bool PatternScanner::Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
    for (; *szMask; ++szMask, ++pData, ++bMask)
    {
        if (*szMask == 'x' && *pData != *bMask)
            return false;
    }
    
    return (*szMask) == 0;
}

uintptr_t PatternScanner::FindPattern(uintptr_t dwAddress, off_t dwLen, unsigned char* bMask, const char* szMask, uintptr_t offset)
{
    for (uintptr_t i = offset; i < dwLen; i++)
    {
        if (Compare((unsigned char*)(dwAddress + i), bMask, szMask))
            return (uintptr_t)(dwAddress + i);
    }
    
    return 0;
}

uintptr_t PatternScanner::GetPointer(string imageName, unsigned char* bMask, const char* szMask, uint32_t start)
{
    MemoryModule module = loaded_modules[imageName];
    uintptr_t dwAddress = module.address;
    off_t dwLen = module.length;
    
    uintptr_t signatureAddress = FindPattern(dwAddress, dwLen, bMask, szMask) + start;
    uintptr_t fileOffset = signatureAddress - dwAddress;
    uintptr_t offset = *reinterpret_cast<uint32_t*>(signatureAddress);
    
    return dwAddress + (offset + fileOffset);
}

uintptr_t PatternScanner::GetProcedure(string imageName, unsigned char* bMask, const char* szMask, uintptr_t offset)
{
    MemoryModule module = loaded_modules[imageName];
    uintptr_t dwAddress = module.address;
    off_t dwLen = module.length;
    
    return FindPattern(dwAddress, dwLen, bMask, szMask, offset);
}

string PatternScanner::GetModulePath(string imageName)
{
    return loaded_modules[imageName].path;
}

uintptr_t PatternScanner::GetBaseAddress(string imageName)
{
    MemoryModule module = loaded_modules[imageName];
    return module.address;
}
