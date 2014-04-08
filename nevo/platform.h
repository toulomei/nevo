#pragma once

#define PLATFORM_WINDOWS    1
#define PLATFORM_LINUX      2
#define PLATFORM_MACOS      3
#define PLATFORM_ANDROID    4
#define PLATFORM_IOS        5

#if defined(_WIN32)
    #define PLATFORM_ID PLATFORM_WINDOWS
#elif defined(__ANDROID__)
    #define PLATFORM_ID PLATFORM_ANDROID
#elif defined(__linux__)
    #define PLATFORM_ID PLATFORM_LINUX
#endif
