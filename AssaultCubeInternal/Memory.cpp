#include "pch.h"
#include "Memory.h"

/*
 * Basically AnomanderRake's (or just Rake) code from his GuidedHacking tutorials but once again
 * modified to comply with most modern C++ conventions
 */

/**
 * \brief Will overwrite whichever amount of bytes needed
 * \param dest Start of the bytes to be overwritten
 * \param source What should replace those bytes
 * \param size Amount of bytes to be replaced
 */
void Memory::patch(BYTE* dest, const BYTE* source, const unsigned int size)
{
	DWORD oldProtect;

	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dest, source, size);
	VirtualProtect(dest, size, oldProtect, &oldProtect);
}

/**
 * \brief Will replace the provided amount of bytes with 0x90, NOP (no operation) to make code do nothing
 * \param dest Start of the bytes to be overwritten
 * \param size Amount of bytes to be replaced
 */
void Memory::nop(BYTE* dest, const unsigned int size)
{
	DWORD oldProtect;

	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dest, 0x90, size);
	VirtualProtect(dest, size, oldProtect, &oldProtect);
}

/**
 * \brief Finds the end address of a multilevel pointer chain
 * \param ptr Base address
 * \param offsets Different offsets to be applied to each address per level
 * \return End address of the multilevel pointer
 */
uintptr_t Memory::findDMAAddy(const uintptr_t ptr, const std::vector<unsigned int>& offsets)
{
	uintptr_t addr{ ptr };

	for (const auto off : offsets)
	{
		addr = *reinterpret_cast<uintptr_t*>(addr);
		addr += off;
	}

	return addr;
}
