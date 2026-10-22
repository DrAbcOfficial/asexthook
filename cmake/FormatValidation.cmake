if(NOT DEFINED FORMAT_VALIDATION_SOURCE_PATH)
    set(FORMAT_VALIDATION_SOURCE_PATH "$ENV{FORMAT_VALIDATION_SOURCE_PATH}" CACHE PATH "Local shared format tooling")
endif()
if(FORMAT_VALIDATION_SOURCE_PATH)
    get_filename_component(format_source "${FORMAT_VALIDATION_SOURCE_PATH}" ABSOLUTE)
else()
    include(FetchContent)
    FetchContent_Declare(mmfg_format_validation
        GIT_REPOSITORY https://github.com/MetaHookSv/FormatValidation.git
        GIT_TAG 13c9fabe058e1f887ad1b03bb6884de911192c6a
        GIT_SUBMODULES "" SOURCE_SUBDIR cmake)
    FetchContent_MakeAvailable(mmfg_format_validation)
    set(format_source "${mmfg_format_validation_SOURCE_DIR}")
endif()
include("${format_source}/cmake/FormatValidation.cmake")
format_validation_add_component(asexthook "${CMAKE_CURRENT_SOURCE_DIR}")
