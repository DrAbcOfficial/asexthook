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
#include "enginedef.h"
#include "asext_api.h"
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

/// <summary>
/// Monster Take Damage
/// </summary>
hook_t* g_phook_BaseMonsterTakeDamage = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterTakeDamage);
int _fastcall NewBaseMonsterTakeDamage(void* pThis, int dummy, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	int r = g_call_original_BaseMonsterTakeDamage(pThis, dummy, pevInflictor, pevAttacker, flDamage, bitsDamageType);
	if (ASEXT_CallHook) {
		//CBaseMonster@ pMonster, entvars_t@ pAttacker, entvars_t@ pInflictor, float flDamage, int bitDamageType
		(*ASEXT_CallHook)(g_AngelHook.pMonsterTakeDamage, 0, pThis, pevAttacker, pevInflictor, flDamage, bitsDamageType);
	}
	return r;
}
/// <summary>
/// Monster Killed
/// </summary>
hook_t* g_phook_BaseMonsterKilled = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterKilled);
void _fastcall NewBaseMonsterKilled(void* pThis, int dummy, entvars_t* pevAttacker, int iGib) {
	g_call_original_BaseMonsterKilled(pThis, dummy, pevAttacker, iGib);
	if (ASEXT_CallHook) {
		//CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib
		(*ASEXT_CallHook)(g_AngelHook.pMonsterKilled, 0, pThis, pevAttacker, iGib);
	}
}
/// <summary>
/// Monster Trace Attack
/// </summary>
hook_t* g_phook_BaseMonsterTraceAttack = nullptr;
PRIVATE_FUNCTION_DEFINE(BaseMonsterTraceAttack);
void _fastcall NewBaseMonsterTraceAttack(void* pThis, int dummy, entvars_t* pevAttacker, float flDamage, vec3_t vecHitpos, TraceResult tr, int bitDamage) {
	g_call_original_BaseMonsterTraceAttack(pThis, dummy, pevAttacker, flDamage, vecHitpos, tr, bitDamage);
	if (ASEXT_CallHook) {
		//CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecHitpos, TraceResult tr, int bitDamageType
		(*ASEXT_CallHook)(g_AngelHook.pMonsterTraceAttack, 0, pThis, pevAttacker, flDamage, vecHitpos, tr, bitDamage);
	}
}
hook_t* g_phook_BreakableDie = nullptr;
PRIVATE_FUNCTION_DEFINE(BreakableDie);
void _fastcall NewBreakableDie(void* pThis, int dummy) {
	g_call_original_BreakableDie(pThis, dummy);
	if (ASEXT_CallHook) {
		//CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecHitpos, TraceResult tr, int bitDamageType
		(*ASEXT_CallHook)(g_AngelHook.pBreakableDie, 0, pThis);
	}
}

C_DLLEXPORT int GetEngineFunctions(enginefuncs_t* pengfuncsFromEngine,
	int* interfaceVersion)
{
	if (!pengfuncsFromEngine) {
		UTIL_LogPrintf("GetEngineFunctions called with null pengfuncsFromEngine");
		return(FALSE);
	}
	else if (*interfaceVersion != ENGINE_INTERFACE_VERSION) {
		UTIL_LogPrintf("GetEngineFunctions version mismatch; requested=%d ours=%d", *interfaceVersion, ENGINE_INTERFACE_VERSION);
		// Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = ENGINE_INTERFACE_VERSION;
		return(FALSE);
	}
	memcpy(pengfuncsFromEngine, &meta_engfuncs, sizeof(enginefuncs_t));
#ifdef WIN32
	HMODULE g_dwServerBase = GetModuleHandleA("server.dll");
	HMODULE g_dwEngineBase = GetModuleHandleA("hw.dll");

#define BaseMonsterTakeDamage_Signature "\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x48\xF7\x45\x14\x00\x00\x00\x08\x56\x57\x8B\xF9\x0F\x84\x90\x00\x00\x00"
	FILL_FROM_SIGNATURE(g_dwServer, BaseMonsterTakeDamage);
	INSTALL_INLINEHOOK(BaseMonsterTakeDamage);
#undef BaseMonsterTakeDamage_Signature

#define BaseMonsterKilled_Signature "\x53\x8B\x5C\x24\x0C\x56\x8B\xF1\x57\x8B\x7C\x24\x10"
	FILL_FROM_SIGNATURE(g_dwServer, BaseMonsterKilled);
	INSTALL_INLINEHOOK(BaseMonsterKilled);
#undef BaseMonsterKilled_Signature

#define BaseMonsterTraceAttack_Signature "\x53\x55\x56\x8B\xF1\x57\x8B\x46\x04\xF3\x0F\x10\x80\x6C\x01\x00\x00"
	FILL_FROM_SIGNATURE(g_dwServer, BaseMonsterTraceAttack);
	INSTALL_INLINEHOOK(BaseMonsterTraceAttack);
#undef BaseMonsterTraceAttack_Signature

#define BreakableDie_Signature "\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF8\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x6A\xFF\x68\xB7\x71\x38\x10"
	FILL_FROM_SIGNATURE(g_dwServer, BreakableDie);
	INSTALL_INLINEHOOK(BreakableDie);
#undef BreableDie_Signature

#else
	UTIL_LogPrintf("Fuck! not support Linux yet!");
#endif
	return(TRUE);
}
