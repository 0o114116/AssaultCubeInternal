#include "pch.h"
#include "HackMainLoop.h"

#include "HookInfo.h"
#include "Hooking.h"
#include "hooks.h"
#include "Memory.h"
#include "Player.h"

/**
 * \brief Main loop for the hack client
 * \param hModule The process module into which the DLL is loaded
 * \return Error code as a 32bit uint. Will return 0 if the main loop is stopped
 */
DWORD WINAPI HackThread(const HMODULE hModule)
{
    AllocConsole();

    FILE* file{ nullptr };

    freopen_s(&file, "CONOUT$", "w", stdout);  // NOLINT(cert-err33-c)
    // These lines above allocate a console and redirect stdout to it
    std::cout << "AssaultCube Internal Hacks Successfully Injected!" << std::endl;

    const uintptr_t moduleBase{ reinterpret_cast<uintptr_t>(GetModuleHandle(L"ac_client.exe")) };
    bool bHealth{ false }, bAmmo{ false }, bGrenades{ false }, bRecoil{ false }, bAutoTrigger{ false };
    const auto localPlayer
    {
        reinterpret_cast<Player*>(Memory::findDMAAddy(moduleBase + 0xFAD28, { 0xC0, 0x274, 0x354 }))
    };

    std::cout << localPlayer << std::endl;
    HookInfo::init(moduleBase, localPlayer);
    hook(reinterpret_cast<void*>(HookInfo::rapidFire.address), 
        reinterpret_cast<void*>(rapidFireHook), 
        HookInfo::rapidFire.length);

    while (true)
    {
        if (localPlayer)
        {
            if (GetAsyncKeyState(0x5A /*Z Key*/) & 1)
            {
                /*
                 * If the Z key is pressed, it will disable or enable assault rifle ammo refilling.
                 * if enabled, the assault rifle ammo will be refilled back up to 20 by writing to
                 * the local player's AR clip memory address whenever it gets down to one
                 */
                bAmmo = !bAmmo;

                std::cout << "Z Key Pressed. Ammo Refilling Toggled. State: " << bAmmo << std::endl;
            }

            if (bAmmo && localPlayer->mArClip == 1)
                localPlayer->mArClip = 13;

            if (GetAsyncKeyState(0x58 /*X Key*/) & 1)
            {
                /*
                 * If the X key is pressed, recoil will be enabled or disabled. If enabled, the
                 * client will internally NOP the function which takes care of it
                 */
                bRecoil = !bRecoil;

                std::cout << "X Key Pressed. Recoil Toggled. State: " << bRecoil << std::endl;

                if (bRecoil)
                    Memory::nop(reinterpret_cast<BYTE*>((moduleBase + 0x63786)), 10);
                else
                    Memory::patch(
                        reinterpret_cast<BYTE*>((moduleBase + 0x63786)),
                        reinterpret_cast<BYTE*>(const_cast<char*>("\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2")),
                        10);
            }

            if (GetAsyncKeyState(0x43 /*C Key*/) & 1)
            {
                /*
                 * If the C key is pressed, freezing armor and health values will be enabled.
                 * If enabled the client will internally and continuously write the value '100' to the
                 * local player's health and armor memory addresses.
                 */
                bHealth = !bHealth;

                std::cout << "C Key Pressed. Infinite Health & Armor Toggled. State: " << bHealth << std::endl;
            }

            if (bHealth)
            {
                localPlayer->mHealth = 100;
                localPlayer->mArmor = 100;
            }

            if (GetAsyncKeyState(0x51 /*Q Key*/) & 1)
            {
                /*
                 * If the Q key is pressed, infinite grenades will be enabled or disabled.
                 * If enabled, the client will continuously write the value '3' to the local player
                 * grenades memory address
                 */
                bGrenades = !bGrenades;

                std::cout << "Q Key Pressed. Infinite Grenades Toggled. State: " << bGrenades << std::endl;
            }

            if (bGrenades)
                localPlayer->mGrenades = 3;

            if (GetAsyncKeyState(0x4C /*L Key*/) & 1)
            {
                /*
                 * If the L key is pressed, whenever a player is targeted, they will be shot.
                 */
                bAutoTrigger = !bAutoTrigger;

                std::cout << "L key pressed. Auto trigger toggled. State: " << bAutoTrigger << std::endl;
            }

            if (bAutoTrigger)
            {
                const Player* targeted{ HookInfo::getTargeted() };

                if (targeted)
                {
                    if (targeted->mTeam != localPlayer->mTeam)
                        localPlayer->mIsAttacking = 1;
                }
                else
                    localPlayer->mIsAttacking = 0;
            }

            // If the F key is pressed, the client will exit the main loop
            if (GetAsyncKeyState(0x46 /*F Key*/) & 1)
                break;

            Sleep(10);
        }
    }

    if (file)
        fclose(file);  // NOLINT(cert-err33-c)

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}
