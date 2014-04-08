cmake_minimum_required(VERSION 2.8)

project(nevo)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ANDROID_NATIVE_API_LEVEL android-9)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PROJECT_SRC_DIR ${PROJECT_ROOT_DIR}/nevo)

set(SRC_COMMON
	${PROJECT_SRC_DIR}/opengl/context.cpp
)

set(HDR_COMMON
	${PROJECT_SRC_DIR}/opengl/context.h
)

if(MSVC)
	set(SRC_PLATFORM
		${PROJECT_SRC_DIR}/platform/windows/window.cpp
		${PROJECT_SRC_DIR}/platform/windows/opengl/context.cpp
	)

	set(HDR_PLATFORM
		${PROJECT_SRC_DIR}/platform/windows/message_loop.h
		${PROJECT_SRC_DIR}/platform/windows/window.h
		${PROJECT_SRC_DIR}/platform/windows/window_class.h
		${PROJECT_SRC_DIR}/platform/windows/opengl/context.h
	)
elseif(ANDROID)
	set(SRC_PLATFORM
		${PROJECT_SRC_DIR}/platform/android/opengl/context.cpp
	)
endif()

include_directories(${PROJECT_ROOT_DIR})

set(SRC ${SRC_COMMON} ${SRC_PLATFORM})

if(MSVC)
	set(SRC ${SRC} ${HDR_COMMON} ${HDR_PLATFORM})
endif()

add_library(nevo STATIC ${SRC})

if(MSVC)
	include_directories(${PROJECT_ROOT_DIR}/thirdparties/glew/include)
	add_subdirectory(${PROJECT_ROOT_DIR}/cmake/glew glew)
	target_link_libraries(nevo glew)

	source_group("Source Files" FILES ${SRC_COMMON})
	source_group("Source Files\\Platform" FILES ${SRC_PLATFORM})
	source_group("Header Files" FILES ${HDR_COMMON})
	source_group("Header Files\\Platform" FILES ${HDR_PLATFORM})
elseif(ANROID)
	target_link_libraries(nevo)
endif()