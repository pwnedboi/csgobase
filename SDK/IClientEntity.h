#pragma once

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

#define LIFE_ALIVE 0

class KeyValues;

struct model_t
{
    char name[255];
};


enum MoveType_t
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};


enum CSWeaponType
{
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL,
    WEAPONTYPE_SUBMACHINEGUN,
    WEAPONTYPE_RIFLE,
    WEAPONTYPE_SHOTGUN,
    WEAPONTYPE_SNIPER_RIFLE,
    WEAPONTYPE_MACHINEGUN,
    WEAPONTYPE_C4,
    WEAPONTYPE_GRENADE,
    WEAPONTYPE_UNKNOWN
};
    

enum WeaponSound_t
{
    EMPTY,
    SINGLE,
    SINGLE_NPC,
    WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
    DOUBLE_NPC,
    BURST,
    RELOAD,
    RELOAD_NPC,
    MELEE_MISS,
    MELEE_HIT,
    MELEE_HIT_WORLD,
    SPECIAL1,
    SPECIAL2,
    SPECIAL3,
    TAUNT,
    FAST_RELOAD,
    REVERSE_THE_NEW_SOUND,
    NUM_SHOOT_SOUND_TYPES,
};

    
enum DataUpdateType_t
{
    DATA_UPDATE_CREATED = 0,
    DATA_UPDATE_DATATABLE_CHANGED,
};

    
class CHudTexture
{
private:
    char pad[0x82];
public:
    char cCharacterInFont;
};


class FileWeaponInfo_t
{
public:
    
    FileWeaponInfo_t();
    
    // Each game can override this to get whatever values it wants from the script.
    virtual void Parse(KeyValues* pKeyValuesData, const char* szWeaponName);
    
    bool bParsedScript;
    bool bLoadedHudElements;
    
    char szClassName[MAX_WEAPON_STRING];
    char szPrintName[MAX_WEAPON_STRING];
    
    char szViewModel[MAX_WEAPON_STRING];
    char szWorldModel[MAX_WEAPON_STRING];
    char szAmmo1[MAX_WEAPON_AMMO_NAME];
    char szWorldDroppedModel[MAX_WEAPON_STRING];
    char szAnimationPrefix[MAX_WEAPON_PREFIX];
    int iSlot;
    int iPosition;
    int iMaxClip1;
    int iMaxClip2;
    int iDefaultClip1;
    int iDefaultClip2;
    int iWeight;
    int iRumbleEffect;
    bool bAutoSwitchTo;
    bool bAutoSwitchFrom;
    int iFlags;
    char szAmmo2[MAX_WEAPON_AMMO_NAME];
    char szAIAddOn[MAX_WEAPON_STRING];
    
    // Sound blocks
    char aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];
    
    int iAmmoType;
    int iAmmo2Type;
    bool m_bMeleeWeapon;
    
    // This tells if the weapon was built right-handed (defaults to true).
    // This helps cl_righthand make the decision about whether to flip the model or not.
    bool m_bBuiltRightHanded;
    bool m_bAllowFlipping;
    
    // Sprite data, read from the data file
    int iSpriteCount;
    CHudTexture* iconActive;
    CHudTexture* iconInactive;
    CHudTexture* iconAmmo;
    CHudTexture* iconAmmo2;
    CHudTexture* iconCrosshair;
    CHudTexture* iconAutoaim;
    CHudTexture* iconZoomedCrosshair;
    CHudTexture* iconZoomedAutoaim;
    CHudTexture* iconSmall;
};


