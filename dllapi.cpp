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

#include "signatures.h"
#include "asext_api.h"
#include "angelscript.h"
#include "vftable.h"
#include "utility.h"

#include "dlldef.h"

using namespace std;

bool g_HookedFlag = false;

struct hookitems_t {
	hookitem_t ApacheTakeDamage;
	hookitem_t ApacheKilled;
	hookitem_t OspreyKilled;
};
hookitems_t gHookItems;
vector<hook_t*> gHooks;
#define CALL_ORIGIN(item, type, ...) ((decltype(item.pVtable->type))item.pfnOriginalCall)(pThis, SC_SERVER_PASS_DUMMYARG __VA_ARGS__)
#define CALL_ANGEL(pfn, ...) if (ASEXT_CallHook){(*ASEXT_CallHook)(g_AngelHook.pfn, 0, __VA_ARGS__);}
int SC_SERVER_DECL NewApacheTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) {
	damageinfo_t dmg = {
			pThis,
			GetEntVarsVTable(pevInflictor),
			GetEntVarsVTable(pevAttacker),
			flDamage,
			bitsDamageType
	};
	CALL_ANGEL(pMonsterPostTakeDamage, &dmg)
	return CALL_ORIGIN(gHookItems.ApacheTakeDamage, TakeDamage, pevInflictor, pevAttacker, dmg.flDamage, dmg.bitsDamageType);
}
void SC_SERVER_DECL NewApacheKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGEL(pMonsterKilled, pevAttacker, iGib)
	CALL_ORIGIN(gHookItems.ApacheKilled, Killed, pevAttacker, iGib);
}
void SC_SERVER_DECL NewOspreyKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) {
	CALL_ANGEL(pMonsterKilled, pThis, pevAttacker, iGib)
	CALL_ORIGIN(gHookItems.OspreyKilled, Killed, pevAttacker, iGib);
}
#undef CALL_ANGEL
#undef CALL_ORIGIN

void ServerActivate (edict_t* pEdictList, int edictCount, int clientMax) {
	if (g_HookedFlag) {
		SET_META_RESULT(MRES_IGNORED);
		return;
	}
#define ITEM_HOOK(item, type, table, newfunc) item.pfnOriginalCall=item.pfnCall=table->type;item.pVtable=table;item.pHook=gpMetaUtilFuncs->pfnInlineHook(item.pfnCall,(void*)newfunc,(void**)&item.pfnOriginalCall,false);gHooks.push_back(item.pHook)
	vtable_base_t* vtable = AddEntityVTable("monster_apache");
	ITEM_HOOK(gHookItems.ApacheTakeDamage, TakeDamage, vtable, NewApacheTakeDamage);
	ITEM_HOOK(gHookItems.ApacheKilled, Killed, vtable, NewApacheKilled);
	vtable = AddEntityVTable("monster_osprey");
	ITEM_HOOK(gHookItems.OspreyKilled, Killed, vtable, NewOspreyKilled);
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
	NULL,					// pfnClientCommand
	NULL,					// pfnClientUserInfoChanged
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
	int* interfaceVersion)
{
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