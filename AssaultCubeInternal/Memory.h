#pragma once

#include "pch.h"

namespace Memory
{
	void patch(BYTE* dest, const BYTE* source, unsigned int size);
	void nop(BYTE* dest, unsigned int size);
	uintptr_t findDMAAddy(uintptr_t ptr, const std::vector<unsigned int>& offsets);
}