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

#include <vector>

#include <detours.h>
#include <dllapi.h>
#include <meta_api.h>
#include <log_meta.h>
#include "usercmd.h"

#include "signatures.h"
#include "asext_api.h"
#include "angelscript.h"
#include "vftable.h"
#include "utility.h"

#include "dlldef.h"

#define CALL_ANGELSCRIPT(pfn, ...) if (ASEXT_CallHook){(*ASEXT_CallHook)(g_AngelHook.pfn, 0, __VA_ARGS__);}

using namespace std;

bool g_HookedFlag = false;

struct{
	hookitem_t BaseMonsterTraceAttack;
	hookitem_t BaseMonsterTakeDamage;
	hookitem_t BaseMonsterKilled;

	hookitem_t ApacheTraceAttack;
	hookitem_t ApacheTakeDamage;
	hookitem_t ApacheKilled;

	hookitem_t OspreyTraceAttack;
	hookitem_t OspreyKilled;

	hookitem_t SentryTakeDamage;
	hookitem_t SentryKilled;

	hookitem_t TurretTraceAttack;
	hookitem_t TurretTakeDamage;

	hookitem_t BreakableTraceAttack;
	hookitem_t BreakableKilled;
	hookitem_t BreakableTakeDamage;
	
	hookitem_t PlayerPostTakeDamage;
	hookitem_t PlayerTakeHealth;
} gHookItems;
vector<hook_t*> gHooks;
#define CALL_ORIGIN(item, type, ...) ((decltype(item.pVtable->type))item.pfnOriginalCall)(pThis, SC_SERVER_PASS_DUMMYARG __VA_ARGS__)
#define CALL_ORIGIN_NOARG(item, type) ((decltype(item.pVtable->type))item.pfnOriginalCall)(pThis, SC_SERVER_PASS_DUMMYARG_NOCOMMA)

void SC_SERVER_DECL BaseMonsterTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.BaseMonsterTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
int SC_SERVER_DECL BaseMonsterTakeDamage(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
		pThis,
		GetEntVarsVTable(pevInflictor),
		GetEntVarsVTable(pevAttacker),
		flDamage,
		bitsDamageType
	};
	CALL_ANGELSCRIPT(pMonsterTakeDamage, &dmg)
	return CALL_ORIGIN(gHookItems.BaseMonsterTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}
void SC_SERVER_DECL BaseMonsterKilled(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pMonsterKilled, pThis, pevAttacker, iGib)
	CALL_ORIGIN(gHookItems.BaseMonsterKilled, Killed, pevAttacker, iGib);
}

void SC_SERVER_DECL ApacheTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.ApacheTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
int SC_SERVER_DECL ApacheTakeDamage(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGELSCRIPT(pMonsterTakeDamage, &dmg)
	return CALL_ORIGIN(gHookItems.ApacheTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}
void SC_SERVER_DECL ApacheKilled(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pMonsterKilled, pevAttacker, iGib)
	CALL_ORIGIN(gHookItems.ApacheKilled, Killed, pevAttacker, iGib);
}

void SC_SERVER_DECL OspreyTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.OspreyTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
void SC_SERVER_DECL OspreyKilled(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pMonsterKilled, pThis, pevAttacker, iGib);
	CALL_ORIGIN(gHookItems.OspreyKilled, Killed, pevAttacker, iGib);
}

int SC_SERVER_DECL SentryTakeDamage(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGELSCRIPT(pMonsterTakeDamage, &dmg)
		return CALL_ORIGIN(gHookItems.SentryTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}
void SC_SERVER_DECL SentryKilled(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pMonsterKilled, pThis, pevAttacker, iGib)
	CALL_ORIGIN(gHookItems.SentryKilled, Killed, pevAttacker, iGib);
}

