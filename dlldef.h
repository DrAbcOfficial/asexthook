#pragma once
#include "progdefs.h"

typedef struct hookitem_s {
	hook_t* pHook;
	void* pfnCall;
	void* pfnOriginalCall;
	vtable_base_t* pVtable;
}hookitem_t;
void VtableUnhook();