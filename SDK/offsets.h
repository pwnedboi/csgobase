#pragma once

void get_offsets();

struct COffsets
{
    struct
    {
        int m_flAnimTime;
        int m_flSimulationTime;
        int m_vecOrigin;
        int m_nRenderMode;
        int m_iTeamNum;
        int m_MoveType;
        int m_Collision;
        int m_bSpotted;
    } DT_BaseEntity;
    
    struct
    {
        int m_Local;
        int m_aimPunchAngle;
        int m_viewPunchAngle;
        int m_vecViewOffset;
        int m_nTickBase;
        int m_vecVelocity;
        int m_iHealth;
        int m_lifeState;
        int m_fFlags;
        int m_iObserverMode;
        int m_hObserverTarget;
        int m_hViewModel;
        int m_szLastPlaceName;
        int deadflag;
        int m_nHitboxSet;
        int m_dwCrosshairID;
    } DT_BasePlayer;
    
    struct
    {
        int m_hActiveWeapon;
        int m_hMyWeapons;
        int m_hMyWearables;
    } DT_BaseCombatCharacter;
    
    struct
    {
        int m_iPing;
        int m_iKills;
        int m_iAssists;
        int m_iDeaths;
        int m_bConnected;
        int m_iTeam;
        int m_iPendingTeam;
        int m_bAlive;
        int m_iHealth;
    } DT_PlayerResource;
    
    // Unused
    struct
    {
        int m_iPlayerC4;
        int m_iPlayerVIP;
        int m_bHostageAlive;
        int m_isHostageFollowingSomeone;
        int m_iHostageEntityIDs;
        int m_bombsiteCenterB;
        int m_hostageRescueX;
        int m_hostageRescueY;
        int m_hostageRescueZ;
        int m_iMVPs;
        int m_iArmor;
        int m_bHasHelmet;
        int m_bHasDefuser;
        int m_iScore;
        int m_iCompetitiveRanking;
        int m_iCompetitiveWins;
        int m_iCompTeammateColor;
        int m_bControllingBot;
        int m_iControlledPlayer;
        int m_iControlledByPlayer;
        int m_iBotDifficulty;
        int m_szClan;
        int m_iTotalCashSpent;
        int m_iCashSpentThisRound;
        int m_nEndMatchNextMapVotes;
        int m_bEndMatchNextMapAllVoted;
        int m_nActiveCoinRank;
        int m_nMusicID;
        int m_nPersonaDataPublicLevel;
        int m_nPersonaDataPublicCommendsLeader;
        int m_nPersonaDataPublicCommendsTeacher;
        int m_nPersonaDataPublicCommendsFriendly;
    } DT_CSPlayerResource;
    
    struct
    {
        int m_bBombTicking;
        int m_flC4Blow;
        int m_bBombDefused;
        int m_hBombDefuser;
    } DT_PlantedC4;
    
    struct
    {
        int m_iShotsFired;
        int m_angEyeAngles[2];
        int m_iAccount;
        int m_ArmorValue;
        int m_bHasDefuser;
        int m_bIsDefusing;
        int m_bIsGrabbingHostage;
        int m_bIsScoped;
        int m_bGunGameImmunity;
        int m_bIsRescuing;
        int m_bHasHelmet;
        int m_flFlashDuration;
        int m_flFlashMaxAlpha;
        int m_nTickBase;
        int m_flLowerBodyYawTarget;
    } DT_CSPlayer;
    
    struct
    {
        int m_iItemDefinitionIndex;
        int m_iItemIDHigh;
        int m_iAccountID;
        int m_iEntityQuality;
        int m_szCustomName;
        int m_nFallbackPaintKit;
        int m_nFallbackSeed;
        int m_flFallbackWear;
        int m_nFallbackStatTrak;
        int m_OriginalOwnerXuidLow;
        int m_OriginalOwnerXuidHigh;
    } DT_BaseAttributableItem;
    
    struct
    {
        int m_nModelIndex;
        int m_hWeapon;
        int m_hOwner;
    } DT_BaseViewModel;
    
    struct
    {
        int m_fAccuracyPenalty;
        int m_flPostponeFireReadyTime;
    } DT_WeaponCSBase;
    
    struct
    {
        int m_bStartedArming;
    } DT_WeaponC4;
    
    struct
    {
        int m_flNextPrimaryAttack;
        int m_hOwner;
        int m_iClip1;
        int m_bInReload;
    } DT_BaseCombatWeapon;
    
    struct
    {
        int m_bIsHeldByPlayer;
        int m_bPinPulled;
        int m_fThrowTime;
        int m_flThrowStrength;
    }DT_BaseCSGrenade;
    
    struct
    {
        int m_bShouldGlow;
    } DT_DynamicProp;
    
    struct
    {
        int m_nSequence;
        int m_flPoseParameter;
        
        struct
        {
            int m_flCycle;
        }DT_ServerAnimationData;
        
        int m_Activity;
        int m_IdealActivity;
        int m_eCurrentMainSequenceActivity;
        
    }DT_BaseAnimating;
    
};

extern COffsets offsets;

