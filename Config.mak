CFLAGS-=-std=gnu++14
CFLAGS+=-std=gnu++20
MODNAME = asexthook
SRCFILES = angelscript.cpp dllapi.cpp engine_api.cpp sdk_util.cpp h_export.cpp meta_api.cpp vftable.cpp CASBinaryStringBuilder.cpp CASSQLite.cpp CASBaseObject.cpp
INCLUDEDIRS+=-I$(SDKSRC)/../CDetour
INCLUDEDIRS+=-I$(SDKSRC)/../asext/include
EXTRA_CFLAGS += -DPLATFORM_POSIX
