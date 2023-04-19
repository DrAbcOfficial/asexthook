#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
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

/// <summary>
/// Regiter
/// </summary>
void RegisterAngelScriptMethods(){
	

	ASEXT_RegisterDocInitCallback([](CASDocumentation* pASDoc) {
		//Regist HealthInfo type
		ASEXT_RegisterObjectType(pASDoc, "Entity takehealth info", "HealthInfo", 0, asEObjTypeFlags::asOBJ_REF | asEObjTypeFlags::asOBJ_NOCOUNT);
		ASEXT_RegisterObjectProperty(pASDoc, "Who get healing?", "HealthInfo", "CBaseEntity@ pEntity", offsetof(healthinfo_t, pEntity));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover amount.", "HealthInfo", "float flHealth", offsetof(healthinfo_t, flHealth));
		ASEXT_RegisterObjectProperty(pASDoc, "Recover dmg type.", "HealthInfo", "int bitsDamageType", offsetof(healthinfo_t, bitsDamageType));
		ASEXT_RegisterObjectProperty(pASDoc, "If health_cap is non-zero, won't add more than health_cap. Returns true if it took damage, false otherwise.", "HealthInfo", "int health_cap", offsetof(healthinfo_t, health_cap));

		ASEXT_RegisterObjectType(pASDoc, "Binary String Builder", "CBinaryStringBuilder", 0, 5);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Default constructor.", "CBinaryStringBuilder", asBEHAVE_CONSTRUCT, "CBinaryStringBuilder@ CBinaryStringBuilder()", (void*)CBinaryStringBuilder::Factory, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Destructor.", "CBinaryStringBuilder", asBEHAVE_DESTRUCT, "void DestructCBinaryStringBuilder()", (void*)CBinaryStringBuilder::Release, asCALL_CDECL_OBJLAST);
		ASEXT_RegisterObjectBehaviour(pASDoc, "AddRef", "CBinaryStringBuilder", asBEHAVE_ADDREF, "void AddRef()", (void*)CBinaryStringBuilder::AddRef, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Release", "CBinaryStringBuilder", asBEHAVE_RELEASE, "void Release()", (void*)CBinaryStringBuilder::Release, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Set GC Flag", "CBinaryStringBuilder", asBEHAVE_SETGCFLAG, "void SetGCFlag()", (void*)CBinaryStringBuilder::SetGCFlag, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Get GC Flag", "CBinaryStringBuilder", asBEHAVE_GETGCFLAG, "bool GetGCFlag() const", (void*)CBinaryStringBuilder::GetGCFlag, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Get reference count", "CBinaryStringBuilder", asBEHAVE_GETREFCOUNT, "int GetRefCount() const", CBinaryStringBuilder::GetRefCount, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Enumerate references held by this class", "CBinaryStringBuilder", asBEHAVE_ENUMREFS, "void EnumReferences(int& in a)", (void*)(void*)CBinaryStringBuilder::EnumReferences, asCALL_THISCALL);
		ASEXT_RegisterObjectBehaviour(pASDoc, "Release all references held by this class", "CBinaryStringBuilder", asBEHAVE_RELEASEREFS, "void ReleaseReferences(int& in a)", (void*)CBinaryStringBuilder::ReleaseAllReferences, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Is Read to end?", "CBinaryStringBuilder", "bool ReadToEnd()", (void*)CBinaryStringBuilder::ReadToEnd, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Get output to a string", "CBinaryStringBuilder", "void Get(string&out buffer)", (void*)CBinaryStringBuilder::Get, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Set a read buffer", "CBinaryStringBuilder", "bool Set(string&in buffer)", (void*)CBinaryStringBuilder::Set, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Get the read pointer", "CBinaryStringBuilder", "uint GetReadPointer()", (void*)CBinaryStringBuilder::GetReadPointer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Set the read pointer", "CBinaryStringBuilder", "void SetReadPointer(uint iPointer)", (void*)CBinaryStringBuilder::SetReadPointer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteInt(int value)", (void*)CBinaryStringBuilder::WriteInt, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteLong(int64 value)", (void*)CBinaryStringBuilder::WriteLong, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteFloat(float value)", (void*)CBinaryStringBuilder::WriteFloat, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteDouble(double value)", (void*)CBinaryStringBuilder::WriteDouble, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteVector(Vector value)", (void*)CBinaryStringBuilder::WriteVector, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteString(string&in value)", (void*)CBinaryStringBuilder::WriteString, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "int ReadInt()", (void*)CBinaryStringBuilder::ReadInt, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "int64 ReadLong()", (void*)CBinaryStringBuilder::ReadLong, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "float ReadFloat()", (void*)CBinaryStringBuilder::ReadFloat, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "double ReadDouble()", (void*)CBinaryStringBuilder::ReadDouble, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadVector(Vector&out value)", (void*)CBinaryStringBuilder::ReadVector, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadString(string&out value)", (void*)CBinaryStringBuilder::ReadString, asCALL_THISCALL);

		/*
		ASEXT_RegisterObjectType(pASDoc, "Binary String Builder", "CBinaryStringBuilder", 0, asEObjTypeFlags::asOBJ_REF | asEObjTypeFlags::asOBJ_NOCOUNT);
		ASEXT_RegisterObjectMethod(pASDoc, "Initial buffer", "CBinaryStringBuilder", "void Init()", (void*)ASBinaryBuilder_ClearBuffer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Is Read to end?", "CBinaryStringBuilder", "bool ReadToEnd()", (void*)ASBinaryBuilder_ReadToEnd, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Copy ", "CBinaryStringBuilder", "void Copy(string&out buffer)", (void*)ASBinaryBuilder_Output, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Bind a read buffer", "CBinaryStringBuilder", "void SetReadBuffer(string&in buffer)", (void*)ASBinaryBuilder_SetBuffer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Get the read pointer", "CBinaryStringBuilder", "uint GetReadPointer()", (void*)ASBinaryBuilder_GetReadPointer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Set the read pointer", "CBinaryStringBuilder", "void SetReadPointer(uint iPointer)", (void*)ASBinaryBuilder_SetReadPointer, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteInt(int value)", (void*)ASBinaryBuilder_WriteInt, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteLong(int64 value)", (void*)ASBinaryBuilder_WriteLong, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteFloat(float value)", (void*)ASBinaryBuilder_WriteFloat, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteDouble(double value)", (void*)ASBinaryBuilder_WriteDouble, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteVector(Vector value)", (void*)ASBinaryBuilder_WriteVector, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Write a Value", "CBinaryStringBuilder", "void WriteString(string&in value)", (void*)ASBinaryBuilder_WriteString, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "int ReadInt()", (void*)ASBinaryBuilder_ReadInt, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "int64 ReadLong()", (void*)ASBinaryBuilder_ReadLong, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "float ReadFloat()", (void*)ASBinaryBuilder_ReadFloat, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "double ReadDouble()", (void*)ASBinaryBuilder_ReadDouble, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadVector(Vector&out value)", (void*)ASBinaryBuilder_ReadVector, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc, "Read a Value", "CBinaryStringBuilder", "void ReadString(string&out value)", (void*)ASBinaryBuilder_ReadString, asCALL_THISCALL);
		ASEXT_RegisterGlobalProperty(pASDoc, "Binary String Builder", "CBinaryStringBuilder g_BinaryStringBuilder", (void*)&g_ASBinaryStringBuilder);
		*/
		//Regist New Method
		ASEXT_RegisterObjectMethod(pASDoc,
			"Caculate CRC32 for a string", "CEngineFuncs", "uint32 CRC32(const string& in szBuffer)",
			(void*)CASEngineFuncs_CRC32, asCALL_THISCALL);
		ASEXT_RegisterObjectMethod(pASDoc,
			"copy class, If src and dst are different type, return false.\nIf not class ref, crash game.", "CEngineFuncs", "bool ClassMemcpy(?& in src, ?& in dst)",
			(void*)CASEngineFuncs_ClassMemcpy, asCALL_THISCALL);
	});
}

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