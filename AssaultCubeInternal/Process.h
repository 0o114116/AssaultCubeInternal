#pragma once

#include "pch.h"

uint32_t getProcID(const wchar_t* procName);
uintptr_t getModuleBaseAddr(uint32_t procID, const wchar_t* procName);