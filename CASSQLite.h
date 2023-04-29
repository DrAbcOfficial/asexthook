#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include "CASBaseObject.h"
class CASSQLite : public CASBaseGCObject
{
public:
	CASSQLite(CString* szPath, int iMode);
	static CASSQLite* Factory(CString* szPath, int iMode);
	
	int Exec(CString* szCommand);
	void Close();

	~CASSQLite();
private:
	SQLite::Database* m_pDatabase = nullptr;
};