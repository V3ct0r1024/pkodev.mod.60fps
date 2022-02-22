#include <windows.h>
#include <detours.h>

// CSteadyFrame address
const unsigned int CSteadyFrame__Address = 0x00660540;

// void CHeadSay::Render(D3DXVECTOR3& pos) pointer
typedef void(__thiscall* CHeadSay__Render__Ptr)(void*, void*);
CHeadSay__Render__Ptr CHeadSay__Render = (CHeadSay__Render__Ptr)(void*)(0x004706D0);

// void CSteadyFrame::SetFPS(DWORD v)	
typedef void(__thiscall* CSteadyFrame__SetFPS__Ptr)(void*, unsigned int);
CSteadyFrame__SetFPS__Ptr CSteadyFrame__SetFPS = (CSteadyFrame__SetFPS__Ptr)(void*)(0x0040C940);

// void CHeadSay::Render(D3DXVECTOR3& pos) hook
void __fastcall CHeadSay__Render__Hook(void* This, void* NotUsed, void* Pos);


// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call != DLL_PROCESS_DETACH)
    {
        if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        {
            DetourRestoreAfterWith();
            DetourTransactionBegin();
            DetourAttach(&(PVOID&)CHeadSay__Render, CHeadSay__Render__Hook);
            DetourTransactionCommit();
        }
    }
    else
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)CHeadSay__Render, CHeadSay__Render__Hook);
        DetourTransactionCommit();
    }

    return TRUE;
}

// void CHeadSay::Render(D3DXVECTOR3& pos) hook
void __fastcall CHeadSay__Render__Hook(void* This,
    void* NotUsed, void* Pos)
{
    // Set 60 FPS
    CSteadyFrame__SetFPS(reinterpret_cast<void *>(CSteadyFrame__Address), 60);

    // Call the original function
    CHeadSay__Render(This, Pos);
}