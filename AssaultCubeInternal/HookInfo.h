#pragma once

#include "Player.h"

struct SingleHook
{
    int length;
    DWORD address;
    DWORD jumpBack;
};

/**
 * \brief Static class which will contain different variables and values hooks need to be able to see
 */
class HookInfo
{
public:
    // A pointer to a function that takes no parameters and returns a Player pointer
    typedef Player* (__cdecl* tGetTargeted)();

    static SingleHook rapidFire;
    static DWORD localPlayerTeam;
    static tGetTargeted getTargeted;

    static void init(DWORD moduleBase, const Player* localPlayer);
};