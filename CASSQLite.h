#pragma once
#include "CASBaseObject.h"
#include <string>

typedef struct sqlite3;
typedef int (*fnSqlCallBack)(aslScriptFunction*, int, char**, char**);

class CASSQLite : public CASBaseGCObject
{
public:
	CASSQLite(CString* szPath, int iMode);
	static CASSQLite* Factory(CString* szPath, int iMode);
	static int Sqlite3Callback(aslScriptFunction* pfnASCallBack, int column_size, char* column_value[], char* column_name[]);
	static void LoadSQLite3Dll();

	int Open();
	int Exec(CString* sql, CString* errMsg);
	int ExecWithCallBack(CString* sql, aslScriptFunction* pfnCallBack, CString* errMsg);
	void Close();

	~CASSQLite();
private:
	int Call(CString* sql, fnSqlCallBack pfnSqlCallBack, aslScriptFunction* pfnASCallBack, CString* errMsg);
	sqlite3* m_pDatabase = nullptr;
	bool m_bClosed = false;
	bool m_bAviliable = false;
	std::string m_szStoredPath;
	int m_iMode = 0;
};