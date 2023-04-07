#include <extdll.h>
#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

#include "CASBinaryStringBuilder.h"

BinaryStringBuilder g_ASBinaryStringBuilder;

template <typename T>
void WriteBuffer(BinaryStringBuilder* pThis, T value) {
	size_t length = sizeof(value);
	for (size_t i = 0; i < length; i++) {
		pThis->szBuffer += static_cast<char>(value << (i * 8) >> ((length - 1) * 8));
	}
}
void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer) {
	pthis->szBuffer = buffer->c_str();
	pthis->iReadPointer = 0;
}
size_t SC_SERVER_DECL ASBinaryBuilder_GetReadPointer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer;
}
void SC_SERVER_DECL ASBinaryBuilder_SetReadPointer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG size_t pointer){
	pthis->iReadPointer = min(pthis->szBuffer.length(), pointer);
}
void SC_SERVER_DECL ASBinaryBuilder_Output(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer){
	buffer->assign(pthis->szBuffer.c_str(), pthis->szBuffer.length());
}
void SC_SERVER_DECL ASBinaryBuilder_WriteInt(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value){
	WriteBuffer(pthis, std::bit_cast<int>(value));
}
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value){
	WriteBuffer(pthis, std::bit_cast<int64>(value));
}
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value){
	WriteBuffer(pthis, std::bit_cast<int>(value.x));
	WriteBuffer(pthis, std::bit_cast<int>(value.y));
	WriteBuffer(pthis, std::bit_cast<int>(value.z));
}
void SC_SERVER_DECL ASBinaryBuilder_WriteString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value){
	pthis->szBuffer += value->c_str();
}
template <typename T1, typename T2>
T1 ReadBuffer(BinaryStringBuilder* pThis) {
	T2 temp = 0;
	size_t length = sizeof(T2);
	for (size_t i = 0; i < length; i++) {
		temp += std::bit_cast<T2>(pThis->szBuffer[pThis->iReadPointer]) << ((length - 1 - i) * 8);
		pThis->iReadPointer++;
	}
	return std::bit_cast<T1>(temp);
}
int SC_SERVER_DECL ASBinaryBuilder_ReadInt(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<int, int>(pthis) : 0;
}
int64 SC_SERVER_DECL ASBinaryBuilder_ReadLong(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<int64, int64>(pthis) : 0;
}
float SC_SERVER_DECL ASBinaryBuilder_ReadFloat(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<float, int>(pthis) : 0.0f;
}
double SC_SERVER_DECL ASBinaryBuilder_ReadDouble(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	return pthis->iReadPointer < pthis->szBuffer.length() ? ReadBuffer<double, int64>(pthis) : 0.0;
}
void SC_SERVER_DECL ASBinaryBuilder_ReadVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t vecBuffer){
	vecBuffer.x = ReadBuffer<float, int>(pthis);
	vecBuffer.y = ReadBuffer<float, int>(pthis);
	vecBuffer.z = ReadBuffer<float, int>(pthis);
}
void SC_SERVER_DECL ASBinaryBuilder_ReadString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* szBuffer){
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
void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	pthis->szBuffer.clear();
	pthis->iReadPointer = 0;
}