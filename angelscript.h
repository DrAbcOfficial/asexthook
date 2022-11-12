#pragma once
void RegisterAngelScriptMethods();
void RegisterAngelScriptHooks();

typedef struct damageinfo_s{
	void* pVictim;
	void* pInflictor;
	void* pAttacker;
	float flDamage;
	int bitsDamageType;
}damageinfo_t;

typedef struct angelhook_s {
	void* pPlayerPostTakeDamage = nullptr;

	void* pMonsterTakeDamage = nullptr;
	void* pMonsterKilled = nullptr;
	void* pMonsterTraceAttack = nullptr;

	void* pBreakableTraceAttack = nullptr;
	void* pBreakableKilled = nullptr;
	void* pBreakableTakeDamage = nullptr;

	void* pGrappleCheckMonsterType = nullptr;

	void* pSendScoreInfo = nullptr;
}angelhook_t;
extern angelhook_t g_AngelHook;