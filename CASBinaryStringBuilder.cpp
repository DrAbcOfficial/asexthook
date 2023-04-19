#include <extdll.h>
#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

#include "CASBinaryStringBuilder.h"

CBinaryStringBuilder::CBinaryStringBuilder(asIScriptEngine* engine){
	refCount = 1;
}
CBinaryStringBuilder* SC_SERVER_DECL CBinaryStringBuilder::Factory(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA) {
	asIScriptEngine* engine = ASEXT_GetServerManager()->scriptEngine;
	CBinaryStringBuilder* obj = new CBinaryStringBuilder(engine);
	asITypeInfo* type = engine->GetTypeInfoByName("gc");
	engine->NotifyGarbageCollectorOfNewObject(obj, type);
	return obj;
}
void SC_SERVER_DECL CBinaryStringBuilder::AddRef(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA) {
	pthis->refCount = (pthis->refCount & 0x7FFFFFFF) + 1;
}
void SC_SERVER_DECL CBinaryStringBuilder::Release(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	pthis->refCount &= 0x7FFFFFFF;
	if (--pthis->refCount == 0)
		delete pthis;
}
void SC_SERVER_DECL CBinaryStringBuilder::SetGCFlag(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	pthis->refCount |= 0x80000000;
}
bool SC_SERVER_DECL CBinaryStringBuilder::GetGCFlag(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return (pthis->refCount & 0x80000000) ? true : false;
}
int SC_SERVER_DECL CBinaryStringBuilder::GetRefCount(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return (pthis->refCount & 0x7FFFFFFF);
}
void SC_SERVER_DECL CBinaryStringBuilder::EnumReferences(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG asIScriptEngine* engine){

}
void SC_SERVER_DECL CBinaryStringBuilder::ReleaseAllReferences(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG asIScriptEngine* engine){

}
void SC_SERVER_DECL CBinaryStringBuilder::Get(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer){
	buffer->assign(pthis->szBuffer.c_str(), pthis->szBuffer.length());
}
void SC_SERVER_DECL CBinaryStringBuilder::Set(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer){
	pthis->szBuffer = buffer->c_str();
	pthis->iReadPointer = 0;
}
size_t SC_SERVER_DECL CBinaryStringBuilder::GetReadPointer(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer;
}
void SC_SERVER_DECL CBinaryStringBuilder::SetReadPointer(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG size_t pointer){
	pthis->iReadPointer = min(pthis->szBuffer.length(), pointer);
}
template <typename T>
void WriteBuffer(CBinaryStringBuilder* pThis, T value) {
	size_t length = sizeof(value);
	for (size_t i = 0; i < length; i++) {
		pThis->szBuffer += static_cast<char>(value << (i * 8) >> ((length - 1) * 8));
	}
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteInt(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteLong(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteFloat(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value){
	WriteBuffer(pthis, std::bit_cast<int>(value));
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteDouble(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value){
	WriteBuffer(pthis, std::bit_cast<int64>(value));
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteVector(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value){
	WriteBuffer(pthis, std::bit_cast<int>(value.x));
	WriteBuffer(pthis, std::bit_cast<int>(value.y));
	WriteBuffer(pthis, std::bit_cast<int>(value.z));
}
void SC_SERVER_DECL CBinaryStringBuilder::WriteString(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value){
	pthis->szBuffer += value->c_str();
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
int SC_SERVER_DECL CBinaryStringBuilder::ReadInt(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<int, int>(pthis) : 0;
}
int64 SC_SERVER_DECL CBinaryStringBuilder::ReadLong(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<int64, int64>(pthis) : 0;
}
float SC_SERVER_DECL CBinaryStringBuilder::ReadFloat(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<float, int>(pthis) : 0.0f;
}
double SC_SERVER_DECL CBinaryStringBuilder::ReadDouble(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<double, int64>(pthis) : 0.0;
}
void SC_SERVER_DECL CBinaryStringBuilder::ReadVector(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t vecBuffer){
	vecBuffer.x = ReadBuffer<float, int>(pthis);
	vecBuffer.y = ReadBuffer<float, int>(pthis);
	vecBuffer.z = ReadBuffer<float, int>(pthis);
}
void SC_SERVER_DECL CBinaryStringBuilder::ReadString(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* szBuffer){
	std::string temp;
	for (size_t i = pthis->iReadPointer; i < pthis->szBuffer.length(); i++) {
		char c = pthis->szBuffer[pthis->iReadPointer];
		temp += c;
		pthis->iReadPointer++;
		if (c == '\0')
			break;
	}
	szBuffer->assign(temp.c_str(), temp.length());
}
bool SC_SERVER_DECL CBinaryStringBuilder::ReadToEnd(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer >= pthis->szBuffer.length();
}