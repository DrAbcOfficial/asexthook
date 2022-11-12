#include <extdll.h>

#include <meta_api.h>
#include <enginecallback.h>
#include <map>
#include "edict.h"
#include "asext_api.h"
#include "vftable.h"

std::map<const char*, vtable_base_s*> g_vtableMap;

vtable_base_s* GetEntityVTable(const char* szClassName) {
	if (g_vtableMap.count(szClassName))
		return g_vtableMap[szClassName];
	return nullptr;
}
vtable_base_s* AddEntityVTable(const char* szClassName) {
	if (g_vtableMap.count(szClassName))
		return g_vtableMap[szClassName];
	edict_t* tentEntity = CREATE_ENTITY();
	CALL_GAME_ENTITY(PLID, szClassName, &tentEntity->v);
	if (tentEntity->pvPrivateData == NULL){
		REMOVE_ENTITY(tentEntity);
		return nullptr;
	}
	g_vtableMap[szClassName] = *(vtable_base_t**)tentEntity->pvPrivateData;
	REMOVE_ENTITY(tentEntity);
	return g_vtableMap[szClassName];
}