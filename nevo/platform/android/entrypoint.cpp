#include <nevo/platform/android/entrypoint.h>
#include <nevo/platform/android/native_window_lock.h>

#include <jni.h>

#include <android/log.h>

namespace {
    template<typename T>
    inline T* to_ptr(int v) {
        return static_cast<T*>(static_cast<void*>(static_cast<char*>(0) + v));
    }

    template<typename T>
    inline int to_int(T* v) {
        return static_cast<char*>(static_cast<void*>(v)) - static_cast<char*>(0);
    }
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_2) != JNI_OK) {
        return -1;
    }

    nevo::platform::android::initialize();

    return JNI_VERSION_1_2;
}

extern "C" JNIEXPORT jlong JNICALL Java_nevo_SurfaceTextureHandler_nativeCreateHandler(JNIEnv * env, jclass clazz, jlong id) {
    return to_int(nevo::platform::android::create_handler(id));
}

extern "C" JNIEXPORT jlong JNICALL Java_nevo_SurfaceTextureHandler_nativeRelease(JNIEnv * env, jclass clazz, jlong instance) {
    delete to_ptr<nevo::platform::android::surface_texture_handler>(instance);
}

extern "C" JNIEXPORT jlong JNICALL Java_nevo_SurfaceTextureHandler_nativeAvailable(JNIEnv * env, jclass clazz, jlong instance, jobject surface) {
    nevo::platform::android::native_window_lock native_window(env, surface);
    to_ptr<nevo::platform::android::surface_texture_handler>(instance)->surface_available(native_window);
}

extern "C" JNIEXPORT jlong JNICALL Java_nevo_SurfaceTextureHandler_nativeChanged(JNIEnv * env, jclass clazz, jlong instance) {
    to_ptr<nevo::platform::android::surface_texture_handler>(instance)->surface_size_changed();
}

extern "C" JNIEXPORT jlong JNICALL Java_nevo_SurfaceTextureHandler_nativeDestroyed(JNIEnv * env, jclass clazz, jlong instance) {
    to_ptr<nevo::platform::android::surface_texture_handler>(instance)->surface_destroyed();
}
