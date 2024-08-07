#include "pch.h"
#include "HookInfo.h"

SingleHook HookInfo::rapidFire;
DWORD HookInfo::localPlayerTeam;
HookInfo::tGetTargeted HookInfo::getTargeted;

/**
 * \brief A function which serves as a constructor for the static hooks class
 * \param moduleBase The address into which the assault cube client executable was loaded at
 * \param localPlayer Pointer to the base of the local player object 
 */
void HookInfo::init(const DWORD moduleBase, const Player* localPlayer)
{
    rapidFire = {
    	5,
    	moduleBase + 0x637E4,
    	rapidFire.length == 0 || rapidFire.address == 0 ? 0 : rapidFire.address + rapidFire.length
    };
    localPlayerTeam = static_cast<unsigned char>(localPlayer->mTeam);
    /*
     * I got this address from IDA by basically checking what function writes the name of the
     * player being pointed to on my screen
     */
    getTargeted = reinterpret_cast<tGetTargeted>(moduleBase + 0x607C0);

    if (!rapidFire.jumpBack)
        rapidFire.jumpBack = rapidFire.address + rapidFire.length;
}