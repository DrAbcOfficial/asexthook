#include <vector>
#include <map>

#include <extdll.h>
#include <meta_api.h>


#include "signatures.h"
#include "asext_api.h"

#include "angelscript_hooks.h"
#include "utility.h"

#pragma region Function Def
// GrappleGetMonsterType
enum GRAPPLE_RESULT
{
    PULL_COME = 1,
    PULL_TO   = 2
};
typedef GRAPPLE_RESULT(SC_SERVER_DECL* fnGrappleGetMonsterType)(void* pThis, SC_SERVER_DUMMYARG void* pEntity);
PRIVATE_FUNCTION_EXTERN(GrappleGetMonsterType);
// SendScoreInfo
//typedef void(SC_SERVER_DECL *fnSendScoreInfo)(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName);
//void SC_SERVER_DECL NewSendScoreInfo(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName);
//PRIVATE_FUNCTION_EXTERN(SendScoreInfo);
#pragma endregion

#pragma region GameDataHooks
/// <summary>
/// Grapple GetMonsterType
/// </summary>
hook_t* g_phook_GrappleGetMonsterType = nullptr;
PRIVATE_FUNCTION_DEFINE(GrappleGetMonsterType);
GRAPPLE_RESULT SC_SERVER_DECL NewGrappleGetMonsterType(void* pThis, SC_SERVER_DUMMYARG void* pEntity)
{
    int uiFlag = 0;
    if (ASEXT_CallHook)
        (*ASEXT_CallHook)(g_AngelHook.pGrappleCheckMonsterType, 0, pThis, pEntity, &uiFlag);
    if (uiFlag != 0 && uiFlag <= 2 && uiFlag >= 1)
        return (GRAPPLE_RESULT)uiFlag;
    return g_call_original_GrappleGetMonsterType(pThis, SC_SERVER_PASS_DUMMYARG pEntity);
}
/// <summary>
/// SendScoreInfo
/// </summary>
//hook_t* g_phook_SendScoreInfo = nullptr;
//PRIVATE_FUNCTION_DEFINE(SendScoreInfo);
//void SC_SERVER_DECL NewSendScoreInfo(void* pThis, SC_SERVER_DUMMYARG edict_t* eSendTarget, int iTeamID, char* szTeamName) {
//	int uiFlag = 0;
//	if (ASEXT_CallHook)
//		(*ASEXT_CallHook)(g_AngelHook.pSendScoreInfo, 0, pThis, eSendTarget, iTeamID, szTeamName, &uiFlag);
//	if (uiFlag != 0)
//		return;
//	g_call_original_SendScoreInfo(pThis, SC_SERVER_PASS_DUMMYARG eSendTarget, iTeamID, szTeamName);
//}
bool ResolveEngineSymbols()
{
    auto serverBase = gpMetaUtilFuncs->pfnGetGameDllBase();
    FILL_FROM_GAMEDATA(server, GrappleGetMonsterType);
    return true;
}
bool InstallEngineHook()
{
    if (g_phook_GrappleGetMonsterType)
        return true;
    if (!g_pfn_GrappleGetMonsterType)
    {
        LOG_ERROR(PLID, "GrappleGetMonsterType gamedata has not been resolved");
        return false;
    }
    INSTALL_INLINEHOOK(GrappleGetMonsterType);
    if (!g_phook_GrappleGetMonsterType)
    {
        LOG_ERROR(PLID, "Failed to install GrappleGetMonsterType hook");
        return false;
    }
    return true;
}
void UninstallEngineHook()
{
    UNINSTALL_HOOK(GrappleGetMonsterType);
    //UNINSTALL_HOOK(SendScoreInfo);
}
#pragma endregion