void SC_SERVER_DECL TurretTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.TurretTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
int SC_SERVER_DECL TurretTakeDamage(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGELSCRIPT(pMonsterTakeDamage, &dmg)
		return CALL_ORIGIN(gHookItems.TurretTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}

void SC_SERVER_DECL BreakableTraceAttack(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pBreakableTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.BreakableTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
void SC_SERVER_DECL BreakableKilled(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pBreakableKilled, pThis, pevAttacker, iGib);
	CALL_ORIGIN(gHookItems.BreakableKilled, Killed, pevAttacker, iGib);
}
int SC_SERVER_DECL BreakableTakeDamage(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGELSCRIPT(pBreakableTakeDamage, &dmg)
	return CALL_ORIGIN(gHookItems.BreakableTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}

int SC_SERVER_DECL PlayerPostTakeDamage(CBasePlayer* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	int result = CALL_ORIGIN(gHookItems.PlayerPostTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
	CALL_ANGELSCRIPT(pPlayerPostTakeDamage, &dmg);
	return result;
}
int SC_SERVER_DECL PlayerTakeHealth(CBasePlayer* pThis, SC_SERVER_DUMMYARG float flDamage, int bitsDamageType, int cap) {
	healthinfo_t dmg = {
		pThis,
		flDamage,
		bitsDamageType,
		cap
	};
	CALL_ANGELSCRIPT(pPlayerTakeHealth, &dmg);
	return CALL_ORIGIN(gHookItems.PlayerTakeHealth, TakeHealth, dmg.flHealth, dmg.bitsDamageType, dmg.health_cap);
}
#undef CALL_ORIGIN
#undef CALL_ORIGIN_NOARG

void ServerActivate (edict_t* pEdictList, int edictCount, int clientMax) {
	if (g_HookedFlag) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}

#define ITEM_HOOK(item, type, table, newfunc) item.pfnOriginalCall=item.pfnCall=(void*)table->type;item.pVtable=table;item.pHook=gpMetaUtilFuncs->pfnInlineHook(item.pfnCall,(void*)newfunc,(void**)&item.pfnOriginalCall,false);gHooks.push_back(item.pHook)
	vtable_base_t* vtable = AddEntityVTable("monster_apache");
	ITEM_HOOK(gHookItems.ApacheTraceAttack, TraceAttack, vtable, ApacheTraceAttack);
	ITEM_HOOK(gHookItems.ApacheTakeDamage, TakeDamage, vtable, ApacheTakeDamage);
	ITEM_HOOK(gHookItems.ApacheKilled, Killed, vtable, ApacheKilled);
	vtable = AddEntityVTable("monster_osprey");
	ITEM_HOOK(gHookItems.OspreyTraceAttack, TraceAttack, vtable, OspreyTraceAttack);
	ITEM_HOOK(gHookItems.OspreyKilled, Killed, vtable, OspreyKilled);
	vtable = AddEntityVTable("monster_sentry");
	ITEM_HOOK(gHookItems.SentryTakeDamage, TakeDamage, vtable, SentryTakeDamage);
	ITEM_HOOK(gHookItems.SentryKilled, Killed, vtable, SentryKilled);
	vtable = AddEntityVTable("monster_turret");
	ITEM_HOOK(gHookItems.TurretTraceAttack, TraceAttack, vtable, TurretTraceAttack);
	ITEM_HOOK(gHookItems.TurretTakeDamage, TakeDamage, vtable, TurretTakeDamage);
	vtable = AddEntityVTable("func_breakable");
	ITEM_HOOK(gHookItems.BreakableTraceAttack, TraceAttack, vtable, BreakableTraceAttack);
	ITEM_HOOK(gHookItems.BreakableTakeDamage, TakeDamage, vtable, BreakableTakeDamage);
	ITEM_HOOK(gHookItems.BreakableKilled, Killed, vtable, BreakableKilled);
	vtable = AddEntityVTable("monster_bloater");
	ITEM_HOOK(gHookItems.BaseMonsterTraceAttack, TraceAttack, vtable, BaseMonsterTraceAttack);
	ITEM_HOOK(gHookItems.BaseMonsterKilled, Killed, vtable, BaseMonsterKilled);
	vtable = AddEntityVTable("monster_ichthyosaur");
	ITEM_HOOK(gHookItems.BaseMonsterTakeDamage, TakeDamage, vtable, BaseMonsterTakeDamage);
	vtable = AddEntityVTable("player");
	ITEM_HOOK(gHookItems.PlayerPostTakeDamage, TakeDamage, vtable, PlayerPostTakeDamage);
	ITEM_HOOK(gHookItems.PlayerTakeHealth, TakeHealth, vtable, PlayerTakeHealth);
#undef ITEM_HOOK

	g_HookedFlag = true;
	SET_META_RESULT(MRES_HANDLED);
}
void VtableUnhook() {
	for (auto iter = gHooks.begin(); iter != gHooks.end(); iter++) {
		if (*iter) { 
			gpMetaUtilFuncs->pfnUnHook(*iter);
			*iter = nullptr;
		}
	}
	gHooks.clear();
}

void ClientCommand(edict_t* pEntity) {
	if (!pEntity->pvPrivateData) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}
	const char* pcmd = CMD_ARGV(0);
	if (!strcmp(pcmd, "medic")) {
		CALL_ANGELSCRIPT(pPlayerCallMedic, pEntity->pvPrivateData);
		SET_META_RESULT(MRES_HANDLED);
		return;
	}
	else if (!strcmp(pcmd, "grenade")) {
		CALL_ANGELSCRIPT(pPlayerCallGrenade, pEntity->pvPrivateData);
		SET_META_RESULT(MRES_HANDLED);
		return;
	}
	SET_META_RESULT(MRES_IGNORED);
}

void ClientUserInfoChanged(edict_t* pEntity, char* infobuffer) {
	if (pEntity == nullptr) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}
	int uiFlag = 0;
	CALL_ANGELSCRIPT(pPlayerUserInfoChanged, pEntity->pvPrivateData, infobuffer, &uiFlag);
	if (uiFlag != 0)
		SET_META_RESULT(MRES_SUPERCEDE);
	else
		SET_META_RESULT(MRES_HANDLED);
}
int AllowLagCompensation() {
	SET_META_RESULT(MRES_SUPERCEDE);
	return CVAR_GET_FLOAT("sv_unlag") > 0 ? 1 : 0;
}

