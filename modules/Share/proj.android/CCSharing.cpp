#include "cocos2d.h"
#include "jni/JniHelper.h"

USING_NS_CC;

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxSharing"

extern "C"
{
  
    void CCSharing::shareText(const char* text) {
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxSharing"
                        ,"shareText"
                        ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(text);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
            
            t.env->DeleteLocalRef(StringArg1);
        	t.env->DeleteLocalRef(t.classID);
        }

    }
}

}

void shareImage(const char* imageName) {

}

void shareUrl(const char* url, const char* title) {

}

void shareFile(const char* fileName) {

}
