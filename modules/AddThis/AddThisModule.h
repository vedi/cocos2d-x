//
// Created by Alexandr on 29.07.13.
//



#ifndef __ShareModule_H_
#define __ShareModule_H_

#include "cocos2d.h"

#define EASY_NDK_METHOD "addThis_easyNDK"


class AddThisModule {
public:
    static void init(cocos2d::CCDictionary *initParams);
    static void setFacebookKeys(const char* key, const char *serviceName);

    static void shareText(const char* text, const char*serviceName = NULL);
    static void shareUrl(const char*urlStr, const char* title = NULL, const char*serviceName = NULL);
    static void shareImage(const char* imagePath, const char* title = NULL, const char*serviceName = NULL);

    static void share(char const *text, char const *urlStr, char const *imagePath, char const *title = NULL, const char*serviceName = NULL);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);

};


#endif //__AddThisModule_H_
