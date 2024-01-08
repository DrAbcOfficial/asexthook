#pragma once
#include "progdefs.h"

void UninstallHook();

// GrappleGetMonsterType
enum GRAPPLE_RESULT{
	PULL_COME = 1,
	PULL_TO = 2
};
typedef GRAPPLE_RESULT(SC_SERVER_DECL* fnGrappleGetMonsterType)(void* pThis, SC_SERVER_DUMMYARG void* pEntity);
PRIVATE_FUNCTION_EXTERN(GrappleGetMonsterType);
// SendScoreInfo
typedef void(SC_SERVER_DECL *fnSendScoreInfo)(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName);
PRIVATE_FUNCTION_EXTERN(SendScoreInfo);
//
// SendScoreInfo
typedef char*(SC_SERVER_DECL* fnCWorldMODELREPLACEMENTFind)(void* pThis, SC_SERVER_DUMMYARG const char* modelname);
PRIVATE_FUNCTION_EXTERN(CWorldMODELREPLACEMENTFind);