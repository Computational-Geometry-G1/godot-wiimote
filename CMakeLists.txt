cmake_minimum_required(VERSION 3.20)

set(GDEXTENSION_LIB_NAME gdwiimote)
set(GDEXTENSION_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/project/bin")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_MESSAGE_LOG_LEVEL STATUS)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
    "${CMAKE_CURRENT_SOURCE_DIR}/extern/godot-cpp/cmake/"
)

project("${GDEXTENSION_LIB_NAME}"
  LANGUAGES
    C CXX
  VERSION
    0.1.0
)

include(godot-engine-configuration)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extern/godot-cpp")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extern/wiiuse")
set(BUILD_SHARED_LIBS ON)

set(compiler_is_clang "$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>")
set(compiler_is_gnu "$<CXX_COMPILER_ID:GNU>")
set(compiler_is_msvc "$<CXX_COMPILER_ID:MSVC>")

file(GLOB_RECURSE gdext_sources
     CONFIGURE_DEPENDS
       "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]"
       "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]pp"
)

add_library(${PROJECT_NAME}
    SHARED
      ${gdext_sources}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
   WIIUSE_STATIC
)

target_compile_options(${PROJECT_NAME} PUBLIC
    $<${compiler_is_msvc}:
        /EHsc
        /utf-8
        /Zc:preprocessor
        $<$<CONFIG:Debug>:
            /MDd
        >
        $<$<CONFIG:Release>:
            /MD
            /O2
        >
    >
    $<$<NOT:${compiler_is_msvc}>:
        -g
        -Wno-unused-value
        $<${compiler_is_gnu}:
            -Wno-attributes
            -Wno-attributes=rl::
        >
        $<${compiler_is_clang}:
            -Wno-ignored-attributes
            -Wno-unknown-attributes
        >
        $<$<CONFIG:Debug>:
            -fno-omit-frame-pointer
            -O0
        >
        $<$<CONFIG:Release>:
            -O3
        >
    >
)

# include directories gdextension library
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    SYSTEM "${WIIUSE_INCLUDE_DIRS}"
)

if (NOT APPLE)
    # linker options for the gdextension library
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<NOT:${compiler_is_msvc}>:
            -static-libgcc
            -static-libstdc++
            -Wl,-R,'$$ORIGIN'
        >
    )
endif()

# gdextension library dependency linkage
target_link_libraries(${PROJECT_NAME}
    PUBLIC godot::cpp
    PRIVATE wiiuse
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(system_bits 64)
else()
    set(system_bits 32)
endif()

string(TOLOWER
    "${PROJECT_NAME}.${CMAKE_SYSTEM_NAME}.${system_bits}.${CMAKE_BUILD_TYPE}"
    gde_lib_name
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		POSITION_INDEPENDENT_CODE ON
        CMAKE_EXPORT_COMPILE_COMMANDS ON
        CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON
		ARCHIVE_OUTPUT_DIRECTORY "${GDEXTENSION_LIB_PATH}"
		LIBRARY_OUTPUT_DIRECTORY "${GDEXTENSION_LIB_PATH}"
		RUNTIME_OUTPUT_DIRECTORY "${GDEXTENSION_LIB_PATH}"
        CMAKE_PDB_OUTPUT_DIRECTORY "${GDEXTENSION_LIB_PATH}"
        CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${GDEXTENSION_LIB_PATH}"
		OUTPUT_NAME "${gde_lib_name}"
)

# include utility script that prints a handful of
# useful build/configuration cmake variables
include(cmake-utils)
print_project_variables()
