package nevo;

import android.view.Surface;

public class SurfaceTextureHandler {
    private long nativeInstance;

    SurfaceTextureHandler(long id) throws Exception {
        long nativeInstance = nativeCreateHandler(id);
        if (nativeInstance == 0)
            throw new Exception("No implementation is assigned for id = '" + Id + "'");
    }

    public void release() {
        if (nativeInstance != 0) {
            nativeDestroyHandler(nativeInstance);
            nativeInstance = 0;
        }
    }

    protected void finalize() {
        release();
    }

    public void surfaceAvailable(SurfaceTexture surface) {
        nativeSurfaceAvailable(nativeInstance, surface);
    }

    public void surfaceSizeChanged() {
        nativeSurfaceSizeChanged(nativeInstance);
    }

    public void surfaceDestroyed() {
        nativeSurfaceDestroyed(nativeInstance);
    }

    private native long nativeCreateHandler(long id);
    private native void nativeDestroyHandler(long nativeInstance);
    private native void nativeSurfaceAvailable(long nativeInstance, SurfaceTexture surface);
    private native void nativeSurfaceSizeChanged(long nativeInstance);
    private native void nativeSurfaceDestroyed(long nativeInstance);
}
