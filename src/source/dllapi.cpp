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

#include <vector>
#include <string>
#include <map>

#include <dllapi.h>
#include <meta_api.h>

#include "asext_api.h"
#include "angelscript.h"
#include "vftable.h"
#include "utility.h"

#include "dlldef.h"

#define CALL_ANGELSCRIPT(pfn, ...) if (ASEXT_CallHook){(*ASEXT_CallHook)(g_AngelHook.pfn, 0, __VA_ARGS__);}

bool g_HookedFlag = false;

std::map<char*, char*> g_dicGMRList = {};
struct{
	hookitem_t BaseMonsterTraceAttack;
	hookitem_t BaseMonsterTakeDamage;

	hookitem_t ApacheTraceAttack;
	hookitem_t OspreyTraceAttack;
	hookitem_t TurretTraceAttack;
	hookitem_t BreakableTraceAttack;
	
	hookitem_t PlayerPostTakeDamage;
	hookitem_t PlayerTakeHealth;

	hookitem_t BreakableKilled;
	hookitem_t BreakableTakeDamage;

	hookitem_t IRelationship;
} gHookItems;
static std::vector<hook_t*> gHooks;

#pragma region VTableHooks
#define CALL_ORIGIN(item, type, ...) ((decltype(item.pVtable->type))item.pfnOriginalCall)(pThis, SC_SERVER_PASS_DUMMYARG __VA_ARGS__)
#define CALL_ORIGIN_NOARG(item, type) ((decltype(item.pVtable->type))item.pfnOriginalCall)(pThis, SC_SERVER_PASS_DUMMYARG_NOCOMMA)
static int SC_SERVER_DECL BaseMonsterTakeDamage(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	int ret = CALL_ORIGIN(gHookItems.BaseMonsterTakeDamage, TakeDamage, pevInflictor, pevAttacker, flDamage, bitsDamageType);
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGELSCRIPT(pMonsterPostTakeDamage, &dmg)
	return ret;
}
static void SC_SERVER_DECL BaseMonsterTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	edict_t* ent = PrivateToEdict(pThis);
	if (ent) {
		entvars_t* var = &ent->v;
		if (var->flags & FL_MONSTER)
			CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	}
	CALL_ORIGIN(gHookItems.BaseMonsterTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
static void SC_SERVER_DECL ApacheTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.ApacheTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
static void SC_SERVER_DECL OspreyTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.OspreyTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
static void SC_SERVER_DECL TurretTraceAttack(CBaseMonster* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pMonsterTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.TurretTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
static void SC_SERVER_DECL BreakableTraceAttack(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, vec3_t vecDir, TraceResult* ptr, int bitsDamageType) {
	CALL_ANGELSCRIPT(pBreakableTraceAttack, pThis, pevAttacker, flDamage, &vecDir, ptr, bitsDamageType);
	CALL_ORIGIN(gHookItems.BreakableTraceAttack, TraceAttack, pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}
static void SC_SERVER_DECL BreakableKilled(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGELSCRIPT(pBreakableKilled, pThis, pevAttacker, iGib);
	CALL_ORIGIN(gHookItems.BreakableKilled, Killed, pevAttacker, iGib);
}
static int SC_SERVER_DECL BreakableTakeDamage(CBaseEntity* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
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
static int SC_SERVER_DECL PlayerPostTakeDamage(CBasePlayer* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
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
static int SC_SERVER_DECL PlayerTakeHealth(CBasePlayer* pThis, SC_SERVER_DUMMYARG float flDamage, int bitsDamageType, int cap) {
	healthinfo_t dmg = {
		pThis,
		flDamage,
		bitsDamageType,
		cap
	};
	CALL_ANGELSCRIPT(pPlayerTakeHealth, &dmg);
	return CALL_ORIGIN(gHookItems.PlayerTakeHealth, TakeHealth, dmg.flHealth, dmg.bitsDamageType, dmg.health_cap);
}
static int SC_SERVER_DECL IRelationship(CBasePlayer* pThis, SC_SERVER_DUMMYARG CBaseEntity* pOther, bool param_2) {
	int iNewReturn = 114514;
	CALL_ANGELSCRIPT(pEntityIRelationship, pThis, pOther, param_2, &iNewReturn);
	return iNewReturn == 114514 ? CALL_ORIGIN(gHookItems.IRelationship, IRelationship, pOther, param_2) : iNewReturn;
}
#undef CALL_ORIGIN
#undef CALL_ORIGIN_NOARG
void VtableUnhook() {
	for (auto iter = gHooks.begin(); iter != gHooks.end(); iter++) {
		if (*iter) {
			gpMetaUtilFuncs->pfnUnHook(*iter);
			*iter = nullptr;
		}
	}
	gHooks.clear();
}
#pragma endregion

#pragma region PreHooks
static void ServerActivate(edict_t* pEdictList, int edictCount, int clientMax) {
#pragma region LoadMapGMR
	//Clear Mem
	for (auto iter = g_dicGMRList.begin(); iter != g_dicGMRList.end(); iter++) {
		delete[] (*iter).first;
		delete[] (*iter).second;
	}
	g_dicGMRList.clear();
	//Read to Mem
	char gmrfile[MAX_PATH] = {};
	snprintf(gmrfile, MAX_PATH, "maps/%s.gmr", STRING(gpGlobals->mapname));
	int length = 0;
	char* content = reinterpret_cast<char*>(g_engfuncs.pfnLoadFileForMe(gmrfile, &length));
	if (content != nullptr) {
		char src[MAX_PATH]{};
		char dst[MAX_PATH]{};
		std::string buf;
		bool inread = false;
		bool indst = false;
		for (size_t i = 0; i < strlen(content); i++) {
			char tok = content[i];
			if (tok == '\n') {
				inread = false;
				indst = false;
				char* msrc = new char[MAX_PATH];
				char* mdst = new char[MAX_PATH];
				strcpy_s(msrc, MAX_PATH, src);
				strcpy_s(mdst, MAX_PATH, dst);
				g_dicGMRList.insert(std::make_pair(msrc, mdst));
				memset(src, 0, MAX_PATH);
				memset(dst, 0, MAX_PATH);
				buf.clear();
				continue;
			}
			else if (tok == '\"') {
				if (inread) {
					if (indst) {
						strcpy(dst, buf.c_str());
						indst = false;
					}
					else {
						strcpy(src, buf.c_str());
						indst = true;
					}
					inread = false;
				}
				else
					inread = true;
			}
			if (inread) {
				buf += tok;
			}
		}
		g_engfuncs.pfnFreeFile(content);
	}
#pragma endregion

	if (g_HookedFlag) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}
#define ITEM_HOOK(item, type, table, newfunc) item.pfnOriginalCall=item.pfnCall=(void*)table->type;item.pVtable=table;item.pHook=gpMetaUtilFuncs->pfnInlineHook(item.pfnCall,(void*)newfunc,(void**)&item.pfnOriginalCall,false);gHooks.push_back(item.pHook)
	vtable_base_t* vtable = AddEntityVTable("monster_apache");
	ITEM_HOOK(gHookItems.ApacheTraceAttack, TraceAttack, vtable, ApacheTraceAttack);
	vtable = AddEntityVTable("monster_osprey");
	ITEM_HOOK(gHookItems.OspreyTraceAttack, TraceAttack, vtable, OspreyTraceAttack);
	vtable = AddEntityVTable("monster_turret");
	ITEM_HOOK(gHookItems.TurretTraceAttack, TraceAttack, vtable, TurretTraceAttack);
	vtable = AddEntityVTable("func_breakable");
	ITEM_HOOK(gHookItems.BreakableTraceAttack, TraceAttack, vtable, BreakableTraceAttack);
	ITEM_HOOK(gHookItems.BreakableTakeDamage, TakeDamage, vtable, BreakableTakeDamage);
	ITEM_HOOK(gHookItems.BreakableKilled, Killed, vtable, BreakableKilled);
	vtable = AddEntityVTable("monster_bloater");
	ITEM_HOOK(gHookItems.BaseMonsterTraceAttack, TraceAttack, vtable, BaseMonsterTraceAttack);
	vtable = AddEntityVTable("player");
	ITEM_HOOK(gHookItems.PlayerPostTakeDamage, TakeDamage, vtable, PlayerPostTakeDamage);
	ITEM_HOOK(gHookItems.PlayerTakeHealth, TakeHealth, vtable, PlayerTakeHealth);
	ITEM_HOOK(gHookItems.IRelationship, IRelationship, vtable, IRelationship);
#undef ITEM_HOOK
	g_HookedFlag = true;
	SET_META_RESULT(MRES_HANDLED);
}
static void ClientCommand(edict_t* pEntity) {
	if (!pEntity->pvPrivateData) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}
	const char* pcmd = CMD_ARGV(0);
	if (!strncmp(pcmd, "medic", 5)) {
		CALL_ANGELSCRIPT(pPlayerCallMedic, pEntity->pvPrivateData);
		SET_META_RESULT(MRES_HANDLED);
		return;
	}
	else if (!strncmp(pcmd, "grenade", 7)) {
		CALL_ANGELSCRIPT(pPlayerCallGrenade, pEntity->pvPrivateData);
		SET_META_RESULT(MRES_HANDLED);
		return;
	}
	SET_META_RESULT(MRES_IGNORED);
}
static void ClientUserInfoChanged(edict_t* pEntity, char* infobuffer) {
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
	NULL,					// pfnAllowLagCompensation
};
C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS* pFunctionTable,
	int* interfaceVersion) {
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
#pragma endregion

#pragma region PostHook
static void GameInitPost() {
	static cvar_t fixgmr = { const_cast<char*>("sv_fixgmr"),const_cast<char*>("1"), FCVAR_SERVER };
	CVAR_REGISTER(&fixgmr);
	SET_META_RESULT(MRES_HANDLED);
}
static int Spawn_Post(edict_t* pent) {
	if (pent != nullptr) {
		if (pent->pvPrivateData != nullptr) {
			CALL_ANGELSCRIPT(pEntitySpawn, pent->pvPrivateData);
			if ((VARS(pent)->flags & FL_MONSTER) > 0) {
				const char* szName = STRING((VARS(pent)->classname));
				if (!strncmp(szName, "monster_", 8))
					CALL_ANGELSCRIPT(pMonsterSpawn, pent->pvPrivateData);
			}
		}
	}
	SET_META_RESULT(MRES_HANDLED);
	return 1919810;
}
static DLL_FUNCTIONS gFunctionTable_Post = {
	GameInitPost,					// pfnGameInit
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
	memcpy(pFunctionTable, &gFunctionTable_Post, sizeof(DLL_FUNCTIONS));
	return(TRUE);
}
#pragma endregion