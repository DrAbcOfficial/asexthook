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
		INT8 temp = (value << (i*8) >> (length - 1) * 8);
		pThis->szBuffer += (char)temp;
	}
}

void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer){
	buffer->empty();
	buffer->assign(pthis->szBuffer.c_str(), pthis->szBuffer.length());
}
void SC_SERVER_DECL ASBinaryBuilder_WriteInt(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value){
	WriteBuffer(pthis, value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value){
	WriteBuffer(pthis, *(int*)&value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value){
	WriteBuffer(pthis, *(int64*)&value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value){
	WriteBuffer(pthis, *(int*)&value.x);
	WriteBuffer(pthis, *(int*)&value.y);
	WriteBuffer(pthis, *(int*)&value.z);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value){
	pthis->szBuffer += value->c_str();
}
void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	pthis->szBuffer.clear();
}
