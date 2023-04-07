#pragma once
#include <string>
struct BinaryStringBuilder{
	size_t iReadPointer = 0;
	std::string szBuffer;
};

extern BinaryStringBuilder g_ASBinaryStringBuilder;

void SC_SERVER_DECL ASBinaryBuilder_Output(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer);
void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer);

size_t SC_SERVER_DECL ASBinaryBuilder_GetReadPointer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
void SC_SERVER_DECL ASBinaryBuilder_SetReadPointer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG size_t pointer);

void SC_SERVER_DECL ASBinaryBuilder_WriteInt(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value);
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value);
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value);
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value);
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value);
void SC_SERVER_DECL ASBinaryBuilder_WriteString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value);

int SC_SERVER_DECL ASBinaryBuilder_ReadInt(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
int64 SC_SERVER_DECL ASBinaryBuilder_ReadLong(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
float SC_SERVER_DECL ASBinaryBuilder_ReadFloat(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
double SC_SERVER_DECL ASBinaryBuilder_ReadDouble(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
void SC_SERVER_DECL ASBinaryBuilder_ReadVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t vecBuffer);
void SC_SERVER_DECL ASBinaryBuilder_ReadString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* szBuffer);
bool SC_SERVER_DECL ASBinaryBuilder_ReadToEnd(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);

void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);