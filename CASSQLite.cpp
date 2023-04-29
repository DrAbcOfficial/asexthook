#include "CASSQLite.h"

CASSQLite::CASSQLite(CString* szPath, int iMode){
	m_pDatabase = new SQLite::Database(szPath->c_str(), iMode);
}

CASSQLite* CASSQLite::Factory(CString* szPath, int iMode){
	CASSQLite* obj = new CASSQLite(szPath, iMode);
	return obj;
}

int CASSQLite::Exec(CString* szCommand){
	return m_pDatabase->exec(szCommand->c_str());
}

void CASSQLite::Close(){
	if(m_pDatabase)
		delete m_pDatabase;
	m_pDatabase = nullptr;
}

CASSQLite::~CASSQLite(){
	Close();
}
