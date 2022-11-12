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
// GrappleGetMonsterType
enum GRAPPLE_RESULT{
	PULL_COME = 1,
	PULL_TO = 2
};
typedef GRAPPLE_RESULT(SC_SERVER_DECL* fnGrappleGetMonsterType)(void* pThis, SC_SERVER_DUMMYARG void* pEntity);
GRAPPLE_RESULT SC_SERVER_DECL NewGrappleGetMonsterType(void* pThis, SC_SERVER_DUMMYARG void* pEntity);
PRIVATE_FUNCTION_EXTERN(GrappleGetMonsterType);
// SendScoreInfo
typedef void(SC_SERVER_DECL *fnSendScoreInfo)(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName);
void SC_SERVER_DECL NewSendScoreInfo(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName);
PRIVATE_FUNCTION_EXTERN(SendScoreInfo);
// LookupSoundIndex
//typedef int(SC_SERVER_DECL* fnLookupSoundIndex)(void* pThis, SC_SERVER_DUMMYARG char* szSample);
//PRIVATE_FUNCTION_EXTERN(LookupSoundIndex);

