#include "CASSQLite.h"
#include <extdll.h>
#include <meta_api.h>
#include <filesystem>

typedef int(*fnSQLite3Open)(const char* filename, sqlite3** ppDb, int flags, const char* zVfs);
fnSQLite3Open SQLite3_Open;

typedef int(*fnSQLite3Exec)(sqlite3*,           /* An open database */
	const char* sql,                           /* SQL to be evaluated */
	fnSqlCallBack callback,  /* Callback function */
	void*,                                    /* 1st argument to callback */
	char** errmsg                              /* Error msg written here */);
fnSQLite3Exec SQLite3_Exec;

typedef int(*fnSQLite3Close)(sqlite3*);
fnSQLite3Close SQLite3_Close;

CASSQLite::CASSQLite(CString* szPath, int iMode){
	namespace fs = std::filesystem;
	std::string szNPath = szPath->c_str();
	szNPath = "./svencoop/scripts/plugins/store/" + szNPath;
	fs::path path = fs::relative(szNPath);
	if (path.native().starts_with(fs::relative("svencoop/scripts/plugins/store").native())){
		if (!fs::exists(path.remove_filename()))
			fs::create_directories(path.remove_filename());
		m_szStoredPath = szNPath;
		m_iMode = iMode;
		SQLite3_Open(m_szStoredPath.c_str(), &m_pDatabase, m_iMode, nullptr);
		m_bAviliable = true;
		m_bClosed = false;
	}
}
CASSQLite* CASSQLite::Factory(CString* szPath, int iMode){
	CASSQLite* obj = new CASSQLite(szPath, iMode);
	return obj;
}
int CASSQLite::Call(CString* sql, fnSqlCallBack callback, aslScriptFunction* pfnASCallBack, CString* errMsg) {
	if (m_bClosed)
		return 999;
	else if (!m_bAviliable)
		return 1;
	int iReturn;
	char* temp = nullptr;
	iReturn = SQLite3_Exec(m_pDatabase, sql->c_str(), callback, pfnASCallBack, &temp);
	if (temp)
		errMsg->assign(temp, strlen(temp));
	return iReturn;
}
int CASSQLite::Open(){
	if (!m_bClosed || !m_bAviliable)
		return 1;
	m_bClosed = false;
	return SQLite3_Open(m_szStoredPath.c_str(), &m_pDatabase, m_iMode, nullptr);
}
int CASSQLite::Exec(CString* sql, CString* errMsg){
	return Call(sql, nullptr, nullptr, errMsg);
}
int CASSQLite::ExecWithCallBack(CString* sql, aslScriptFunction* pfnASCallBack, CString* errMsg){
	return Call(sql, &Sqlite3Callback, pfnASCallBack, errMsg);
}
void CASSQLite::Close(){
	if (m_pDatabase) {
		SQLite3_Close(m_pDatabase);
		m_pDatabase = nullptr;
	}
	m_bClosed = true;
	m_bAviliable = false;
}
CASSQLite::~CASSQLite(){
	Close();
}
int CASSQLite::Sqlite3Callback(aslScriptFunction* pfnASCallBack, int column_size, char* column_value[], char* column_name[]) {
	CASServerManager* manager = ASEXT_GetServerManager();
	asIScriptEngine* engine = manager->scriptEngine;
	asIScriptContext* ctx = engine->RequestContext();

    asITypeInfo* aryInfo = engine->GetTypeInfoByDecl("array<string>");
	asITypeInfo* strInfo = engine->GetTypeInfoByName("string");
	asIScriptFunction* funcAryInsert = aryInfo->GetMethodByName("insertLast");

	void* aryVal = engine->CreateScriptObject(aryInfo);
	void* aryName = engine->CreateScriptObject(aryInfo);
	for (int i = 0; i < column_size; i++){
		CString* val = static_cast<CString*>(engine->CreateScriptObject(strInfo));
		val->assign(column_value[i], strlen(column_value[i]));
		ctx->Prepare(funcAryInsert);
		ctx->SetObject(aryVal);
		ctx->SetArgObject(0, val);
		ctx->Execute();

		CString* name = static_cast<CString*>(engine->CreateScriptObject(strInfo));
		name->assign(column_name[i], strlen(column_name[i]));
		ctx->Prepare(funcAryInsert);
		ctx->SetObject(aryName);
		ctx->SetArgObject(0, name);
		ctx->Execute();
	}
	CASFunction* m_callback = ASEXT_CreateCASFunction(pfnASCallBack, ASEXT_GetServerManager()->curModule, 1);
	(*ASEXT_CallCASBaseCallable)(m_callback, 0, column_size, aryVal, aryName);
	return 0;
}

void CASSQLite::LoadSQLite3Dll(){
#ifdef _WIN32
	auto pDllHandle = LoadLibraryA("svencoop/sqlite3.dll");
	SQLite3_Open = (decltype(SQLite3_Open))DLSYM((DLHANDLE)pDllHandle, "sqlite3_open_v2");
	SQLite3_Exec = (decltype(SQLite3_Exec))DLSYM((DLHANDLE)pDllHandle, "sqlite3_exec");
	SQLite3_Close = (decltype(SQLite3_Close))DLSYM((DLHANDLE)pDllHandle, "sqlite3_close_v2");
#else
	auto pDllHandle = dlopen("svencoop/dlls/libsqlite3.so", RTLD_LAZY);
	SQLite3_Open = (decltype(SQLite3_Open))dlsym((DLHANDLE)pDllHandle, "sqlite3_open_v2");
	SQLite3_Exec = (decltype(SQLite3_Exec))dlsym((DLHANDLE)pDllHandle, "sqlite3_exec");
	SQLite3_Close = (decltype(SQLite3_Close))dlsym((DLHANDLE)pDllHandle, "sqlite3_close_v2");
#endif
}
