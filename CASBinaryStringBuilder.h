#pragma once
#include <string>
class CBinaryStringBuilder
{
public:
    CBinaryStringBuilder(asIScriptEngine* engine);
    static CBinaryStringBuilder* SC_SERVER_DECL Factory(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);

    // Reference counting
    static void SC_SERVER_DECL AddRef(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static void SC_SERVER_DECL Release(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);

    static void SC_SERVER_DECL SetGCFlag(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static bool SC_SERVER_DECL GetGCFlag(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static int SC_SERVER_DECL GetRefCount(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static void SC_SERVER_DECL EnumReferences(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG asIScriptEngine* engine);
    static void SC_SERVER_DECL ReleaseAllReferences(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG asIScriptEngine* engine);

    static void SC_SERVER_DECL Get(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer);
    static void SC_SERVER_DECL Set(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* buffer);

    static size_t SC_SERVER_DECL GetReadPointer(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static void SC_SERVER_DECL SetReadPointer(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG size_t pointer);

    static void SC_SERVER_DECL WriteInt(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int value);
    static void SC_SERVER_DECL WriteLong(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG int64 value);
    static void SC_SERVER_DECL WriteFloat(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG float value);
    static void SC_SERVER_DECL WriteDouble(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG double value);
    static void SC_SERVER_DECL WriteVector(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t value);
    static void SC_SERVER_DECL WriteString(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* value);

    static int SC_SERVER_DECL ReadInt(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static int64 SC_SERVER_DECL ReadLong(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static float SC_SERVER_DECL ReadFloat(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static double SC_SERVER_DECL ReadDouble(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);
    static void SC_SERVER_DECL ReadVector(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG vec3_t vecBuffer);
    static void SC_SERVER_DECL ReadString(CBinaryStringBuilder* pthis, SC_SERVER_DUMMYARG CString* szBuffer);
    static bool SC_SERVER_DECL ReadToEnd(CBinaryStringBuilder* pthis SC_SERVER_DUMMYARG_NOCOMMA);

    size_t iReadPointer = 0;
    std::string szBuffer;
private:
    size_t  refCount;
};