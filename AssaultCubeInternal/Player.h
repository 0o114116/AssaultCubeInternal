#pragma once

// Auto-padding! Thanks to Can1357 from UnknownCheats :pepedance:
#define STR_MERGE_IMPL(a, b) a##b 
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b) 
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size] 
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

/**
 * \brief 3 dimensional vector. Unlike Minecraft, Z acts as the height value here
 */
struct Vec3 { float x, y, z; };

class Weapon
{
public:
    union
    {
        DEFINE_MEMBER_N(int32_t, mWeaponId, 0x4);
        DEFINE_MEMBER_N(int32_t*, mMagPtr, 0x10);
        DEFINE_MEMBER_N(int32_t*, mClipPtr, 0x14);
    };
};

/**
 * \brief Pretty complete player class with most of the actually useful members. Uses auto-padding
 */
class Player
{
public:
    union 
    {
        DEFINE_MEMBER_N(Vec3, mHead, 0x8);
        DEFINE_MEMBER_N(Vec3, mPos, 0x38);
        DEFINE_MEMBER_N(Vec3, mViewAngles, 0x44);	// Z isn't used here, it will always be 0.
                                                    // Don't really know why they used a Vec3 and not
                                                    // a Vec2
        DEFINE_MEMBER_N(int32_t, mHealth, 0xFC);
        DEFINE_MEMBER_N(int32_t, mArmor, 0x100);
        DEFINE_MEMBER_N(int32_t, mPistolAmmo, 0x118);
        DEFINE_MEMBER_N(int32_t, mCarbineAmmo, 0x11C);
        DEFINE_MEMBER_N(int32_t, mShotgunAmmo, 0x120);
        DEFINE_MEMBER_N(int32_t, mSmgAmmo, 0x124);
        DEFINE_MEMBER_N(int32_t, mSniperAmmo, 0x128);
        DEFINE_MEMBER_N(int32_t, mArAmmo, 0x12C);
        DEFINE_MEMBER_N(int32_t, mAkimboAmmo, 0x138);
        DEFINE_MEMBER_N(int32_t, mPistolClip, 0x140);
        DEFINE_MEMBER_N(int32_t, mCarbineClip, 0x144);
        DEFINE_MEMBER_N(int32_t, mShotgunClip, 0x148);
        DEFINE_MEMBER_N(int32_t, mSmgClip, 0x14C);
        DEFINE_MEMBER_N(int32_t, mSniperClip, 0x150);
        DEFINE_MEMBER_N(int32_t, mArClip, 0x154);
        DEFINE_MEMBER_N(int32_t, mGrenades, 0x15C);
        DEFINE_MEMBER_N(int32_t, mDoublePistolMag, 0x160);
        DEFINE_MEMBER_N(int32_t, mPistolCooldown, 0x168);
        DEFINE_MEMBER_N(int32_t, mCarabineCooldown, 0x16C);
        DEFINE_MEMBER_N(int32_t, mShotgunCooldown, 0x170);
        DEFINE_MEMBER_N(int32_t, mSmgCooldown, 0x174);
        DEFINE_MEMBER_N(int32_t, mSniperCooldown, 0x178);
        DEFINE_MEMBER_N(int32_t, mArCooldown, 0x17C);
        DEFINE_MEMBER_N(int32_t, mPistolFired, 0x190);
        DEFINE_MEMBER_N(int32_t, mCarbineFired, 0x194);
        DEFINE_MEMBER_N(int32_t, mShotgunFired, 0x198);
        DEFINE_MEMBER_N(int32_t, mSmgFired, 0x19C);
        DEFINE_MEMBER_N(int32_t, mSniperFired, 0x1A0);
        DEFINE_MEMBER_N(int32_t, mArFired, 0x1A4);
        DEFINE_MEMBER_N(int32_t, mGrenadesThrown, 0x1AC);
        DEFINE_MEMBER_N(int8_t, mIsAttacking, 0x228);
//		DEFINE_MEMBER_N(char, mName[16], 0x229);
        DEFINE_MEMBER_N(int8_t, mTeam, 0x330);
//      DEFINE_MEMBER_N(void*, mKnifePtr, 0x34C);
        DEFINE_MEMBER_N(Weapon*, mPistolPtr, 0x350);
        DEFINE_MEMBER_N(Weapon*, mCarbinePtr, 0x354);
        DEFINE_MEMBER_N(Weapon*, mShotgunPtr, 0x358);
        DEFINE_MEMBER_N(Weapon*, mSmgPtr, 0x35C);
        DEFINE_MEMBER_N(Weapon*, mSniperPtr, 0x360);
        DEFINE_MEMBER_N(Weapon*, mArPtr, 0x364);
//      DEFINE_MEMBER_N(void*, mCPistolPtr, 0x368);
//      DEFINE_MEMBER_N(void*, mGrenadesPtr, 0x36C);
        DEFINE_MEMBER_N(Weapon*, mAkimboPtr, 0x370);
        DEFINE_MEMBER_N(Weapon*, mCurrentGunPtr, 0x374);
    };
};