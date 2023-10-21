include_directories(../wiiuse/src)
add_executable(test src/main.cpp)
target_link_libraries(test "${CMAKE_BINARY_DIR}/wiiuse/src/libwiiuse.a" bluetooth )#wiiuse

# if(INSTALL_EXAMPLES)
# 	install(TARGETS wiiuseexample
# 		RUNTIME DESTINATION bin COMPONENT examples)
# endif()