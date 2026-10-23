void PluginInit()
{
	g_Module.ScriptInfo.SetAuthor( "a" );
	g_Module.ScriptInfo.SetContactInfo( "a" );
	
	//in svencoop/scripts/plugins/store
	CSQLite pSQL("test.db", SQLiteMode(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
	pSQL.Exec("SELECT omg FROM gesus;", function(int iColumnSize, array<CSQLItem@>@ aryColumnValue, array<CSQLItem@>@ aryColumnName){
		g_Log.PrintF("size: " + iColumnSize + "\ncolumn:\n");
		for(int i = 0; i < iColumnSize; i++){
			string name;
			string value;
			aryColumnName[i].Get(name);
			aryColumnValue[i].Get(value);
			g_Log.PrintF(name + ": " + value + "\n");
		}
	}, void);
	//close db manualy...
	pSQL.Close();
}