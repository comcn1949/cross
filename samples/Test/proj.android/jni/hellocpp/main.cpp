#include "AppDelegate.h"
#include "ccTypes.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace CrossApp;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_CrossApp_lib_CrossAppRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CAApplication::getApplication()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        CAImageCache::reloadAllImages();
        CANotificationCenter::getInstance()->postNotification(EVENT_COME_TO_FOREGROUND);
        CAApplication::getApplication()->setGLDefaultValues();
    }
}

}
