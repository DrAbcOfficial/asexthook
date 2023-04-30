void PluginInit()
{
	g_Module.ScriptInfo.SetAuthor( "a" );
	g_Module.ScriptInfo.SetContactInfo( "a" );
	
	//in svencoop/scripts/plugins/store
	CSQLite pSQL("test.db", SQLiteMode(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
	pSQL.Exec("select num from t_student;", function(int iColumnSize, array<string>@ aryColumnValue, array<string>@ aryColumnName){
		g_Log.PrintF("size: " + iColumnSize + "\ncolumn:\n");
		for(int i = 0; i < iColumnSize; i++){
			g_Log.PrintF(aryColumnName[i] + ": " + aryColumnValue[i] + "\n");
		}
	}, void);
	//close db manualy...
	pSQL.Close();
}