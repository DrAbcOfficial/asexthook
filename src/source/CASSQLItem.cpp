#include "CASBinaryStringBuilder.h"
#include "CASSQLItem.h"

CASSQLItem::CASSQLItem(){
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	m_pBlobInfo = engine->GetTypeInfoByDecl("CBinaryStringBuilder");
	m_bIsNull = true;
}

CASSQLItem::~CASSQLItem(){
	m_szData.clear();
}

CASSQLItem* CASSQLItem::Factory(){
	CASSQLItem* obj = new CASSQLItem();
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	asITypeInfo* type = engine->GetTypeInfoByName("CSQLItem");
	engine->NotifyGarbageCollectorOfNewObject(obj, type);
	return obj;
}

CASSQLItem* CASSQLItem::ParamFactory(char* str){
	CASSQLItem* pItem = Factory();
	pItem->SetData(str);
	return pItem;
}

void CASSQLItem::SetData(char* str){
	m_szData = str;
	m_bIsNull = false;
}

void CASSQLItem::Get(CString* str){
	str->assign(m_szData.c_str(), m_szData.size());
}

int64 CASSQLItem::GetInt64(){
	return std::atoll(m_szData.c_str());
}

int32 CASSQLItem::GetInt(){
	return std::atoi(m_szData.c_str());
}

uint64 CASSQLItem::GetUInt64(){
	return strtoull(m_szData.c_str(), nullptr, 10);
}

uint32 CASSQLItem::GetUInt(){
	//ILP32 so... yeah, thats fine
	return strtoul(m_szData.c_str(), nullptr, 10);
}

double CASSQLItem::GetReal(){
	return std::atof(m_szData.c_str());
}

CBinaryStringBuilder** CASSQLItem::GetBlob(){
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	CBinaryStringBuilder* pBlob = static_cast<CBinaryStringBuilder*>(engine->CreateScriptObject(m_pBlobInfo));
	pBlob->WriteData(m_szData.c_str(), m_szData.size());
	return &pBlob;
}

bool CASSQLItem::IsNull(){
	return m_bIsNull;
}
