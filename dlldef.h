#pragma once
#include "progdefs.h"
// These stupid just not call baseclass method
// Apache
typedef int (SC_SERVER_DECL* fnApacheTakeDamage)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
int SC_SERVER_DECL NewApacheTakeDamage(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
typedef void(SC_SERVER_DECL* fnApacheKilled)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
void SC_SERVER_DECL NewApacheKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
typedef void(SC_SERVER_DECL* fnApacheTraceAttack)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType);
PRIVATE_FUNCTION_EXTERN(ApacheTakeDamage);
PRIVATE_FUNCTION_EXTERN(ApacheKilled);
// Osprey
typedef void(SC_SERVER_DECL* fnOspreyKilled)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
void SC_SERVER_DECL NewOspreyKilled(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib);
PRIVATE_FUNCTION_EXTERN(OspreyKilled);

void VtableUnhook();