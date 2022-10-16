#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

angelhook_t g_AngelHook;

void RegisterAngelScriptMethods(){
}

void RegisterAngelScriptHooks(){
	g_AngelHook.pMonsterTakeDamage = ASEXT_RegisterHook("Post call after a monster took damage", StopMode_CALL_ALL, 2, ASFlag_MapScript | ASFlag_Plugin, "Entity", "MonsterTakedamage", "CBaseMonster@ pMonster, entvars_t@ pAttacker, entvars_t@ pInflictor, float flDamage, int bitDamageType");
}