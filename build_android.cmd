set MAKE_PROGRAM=%ANDROID_NDK%\prebuilt\windows-x86_64\bin\make.exe

set CMAKE_PARAMS=-DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchains/android.toolchain.cmake
set CMAKE_PARAMS=%CMAKE_PARAMS% -DCMAKE_MAKE_PROGRAM=%MAKE_PROGRAM%
set CMAKE_PARAMS=%CMAKE_PARAMS% -DANDROID_NATIVE_API_LEVEL=android-9

mkdir _build_android
cd _build_android
cmake -G "Unix Makefiles" %CMAKE_PARAMS% ../cmake/nevo
%MAKE_PROGRAM% -j %NUMBER_OF_PROCESSORS%