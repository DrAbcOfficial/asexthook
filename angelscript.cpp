#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include "angelscriptlib.h"

#include <meta_api.h>
#include "CASBinaryStringBuilder.h"

angelhook_t g_AngelHook;

uint32 SC_SERVER_DECL CASEngineFuncs_CRC32(void* pthis, SC_SERVER_DUMMYARG CString* szBuffer){
	CRC32_t crc;
	CRC32_INIT(&crc);
	CRC32_PROCESS_BUFFER(&crc, (void*)szBuffer->c_str(), szBuffer->length());
	return CRC32_FINAL(crc);
}

bool SC_SERVER_DECL CASEngineFuncs_ClassMemcpy(void* pthis, SC_SERVER_DUMMYARG void* _src, int srctypeid, void* _dst, int dsttypeid) {
	if (srctypeid != dsttypeid)
		return false;
	asIScriptObject* src = *static_cast<asIScriptObject**>(_src);
	asIScriptObject* dst = *static_cast<asIScriptObject**>(_dst);
	if (!src || !dst)
		return false;
	dst->CopyFrom(src);
	return true;
}

template <typename T>
void RegisteRefObject(CASDocumentation* pASDoc, const char* szName) {
	asSFuncPtr reg;
	reg = asMETHOD(T, AddRef);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "AddRef", szName, asBEHAVE_ADDREF, "void AddRef()", &reg, asCALL_THISCALL);
	reg = asMETHOD(T, Release);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Release", szName, asBEHAVE_RELEASE, "void Release()", &reg, asCALL_THISCALL);
}
template <typename T>
void RegisteGCObject(CASDocumentation* pASDoc, const char* szName) {
	RegisteRefObject<T>(pASDoc, szName);
	asSFuncPtr reg;
	reg = asMETHOD(T, SetGCFlag);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Set GC Flag", szName, asBEHAVE_SETGCFLAG, "void SetGCFlag()", &reg, asCALL_THISCALL);
	reg = asMETHOD(T, GetGCFlag);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Get GC Flag", szName, asBEHAVE_GETGCFLAG, "bool GetGCFlag() const", &reg, asCALL_THISCALL);
	reg = asMETHOD(T, GetRefCount);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Get reference count", szName, asBEHAVE_GETREFCOUNT, "int GetRefCount() const", &reg, asCALL_THISCALL);
	reg = asMETHOD(T, EnumReferences);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Enumerate references held by this class", szName, asBEHAVE_ENUMREFS, "void EnumReferences(int& in)", &reg, asCALL_THISCALL);
	reg = asMETHOD(T, ReleaseReferences);
	ASEXT_RegisterObjectBehaviourEx(pASDoc, "Release all references held by this class", szName, asBEHAVE_RELEASEREFS, "void ReleaseReferences(int& in)", &reg, asCALL_THISCALL);
}
/// <summary>
/// Regiter
/// </summary>
#define REGISTE_OBJMETHODEX(r, d, e, c, m, cc, mm, call) r=asMETHOD(cc,mm);ASEXT_RegisterObjectMethodEx(d,e,c,m,&r,call)
void RegisterAngelScriptMethods(){
	
	ASEXT_RegisterDocInitCallback([](CASDocumentation* pASDoc) {
		//Regist HealthInfo type
		ASEXT_RegisterObjectType(pASDoc, "Entity takehealth info", "HealthInfo", 0, asEObjTypeFlags::asOBJ_REF | asEObjTypeFlags::asOBJ_NOCOUNT);
		ASEXT_RegisterObjectProperty(pASDoc, "Who get healing?", "HealthInfo", "CBaseEntity@ pEntity", offsetof(healthinfo_t, pEntity));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover amount.", "HealthInfo", "float flHealth", offsetof(healthinfo_t, flHealth));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover dmg type.", "HealthInfo", "int bitsDamageType", offsetof(healthinfo_t, bitsDamageType));
		ASEXT_RegisterObjectProperty(pASDoc, "If health_cap is non-zero, won't add more than health_cap. Returns true if it took damage, false otherwise.", "HealthInfo", "int health_cap", offsetof(healthinfo_t, health_cap));
		
		asSFuncPtr reg;
		ASEXT_RegisterObjectType(pASDoc, "Binary String Builder", "CBinaryStringBuilder", 0, 5);
		reg = asFUNCTION(CBinaryStringBuilder::Factory);
		ASEXT_RegisterObjectBehaviourEx(pASDoc, "Factory", "CBinaryStringBuilder", asBEHAVE_FACTORY, "CBinaryStringBuilder@ CBinaryStringBuilder()", &reg, asCALL_CDECL);
		reg = asFUNCTION(CBinaryStringBuilder::ParamFactory);
		ASEXT_RegisterObjectBehaviourEx(pASDoc, "Factory", "CBinaryStringBuilder", asBEHAVE_FACTORY, "CBinaryStringBuilder@ CBinaryStringBuilder(string&in buffer)", &reg, asCALL_CDECL);
		RegisteGCObject<CBinaryStringBuilder>(pASDoc, "CBinaryStringBuilder");
		REGISTE_OBJMETHODEX(reg, pASDoc, "Is Read to end?", "CBinaryStringBuilder", "bool IsReadToEnd()", CBinaryStringBuilder, IsReadToEnd, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Get output to a string", "CBinaryStringBuilder", "void Get(string&out buffer)", CBinaryStringBuilder, Get, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Set a read buffer", "CBinaryStringBuilder", "bool Set(string&in buffer)", CBinaryStringBuilder, Set, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Get the read pointer", "CBinaryStringBuilder", "uint GetReadPointer()", CBinaryStringBuilder, GetReadPointer, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Set the read pointer", "CBinaryStringBuilder", "void SetReadPointer(uint iPointer)", CBinaryStringBuilder, SetReadPointer, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteInt(int value)", CBinaryStringBuilder, WriteInt, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteLong(int64 value)", CBinaryStringBuilder, WriteLong, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteFloat(float value)", CBinaryStringBuilder, WriteFloat, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteDouble(double value)", CBinaryStringBuilder, WriteDouble, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteVector(Vector value)", CBinaryStringBuilder, WriteVector, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteString(string&in value)", CBinaryStringBuilder, WriteString, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "int ReadInt()", CBinaryStringBuilder, ReadInt, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "int64 ReadLong()", CBinaryStringBuilder, ReadLong, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "float ReadFloat()", CBinaryStringBuilder, ReadFloat, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "double ReadDouble()", CBinaryStringBuilder, ReadDouble, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadVector(Vector&out value)", CBinaryStringBuilder, ReadVector, asCALL_THISCALL);
		REGISTE_OBJMETHODEX(reg, pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadString(string&out value)", CBinaryStringBuilder, ReadString, asCALL_THISCALL);

		//Regist New Method
		ASEXT_RegisterObjectMethod(pASDoc,
			"Caculate CRC32 for a string", "CEngineFuncs", "uint32 CRC32(const string& in szBuffer)",
			(void*)CASEngineFuncs_CRC32, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc,
			"copy class, If src and dst are different type, return false.\nIf not class ref, crash game.", "CEngineFuncs", "bool ClassMemcpy(?& in src, ?& in dst)",
			(void*)CASEngineFuncs_ClassMemcpy, asCALL_THISCALL);
	});
}
#undef REGISTE_OBJMETHODEX

#define CREATE_AS_HOOK(item, des, tag, name, arg) g_AngelHook.item=ASEXT_RegisterHook(des,StopMode_CALL_ALL,2,ASFlag_MapScript|ASFlag_Plugin,tag,name,arg)
void RegisterAngelScriptHooks(){
	CREATE_AS_HOOK(pPlayerUserInfoChanged, "Pre call before a player info changed", "Player", "PlayerUserInfoChanged", "CBasePlayer@ pClient, string szInfoBuffer, uint&out uiFlag");
	CREATE_AS_HOOK(pPlayerPostTakeDamage, "Pre call before a player took damage", "Player", "PlayerPostTakeDamage", "DamageInfo@ info");
	CREATE_AS_HOOK(pPlayerTakeHealth, "Pre call before a player took health", "Player", "PlayerTakeHealth", "HealthInfo@ info");
	CREATE_AS_HOOK(pPlayerCallMedic, "Pre call before a player call medic", "Player", "PlayerCallMedic", "CBasePlayer@ pPlayer");
	CREATE_AS_HOOK(pPlayerCallGrenade, "Pre call before a player call grenade", "Player", "PlayerCallGrenade", "CBasePlayer@ pPlayer");

	CREATE_AS_HOOK(pEntitySpawn, "Post call after a Entity spawn", "Entity", "EntitySpawn", "CBaseEntity@ pEntity");
	CREATE_AS_HOOK(pEntityIRelationship, "Pre call before checking relation", "Entity", "IRelationship", "CBaseEntity@ pEntity, CBaseEntity@ pOther, bool param, int& out newValue");

	CREATE_AS_HOOK(pMonsterSpawn, "Post call after a monster spawn", "Monster", "MonsterSpawn", "CBaseMonster@ pEntity");
	CREATE_AS_HOOK(pMonsterTraceAttack, "Pre call before a monster trace attack", "Monster", "MonsterTraceAttack", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType");
	CREATE_AS_HOOK(pMonsterTakeDamage, "Pre call before a monster took damage", "Monster", "MonsterTakeDamage", "DamageInfo@ info");
	CREATE_AS_HOOK(pMonsterKilled, "Pre call before a monster died", "Monster", "MonsterKilled", "CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib");

	CREATE_AS_HOOK(pBreakableTraceAttack, "Pre call before a breakable trace attack","Entity", "BreakableTraceAttack", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType");
	CREATE_AS_HOOK(pBreakableKilled, "Pre call before a breakable died", "Entity", "BreakableDie", "CBaseEntity@ pBreakable, entvars_t@ pevAttacker, int iGib");
	CREATE_AS_HOOK(pBreakableTakeDamage, "Pre call before a breakable took damage", "Entity", "BreakableTakeDamage", "DamageInfo@ info");

	CREATE_AS_HOOK(pGrappleCheckMonsterType, "Pre call before Weapon Grapple checking monster type", "Weapon", "GrappleGetMonsterType", "CBaseEntity@ pThis, CBaseEntity@ pEntity, uint& out flag");
	CREATE_AS_HOOK(pSendScoreInfo, "Pre call before sending hud info to edict", "Player", "SendScoreInfo", "CBasePlayer@ pPlayer, edict_t@ pTarget, int iTeamID, string szTeamName, uint& out flag");
}
#undef CREATE_AS_HOOK