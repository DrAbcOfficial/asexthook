#pragma once
#include <string>
struct BinaryStringBuilder{
	std::string szBuffer;
};

extern BinaryStringBuilder g_ASBinaryStringBuilder;

void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer);
void SC_SERVER_DECL ASBinaryBuilder_WriteInt(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value);
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value);
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value);
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value);
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value);
void SC_SERVER_DECL ASBinaryBuilder_WriteString(BinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value);
void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(BinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);