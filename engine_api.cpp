// vi: set ts=4 sw=4 :
// vim: set tw=75 :

/*
 * Copyright (c) 2001-2006 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#include <extdll.h>

#include <meta_api.h>
#include <detours.h>
#include <vector>
#include <string>
#include "signatures.h"
#include "asext_api.h"
#include "enginedef.h"
#include "angelscript.h"

enginefuncs_t meta_engfuncs = 
{
	NULL,						// pfnPrecacheModel()
	NULL,						// pfnPrecacheSound()
	NULL,						// pfnSetModel()
	NULL,						// pfnModelIndex()
	NULL,						// pfnModelFrames()

	NULL,						// pfnSetSize()
	NULL,						// pfnChangeLevel()
	NULL,						// pfnGetSpawnParms()
	NULL,						// pfnSaveSpawnParms()

	NULL,						// pfnVecToYaw()
	NULL,						// pfnVecToAngles()
	NULL,						// pfnMoveToOrigin()
	NULL,						// pfnChangeYaw()
	NULL,						// pfnChangePitch()

	NULL,						// pfnFindEntityByString()
	NULL,						// pfnGetEntityIllum()
	NULL,						// pfnFindEntityInSphere()
	NULL,						// pfnFindClientInPVS()
	NULL,						// pfnEntitiesInPVS()

	NULL,						// pfnMakeVectors()
	NULL,						// pfnAngleVectors()

	NULL,						// pfnCreateEntity()
	NULL,						// pfnRemoveEntity()
	NULL,						// pfnCreateNamedEntity()

	NULL,						// pfnMakeStatic()
	NULL,						// pfnEntIsOnFloor()
	NULL,						// pfnDropToFloor()

	NULL,						// pfnWalkMove()
	NULL,						// pfnSetOrigin()

	NULL,						// pfnEmitSound()
	NULL,						// pfnEmitAmbientSound()

	NULL,						// pfnTraceLine()
	NULL,						// pfnTraceToss()
	NULL,						// pfnTraceMonsterHull()
	NULL,						// pfnTraceHull()
	NULL,						// pfnTraceModel()
	NULL,						// pfnTraceTexture()
	NULL,						// pfnTraceSphere()
	NULL,						// pfnGetAimVector()

	NULL,						// pfnServerCommand()
	NULL,						// pfnServerExecute()
	NULL,						// pfnClientCommand()

	NULL,						// pfnParticleEffect()
	NULL,						// pfnLightStyle()
	NULL,						// pfnDecalIndex()
	NULL,						// pfnPointContents()

	NULL,						// pfnMessageBegin()
	NULL,						// pfnMessageEnd()

	NULL,						// pfnWriteByte()
	NULL,						// pfnWriteChar()
	NULL,						// pfnWriteShort()
	NULL,						// pfnWriteLong()
	NULL,						// pfnWriteAngle()
	NULL,						// pfnWriteCoord()
	NULL,						// pfnWriteString()
	NULL,						// pfnWriteEntity()

	NULL,						// pfnCVarRegister()
	NULL,						// pfnCVarGetFloat()
	NULL,						// pfnCVarGetString()
	NULL,						// pfnCVarSetFloat()
	NULL,						// pfnCVarSetString()

	NULL,						// pfnAlertMessage()
	NULL,						// pfnEngineFprintf()

	NULL,						// pfnPvAllocEntPrivateData()
	NULL,						// pfnPvEntPrivateData()
	NULL,						// pfnFreeEntPrivateData()

	NULL,						// pfnSzFromIndex()
	NULL,						// pfnAllocString()

	NULL, 						// pfnGetVarsOfEnt()
	NULL,						// pfnPEntityOfEntOffset()
	NULL,						// pfnEntOffsetOfPEntity()
	NULL,						// pfnIndexOfEdict()
	NULL,						// pfnPEntityOfEntIndex()
	NULL,						// pfnFindEntityByVars()
	NULL,						// pfnGetModelPtr()

	NULL,						// pfnRegUserMsg()

	NULL,						// pfnAnimationAutomove()
	NULL,						// pfnGetBonePosition()

	NULL,						// pfnFunctionFromName()
	NULL,						// pfnNameForFunction()

	NULL,						// pfnClientPrintf()
	NULL,						// pfnServerPrint()

	NULL,						// pfnCmd_Args()
	NULL,						// pfnCmd_Argv()
	NULL,						// pfnCmd_Argc()

	NULL,						// pfnGetAttachment()

	NULL,						// pfnCRC32_Init()
	NULL,						// pfnCRC32_ProcessBuffer()
	NULL,						// pfnCRC32_ProcessByte()
	NULL,						// pfnCRC32_Final()

	NULL,						// pfnRandomLong()
	NULL,						// pfnRandomFloat()

	NULL,						// pfnSetView()
	NULL,						// pfnTime()
	NULL,						// pfnCrosshairAngle()

	NULL,						// pfnLoadFileForMe()
	NULL,						// pfnFreeFile()

	NULL,						// pfnEndSection()
	NULL,						// pfnCompareFileTime()
	NULL,						// pfnGetGameDir()
	NULL,						// pfnCvar_RegisterVariable()
	NULL,						// pfnFadeClientVolume()
	NULL,						// pfnSetClientMaxspeed()
	NULL,						// pfnCreateFakeClient()
	NULL,						// pfnRunPlayerMove()
	NULL,						// pfnNumberOfEntities()

	NULL,						// pfnGetInfoKeyBuffer()
	NULL,						// pfnInfoKeyValue()
	NULL,						// pfnSetKeyValue()
	NULL,						// pfnSetClientKeyValue()

	NULL,						// pfnIsMapValid()
	NULL,						// pfnStaticDecal()
	NULL,						// pfnPrecacheGeneric()
	NULL, 						// pfnGetPlayerUserId()
	NULL,						// pfnBuildSoundMsg()
	NULL,						// pfnIsDedicatedServer()
	NULL,						// pfnCVarGetPointer()
	NULL,						// pfnGetPlayerWONId()

	NULL,						// pfnInfo_RemoveKey()
	NULL,						// pfnGetPhysicsKeyValue()
	NULL,						// pfnSetPhysicsKeyValue()
	NULL,						// pfnGetPhysicsInfoString()
	NULL,						// pfnPrecacheEvent()
	NULL,						// pfnPlaybackEvent()

	NULL,						// pfnSetFatPVS()
	NULL,						// pfnSetFatPAS()

	NULL,						// pfnCheckVisibility()

	NULL,						// pfnDeltaSetField()
	NULL,						// pfnDeltaUnsetField()
	NULL,						// pfnDeltaAddEncoder()
	NULL,						// pfnGetCurrentPlayer()
	NULL,						// pfnCanSkipPlayer()
	NULL,						// pfnDeltaFindField()
	NULL,						// pfnDeltaSetFieldByIndex()
	NULL,						// pfnDeltaUnsetFieldByIndex()

	NULL,						// pfnSetGroupMask()

	NULL,						// pfnCreateInstancedBaseline()
	NULL,						// pfnCvar_DirectSet()

	NULL,						// pfnForceUnmodified()

	NULL,						// pfnGetPlayerStats()

	NULL,						// pfnAddServerCommand()

	// Added in SDK 2.2:
	NULL,						// pfnVoice_GetClientListening()
	NULL,						// pfnVoice_SetClientListening()

	// Added for HL 1109 (no SDK update):
	NULL,						// pfnGetPlayerAuthId()

	// Added 2003/11/10 (no SDK update):
	NULL,						// pfnSequenceGet()
	NULL,						// pfnSequencePickSentence()
	NULL,						// pfnGetFileSize()
	NULL,						// pfnGetApproxWavePlayLen()
	NULL,						// pfnIsCareerMatch()
	NULL,						// pfnGetLocalizedStringLength()
	NULL,						// pfnRegisterTutorMessageShown()
	NULL,						// pfnGetTimesTutorMessageShown()
	NULL,						// pfnProcessTutorMessageDecayBuffer()
	NULL,						// pfnConstructTutorMessageDecayBuffer()
	NULL,						// pfnResetTutorMessageDecayData()

	// Added Added 2005-08-11 (no SDK update)
	NULL,						// pfnQueryClientCvarValue()
	// Added Added 2005-11-22 (no SDK update)
	NULL,						// pfnQueryClientCvarValue2()
	// Added 2009-06-17 (no SDK update)
	NULL,						// pfnEngCheckParm()
};

void* GetEntVarsVTable(entvars_t* var) {
	if (var == nullptr)
		return nullptr;
	return ENT(var)->pvPrivateData;
}

/// <summary>
/// Monster Take Damage
/// </summary>
hook_t* g_phook_BaseMonsterTakeDamage = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterTakeDamage);
int SC_SERVER_DECL NewBaseMonsterTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
		};
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterTakeDamage, 0, &dmg);
	int result = g_call_original_BaseMonsterTakeDamage(pThis, SC_SERVER_PASS_DUMMYARG pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterPostTakeDamage, 0, &dmg);
	return result;
}
// Apache
hook_t* g_phook_ApacheTakeDamage = nullptr;
PRIVATE_FUNCTION_DEFINE(ApacheTakeDamage);
int SC_SERVER_DECL NewApacheTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
		};
	int result = g_call_original_ApacheTakeDamage(pThis, SC_SERVER_PASS_DUMMYARG pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterPostTakeDamage, 0, &dmg);
	return result;
}

/// <summary>
/// Monster Killed
/// </summary>
hook_t* g_phook_BaseMonsterKilled = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterKilled);
void SC_SERVER_DECL NewBaseMonsterKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterKilled, 0, pThis, pevAttacker, iGib);
	g_call_original_BaseMonsterKilled(pThis, SC_SERVER_PASS_DUMMYARG pevAttacker, iGib);
}
// Apache
hook_t* g_phook_ApacheKilled = nullptr;
PRIVATE_FUNCTION_DEFINE(ApacheKilled);
void SC_SERVER_DECL NewApacheKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterKilled, 0, pThis, pevAttacker, iGib);
	g_call_original_ApacheKilled(pThis, SC_SERVER_PASS_DUMMYARG pevAttacker, iGib);
}
// Osprey
hook_t* g_phook_OspreyKilled = nullptr;
PRIVATE_FUNCTION_DEFINE(OspreyKilled);
void SC_SERVER_DECL NewOspreyKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	if (ASEXT_CallHook) 
		(*ASEXT_CallHook)(g_AngelHook.pMonsterKilled, 0, pThis, pevAttacker, iGib);
	g_call_original_OspreyKilled(pThis, SC_SERVER_PASS_DUMMYARG pevAttacker, iGib);
}
/// <summary>
/// Monster Trace Attack
/// </summary>
hook_t* g_phook_BaseMonsterTraceAttack = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterTraceAttack);
void SC_SERVER_DECL NewBaseMonsterTraceAttack(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterTraceAttack, 0, pThis, pevAttacker, flDamage, ptr, bitsDamageType);
	g_call_original_BaseMonsterTraceAttack(pThis, SC_SERVER_PASS_DUMMYARG pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
// Apache
hook_t* g_phook_ApacheTraceAttack = nullptr;
PRIVATE_FUNCTION_DEFINE(ApacheTraceAttack);
void SC_SERVER_DECL NewApacheTraceAttack(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pMonsterTraceAttack, 0, pThis, pevAttacker, flDamage, ptr, bitsDamageType);
	g_call_original_ApacheTraceAttack(pThis, SC_SERVER_PASS_DUMMYARG pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
/// <summary>
/// Breakable Die
/// </summary>
hook_t* g_phook_BreakableDie = nullptr;
PRIVATE_FUNCTION_DEFINE(BreakableDie);
void SC_SERVER_DECL NewBreakableDie(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) {
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pBreakableDie, 0, pThis);
	g_call_original_BreakableDie(pThis SC_SERVER_PASS_DUMMYARG_NOCOMMA);
}
/// <summary>
/// Breakable TakeDamage
/// </summary>
hook_t* g_phook_BreakableTakeDamage = nullptr;
PRIVATE_FUNCTION_DEFINE(BreakableTakeDamage);
int SC_SERVER_DECL NewBreakableTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
		};
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pBreakableTakeDamage, 0, &dmg);
	return g_call_original_BreakableTakeDamage(pThis, SC_SERVER_PASS_DUMMYARG pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}

/// <summary>
/// Grapple GetMonsterType
/// </summary>
hook_t* g_phook_GrappleGetMonsterType = nullptr;
PRIVATE_FUNCTION_DEFINE(GrappleGetMonsterType);
GRAPPLE_RESULT SC_SERVER_DECL NewGrappleGetMonsterType(void* pThis, SC_SERVER_DUMMYARG void* pEntity) {
	int uiFlag = 0;
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pGrappleCheckMonsterType, 0, pThis, pEntity, &uiFlag);
	if (uiFlag != 0 && uiFlag <= 2 && uiFlag >= 1)
		return (GRAPPLE_RESULT)uiFlag;
	return g_call_original_GrappleGetMonsterType(pThis, SC_SERVER_PASS_DUMMYARG pEntity);
}
/// <summary>
/// SendScoreInfo
/// </summary>
hook_t* g_phook_SendScoreInfo = nullptr;
PRIVATE_FUNCTION_DEFINE(SendScoreInfo);
void SC_SERVER_DECL NewSendScoreInfo(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName) {
	int uiFlag = 0;
	if (ASEXT_CallHook)
		(*ASEXT_CallHook)(g_AngelHook.pSendScoreInfo, 0, pThis, eSendTarget, iTeamID, szTeamName, &uiFlag);
	if (uiFlag != 0)
		return;
	g_call_original_SendScoreInfo(pThis, SC_SERVER_PASS_DUMMYARG eSendTarget, iTeamID, szTeamName);
}


/// <summary>
/// Fiil
/// </summary>
//PRIVATE_FUNCTION_DEFINE(LookupSoundIndex);

bool SearchAndHook() {
	auto ServerHandle = gpMetaUtilFuncs->pfnGetGameDllHandle();
	auto EngineHandle = gpMetaUtilFuncs->pfnGetEngineHandle();

	auto ServerBase = gpMetaUtilFuncs->pfnGetGameDllBase();
	auto EngineBase = gpMetaUtilFuncs->pfnGetEngineBase();
#ifdef WIN32
#define BaseMonsterTakeDamage_Signature "\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x48\xF7\x45\x14\x00\x00\x00\x08\x56\x57\x8B\xF9\x0F\x84\x90\x00\x00\x00"
//Apache
#define ApacheTakeDamage_Signature "\x83\xEC\x0C\x53\x8B\x5C\x24\x20\x55\x56\x8B\xF1\x57\xF7\xC3\x00\x00\x00\x08\x0F\x84\x90\x00\x00\x00"
#define ApacheKilled_Signature "\x83\xEC\x18\x56\x8B\xF1\x8B\x46\x04\x8B\x80\x98\x01\x00\x00\x85\xC0\x75\x0E\x50"
#define ApacheTraceAttack_Signature "\x8B\x54\x24\x18\x57\x8B\xF9\x8B\x42\x34\x83\xF8\x06\x75\x0A"
//Ospery
#define OspreyKilled_Signature "\x83\xEC\x18\x56\x8B\xF1\x57\x8B\x46\x04\x85\xC0\x74\x06\x8B\x80\x08\x02\x00\x00\x68\x2A\x2A\x2A\x2A\x50\xE8\xF1\x8F\x0A\x00\x8B\x56\x04"

#define BaseMonsterKilled_Signature "\x53\x8B\x5C\x24\x0C\x56\x8B\xF1\x57\x8B\x7C\x24\x10"
#define BaseMonsterTraceAttack_Signature "\x53\x55\x56\x8B\xF1\x57\x8B\x46\x04\xF3\x0F\x10\x80\x6C\x01\x00\x00"
#define BreakableDie_Signature "\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF8\x83\xC4\x04\x55\x8B\x6B\x04\x89\x2A\x2A\x2A\x2A\xEC\x6A\xFF\x68\xB7\x71"
#define BreakableTakeDamage_Signature "\x83\xEC\x5C\x53\x55\x56\x8B\xF1\x57\x80\x2A\x2A\x2A\x2A\x00\x00\x0F\x85\xF6\x04\x00\x00\x8B\x7C"
#define GrappleGetMonsterType_Signature "\x8B\x44\x24\x04\xB9\x2A\x2A\x2A\x2A\x53\x56\x8B\x70\x04\xA1\x2A\x2A\x2A\x2A\x8B\x90\x98\x00\x00\x00\x03\x16\x8B\xC2\x0F\x1F\x00"
#define SendScoreInfo_Signature "\x53\x8B\x5C\x24\x08\x57\x8B\xF9\x85\xDB\x0F\x84\xBB\x01\x00\x00"

#else
#define BaseMonsterTakeDamage_Signature "_ZN12CBaseMonster10TakeDamageEP9entvars_sS1_fi"
//Apache
#define ApacheTakeDamage_Signature "_ZN7CApache10TakeDamageEP9entvars_sS1_fi"
#define ApacheKilled_Signature "_ZN7CApache6KilledEP9entvars_si"
#define ApacheTraceAttack_Signature "_ZN7CApache11TraceAttackEP9entvars_sf6VectorP11TraceResulti"
//Ospery
#define OspreyKilled_Signature "_ZN7COsprey6KilledEP9entvars_si"

#define BaseMonsterKilled_Signature "_ZN12CBaseMonster6KilledEP9entvars_si"
#define BaseMonsterTraceAttack_Signature "_ZN12CBaseMonster11TraceAttackEP9entvars_sf6Ve"
#define BreakableDie_Signature "_ZN10CBreakable3DieEv"
#define BreakableTakeDamage_Signature "_ZN10CBreakable10TakeDamageEP9entvars_sS1_fi"
#define GrappleGetMonsterType_Signature "_ZN22CBarnacleGrappleTongue14GetMonsterTypeEP11CBaseEntity"
#define SendScoreInfo_Signature "_ZN11CBasePlayer26SendScoreInfoToOtherPlayerEP7edict_siPKc"
#endif
	//Fill
	
	// Fill and Hook
	FILL_AND_HOOK(Server, BaseMonsterTakeDamage);
	//Apache
	FILL_AND_HOOK(Server, ApacheTakeDamage);
	FILL_AND_HOOK(Server, ApacheKilled);
	FILL_AND_HOOK(Server, ApacheTraceAttack);
	//Ospery
	FILL_AND_HOOK(Server, OspreyKilled);

	FILL_AND_HOOK(Server, BaseMonsterKilled);
	FILL_AND_HOOK(Server, BaseMonsterTraceAttack);
	FILL_AND_HOOK(Server, BreakableDie);
	FILL_AND_HOOK(Server, BreakableTakeDamage);
	FILL_AND_HOOK(Server, GrappleGetMonsterType);
	FILL_AND_HOOK(Server, SendScoreInfo);
	return true;
}
void UninstallHook() {
	UNINSTALL_HOOK(BaseMonsterTakeDamage);
	UNINSTALL_HOOK(ApacheTakeDamage);
	UNINSTALL_HOOK(ApacheKilled);
	UNINSTALL_HOOK(ApacheTraceAttack);
	UNINSTALL_HOOK(OspreyKilled);

	UNINSTALL_HOOK(BaseMonsterKilled);
	UNINSTALL_HOOK(BaseMonsterTraceAttack);
	UNINSTALL_HOOK(BreakableDie);
	UNINSTALL_HOOK(BreakableTakeDamage);
	UNINSTALL_HOOK(GrappleGetMonsterType);
	UNINSTALL_HOOK(SendScoreInfo);
}

C_DLLEXPORT int GetEngineFunctions(enginefuncs_t* pengfuncsFromEngine,
	int* interfaceVersion)
{
	if (!pengfuncsFromEngine) {
		UTIL_LogPrintf("GetEngineFunctions called with null pengfuncsFromEngine");
		return false;
	}
	else if (*interfaceVersion != ENGINE_INTERFACE_VERSION) {
		UTIL_LogPrintf("GetEngineFunctions version mismatch; requested=%d ours=%d", *interfaceVersion, ENGINE_INTERFACE_VERSION);
		// Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = ENGINE_INTERFACE_VERSION;
		return false;
	}
	memcpy(pengfuncsFromEngine, &meta_engfuncs, sizeof(enginefuncs_t));
	
	return SearchAndHook();
}
