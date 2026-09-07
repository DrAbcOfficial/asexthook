#pragma once
// 本文件与 SDK 的 angelscript.h 同名（./src/header 位于包含目录中），
// asext_api.h 的 #include <angelscript.h> 会命中本文件。
// 这里按相对路径转发到 metamod 子模块内的 SDK 真头，
// 补全 asIScriptEngine/asITypeInfo/asCALL_*/asOBJ_* 等全部声明，
// 之后才是本项目自己的 hook 结构与回调注册声明
#include "../../metamod/thirdparty/angelscript-sdk/angelscript/include/angelscript.h"
void RegisterAngelScriptMethods();
void RegisterAngelScriptHooks();
void CloseAngelScriptsItem();

typedef struct damageinfo_s{
	void* pVictim;
	void* pInflictor;
	void* pAttacker;
	float flDamage;
	int bitsDamageType;
}damageinfo_t;

typedef struct healthinfo_s {
	void* pEntity;
	float flHealth;
	int bitsDamageType;
	int health_cap;
}healthinfo_t;

typedef struct angelhook_s {
	void* pPlayerUserInfoChanged = nullptr;
	void* pPlayerPostTakeDamage = nullptr;
	void* pPlayerTakeHealth = nullptr;
	void* pPlayerCallMedic = nullptr;
	void* pPlayerCallGrenade = nullptr;

	void* pEntitySpawn = nullptr;

	void* pMonsterSpawn = nullptr;
	void* pMonsterTraceAttack = nullptr;
	void* pMonsterPostTakeDamage = nullptr;

	void* pBreakableTraceAttack = nullptr;
	void* pBreakableKilled = nullptr;
	void* pBreakableTakeDamage = nullptr;

	void* pGrappleCheckMonsterType = nullptr;

	//void* pSendScoreInfo = nullptr;

	void* pEntityIRelationship = nullptr;
}angelhook_t;
extern angelhook_t g_AngelHook;
