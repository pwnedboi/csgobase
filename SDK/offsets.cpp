// =============== offsetts.cpp =============== \\
//
//  - Initialises all offset variables
//  -
//  -
//

#include "main.h"
#include "offsets.h"

COffsets offsets;

void get_offsets()
{
    vector<RecvTable*> tables = NetVar::GetTables();
    
    offsets.DT_BasePlayer.m_Local = NetVar::GetOffset(tables, "DT_BasePlayer", "m_Local");
    offsets.DT_BasePlayer.m_aimPunchAngle = NetVar::GetOffset(tables, "DT_BasePlayer", "m_aimPunchAngle");
    offsets.DT_BasePlayer.m_viewPunchAngle = NetVar::GetOffset(tables, "DT_BasePlayer", "m_viewPunchAngle");
    offsets.DT_BasePlayer.m_vecViewOffset = NetVar::GetOffset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
    offsets.DT_BasePlayer.m_nTickBase = NetVar::GetOffset(tables, "DT_BasePlayer", "m_nTickBase");
    offsets.DT_BasePlayer.m_vecVelocity = NetVar::GetOffset(tables, "DT_BasePlayer", "m_vecVelocity[0]");
    offsets.DT_BasePlayer.m_iHealth = NetVar::GetOffset(tables, "DT_BasePlayer", "m_iHealth");
    offsets.DT_BasePlayer.m_lifeState = NetVar::GetOffset(tables, "DT_BasePlayer", "m_lifeState");
    offsets.DT_BasePlayer.m_fFlags = NetVar::GetOffset(tables, "DT_BasePlayer", "m_fFlags");
    offsets.DT_BasePlayer.m_iObserverMode = NetVar::GetOffset(tables, "DT_BasePlayer", "m_iObserverMode");
    offsets.DT_BasePlayer.m_hObserverTarget = NetVar::GetOffset(tables, "DT_BasePlayer", "m_hObserverTarget");
    offsets.DT_BasePlayer.m_hViewModel = NetVar::GetOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
    offsets.DT_BasePlayer.m_szLastPlaceName = NetVar::GetOffset(tables, "DT_BasePlayer", "m_szLastPlaceName");
    offsets.DT_BasePlayer.deadflag = NetVar::GetOffset(tables, "DT_BasePlayer", "deadflag");
    offsets.DT_BasePlayer.m_nHitboxSet = NetVar::GetOffset(tables, "DT_BasePlayer", "m_nHitboxSet");
    
    offsets.DT_BaseEntity.m_flAnimTime = NetVar::GetOffset(tables, "DT_BaseEntity", "m_flAnimTime");
    offsets.DT_BaseEntity.m_flSimulationTime = NetVar::GetOffset(tables, "DT_BaseEntity", "m_flSimulationTime");
    offsets.DT_BaseEntity.m_vecOrigin = NetVar::GetOffset(tables, "DT_BaseEntity", "m_vecOrigin");
    offsets.DT_BaseEntity.m_nRenderMode = NetVar::GetOffset(tables, "DT_BaseEntity", "m_nRenderMode");
    offsets.DT_BaseEntity.m_iTeamNum = NetVar::GetOffset(tables, "DT_BaseEntity", "m_iTeamNum");
    offsets.DT_BaseEntity.m_MoveType = offsets.DT_BaseEntity.m_nRenderMode + 1;
    offsets.DT_BaseEntity.m_Collision = NetVar::GetOffset(tables, "DT_BaseEntity", "m_Collision");
    offsets.DT_BaseEntity.m_bSpotted = NetVar::GetOffset(tables, "DT_BaseEntity", "m_bSpotted");
    
    offsets.DT_BaseCombatCharacter.m_hActiveWeapon = NetVar::GetOffset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");
    offsets.DT_BaseCombatCharacter.m_hMyWeapons = NetVar::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
    offsets.DT_BaseCombatCharacter.m_hMyWearables = NetVar::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWearables");
    
    offsets.DT_PlayerResource.m_iPing = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iPing");
    offsets.DT_PlayerResource.m_iKills = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iKills");
    offsets.DT_PlayerResource.m_iAssists = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iAssists");
    offsets.DT_PlayerResource.m_iDeaths = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iDeaths");
    offsets.DT_PlayerResource.m_bConnected = NetVar::GetOffset(tables, "DT_PlayerResource", "m_bConnected");
    offsets.DT_PlayerResource.m_iTeam = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iTeam");
    offsets.DT_PlayerResource.m_iPendingTeam = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iPendingTeam");
    offsets.DT_PlayerResource.m_bAlive = NetVar::GetOffset(tables, "DT_PlayerResource", "m_bAlive");
    offsets.DT_PlayerResource.m_iHealth = NetVar::GetOffset(tables, "DT_PlayerResource", "m_iHealth");
    
    offsets.DT_CSPlayerResource.m_iPlayerC4 = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerC4");
    offsets.DT_CSPlayerResource.m_iPlayerVIP = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerVIP");
    offsets.DT_CSPlayerResource.m_bHostageAlive = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bHostageAlive");
    offsets.DT_CSPlayerResource.m_isHostageFollowingSomeone = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_isHostageFollowingSomeone");
    offsets.DT_CSPlayerResource.m_iHostageEntityIDs = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iHostageEntityIDs");
    offsets.DT_CSPlayerResource.m_bombsiteCenterB = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bombsiteCenterB");
    offsets.DT_CSPlayerResource.m_hostageRescueX = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueX");
    offsets.DT_CSPlayerResource.m_hostageRescueY = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueY");
    offsets.DT_CSPlayerResource.m_hostageRescueZ = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueZ");
    offsets.DT_CSPlayerResource.m_iMVPs = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iMVPs");
    offsets.DT_CSPlayerResource.m_iArmor = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iArmor");
    offsets.DT_CSPlayerResource.m_bHasHelmet = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bHasHelmet");
    offsets.DT_CSPlayerResource.m_bHasDefuser = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bHasDefuser");
    offsets.DT_CSPlayerResource.m_iScore = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iScore");
    offsets.DT_CSPlayerResource.m_iCompetitiveRanking = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveRanking");
    offsets.DT_CSPlayerResource.m_iCompetitiveWins = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveWins");
    offsets.DT_CSPlayerResource.m_iCompTeammateColor = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iCompTeammateColor");
    offsets.DT_CSPlayerResource.m_bControllingBot = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bControllingBot");
    offsets.DT_CSPlayerResource.m_iControlledPlayer = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledPlayer");
    offsets.DT_CSPlayerResource.m_iControlledByPlayer = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledByPlayer");
    offsets.DT_CSPlayerResource.m_iBotDifficulty = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iBotDifficulty");
    offsets.DT_CSPlayerResource.m_szClan = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_szClan");
    offsets.DT_CSPlayerResource.m_iTotalCashSpent = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iTotalCashSpent");
    offsets.DT_CSPlayerResource.m_iCashSpentThisRound = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_iCashSpentThisRound");
    offsets.DT_CSPlayerResource.m_nEndMatchNextMapVotes = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
    offsets.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
    offsets.DT_CSPlayerResource.m_nActiveCoinRank = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nActiveCoinRank");
    offsets.DT_CSPlayerResource.m_nMusicID = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nMusicID");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicLevel = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = NetVar::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");
    
    offsets.DT_PlantedC4.m_bBombTicking = NetVar::GetOffset(tables, "DT_PlantedC4", "m_bBombTicking");
    offsets.DT_PlantedC4.m_flC4Blow = NetVar::GetOffset(tables, "DT_PlantedC4", "m_flC4Blow");
    offsets.DT_PlantedC4.m_bBombDefused = NetVar::GetOffset(tables, "DT_PlantedC4", "m_bBombDefused");
    offsets.DT_PlantedC4.m_hBombDefuser = NetVar::GetOffset(tables, "DT_PlantedC4", "m_hBombDefuser");
    
    offsets.DT_CSPlayer.m_iShotsFired = NetVar::GetOffset(tables, "DT_CSPlayer", "m_iShotsFired");
    offsets.DT_CSPlayer.m_angEyeAngles[0] = NetVar::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[0]");
    offsets.DT_CSPlayer.m_angEyeAngles[1] = NetVar::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[1]");
    offsets.DT_CSPlayer.m_iAccount = NetVar::GetOffset(tables, "DT_CSPlayer", "m_iAccount");
    offsets.DT_CSPlayer.m_ArmorValue = NetVar::GetOffset(tables, "DT_CSPlayer", "m_ArmorValue");
    offsets.DT_CSPlayer.m_bHasDefuser = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
    offsets.DT_CSPlayer.m_bIsDefusing = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bIsDefusing");
    offsets.DT_CSPlayer.m_bIsGrabbingHostage = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bIsGrabbingHostage");
    offsets.DT_CSPlayer.m_bIsScoped = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bIsScoped");
    offsets.DT_CSPlayer.m_bGunGameImmunity = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bGunGameImmunity");
    offsets.DT_CSPlayer.m_bIsRescuing = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bIsRescuing");
    offsets.DT_CSPlayer.m_bHasHelmet = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bHasHelmet");
    offsets.DT_CSPlayer.m_bHasDefuser = NetVar::GetOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
    offsets.DT_CSPlayer.m_flFlashDuration = NetVar::GetOffset(tables, "DT_CSPlayer", "m_flFlashDuration");
    offsets.DT_CSPlayer.m_flFlashMaxAlpha = NetVar::GetOffset(tables, "DT_CSPlayer", "m_flFlashMaxAlpha");
    offsets.DT_CSPlayer.m_flLowerBodyYawTarget = NetVar::GetOffset(tables, "DT_CSPlayer", "m_flLowerBodyYawTarget");
    
    offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
    offsets.DT_BaseAttributableItem.m_iItemIDHigh = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
    offsets.DT_BaseAttributableItem.m_iAccountID = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_iAccountID");
    offsets.DT_BaseAttributableItem.m_iEntityQuality = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
    offsets.DT_BaseAttributableItem.m_szCustomName = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_szCustomName");
    offsets.DT_BaseAttributableItem.m_nFallbackPaintKit = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
    offsets.DT_BaseAttributableItem.m_nFallbackSeed = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
    offsets.DT_BaseAttributableItem.m_flFallbackWear = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
    offsets.DT_BaseAttributableItem.m_nFallbackStatTrak = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");
    offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
    offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidLow = NetVar::GetOffset(tables, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
    
    offsets.DT_BaseViewModel.m_nModelIndex = NetVar::GetOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
    offsets.DT_BaseViewModel.m_hWeapon = NetVar::GetOffset(tables, "DT_BaseViewModel", "m_hWeapon");
    offsets.DT_BaseViewModel.m_hOwner = NetVar::GetOffset(tables, "DT_BaseViewModel", "m_hOwner");
    
    offsets.DT_WeaponCSBase.m_fAccuracyPenalty = NetVar::GetOffset(tables, "DT_WeaponCSBase", "m_fAccuracyPenalty");
    offsets.DT_WeaponCSBase.m_flPostponeFireReadyTime = NetVar::GetOffset(tables, "DT_WeaponCSBase", "m_flPostponeFireReadyTime");
    
    offsets.DT_WeaponC4.m_bStartedArming = NetVar::GetOffset(tables, "DT_WeaponC4", "m_bStartedArming");
    
    offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack = NetVar::GetOffset(tables, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
    offsets.DT_BaseCombatWeapon.m_hOwner = NetVar::GetOffset(tables, "DT_BaseCombatWeapon", "m_hOwner");
    offsets.DT_BaseCombatWeapon.m_iClip1 = NetVar::GetOffset(tables, "DT_BaseCombatWeapon", "m_iClip1");
    offsets.DT_BaseCombatWeapon.m_bInReload = offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;
    
    offsets.DT_BaseCSGrenade.m_bIsHeldByPlayer = NetVar::GetOffset(tables, "DT_BaseCSGrenade", "m_bIsHeldByPlayer");
    offsets.DT_BaseCSGrenade.m_bPinPulled = NetVar::GetOffset(tables, "DT_BaseCSGrenade", "m_bPinPulled");
    offsets.DT_BaseCSGrenade.m_fThrowTime = NetVar::GetOffset(tables, "DT_BaseCSGrenade", "m_fThrowTime");
    offsets.DT_BaseCSGrenade.m_flThrowStrength = NetVar::GetOffset(tables, "DT_BaseCSGrenade", "m_flThrowStrength");
    
    offsets.DT_DynamicProp.m_bShouldGlow = NetVar::GetOffset(tables, "DT_DynamicProp", "m_bShouldGlow");
    
    offsets.DT_BaseAnimating.m_nSequence = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_nSequence");
    offsets.DT_BaseAnimating.m_flPoseParameter = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_flPoseParameter");
    offsets.DT_BaseAnimating.DT_ServerAnimationData.m_flCycle = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_flCycle");
    offsets.DT_BaseAnimating.m_Activity = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_Activity");
    offsets.DT_BaseAnimating.m_IdealActivity = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_IdealActivity");
    offsets.DT_BaseAnimating.m_eCurrentMainSequenceActivity = NetVar::GetOffset(tables, "DT_BaseAnimating", "m_eCurrentMainSequenceActivity");
    
    print("Found offsets", Color::Orange());
}
