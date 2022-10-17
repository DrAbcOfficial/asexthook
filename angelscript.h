#pragma once
void RegisterAngelScriptMethods();
void RegisterAngelScriptHooks();

typedef struct angelhook_s {
	void* pMonsterTakeDamage = nullptr;
	void* pMonsterKilled = nullptr;
	void* pMonsterTraceAttack = nullptr;

	void* pBreakableDie = nullptr;
	void* pBreakableTakeDamage = nullptr;
}angelhook_t;
extern angelhook_t g_AngelHook;