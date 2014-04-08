#include <nevo/platform/android/entrypoint.h>
#include <android/log.h>

void nevo::platform::android::initialize()
{
    __android_log_print(ANDROID_LOG_DEBUG, "libnevo_sample_one", "nevo::platform::android::initialize()");
}

nevo::platform::android::surface_texture_handler* nevo::platform::android::create_handler(unsigned int id)
{
    __android_log_print(ANDROID_LOG_DEBUG, "libnevo_sample_one", "nevo::platform::android::create_handler(%d)", id);
}