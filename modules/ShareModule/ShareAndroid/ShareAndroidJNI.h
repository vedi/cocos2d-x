


#ifndef ShareAndroidJni_h
#define ShareAndroidXJni_h

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

extern "C"
{
    extern void ShareAndroid_showShareDialogJNI( const char*shareText);
    extern void ShareAndroid_rateAppJNI();
    extern bool ShareAndroid_isAmazonStore();
}

#endif // __FF_UTILS_JNI__
