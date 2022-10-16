#pragma once
#include "progdefs.h"
// BaseMonsterTakeDamage
typedef int (_fastcall *fnBaseMonsterTakeDamage)(void* pThis, int dummy, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
int _fastcall NewBaseMonsterTakeDamage(void* pThis, int dummy, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
PRIVATE_FUNCTION_EXTERN(BaseMonsterTakeDamage);  

typedef void(_fastcall* fnBaseMonsterKilled)(void* pThis, int dummy, entvars_t* pevAttacker, int iGib);
void _fastcall NewBaseMonsterKilled(void* pThis, int dummy, entvars_t* pevAttacker, int iGib);
PRIVATE_FUNCTION_EXTERN(BaseMonsterKilled);