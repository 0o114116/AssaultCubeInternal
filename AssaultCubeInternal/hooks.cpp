#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "HookInfo.h"

/**
 * \brief Hook for rapid fire
 */
void __declspec(naked) rapidFireHook()
{
    __asm
    {
        mov ebx, HookInfo::localPlayerTeam  // Moves the local player team value (either 0 or 1) into EBX
        cmp[edx + 0x1B4], ebx               // Compares the local player team value (EBX) to the team value
    										// of whichever player triggered the assault rifle cooldown
    										// activation. EDX here will have the address of the AR
    										// rifle cooldown.
        je goback                           // If the team is the same, do not apply to delay, execute
    										// other overwritten instructions and jump back in order to
    										// continue.
        mov[edx], ecx                       // Else, dereference the pointer to the AR cooldown and write
    										// the value in ECX (should be 25) to it
    goback :
        mov ebx, 0x0                        // EBX should be 0 after this function
        mov esi, [esi + 0x14]               // This instruction gets overwritten by the hook's JMP(jump)
        jmp[HookInfo::rapidFire.jumpBack]   // This goes back to the place in memory after the cooldown reset
    }
}