#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

#include "CASBinaryStringBuilder.h"

void CBinaryStringBuilder::SetBuffer(CString* buffer){
	this->Buffer = buffer;
}
void CBinaryStringBuilder::WriteInt(int value){

}
void CBinaryStringBuilder::WriteLong(long value){
}

void CBinaryStringBuilder::WriteFloat(float value){
}

void CBinaryStringBuilder::WriteDouble(double value){
}

void CBinaryStringBuilder::WriteVector(vec3_t value){
}

void CBinaryStringBuilder::WriteString(CString* value){
}

void CBinaryStringBuilder::ClearBuffer(){
	this->Buffer = nullptr;
}

CBinaryStringBuilder g_ASBinaryStringBuilder;

void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(void* pthis, SC_SERVER_DUMMYARG CString* buffer){
	g_ASBinaryStringBuilder.SetBuffer(buffer);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteInt(void* pthis, SC_SERVER_DUMMYARG int value){
	g_ASBinaryStringBuilder.WriteInt(value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(void* pthis, SC_SERVER_DUMMYARG long value){
	g_ASBinaryStringBuilder.WriteLong(value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(void* pthis, SC_SERVER_DUMMYARG float value){
	g_ASBinaryStringBuilder.WriteFloat(value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(void* pthis, SC_SERVER_DUMMYARG double value){
	g_ASBinaryStringBuilder.WriteDouble(value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(void* pthis, SC_SERVER_DUMMYARG vec3_t value){
	g_ASBinaryStringBuilder.WriteVector(value);
}
void SC_SERVER_DECL ASBinaryBuilder_WriteString(void* pthis, SC_SERVER_DUMMYARG CString* value){
	g_ASBinaryStringBuilder.WriteString(value);
}
void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(void* pthis SC_SERVER_DUMMYARG_NOCOMMA){
	g_ASBinaryStringBuilder.ClearBuffer();
}
