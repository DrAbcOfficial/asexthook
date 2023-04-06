#pragma once
class CBinaryStringBuilder {
public:
	void SetBuffer(CString* buffer);
	void WriteInt(int value);
	void WriteLong(long value);
	void WriteFloat(float value);
	void WriteDouble(double value);
	void WriteVector(vec3_t value);
	void WriteString(CString* value);
	void ClearBuffer();
private:
	CString* Buffer;
};

extern CBinaryStringBuilder g_ASBinaryStringBuilder;

void SC_SERVER_DECL ASBinaryBuilder_SetBuffer(void* pthis, SC_SERVER_DUMMYARG CString* buffer);
void SC_SERVER_DECL ASBinaryBuilder_WriteInt(void* pthis, SC_SERVER_DUMMYARG int value);
void SC_SERVER_DECL ASBinaryBuilder_WriteLong(void* pthis, SC_SERVER_DUMMYARG long value);
void SC_SERVER_DECL ASBinaryBuilder_WriteFloat(void* pthis, SC_SERVER_DUMMYARG float value);
void SC_SERVER_DECL ASBinaryBuilder_WriteDouble(void* pthis, SC_SERVER_DUMMYARG double value);
void SC_SERVER_DECL ASBinaryBuilder_WriteVector(void* pthis, SC_SERVER_DUMMYARG vec3_t value);
void SC_SERVER_DECL ASBinaryBuilder_WriteString(void* pthis, SC_SERVER_DUMMYARG CString* value);
void SC_SERVER_DECL ASBinaryBuilder_ClearBuffer(void* pthis SC_SERVER_DUMMYARG_NOCOMMA);