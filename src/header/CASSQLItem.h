#pragma once
#include "CASBaseObject.h"

class CBinaryStringBuilder;
class CASSQLItem : public CASBaseGCObject{
public:
    CASSQLItem();
    ~CASSQLItem();
    static CASSQLItem* Factory();

    CString* Get();
    int64 GetInt64();
    int GetInt();
    double GetReal();
    CBinaryStringBuilder** GetBlob();

    //Only for c++ not expose to as
    static CASSQLItem* ParamFactory(char* str);
    void SetData(char* str);
private:
    asITypeInfo* m_pStrInfo;
    asITypeInfo* m_pBlobInfo;
    CString* m_szData;
};