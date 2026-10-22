cmake_minimum_required(VERSION 3.21)
option(FORMAT_VALIDATION_ONLY "Configure formatting without native dependencies" OFF)
if(FORMAT_VALIDATION_ONLY)
    project(ASExtHookFormat LANGUAGES NONE)
    include(cmake/FormatValidation.cmake)
    return()
endif()
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/metamod/cmake/Platform.cmake"
   OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/asext/cmake/SDK.cmake")
    message(FATAL_ERROR "Initialize dependencies with git submodule update --init --recursive.")
endif()
set(METAMOD_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/metamod")
set(ASEXT_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/asext")
include("${METAMOD_SOURCE_PATH}/cmake/Platform.cmake")
project(asexthook LANGUAGES C CXX)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build configuration" FORCE)
endif()
include("${METAMOD_SOURCE_PATH}/cmake/Build.cmake")
mmfg_configure_install_layout()
add_subdirectory(metamod)
add_subdirectory(asext)

add_library(asexthook SHARED
    src/angelscript.cpp
    src/angelscript_hooks.h
    src/CASBaseObject.cpp
    src/CASBaseObject.h
    src/CASBinaryStringBuilder.cpp
    src/CASBinaryStringBuilder.h
    src/CASSQLGrid.cpp
    src/CASSQLGrid.h
    src/CASSQLItem.cpp
    src/CASSQLItem.h
    src/CASSQLite.cpp
    src/CASSQLite.h
    src/dll_hook.cpp
    src/dllapi.cpp
    src/dlldef.h
    src/engine_api.cpp
    src/engine_hook.cpp
    src/enginedef.h
    src/extern_hook.h
    src/h_export.cpp
    src/info_name.h
    src/meta_api.cpp
    src/sdk_util.cpp
    src/signatures.h
    src/utility.h
    src/vftable.cpp
    src/vftable.h
)
mmfg_configure_target(asexthook)
target_compile_features(asexthook PRIVATE cxx_std_20)
target_link_libraries(asexthook PRIVATE ASExt::SDK)
if(WIN32)
    target_sources(asexthook PRIVATE src/dllmain.cpp)
    target_link_options(asexthook PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/src/asexthook.def")
endif()
mmfg_assign_source_groups(asexthook)
install(FILES assets/plugins.ini.example DESTINATION addons/metamod)
install(DIRECTORY examples/ DESTINATION examples)
install(DIRECTORY docs/ DESTINATION docs)
install(FILES assets/logo.png DESTINATION assets)
install(FILES README.md LICENSE THIRD_PARTY.md DESTINATION .)
install(FILES metamod/LICENSE DESTINATION licenses RENAME metamod-LICENSE)
install(FILES asext/LICENSE DESTINATION licenses RENAME asext-LICENSE)
install(FILES licenses/astemplate-LICENSE DESTINATION licenses)

option(ASEXTHOOK_BUILD_TESTS "Build the plugin ABI smoke test" ON)
if(ASEXTHOOK_BUILD_TESTS)
    enable_testing()
    add_executable(plugin-smoke tests/plugin_smoke.cpp)
    target_compile_features(plugin-smoke PRIVATE cxx_std_17)
    target_link_libraries(plugin-smoke PRIVATE ASExt::SDK ${CMAKE_DL_LIBS})
    if(NOT WIN32)
        target_compile_definitions(plugin-smoke PRIVATE PLATFORM_POSIX LINUX _LINUX)
    endif()
    add_dependencies(plugin-smoke asexthook asext)
    add_test(NAME plugin-smoke COMMAND plugin-smoke "$<TARGET_FILE:asexthook>" "$<TARGET_FILE:asext>")
endif()
include(cmake/FormatValidation.cmake)
