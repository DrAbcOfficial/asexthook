#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

angelhook_t g_AngelHook;

uint32 SC_SERVER_DECL CASEngineFuncs_CRC32(void* pthis, SC_SERVER_DUMMYARG CString* szBuffer){
	CRC32_t crc;
	CRC32_INIT(&crc);
	CRC32_PROCESS_BUFFER(&crc, (void*)szBuffer->c_str(), szBuffer->length());
	return CRC32_FINAL(crc);
}


/// <summary>
/// Regiter
/// </summary>
void RegisterAngelScriptMethods(){
	ASEXT_RegisterDocInitCallback([](CASDocumentation* pASDoc) {
		//Regist HealthInfo type
		ASEXT_RegisterObjectType(pASDoc, "Entity takehealth info", "HealthInfo", 0, 0x40001u);
		ASEXT_RegisterObjectProperty(pASDoc, "Who get healing?", "HealthInfo", "CBaseEntity@ pEntity", offsetof(healthinfo_t, pEntity));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover amount.", "HealthInfo", "float flHealth", offsetof(healthinfo_t, flHealth));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover dmg type.", "HealthInfo", "int bitsDamageType", offsetof(healthinfo_t, bitsDamageType));
		ASEXT_RegisterObjectProperty(pASDoc, "If health_cap is non-zero, won't add more than health_cap. Returns true if it took damage, false otherwise.", "HealthInfo", "int health_cap", offsetof(healthinfo_t, health_cap));
	
		//Regist New Method
		ASEXT_RegisterObjectMethod(pASDoc,
			"Caculate CRC32 for a string", "CEngineFuncs", "uint32 CRC32(const string& in szBuffer)",
			(void*)CASEngineFuncs_CRC32, 3);
	});
}

#define CREATE_AS_HOOK(item, des, tag, name, arg) g_AngelHook.item=ASEXT_RegisterHook(des,StopMode_CALL_ALL,2,ASFlag_MapScript|ASFlag_Plugin,tag,name,arg)
void RegisterAngelScriptHooks(){
	CREATE_AS_HOOK(pPlayerPostTakeDamage, "Pre call after a player took damage", "Player", "PlayerPostTakeDamage", "DamageInfo@ info");
	CREATE_AS_HOOK(pPlayerTakeHealth, "Pre call before a player took health", "Player", "PlayerTakeHealth", "HealthInfo@ info");
	CREATE_AS_HOOK(pPlayerCallMedic, "Pre call before a player call medic", "Player", "PlayerCallMedic", "CBasePlayer@ pPlayer");
	CREATE_AS_HOOK(pPlayerCallGrenade, "Pre call before a player call grenade", "Player", "PlayerCallGrenade", "CBasePlayer@ pPlayer");

	CREATE_AS_HOOK(pMonsterTraceAttack, "Pre call before a monster trace attack", "Monster", "MonsterTraceAttack", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType");
	CREATE_AS_HOOK(pMonsterTakeDamage, "Pre call before a monster took damage", "Monster", "MonsterTakeDamage", "DamageInfo@ info");
	CREATE_AS_HOOK(pMonsterKilled, "Pre call before a monster died", "Monster", "MonsterKilled", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib");

	CREATE_AS_HOOK(pBreakableTraceAttack, "Pre call before a breakable trace attack","Entity", "BreakableTraceAttack", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType");
	CREATE_AS_HOOK(pBreakableKilled, "Pre call before a breakable died", "Entity", "BreakableDie", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, int iGib");
	CREATE_AS_HOOK(pBreakableTakeDamage, "Pre call before a breakable took damage", "Entity", "BreakableTakeDamage", "DamageInfo@ info");

	CREATE_AS_HOOK(pGrappleCheckMonsterType, "Pre call before Weapon Grapple checking monster type", "Weapon", "GrappleGetMonsterType", "CBaseEntity@ pThis, CBaseEntity@ pEntity, uint& out flag");
	CREATE_AS_HOOK(pSendScoreInfo, "Pre call before sending hud info to edict", "Player", "SendScoreInfo", "CBasePlayer@ pPlayer, edict_t@ pTarget, int iTeamID, string szTeamName, uint& out flag");
}
#undef CREATE_AS_HOOK