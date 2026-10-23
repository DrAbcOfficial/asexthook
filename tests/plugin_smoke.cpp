#include <extdll.h>
#include <meta_api.h>
#include <signatures_template.h>
#include <asext_api.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iterator>
#ifndef _WIN32
#    include <dlfcn.h>
#endif

plugin_info_t  Plugin_info{};
mutil_funcs_t* gpMetaUtilFuncs = nullptr;
IMPORT_ASEXT_API_DEFINE()

namespace
{
int                   g_errors           = 0;
DLHANDLE              g_engineHandle     = nullptr;
void*                 g_engineBase       = nullptr;
void*                 g_dependencyHandle = nullptr;
void*                 g_serverBase       = nullptr;
int                   g_resolveCalls     = 0;
int                   g_missingSymbol    = 0;
constexpr const char* g_symbols[]        = {
    "GrappleGetMonsterType", "ApacheTraceAttack", "OspreyTraceAttack", "TurretTraceAttack",
    "BreakableTraceAttack", "BreakableTakeDamage", "BreakableKilled", "BaseMonsterTraceAttack",
    "PlayerPostTakeDamage", "PlayerTakeHealth", "IRelationship"};

void Check(bool condition, const char* message)
{
    if (!condition)
    {
        std::fprintf(stderr, "FAIL: %s\n", message);
        std::exit(1);
    }
}
void                     Log(plid_t, const char*, ...) {}
void                     Error(plid_t, const char*, ...) { ++g_errors; }
void                     Alert(ALERT_TYPE, const char*, ...) {}
DLHANDLE                 EngineHandle() { return g_engineHandle; }
void*                    EngineBase() { return g_engineBase; }
void*                    ServerBase() { return g_serverBase; }
meta_gamesymbol_status_t Resolve(void* base, const char* name, meta_gamesymbol_kind_t kind, void** address)
{
    Check(g_serverBase == base, "resolve hooks against server module");
    Check(META_GAMESYMBOL_KIND_FUNCTION == kind, "request function gamedata");
    Check(g_resolveCalls < static_cast<int>(std::size(g_symbols)), "bounded symbol requests");
    Check(0 == std::strcmp(g_symbols[g_resolveCalls], name), "request each hook target in order");
    *address = nullptr;
    if (g_resolveCalls++ == g_missingSymbol)
        return META_GAMESYMBOL_SYMBOL_NOT_FOUND;
    *address = g_serverBase; // Never executed: dependency loading still fails below.
    return META_GAMESYMBOL_OK;
}
const char* SymbolStatus(meta_gamesymbol_status_t) { return "mock symbol missing"; }
int         Load(plid_t, const char* path, PLUG_LOADTIME now, void** handle)
{
    Check(PT_ANYTIME == now && std::strstr(path, "addons/metamod/dlls/asext."), "ASExt load request");
    *handle = g_dependencyHandle;
    return *handle ? 0 : -1;
}
bool ImportASExt(void* asextHandle)
{
    IMPORT_ASEXT_API(asext);
    return true;
}
} // namespace

