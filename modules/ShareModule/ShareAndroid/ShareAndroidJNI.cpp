#include "ShareAndroidJNI.h"

#define  CLASS_NAME "com/share/ShareBridge"

using namespace cocos2d;
extern "C"
{
	void ShareAndroid_showShareDialogJNI(const char* shareText){
		JniMethodInfo methodInfo;
		if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showShareDialog", "(Ljava/lang/String;)V")){
			return;
		}
		jstring appidArg = methodInfo.env->NewStringUTF(shareText);

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, appidArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(appidArg);    
	}

	void ShareAndroid_rateAppJNI(){
		JniMethodInfo methodInfo;
        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "rateApp", "()V")){
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

    bool ShareAndroid_isAmazonStore() {
        JniMethodInfo methodInfo;
        jboolean ret = false;
        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "isAmazonStore", "()Z")){
            return ret;
        }
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

        return ret;
    }
}
