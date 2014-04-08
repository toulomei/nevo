cmake_minimum_required(VERSION 2.8)

project(glew)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(NEVO_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(THIRDPARTIES_DIR ${NEVO_ROOT_DIR}/thirdparties)

set(PROJECT_ROOT_DIR ${THIRDPARTIES_DIR}/glew)

set(SRC_DIR ${PROJECT_ROOT_DIR}/src)
set(INCLUDE_DIR ${PROJECT_ROOT_DIR}/include)

set(SRC
	${SRC_DIR}/glew.c
)

set(HDR
	${INCLUDE_DIR}/GL/glew.h
)

include_directories(${INCLUDE_DIR})

if(MSVC)
	add_definitions(-DWIN32_MEAN_AND_LEAN -DVC_EXTRALEAN -DGLEW_BUILD -D_CRT_SECURE_NO_WARNINGS)
	add_library(glew STATIC ${SRC})
	target_link_libraries(glew opengl32.lib)

	#set_property(TARGET libglew_static PROPERTY ARCHIVE_OUTPUT_NAME "glew" )
	#set_property(TARGET libglew_static PROPERTY DEBUG_POSTFIX d )
endif()