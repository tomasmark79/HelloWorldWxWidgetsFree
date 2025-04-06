cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW) # project() command manages VERSION variables
cmake_policy(SET CMP0076 NEW) # target_sources() command creates usage requirements
cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags are selected by an abstraction

# MIT License Copyright (c) 2024-2025 Tomáš Mark

# +-+-+-+-+-+-+-+
# |l|i|b|r|a|r|y|
# +-+-+-+-+-+-+-+

# === shared libraries
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
# === runtime
include(cmake/tmplt-runtime.cmake)
option(USE_STATIC_RUNTIME "Link against static runtime libraries" OFF)
# === sanitizer
include(cmake/tmplt-sanitizer.cmake)
option(SANITIZE_ADDRESS "Enable Address sanitizer" OFF)
option(SANITIZE_UNDEFINED "Enable Undefined Behavior sanitizer" OFF)
option(SANITIZE_THREAD "Enable Thread sanitizer" OFF)
option(SANITIZE_MEMORY "Enable Memory sanitizer" OFF)
# === hardening
include(cmake/tmplt-hardening.cmake)
option(ENABLE_HARDENING "Enable security hardening options" OFF)
# === ipo
include(cmake/tmplt-ipo.cmake)
option(ENABLE_IPO "Enable Interprocedural Optimization" OFF)
# === ccache
include(cmake/ccache.cmake)
option(ENABLE_CCACHE "Enable ccache" ON)

# Linting C/C++ code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# Project attributes - case size will reflect resource files case size
# ==============================================================================
set(LIBRARY_NAME WxWidgetsAdapter)
string(TOLOWER "${LIBRARY_NAME}" LIBRARY_NAME_LOWER)
set(LIBRARY_NAMESPACE dsdotname)
project(
    ${LIBRARY_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX
    DESCRIPTION "template Copyright (c) 2024 TomasMark [at] digitalspace.name"
    HOMEPAGE_URL "https://github.com/tomasmark79")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        WARNING
            "In-source builds. Please make a new directory (called a Build directory) and run CMake from there."
    )
endif()

# ==============================================================================
# System / Conan dependencies
# ==============================================================================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
# find_package(ZLIB REQUIRED) find_package(nlohmann_json REQUIRED) find_package(yaml-cpp REQUIRED)
find_package(
    wxWidgets REQUIRED
    COMPONENTS core base
    REQUIRED config)

# ==============================================================================
# CPM.cmake dependencies - take care conflicts
# ==============================================================================
# export CPM_SOURCE_CACHE=$HOME/.cache/CPM # for localy caching CPM packages
# ==============================================================================
include(cmake/ccache.cmake)
include(cmake/CPM.cmake)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")
CPMAddPackage("gh:cpm-cmake/CPMLicenses.cmake@0.0.7")
cpm_licenses_create_disclaimer_target(
    write-licenses-${LIBRARY_NAME} "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_third_party.txt"
    "${CPM_PACKAGES}")

# ==============================================================================
# include/ for public header files intended for use in other projects or modules.
# ==============================================================================
file(
    GLOB_RECURSE
    headers
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)

# ==============================================================================
# src/ for source files and `internal` header files that are not intended for public use
# ==============================================================================
file(
    GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

# ==============================================================================
# Create target
# ==============================================================================
add_library(${LIBRARY_NAME})
target_sources(${LIBRARY_NAME} PRIVATE ${headers} ${sources})

apply_ipo(${LIBRARY_NAME})
apply_ccache(${LIBRARY_NAME})
apply_hardening(${LIBRARY_NAME})
apply_sanitizers(${LIBRARY_NAME})

# ==============================================================================
# Set headers
# ==============================================================================
# header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# <add_library(${LIBRARY_NAME} INTERFACE)>
target_include_directories(
    ${LIBRARY_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:include/${LIBRARY_NAME}-${PROJECT_VERSION}>)

# ==============================================================================
# Set compile options
# ==============================================================================
# note: generator expressions are evaluated during generation of the buildsystem, and not during
# processing of CMakeLists.txt files
target_compile_options(
    ${LIBRARY_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive-;/W4>"
    PUBLIC
        "$<$<AND:$<NOT:$<COMPILE_LANG_AND_ID:CXX,MSVC>>,$<NOT:$<PLATFORM_ID:Darwin>>>:-Wall;-Wextra;-Wpedantic;-MMD;-MP>"
    PUBLIC
        "$<$<AND:$<NOT:$<COMPILE_LANG_AND_ID:CXX,MSVC>>,$<PLATFORM_ID:Darwin>>:-Wall;-Wextra;-Wpedantic>"
)

# ==============================================================================
# Set compile features C++ version from Conan Profile has priority over this setting
# ==============================================================================
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================================================
# Set linking
# ==============================================================================
target_link_libraries(
    ${LIBRARY_NAME}
    PUBLIC fmt::fmt
    # PRIVATE ZLIB::ZLIB
    # PRIVATE nlohmann_json::nlohmann_json
    # PRIVATE yaml-cpp
    PRIVATE wxWidgets::wxWidgets)

# ==============================================================================
# set packageProject arttributes
# ==============================================================================
packageProject(
    # the name of the target to export
    NAME ${LIBRARY_NAME}
    # the version of the target to export
    VERSION ${PROJECT_VERSION}
    # a temporary directory to create the config files
    BINARY_DIR ${PROJECT_BINARY_DIR}
    # location of the target's public headers
    INCLUDE_DIR "/include"
    # should match the target's INSTALL_INTERFACE include directory
    INCLUDE_DESTINATION include/${LIBRARY_NAME_LOWER}-${PROJECT_VERSION}
    # (optional) option to install only header files with matching pattern
    INCLUDE_HEADER_PATTERN "*.h;*.hpp;*.hh;*.hxx"
    # semicolon separated list of the project's dependencies DEPENDENCIES
    # "zlib#1.2.11;fmt#11.1.1;CPMLicenses.cmake@0.0.7;nlohmann_json#3.11.2"
    DEPENDENCIES "fmt#11.1.0;CPMLicenses.cmake@0.0.7"
    # (optional) create a header containing the version info Note: that the path to headers should
    # be lowercase, but is not enforced
    VERSION_HEADER "${LIBRARY_NAME}/version.h"
    # (optional) create an export header using GenerateExportHeader module
    EXPORT_HEADER "${LIBRARY_NAME}/export.h"
    # (optional) install your library with a namespace (Note: do NOT add extra '::')
    NAMESPACE ${LIBRARY_NAMESPACE}
    # (optional) define the project's version compatibility, defaults to `AnyNewerVersion` supported
    # values: `AnyNewerVersion|SameMajorVersion|SameMinorVersion|HWWxWidgetsVersion`
    COMPATIBILITY AnyNewerVersion
    # (optional) option to disable the versioning of install destinations
    DISABLE_VERSION_SUFFIX YES
    # (optional) option to ignore target architecture for package resolution defaults to YES for
    # header only (i.e. INTERFACE) libraries
    ARCH_INDEPENDENT YES
    # (optional) option to generate CPack variables
    CPACK YES
          # (optional) relative install directory for runtimes: bins, libs, archives by default libs
          # will be installed to <...>/lib/<packagename-version>/ / - means relative to <...>/lib,
          # i.e. install libs to <...>/lib/, bins to <...>/bin/, etc
          RUNTIME_DESTINATION /)

# ==============================================================================
# Add missing installation exports
# ==============================================================================
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME} DESTINATION include/)
