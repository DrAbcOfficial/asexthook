#include "CASBaseObject.h"

void CASBaseRefObject::AddRef()
{
    refCount++;
}
void CASBaseRefObject::Release()
{
    if (--refCount == 0)
        delete this;
}

void CASBaseGCObject::AddRef()
{
    refCount = (refCount & 0x7FFFFFFFu) + 1;
}
void CASBaseGCObject::Release()
{
    refCount &= 0x7FFFFFFFu;
    if (--refCount == 0)
        delete this;
}
void CASBaseGCObject::SetGCFlag()
{
    refCount |= 0x80000000u;
}
bool CASBaseGCObject::GetGCFlag()
{
    return (refCount & 0x80000000u) ? true : false;
}
int CASBaseGCObject::GetRefCount()
{
    return static_cast<int>(refCount & 0x7FFFFFFFu);
}
void CASBaseGCObject::EnumReferences(asIScriptEngine* engine)
{
}
void CASBaseGCObject::ReleaseReferences(asIScriptEngine* engine)
{
}