struct WeaponInfo_t
{
    char    gap0[8];
    char*   m_szConsoleName;
    char    gap1C[232];
    char*   m_szHUDName;
    char    gap100[64];
    int     m_WeaponType;
    char    pad144[36];
    bool    m_bIsFullAuto;
    char    gap169[3];
    int     m_iDamage;
    float   m_flArmorRatio;
    int     m_iBulletsPerShot;
    float   m_flPenetration;
    char    pad17C[8];
    float   m_flRange;
    float   m_flRangeModifier;
    float   m_flThrowVelocity;
    char    pad190[12];
    bool    m_bHasSilencer;
    char    pad19D[163];
    int     m_iZoomLevels;      // 0x1B0
    int     m_iZoomFOV1;        //
    int     m_iZoomFOV2;        //
    float   m_flZoomTime[3];
    char    pad258[152];
    bool    m_bHasBurstMode;
    bool    m_bIsRevolver;
    bool    m_bCanShootUnderwater;
    
    int GetClipSize()
    {
        return *(int*)((uintptr_t)this + 0x20);
    }
    
    char* GetTracerEffect()
    {
        return *(char**)((uintptr_t)this + 0x278);
    }
    
    int* GetTracerFrequency()
    {
        return (int*)((uintptr_t)this + 0x280);
    }
    
};


// Classes

class ICollideable
{
public:
    virtual void pad0( );
    virtual const Vector& OBBMins( ) const;
    virtual const Vector& OBBMaxs( ) const;
};

class CBaseHandle;

class IHandleEntity
{
public:
    virtual ~IHandleEntity() {};
    virtual void SetRefEHandle( const CBaseHandle &handle ) = 0;
    virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class IClientUnknown : public IHandleEntity
{
        
};
    
class IClientRenderable
{
public:
    virtual ~IClientRenderable() {};
    
    model_t* GetModel()
    {
        typedef model_t* (* oGetModel)(void*);
        return getvfunc<oGetModel>(this, 8)(this);
    }
    
    bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
    {
        typedef bool (* oSetupBones)(void*, matrix3x4_t*, int, int, float);
        return getvfunc<oSetupBones>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
    }
};

    
class IClientNetworkable
{
public:
    virtual ~IClientNetworkable() {};
    
    void Release()
    {
        typedef void (* oRelease)(void*);
        return getvfunc<oRelease>(this, 1)(this);
    }
    
    ClientClass* GetClientClass()
    {
        typedef ClientClass* (* oGetClientClass)(void*);
        return getvfunc<oGetClientClass>(this, 2)(this);
    }
    
    void PreDataUpdate(DataUpdateType_t updateType)
    {
        typedef void (* oPreDataUpdate)(void*, DataUpdateType_t);
        return getvfunc<oPreDataUpdate>(this, 6)(this, updateType);
    }
    
    void SetDestroyedOnRecreateEntities()
    {
        typedef void (* oSetDestroyedOnRecreateEntities)(void*);
        return getvfunc<oSetDestroyedOnRecreateEntities>(this, 13)(this);
    }
};

    
class IClientThinkable
{
public:
    virtual ~IClientThinkable() {};
};

    
class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
    virtual ~IClientEntity() {};
    
    int GetIndex()
    {
        return *(int*)((uintptr_t)this + 0x94);
    }
};

    
class C_BaseEntity : public IClientEntity
{
public:
    
    IClientNetworkable* GetNetworkable()
    {
        return (IClientNetworkable*)((uintptr_t)this + 0x10);
    }
    
    int GetId()
    {
        return *(int*)((uintptr_t)this + 0x94);
    }
    
    float GetAnimTime()
    {
        return *(float*)((uintptr_t)this + offsets.DT_BaseEntity.m_flAnimTime);
    }
    
    float GetSimulationTime()
    {
        return *(float*)((uintptr_t)this + offsets.DT_BaseEntity.m_flSimulationTime);
    }
    
    Vector GetVecOrigin()
    {
        return *(Vector*)((uintptr_t)this + offsets.DT_BaseEntity.m_vecOrigin);
    }
    
