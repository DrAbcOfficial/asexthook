#pragma once
#define GetEntVarsVTable(var)var==nullptr?nullptr:ENT(var)->pvPrivateData

#define OFFSET_WIN_ENTVAR			4
#define OFFSET_LIN_ENTVAR			4 // first entry in the virtual class (vtable is 0)

// Converts something such as RESOURCES into OFFSET_WIN_RESOURCES or OFFSET_LIN_RESOURCES
#if defined(__linux__) || defined(__APPLE__)
#define MAKE_OFFSET(Offset) OFFSET_LIN_##Offset
#define MAKE_MEMBER_OFFSET(Offs) (Offs - OFFSET_LIN_MEMBERFUNCSTART)
#else
#define MAKE_OFFSET(Offset) OFFSET_WIN_##Offset
#define MAKE_MEMBER_OFFSET(Offs) (Offs - OFFSET_WIN_MEMBERFUNCSTART)
#endif // __linux__

inline edict_t* PrivateToEdict(void* PrivateData){
	if (PrivateData == nullptr)
		return nullptr;
	return (*((entvars_t**)((char*)PrivateData + MAKE_OFFSET(ENTVAR))))->pContainingEntity;
};