int main(int argc, char** argv)
{
    Check(3 == argc, "plugin and ASExt path arguments");
#ifdef _WIN32
    auto handle = LoadLibraryA(argv[1]);
    auto symbol = [handle](const char* name) {
        return reinterpret_cast<void*>(GetProcAddress(handle, name));
    };
    using GiveFunctions = void(WINAPI*)(enginefuncs_t*, globalvars_t*);
#else
    auto handle = dlopen(argv[1], RTLD_NOW | RTLD_LOCAL);
    auto symbol = [handle](const char* name) {
        return dlsym(handle, name);
    };
    using GiveFunctions = void (*)(enginefuncs_t*, globalvars_t*);
#endif
    Check(nullptr != handle, "load actual native plugin");
    auto query  = reinterpret_cast<META_QUERY_FN>(symbol("Meta_Query"));
    auto attach = reinterpret_cast<META_ATTACH_FN>(symbol("Meta_Attach"));
    auto give   = reinterpret_cast<GiveFunctions>(symbol("GiveFnptrsToDll"));
    Check(query && attach && give && symbol("Meta_Detach"), "required exported entrypoints");

    enginefuncs_t engine{};
    engine.pfnAlertMessage = Alert;
    globalvars_t engineGlobals{};
    give(&engine, &engineGlobals);

    mutil_funcs_t utilities{};
    utilities.pfnLogMessage                = Log;
    utilities.pfnLogError                  = Error;
    utilities.pfnGetEngineHandle           = EngineHandle;
    utilities.pfnGetEngineBase             = EngineBase;
    utilities.pfnLoadPlugin                = Load;
    utilities.pfnGetGameDllBase            = ServerBase;
    utilities.pfnResolveGameSymbol         = Resolve;
    utilities.pfnGetGameSymbolStatusString = SymbolStatus;
    gpMetaUtilFuncs                        = &utilities;
#ifdef _WIN32
    auto asext = LoadLibraryA(argv[2]);
#else
    auto asext = dlopen(argv[2], RTLD_NOW | RTLD_LOCAL);
#endif
    Check(nullptr != asext, "load actual ASExt dependency");
    Check(ImportASExt(reinterpret_cast<void*>(asext)), "resolve every SDK-required ASExt API export");
    plugin_info_t* info = nullptr;
    for (const char* version : {"", "5:16", "6:17", "5:17x"})
        Check(FALSE == query(version, &info, &utilities), "reject incompatible interface");
    Check(TRUE == query(META_INTERFACE_VERSION, &info, &utilities), "accept compiled SDK interface");
    Check(info && 0 == std::strcmp(META_INTERFACE_VERSION, info->ifvers), "report SDK interface");
    Check(PT_ANYTIME == info->loadable && PT_STARTUP == info->unloadable, "preserve lifecycle flags");

    META_FUNCTIONS  functions{};
    meta_globals_t  globals{};
    gamedll_funcs_t game{};
    Check(FALSE == attach(PT_STARTUP, &functions, nullptr, &game), "reject null globals");
    Check(FALSE == attach(PT_STARTUP, nullptr, &globals, &game), "reject null function table");
    Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject missing engine handle");
    g_engineHandle = reinterpret_cast<DLHANDLE>(handle);
    Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject missing engine base");
    g_engineBase = reinterpret_cast<void*>(handle);
    Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject missing server module");
    g_serverBase = reinterpret_cast<void*>(handle);
    for (int missing = 0; missing < static_cast<int>(std::size(g_symbols)); ++missing)
    {
        g_missingSymbol  = missing;
        g_resolveCalls   = 0;
        const int errors = g_errors;
        Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject every missing hook symbol");
        Check(missing + 1 == g_resolveCalls, "stop resolution at missing symbol without scanning or installing hooks");
        Check(errors + 1 == g_errors, "log missing gamedata");
    }
    g_missingSymbol = -1;
    g_resolveCalls  = 0;
    Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject missing ASExt");
    Check(static_cast<int>(std::size(g_symbols)) == g_resolveCalls, "resolve all hooks before importing ASExt");
    g_dependencyHandle = reinterpret_cast<void*>(handle);
    g_resolveCalls     = 0;
    Check(FALSE == attach(PT_STARTUP, &functions, &globals, &game), "reject missing ASExt export");

    Check(functions.pfnGetEntityAPI2 && functions.pfnGetEntityAPI2_Post && functions.pfnGetEngineFunctions,
          "publish plugin function table");
    DLL_FUNCTIONS hooks{};
    int           version = 0;
    Check(FALSE == functions.pfnGetEntityAPI2(&hooks, &version), "reject wrong entity API version");
    Check(INTERFACE_VERSION == version, "report entity API version");
    Check(TRUE == functions.pfnGetEntityAPI2(&hooks, &version), "provide entity API table");
    Check(TRUE == functions.pfnGetEntityAPI2_Post(&hooks, &version), "provide post entity API table");
    version = 0;
    Check(FALSE == functions.pfnGetEngineFunctions(&engine, &version), "reject wrong engine API version");
    Check(ENGINE_INTERFACE_VERSION == version, "report engine API version");
    Check(g_errors >= 6, "log dependency and handshake failures");
    std::puts("Plugin ABI smoke passed (mock host; no game address hooks executed).");
    return 0;
}
