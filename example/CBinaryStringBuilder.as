void Read(){
	File@ pFile = g_FileSystem.OpenFile("./anybinaryshit", OpenFile::READ);
	string binary = "";
	while(!pFile.EOFReached()){
		binary += ReadCharacter();
	}
	pFile.Close();

	CBinaryStringBuilder pBR(binary);
	//or
	//CBinaryStringBuilder pBR();
	//pBR.Set(binary);
	string a = pBR.ReadString();
	array<int> ary = {};
	while(!pBR.IsReadToEnd()){
		ary.insertLast(pBR.ReadInt());
	}
}
void Write(){
	CBinaryStringBuilder pBW();
	pBW.WriteString("sodayo")
	pBW.WriteInt(114514);
	pBW.WriteFloat(1919.810f);

	string binary = pBW.Get();
	File@ pFile = g_FileSystem.OpenFile("./anybinaryshit", OpenFile::WRITE);
	pFile.Write(binary);
	pFile.Close();
}