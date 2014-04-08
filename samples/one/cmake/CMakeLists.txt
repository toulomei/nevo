cmake_minimum_required(VERSION 2.8)

project(nevo_sample_one)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ANDROID_NATIVE_API_LEVEL "android-9")

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(PROJECT_SRC_DIR ${PROJECT_ROOT_DIR}/src)
set(NEVO_DIR ${PROJECT_ROOT_DIR}/../..)

add_subdirectory(${NEVO_DIR}/cmake/nevo nevo)

if(MSVC)
	set(SRC_PLATFORM 
		${PROJECT_SRC_DIR}/platform/windows/main.cpp)
elseif(ANDROID)
	set(SRC_PLATFORM 
		${NEVO_DIR}/nevo/platform/android/entrypoint.cpp
		${PROJECT_SRC_DIR}/platform/android/main.cpp)
endif()

include_directories(${NEVO_DIR})

set(SRC ${SRC_COMMON} ${SRC_PLATFORM})

if(MSVC)
	include_directories(${NEVO_DIR}/thirdparties/glew/include)
	add_executable(nevo_sample_one ${SRC})
elseif(ANDROID)
	add_library(nevo_sample_one SHARED ${SRC})
	target_link_libraries(nevo_sample_one android log)
endif()

target_link_libraries(nevo_sample_one nevo)