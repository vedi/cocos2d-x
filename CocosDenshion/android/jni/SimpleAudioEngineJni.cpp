#include "SimpleAudioEngineJni.h"
#include "platform/android/jni/JniHelper.h"

#include <android/log.h>

#define  LOG_TAG    "libSimpleAudioEngine"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;


extern "C"
{
    // get env and cache it
    static JNIEnv* getJNIEnv(void)
    {
        
        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm) {
            LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
            return NULL;
        }
        
        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
        
        switch (ret) {
            case JNI_OK :
                // Success!
                return env;
                
            case JNI_EDETACHED :
                // Thread not attached
                
                // TODO : If calling AttachCurrentThread() on a native thread
                // must call DetachCurrentThread() in future.
                // see: http://developer.android.com/guide/practices/design/jni.html
                
                if (jvm->AttachCurrentThread(&env, NULL) < 0)
                {
                    LOGD("Failed to get the environment using AttachCurrentThread()");
                    return NULL;
                } else {
                    // Success : Attached and obtained JNIEnv!
                    return env;
                }
                
            case JNI_EVERSION :
                // Cannot recover from this error
                LOGD("JNI interface version 1.4 not supported");
            default :
                LOGD("Failed to get the environment using GetEnv()");
                return NULL;
        }
    }
    
    // get class and make it a global reference, release it at endJni().
    static jclass getClassID(JNIEnv *pEnv)
    {
        jclass ret = pEnv->FindClass(CLASS_NAME);
        if (! ret)
        {
            LOGD("Failed to find class of %s", CLASS_NAME);
        }
        
        return ret;
    }
    
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;
        
        do 
        {
            pEnv = getJNIEnv();
            if (! pEnv)
            {
                break;
            }
            
            jclass classID = getClassID(pEnv);
            
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }
            
            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;
            
            bRet = true;
        } while (0);
        
        return bRet;
    }
    
    void preloadSoundJNI(const char *path, unsigned int channelNum)
    {
        // void playSound(String,boolean)
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "preloadSound", "(Ljava/lang/String;I)V"))
        {            
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, (int)channelNum);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void playSoundJNI(const char *path, bool isLoop, unsigned int channelNum)
    {
        // void playSound(String,boolean)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "playSound", "(Ljava/lang/String;ZI)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, isLoop, (int)channelNum);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void stopSoundJNI(unsigned int channelNum)
    {
        // void stopSound()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopSound", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void pauseSoundJNI(unsigned int channelNum)
    {
        // void pauseSound()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseSound", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeSoundJNI(unsigned int channelNum)
    {
        // void resumeSound()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeSound", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void rewindSoundJNI(unsigned int channelNum)
    {
        // void rewindSound()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "rewindSound", "(I)V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    bool isSoundPlayingJNI(unsigned int channelNum)
    {
        // boolean rewindSound()
        
        JniMethodInfo methodInfo;
        jboolean ret = false;
        
        if (! getStaticMethodInfo(methodInfo, "isSoundPlaying", "(I)Z"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    float getSoundVolumeJNI(unsigned int channelNum)
    {
        // float getSoundVolume()
        
        JniMethodInfo methodInfo;
        jfloat ret = -1.0;
        
        if (! getStaticMethodInfo(methodInfo, "getSoundVolume", "(I)F"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void setSoundVolumeJNI(float volume, unsigned int channelNum)
    {
        // void setSoundVolume()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setSoundVolume", "(FI)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, volume, (int)channelNum);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    float getSoundDurationJNI(const char *path, unsigned int channelNum)
    {
        JniMethodInfo methodInfo;
        jfloat ret = -1.0;
        
        if (! getStaticMethodInfo(methodInfo, "getSoundDuration", "(Ljava/lang/String;I)F"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID, stringArg, (int)channelNum);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    unsigned int playEffectJNI(const char* path, bool bLoop)
    {
        // int playEffect(String)
        
        JniMethodInfo methodInfo;
        int ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "playEffect", "(Ljava/lang/String;Z)I"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, stringArg, bLoop);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return (unsigned int)ret;
    }
    
    void stopEffectJNI(unsigned int nSoundId)
    {
        // void stopEffect(int)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopEffect", "(I)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)nSoundId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void endJNI()
    {
        // void end()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "end", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    float getEffectsVolumeJNI()
    {
        // float getEffectsVolume()
        
        JniMethodInfo methodInfo;
        jfloat ret = -1.0;
        
        if (! getStaticMethodInfo(methodInfo, "getEffectsVolume", "()F"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void setEffectsVolumeJNI(float volume)
    {
        // void setEffectsVolume(float)
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setEffectsVolume", "(F)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, volume);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void preloadEffectJNI(const char *path)
    {
        // void preloadEffect(String)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "preloadEffect", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void unloadEffectJNI(const char* path)
    {
        // void unloadEffect(String)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "unloadEffect", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void pauseEffectJNI(unsigned int nSoundId)
    {
        // void pauseEffect(int)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseEffect", "(I)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)nSoundId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void pauseAllEffectsJNI()
    {
        // void pauseAllEffects()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseAllEffects", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeEffectJNI(unsigned int nSoundId)
    {
        // void resumeEffect(int)
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeEffect", "(I)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)nSoundId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeAllEffectsJNI()
    {
        // void resumeAllEffects()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeAllEffects", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void stopAllEffectsJNI()
    {
        // void stopAllEffects()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopAllEffects", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
