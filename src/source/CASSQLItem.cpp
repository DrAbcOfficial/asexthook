#include "CASBinaryStringBuilder.h"
#include "CASSQLItem.h"

CASSQLItem::CASSQLItem(){
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	m_pStrInfo = engine->GetTypeInfoByName("string");
	m_pBlobInfo = engine->GetTypeInfoByDecl("CBinaryStringBuilder");
	m_szData = static_cast<CString*>(engine->CreateScriptObject(m_pStrInfo));
}

CASSQLItem::~CASSQLItem(){
	ASEXT_GetServerManager()->scriptEngine->ReleaseScriptObject(m_szData, m_pStrInfo);
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
	m_szData->assign(str, strlen(str));
}

CString* CASSQLItem::Get(){
	return m_szData;
}

int64 CASSQLItem::GetInt64(){
	return _atoi64(m_szData->c_str());
}

int CASSQLItem::GetInt(){
	return atoi(m_szData->c_str());
}

double CASSQLItem::GetReal(){
	return atof(m_szData->c_str());
}

CBinaryStringBuilder** CASSQLItem::GetBlob(){
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	CBinaryStringBuilder* pBlob = static_cast<CBinaryStringBuilder*>(engine->CreateScriptObject(m_pBlobInfo));
	pBlob->WriteString(m_szData);
	return &pBlob;
}
