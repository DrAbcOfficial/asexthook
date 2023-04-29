#pragma once
#include <string>
#include "CASBaseObject.h"
class CBinaryStringBuilder : public CASBaseGCObject
{
public:
    CBinaryStringBuilder();
    static CBinaryStringBuilder* Factory();
    static CBinaryStringBuilder* ParamFactory(CString* str);

    void Get(CString* buffer);
    void Set(CString* buffer);

    size_t GetReadPointer();
    void SetReadPointer(size_t pointer);

    void WriteInt(int value);
    void WriteLong(int64 value);
    void WriteFloat(float value);
    void WriteDouble(double value);
    void WriteVector(vec3_t value);
    void WriteString(CString* value);

    int ReadInt();
    int64 ReadLong();
    float ReadFloat();
    double ReadDouble();
    void ReadVector(vec3_t vecBuffer);
    void ReadString(CString* szBuffer);
    bool IsReadToEnd();

    size_t iReadPointer = 0;
    std::string szBuffer;
};