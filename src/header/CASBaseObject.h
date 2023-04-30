#pragma once
#include "asext_api.h"
#include "angelscriptlib.h"
class CASBaseRefObject {
public:
	virtual void AddRef();
    virtual void Release();
protected:
    size_t  refCount = 1;
};
class CASBaseGCObject : public CASBaseRefObject {
public:
    void AddRef() override;
    void Release() override;

    void SetGCFlag();
    bool GetGCFlag();
    int GetRefCount();
    void EnumReferences(asIScriptEngine* engine);
    void ReleaseReferences(asIScriptEngine* engine);
};