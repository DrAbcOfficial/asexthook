#include <extdll.h>
#include <meta_api.h>
#include <vector>
#include "share_obj.h"

std::vector<CEntityObject*> g_EntityObjs;
CEntityObject* GetGameObject(int index) {
	return g_EntityObjs[index];
}
void ClearGameObject() {
	for (size_t i = 0; i < g_EntityObjs.size(); i++) {
		g_EntityObjs[i]->Clean();
		delete g_EntityObjs[i];
		g_EntityObjs[i] = nullptr;
	}
	g_EntityObjs.resize(gpGlobals->maxEntities);
}
void RemoveGameObject(int index) {
	g_EntityObjs[index]->Clean();
	delete g_EntityObjs[index];
	g_EntityObjs[index] = nullptr;
}
CEntityObject* CreateGameObject(int index) {
	CEntityObject* obj = new CEntityObject();
	g_EntityObjs[index] = obj;
	return obj;
}