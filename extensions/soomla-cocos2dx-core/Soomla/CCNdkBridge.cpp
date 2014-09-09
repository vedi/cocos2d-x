//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCNdkBridge.h"
#include "CCJsonHelper.h"

USING_NS_CC;

#define LOG_JSON 0

#if (LOG_JSON == 1)
#define TAG "JSON"
#include "CCSoomlaUtils.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
    #include <jni.h>
    #include <string>
    #include "CCSoomlaEventDispatcher.h"
#ifdef COCOS2D_JAVASCRIPT
    #include "jsb/JSBinding.h"
#endif

    #define CLASS_NAME "com/soomla/cocos2dx/common/NdkGlue"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "CCNdkBridgeIos.h"

#endif

namespace soomla {
    extern "C"
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        // Method for receiving NDK messages
        void Java_com_soomla_cocos2dx_common_NdkGlue_sendCppMessage(JNIEnv* env, jobject thiz, jstring json)
        {
            std::string jsonString = JniHelper::jstring2string(json);
            const char *jsonCharArray = jsonString.c_str();

            json_error_t error;
            json_t *root;
            root = json_loads(jsonCharArray, 0, &error);

            if (!root)
                {
                    fprintf(stderr, "error: at line #%d: %s\n", error.line, error.text);
                    return;
                }

            cocos2d::CCObject *dataToPass = CCJsonHelper::getCCObjectFromJson(root);

#ifdef COCOS2D_JAVASCRIPT
            Soomla::JSBinding::callCallback((cocos2d::CCDictionary *) dataToPass);
#else
            CCSoomlaEventDispatcher::getInstance()->ndkCallback((cocos2d::CCDictionary *)dataToPass);
#endif

            json_decref(root);
        }
#endif

        cocos2d::CCObject *CCNdkBridge::callNative(cocos2d::CCDictionary *params, CCError **pError) {
            cocos2d::CCDictionary *methodParams = params;

            json_t *toBeSentJson = CCJsonHelper::getJsonFromCCObject(methodParams);
            json_t *retJsonParams = NULL;

#if (LOG_JSON == 1)
            CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat(
                    "to native JSON: %s", json_dumps(toBeSentJson, JSON_COMPACT | JSON_ENSURE_ASCII))->getCString());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            JniMethodInfo t;

            if (JniHelper::getStaticMethodInfo(t,
                                               CLASS_NAME,
                                               "receiveCppMessage",
                                               "(Ljava/lang/String;)Ljava/lang/String;")) {

                char* jsonStrLocal = json_dumps(toBeSentJson, JSON_COMPACT | JSON_ENSURE_ASCII);
                std::string jsonStr(jsonStrLocal);
                free(jsonStrLocal);

                jstring stringArg1 = t.env->NewStringUTF(jsonStr.c_str());
                jstring retString = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1);

                t.env->DeleteLocalRef(stringArg1);
                t.env->DeleteLocalRef(t.classID);

                const char *nativeString = t.env->GetStringUTFChars(retString, 0);
                std::string retParamsStr(nativeString);
                t.env->ReleaseStringUTFChars(retString, nativeString);


                const char *jsonCharArray = retParamsStr.c_str();

                json_error_t error;
                retJsonParams = json_loads(jsonCharArray, 0, &error);

                if (!retJsonParams) {
                    fprintf(stderr, "error: at line #%d: %s\n", error.line, error.text);
                    return CCDictionary::create();
                }
            }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            retJsonParams = soomla::CCNdkBridgeIos::receiveCppMessage(toBeSentJson);
#endif

#if (LOG_JSON == 1)
            CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat(
                    "from native JSON: %s", json_dumps(retJsonParams, JSON_COMPACT | JSON_ENSURE_ASCII))->getCString());
#endif

            json_decref(toBeSentJson);
            CCObject *retParams = CCJsonHelper::getCCObjectFromJson(retJsonParams);

            if (retJsonParams) {
                json_decref(retJsonParams);
            }

            if (pError != NULL) {
                CCError *error = CCError::createWithObject(retParams);
                if (error != NULL) {
                    *pError = error;
                }
            }

            return retParams;
        }
    }
}
