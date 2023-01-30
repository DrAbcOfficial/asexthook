MODNAME = asexthook
SRCFILES = angelscript.cpp dllapi.cpp engine_api.cpp sdk_util.cpp h_export.cpp meta_api.cpp
INCLUDEDIRS+=-I$(SDKSRC)/../CDetour
INCLUDEDIRS+=-I$(SDKSRC)/../asext/include
INCLUDEDIRS+=-I/QRCode
EXTRA_CFLAGS += -DPLATFORM_POSIX
