cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# declare a variable projectName and assigned it a value WiiPerspective. We will make use of the same later.
SET(projectName godot-wiimote)
# here we define the project or solution name (for visual studio)
project(${projectName})

#set( WIIUSE_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/wiiuse/src/wiiuse.h" )

# file( GLOB_RECURSE WIIUSE_INCLUDES "${WIIUSE_INCLUDE_PATH}/*.h" )

include_directories(../wiiuse/src)
add_executable(${projectName} src/main.cpp)
target_link_libraries(${projectName} "${CMAKE_BINARY_DIR}/wiiuse/src/libwiiuse.a" bluetooth )#wiiuse

# 	install(TARGETS wiiuseexample
# 		RUNTIME DESTINATION bin COMPONENT examples)
