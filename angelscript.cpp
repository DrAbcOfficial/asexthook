#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

angelhook_t g_AngelHook;

void RegisterAngelScriptMethods(){
}

void RegisterAngelScriptHooks(){
	g_AngelHook.pMonsterTakeDamage = ASEXT_RegisterHook("Pre call after a monster took damage", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterTakedamage", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType");
	g_AngelHook.pMonsterKilled = ASEXT_RegisterHook("Pre call after a monster died", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterKilled", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib");
	g_AngelHook.pMonsterTraceAttack = ASEXT_RegisterHook("Pre call after a monster trace attack", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Monster", "MonsterTraceAttack", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, const TraceResult& in ptr, int bitDamageType");

	g_AngelHook.pBreakableDie = ASEXT_RegisterHook("Pre call after a breakable died", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Entity", "BreakableDie", "CBaseEntity@ pBreakable");
	g_AngelHook.pBreakableTakeDamage = ASEXT_RegisterHook("Pre call after a breakable took damage", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Entity", "BreakableTakeDamage", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType");
}