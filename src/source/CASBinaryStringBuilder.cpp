#include <extdll.h>

#include "angelscript.h"

#include <meta_api.h>
#include <string>
#include <bit>
#include "CASBinaryStringBuilder.h"

CBinaryStringBuilder::CBinaryStringBuilder(){
	refCount = 1;
}
CBinaryStringBuilder* CBinaryStringBuilder::Factory() {
	return new CBinaryStringBuilder();
}
CBinaryStringBuilder* CBinaryStringBuilder::ParamFactory(CString* str) {
	CBinaryStringBuilder* obj = new CBinaryStringBuilder();
	obj->Set(str);
	return obj;
}

CString CBinaryStringBuilder::Get(){
	asIScriptEngine* engine = ASEXT_GetServerManager()->scriptEngine;
	CString* szOutBuffer = static_cast<CString*>(engine->CreateScriptObject(engine->GetTypeInfoByDecl("string")));
	char* temp = new char[szBuffer.size() + 1];
	std::copy(szBuffer.begin(), szBuffer.end(), temp);
	szOutBuffer->assign(temp, szBuffer.size());
	delete[] temp;
	return *szOutBuffer;
}
void CBinaryStringBuilder::Set(CString* buffer){
	szBuffer.clear();
	for (size_t i = 0; i < buffer->length(); i++) {
		szBuffer.push_back(buffer->chatAt(i));
	}
	iReadPointer = 0;
}
size_t CBinaryStringBuilder::GetReadPointer(){
	return iReadPointer;
}
void CBinaryStringBuilder::SetReadPointer(size_t pointer){
#ifdef _WIN32
#undef min
#endif // _WIN32
	iReadPointer = std::min(szBuffer.size(), pointer);
}
template <typename T>
void WriteBuffer(CBinaryStringBuilder* pThis, T value) {
	size_t length = sizeof(value);
	for (size_t i = 0; i < length; i++) {
		pThis->szBuffer.push_back(static_cast<unsigned char>(value << (i * 8) >> ((length - 1) * 8)));
	}
}
void CBinaryStringBuilder::WriteInt(int value){
	WriteBuffer(this, value);
}
void CBinaryStringBuilder::WriteLong(int64 value){
	WriteBuffer(this, value);
}
void CBinaryStringBuilder::WriteFloat(float value){
	WriteBuffer(this, std::bit_cast<int>(value));
}
void CBinaryStringBuilder::WriteDouble(double value){
	WriteBuffer(this, std::bit_cast<int64>(value));
}
void CBinaryStringBuilder::WriteVector(vec3_t value){
	WriteBuffer(this, std::bit_cast<int>(value.x));
	WriteBuffer(this, std::bit_cast<int>(value.y));
	WriteBuffer(this, std::bit_cast<int>(value.z));
}
void CBinaryStringBuilder::WriteString(CString* value){
	for (size_t i = 0; i < value->length(); i++) {
		szBuffer.push_back(value->chatAt(i));
	}
}
template <typename T1, typename T2>
T1 ReadBuffer(CBinaryStringBuilder* pThis) {
	T2 temp = 0;
	size_t length = sizeof(T2);
	for (size_t i = 0; i < length; i++) {
		temp += static_cast<T2>(pThis->szBuffer[pThis->iReadPointer]) << ((length - 1 - i) * 8);
		pThis->iReadPointer++;
	}
	return std::bit_cast<T1>(temp);
}
int CBinaryStringBuilder::ReadInt(){
	return iReadPointer < szBuffer.size() ? ReadBuffer<int, int>(this) : 0;
}
int64 CBinaryStringBuilder::ReadLong(){
	return iReadPointer < szBuffer.size() ? ReadBuffer<int64, int64>(this) : 0;
}
float CBinaryStringBuilder::ReadFloat(){
	return iReadPointer < szBuffer.size() ? ReadBuffer<float, int>(this) : 0.0f;
}
double CBinaryStringBuilder::ReadDouble(){
	return iReadPointer < szBuffer.size() ? ReadBuffer<double, int64>(this) : 0.0;
}
vec3_t CBinaryStringBuilder::ReadVector(){
	asIScriptEngine* engine = ASEXT_GetServerManager()->scriptEngine;
	vec3_t* vecBuffer = static_cast<vec3_t*>(engine->CreateScriptObject(engine->GetTypeInfoByDecl("Vector")));
	vecBuffer->x = ReadBuffer<float, int>(this);
	vecBuffer->y = ReadBuffer<float, int>(this);
	vecBuffer->z = ReadBuffer<float, int>(this);
	return *vecBuffer;
}
CString* CBinaryStringBuilder::ReadString(){
	std::string temp;
	for (size_t i = iReadPointer; i < szBuffer.size(); i++) {
		char c = szBuffer[iReadPointer];
		temp += c;
		iReadPointer++;
		if (c == '\0')
			break;
	}
	asIScriptEngine* engine = ASEXT_GetServerManager()->scriptEngine;
	CString* szOutBuffer = static_cast<CString*>(engine->CreateScriptObject(engine->GetTypeInfoByDecl("string")));
	szOutBuffer->assign(temp.c_str(), temp.length());
	return szOutBuffer;
}
bool CBinaryStringBuilder::IsReadToEnd(){
	return iReadPointer >= szBuffer.size();
}