int Spawn_Post(edict_t* pent) {
	if (pent != nullptr) {
		CALL_ANGELSCRIPT(pEntitySpawn, pent->pvPrivateData);
		//Something(Zomibes Crab etc) will not be tagged FL_MONSTER
		//Something(Handgrenade) will be tagged FL_MONSTER
		//Why u remove MonsterInit() from CZombie::Spawn????
		//if ((VARS(pent)->flags & FL_MONSTER) > 0) {
		const char* szClassName = STRING((VARS(pent)->classname));
		if ((strlen(szClassName) > 8) && (strncmp(szClassName, "monster_", 8) == 0))
			CALL_ANGELSCRIPT(pMonsterSpawn, pent->pvPrivateData);
	}
	SET_META_RESULT(MRES_HANDLED);
	return 1919810;
}
static DLL_FUNCTIONS gFunctionTable = {
	NULL,					// pfnGameInit
	NULL,					// pfnSpawn
	NULL,					// pfnThink
	NULL,					// pfnUse
	NULL,				// pfnTouch
	NULL,				// pfnBlocked
	NULL,					// pfnKeyValue
	NULL,					// pfnSave
	NULL,					// pfnRestore
	NULL,					// pfnSetAbsBox

	NULL,					// pfnSaveWriteFields
	NULL,					// pfnSaveReadFields

	NULL,					// pfnSaveGlobalState
	NULL,					// pfnRestoreGlobalState
	NULL,					// pfnResetGlobalState

	NULL,					// pfnClientConnect
	NULL,					// pfnClientDisconnect
	NULL,					// pfnClientKill
	NULL,					// pfnClientPutInServer
	ClientCommand,					// pfnClientCommand
	ClientUserInfoChanged,					// pfnClientUserInfoChanged
	ServerActivate,					// pfnServerActivate
	NULL,					// pfnServerDeactivate

	NULL,					// pfnPlayerPreThink
	NULL,					// pfnPlayerPostThink

	NULL,					// pfnStartFrame
	NULL,					// pfnParmsNewLevel
	NULL,					// pfnParmsChangeLevel

	NULL,					// pfnGetGameDescription
	NULL,					// pfnPlayerCustomization

	NULL,					// pfnSpectatorConnect
	NULL,					// pfnSpectatorDisconnect
	NULL,					// pfnSpectatorThink

	NULL,					// pfnSys_Error

	NULL,					// pfnPM_Move
	NULL,					// pfnPM_Init
	NULL,					// pfnPM_FindTextureType

	NULL,					// pfnSetupVisibility
	NULL,					// pfnUpdateClientData
	NULL,					// pfnAddToFullPack
	NULL,					// pfnCreateBaseline
	NULL,					// pfnRegisterEncoders
	NULL,					// pfnGetWeaponData
	NULL,					// pfnCmdStart
	NULL,					// pfnCmdEnd
	NULL,					// pfnConnectionlessPacket
	NULL,					// pfnGetHullBounds
	NULL,					// pfnCreateInstancedBaselines
	NULL,					// pfnInconsistentFile
	AllowLagCompensation,					// pfnAllowLagCompensation
};
C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS* pFunctionTable,
	int* interfaceVersion){
	if (!pFunctionTable) {
		UTIL_LogPrintf("GetEntityAPI2 called with null pFunctionTable");
		return(FALSE);
	}
	else if (*interfaceVersion != INTERFACE_VERSION) {
		UTIL_LogPrintf("GetEntityAPI2 version mismatch; requested=%d ours=%d", *interfaceVersion, INTERFACE_VERSION);
		//! Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = INTERFACE_VERSION;
		return(FALSE);
	}
	memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	return(TRUE);
}

