#include "pch.h"
#include "Hooking.h"

/*
 * This is basically Solaire's (thankies GuidedHacking) hook function, slightly modified to comply with
 * most modern C++ conventions
 */

/**
 * \brief Will replace no less than 5 bytes with a JMP (jump) instruction in order to detour
 *	game code to my own
 * \param toHook Address where the hook should be placed
 * \param ourFunc The memory address in which the injected code is located
 * \param len Amount of bytes to be overwritten. Cannot be less than 5 because that's the length of
 *	a JMP (jump) instruction
 * \return A boolean which basically says if the hook was applied successfully
 */
bool hook(void* toHook, void* ourFunc, int len)
{
	if (len < 5)
		return false;

	DWORD oldProtect;

	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(toHook, 0x90, len);

	DWORD relativeAddr{ reinterpret_cast<DWORD>(ourFunc) - reinterpret_cast<DWORD>(toHook) - 5 };
	*static_cast<BYTE*>(toHook) = 0xE9;
	*reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(toHook) + 1) = relativeAddr;

	VirtualProtect(toHook, len, oldProtect, &oldProtect);

	return true;
}