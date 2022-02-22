#include <Windows.h>
#include <cstdio>
#include "loader.h"
#include "address.h"

namespace pkodev
{
    // Handle of the mod implementation library
    HMODULE handle = NULL;
}

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Build path to the mod implementation library
    char buf[MAX_PATH]{ 0x00 };
    sprintf_s(buf, sizeof(buf), "%s\\impl\\pkodev.mod.60fps.impl_%d.dll",
        path, pkodev::address::MOD_EXE_VERSION::impl_id);

    // Load the mod implementation library
    pkodev::handle = LoadLibraryA(buf);
}

// Stop the mod
void Stop()
{
    // Free the mod implementation library
    if (pkodev::handle != NULL)
    {
        FreeLibrary(pkodev::handle);
        pkodev::handle = NULL;
    }
}