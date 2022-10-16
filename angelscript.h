#pragma once
void RegisterAngelScriptMethods();
void RegisterAngelScriptHooks();

typedef struct angelhook_s {
	void* pMonsterTakeDamage = nullptr;
}angelhook_t;
extern angelhook_t g_AngelHook;