#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

angelhook_t g_AngelHook;

int SC_SERVER_DECL CSoundEngine_LookupSoundIndex(void* pthis, SC_SERVER_DUMMYARG char* szSample){
	return 0;
}

void RegisterAngelScriptMethods(){
	//ASEXT_RegisterDocInitCallback([](CASDocumentation* pASDoc) {
	//	ASEXT_RegisterObjectMethod(pASDoc,
	//		"Get index of sound sample", "CSoundEngine", "int LookupSoundIndex(string szSample)",
	//		(void*)CSoundEngine_LookupSoundIndex, 3);
	//	});
}

void RegisterAngelScriptHooks(){
	g_AngelHook.pMonsterTakeDamage = ASEXT_RegisterHook("Pre call before a monster took damage", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterTakedamage", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType");
	g_AngelHook.pMonsterKilled = ASEXT_RegisterHook("Pre call before a monster died", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterKilled", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib");
	g_AngelHook.pMonsterTraceAttack = ASEXT_RegisterHook("Pre call before a monster trace attack", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterTraceAttack", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, const TraceResult& in ptr, int bitDamageType");

	g_AngelHook.pBreakableDie = ASEXT_RegisterHook("Pre call before a breakable died", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Entity", "BreakableDie", "CBaseEntity@ pBreakable");
	g_AngelHook.pBreakableTakeDamage = ASEXT_RegisterHook("Pre call before a breakable took damage", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Entity", "BreakableTakeDamage", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType");

	g_AngelHook.pGrappleCheckMonsterType = ASEXT_RegisterHook("Pre call before Weapon Grapple checking monster type", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Weapon", "GrappleGetMonsterType", "CBaseEntity@ pThis, CBaseEntity@ pEntity, uint& out");
	g_AngelHook.pSendScoreInfo = ASEXT_RegisterHook("Pre call before sending hud info to edict", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Player", "SendScoreInfo", "CBasePlayer@ pPlayer, edict_t@ pTarget, int iTeamID, string szTeamName, uint& out");
}