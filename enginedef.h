#pragma once
#include "progdefs.h"

void UninstallHook();

// BaseMonsterTakeDamage
typedef int (SC_SERVER_DECL *fnBaseMonsterTakeDamage)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
int SC_SERVER_DECL NewBaseMonsterTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
PRIVATE_FUNCTION_EXTERN(BaseMonsterTakeDamage);  
// BaseMonsterKilled
typedef void(SC_SERVER_DECL *fnBaseMonsterKilled)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
void SC_SERVER_DECL NewBaseMonsterKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
PRIVATE_FUNCTION_EXTERN(BaseMonsterKilled);
// BaseMonsterTraceAttack
typedef void(SC_SERVER_DECL *fnBaseMonsterTraceAttack)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType);
void SC_SERVER_DECL NewBaseMonsterTraceAttack(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType);
PRIVATE_FUNCTION_EXTERN(BaseMonsterTraceAttack);
// BreakableDie
typedef void(SC_SERVER_DECL *fnBreakableDie)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA);
void SC_SERVER_DECL NewBreakableDie(void* pThis SC_SERVER_DUMMYARG_NOCOMMA);
PRIVATE_FUNCTION_EXTERN(BreakableDie);
// BreakableTakeDamage
typedef int(SC_SERVER_DECL *fnBreakableTakeDamage)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
int SC_SERVER_DECL NewBreakableTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
PRIVATE_FUNCTION_EXTERN(BreakableTakeDamage);