    int GetTeam()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BaseEntity.m_iTeamNum);
    }
    
    MoveType_t GetMoveType()
    {
        return *(MoveType_t*)((uintptr_t)this + offsets.DT_BaseEntity.m_MoveType);
    }
    
    ICollideable* GetCollideable()
    {
        return (ICollideable*)((uintptr_t)this + offsets.DT_BaseEntity.m_Collision);
    }
    
    bool* GetSpotted()
    {
        return (bool*)((uintptr_t)this + offsets.DT_BaseEntity.m_bSpotted);
    }
    
    Vector GetBonePosition(int boneIndex)
    {
        matrix3x4_t matrix[MAXSTUDIOBONES];
        
        if (!this->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
            return this->GetVecOrigin();
        
        matrix3x4_t hitbox = matrix[boneIndex];        
        return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
    }
    
    bool IsDormant()
    {
        return *(bool*)((uintptr_t)this + 0x121);
    }
  
    int get_hitbox_set()
    {
        return (int)((uintptr_t)this + offsets.DT_BasePlayer.m_nHitboxSet);
    } 
};

    
class C_BasePlayer : public C_BaseEntity
{
public:
    
    bool IsPlayer()
    {
        return this->GetClientClass()->m_ClassID == EClassIds::CCSPlayer;
    }
    
    QAngle* GetAimPunchAngle()
    {
        return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_aimPunchAngle);
    }
    
    QAngle* GetViewPunchAngle()
    {
        return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_viewPunchAngle);
    }
    
    Vector GetVecViewOffset()
    {
        return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecViewOffset);
    }
    
    unsigned int GetTickBase()
    {
        return *(unsigned int*)((uintptr_t)this + offsets.DT_BasePlayer.m_nTickBase);
    }
    
    Vector GetVelocity()
    {
        return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecVelocity);
    }
    
    int GetHealth()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iHealth);
    }
    
    unsigned char GetLifeState()
    {
        return *(unsigned char*)((uintptr_t)this + offsets.DT_BasePlayer.m_lifeState);
    }
    
    bool IsAlive()
    {
        return this->GetHealth() > 0 && this->GetLifeState() == LIFE_ALIVE;
    }
    
    int GetFlags()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_fFlags);
    }
    
    ObserverMode_t* GetObserverMode()
    {
        return (ObserverMode_t*)((uintptr_t)this + offsets.DT_BasePlayer.m_iObserverMode);
    }
    
    void* GetObserverTarget()
    {
        return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hObserverTarget);
    }
    
    void* GetViewModel()
    {
        return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hViewModel);
    }
    
    const char* GetLastPlaceName()
    {
        return (const char*)((uintptr_t)this + offsets.DT_BasePlayer.m_szLastPlaceName);
    }
    
    float GetLowerBodyYaw()
    {
        return *(float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flLowerBodyYawTarget);
    }
    
    int GetShotsFired()
    {
        return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_iShotsFired);
    }
    
    QAngle* GetEyeAngles()
    {
        return (QAngle*)((uintptr_t)this + offsets.DT_CSPlayer.m_angEyeAngles[0]);
    }
    
    int GetMoney()
    {
        return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_iAccount);
    }
    
    int GetArmor()
    {
        return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_ArmorValue);
    }
    
    int HasDefuser()
    {
        return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasDefuser);
    }
    
    bool IsDefusing()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsDefusing);
    }
    
    bool IsGrabbingHostage()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsGrabbingHostage);
    }
    
    bool IsScoped()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsScoped);
    }
    
    bool GetImmune()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bGunGameImmunity);
    }
    
    bool IsRescuing()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsRescuing);
    }
    
    int HasHelmet()
    {
        return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasHelmet);
    }
    
    float GetFlashDuration()
    {
        return *(float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashDuration);
    }
    
    float* GetFlashMaxAlpha()
    {
        return (float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashMaxAlpha);
    }

    QAngle* GetViewAngles()
    {
        return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.deadflag + 0x4);
    }
    
    Vector GetEyePosition()
    {
        return this->GetVecOrigin() + this->GetVecViewOffset();
    }
    
    void* GetActiveWeapon()
    {
        return (void*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hActiveWeapon);
    }
    
    char* GetName();
    
};

    
class C_BasePlantedC4 : public C_BaseEntity
{
public:

