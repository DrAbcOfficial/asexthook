MODNAME = asexthook
SRCFILES = angelscript.cpp dllapi.cpp engine_api.cpp sdk_util.cpp h_export.cpp meta_api.cpp share_obj.cpp vtable.cpp qrcodegen.cpp
INCLUDEDIRS+=-I$(SDKSRC)/../CDetour
INCLUDEDIRS+=-I$(SDKSRC)/../asext/include
EXTRA_CFLAGS += -DPLATFORM_POSIX