static DLL_FUNCTIONS gFunctionTable_Post = {
	NULL,					// pfnGameInit
	Spawn_Post,					// pfnSpawn
	NULL,					// pfnThink
	NULL,					// pfnUse
	NULL,				// pfnTouch
	NULL,				// pfnBlocked
	NULL,					// pfnKeyValue
	NULL,					// pfnSave
	NULL,					// pfnRestore
	NULL,					// pfnSetAbsBox

	NULL,					// pfnSaveWriteFields
	NULL,					// pfnSaveReadFields

	NULL,					// pfnSaveGlobalState
	NULL,					// pfnRestoreGlobalState
	NULL,					// pfnResetGlobalState

	NULL,					// pfnClientConnect
	NULL,					// pfnClientDisconnect
	NULL,					// pfnClientKill
	NULL,					// pfnClientPutInServer
	NULL,					// pfnClientCommand
	NULL,					// pfnClientUserInfoChanged
	NULL,					// pfnServerActivate
	NULL,					// pfnServerDeactivate

	NULL,					// pfnPlayerPreThink
	NULL,					// pfnPlayerPostThink

	NULL,					// pfnStartFrame
	NULL,					// pfnParmsNewLevel
	NULL,					// pfnParmsChangeLevel

	NULL,					// pfnGetGameDescription
	NULL,					// pfnPlayerCustomization

	NULL,					// pfnSpectatorConnect
	NULL,					// pfnSpectatorDisconnect
	NULL,					// pfnSpectatorThink

	NULL,					// pfnSys_Error

	NULL,					// pfnPM_Move
	NULL,					// pfnPM_Init
	NULL,					// pfnPM_FindTextureType

	NULL,					// pfnSetupVisibility
	NULL,					// pfnUpdateClientData
	NULL,					// pfnAddToFullPack
	NULL,					// pfnCreateBaseline
	NULL,					// pfnRegisterEncoders
	NULL,					// pfnGetWeaponData
	NULL,					// pfnCmdStart
	NULL,					// pfnCmdEnd
	NULL,					// pfnConnectionlessPacket
	NULL,					// pfnGetHullBounds
	NULL,					// pfnCreateInstancedBaselines
	NULL,					// pfnInconsistentFile
	NULL,					// pfnAllowLagCompensation
};
C_DLLEXPORT int GetEntityAPI2_Post(DLL_FUNCTIONS* pFunctionTable,
	int* interfaceVersion) {
	if(!pFunctionTable) {
		UTIL_LogPrintf("GetEntityAPI2 called with null pFunctionTable");
		return(FALSE);
	}
	else if (*interfaceVersion != INTERFACE_VERSION) {
		UTIL_LogPrintf("GetEntityAPI2 version mismatch; requested=%d ours=%d", *interfaceVersion, INTERFACE_VERSION);
		//! Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = INTERFACE_VERSION;
		return(FALSE);
	}
	memcpy(pFunctionTable, &gFunctionTable_Post, sizeof(DLL_FUNCTIONS));
	return(TRUE);
}