    bool IsBombTicking()
    {
        return (bool)((uintptr_t)this + offsets.DT_PlantedC4.m_bBombTicking);
    }
    
    float GetBombTime()
    {
        return *(float*)((uintptr_t)this + offsets.DT_PlantedC4.m_flC4Blow);
    }
    
    bool IsBombDefused()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_PlantedC4.m_bBombDefused);
    }
    
    int GetBombDefuser()
    {
        return *(int*)((uintptr_t)this + offsets.DT_PlantedC4.m_hBombDefuser);
    }
    
};

    
class C_BaseAttributableItem : public C_BaseEntity
{
public:

    int* GetItemDefinitionIndex()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex);
    }
    
    int* GetItemIDHigh()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemIDHigh);
    }
    
    int* GetEntityQuality()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iEntityQuality);
    }
    
    char* GetCustomName()
    {
        return (char*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_szCustomName);
    }
    
    int* GetFallbackPaintKit()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackPaintKit);
    }
    
    int* GetFallbackSeed()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackSeed);
    }
    
    float* GetFallbackWear()
    {
        return (float*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_flFallbackWear);
    }
    
    int* GetFallbackStatTrak()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackStatTrak);
    }
    
    int* GetOriginalOwnerXuidLow()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidLow);
    }
    
    int* GetOriginalOwnerXuidHigh()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh);
    }
    
    int* GetAccountID()
    {
        return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iAccountID);
    }
    
};

    
class C_BaseViewModel: public C_BaseEntity
{
public:

    int GetWeapon()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hWeapon);
    }
    
    int GetOwner()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hOwner);
    }
    
};

    
class C_BaseCombatWeapon: public C_BaseAttributableItem
{
public:

    int GetOwner()
    {
        return *(int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_hOwner);
    }
    
    unsigned int GetAmmo()
    {
        return *(unsigned int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_iClip1);
    }
    
    bool CanShoot()
    {
        return GetAmmo() > 0;
    }
    
    float GetNextPrimaryAttack()
    {
        return *(float*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack);
    }
    
    bool GetInReload()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_bInReload);
    }
    
    float GetAccuracyPenalty()
    {
        return *(float*)((uintptr_t)this + offsets.DT_WeaponCSBase.m_fAccuracyPenalty);
    }
    
    float GetFireReadyTime()
    {
        return *(float*)((uintptr_t)this + offsets.DT_WeaponCSBase.m_flPostponeFireReadyTime);
    }
    
    WeaponInfo_t* GetWeaponInfo()
    {
        typedef WeaponInfo_t* (* oGetWeaponInfo)(void*);
        return getvfunc<oGetWeaponInfo>(this, 513)(this);
    }
    
    float GetInaccuracy()
    {
        typedef float (*oGetInaccuracy)(void*);
        return getvfunc<oGetInaccuracy>(this, 536)(this);
    }
    
    float GetSpread()
    {
        typedef float (*oGetSpread)(void*);
        return getvfunc<oGetSpread>(this, 505)(this);
    }
    
    void UpdateAccuracyPenalty()
    {
        typedef void (*oUpdateAccuracyPenalty)(void*);
        return getvfunc<oUpdateAccuracyPenalty>(this, 537)(this);
    }
    
};

    
class C_WeaponC4 : C_BaseCombatWeapon
{
public:

    bool GetStartedArming()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_WeaponC4.m_bStartedArming);
    }
    
};
    
    
class C_BaseCSGrenade : C_BaseCombatWeapon
{
public:

    bool IsHeldByPlayer()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_bIsHeldByPlayer);
    }
    
    bool GetPinPulled()
    {
        return *(bool*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_bPinPulled);
    }
    
    float GetThrowTime()
    {
        return *(float*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_fThrowTime);
    }
    
    float GetThrowStrength()
    {
        return *(float*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_flThrowStrength);
    }
    
};

