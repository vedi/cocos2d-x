//
// Created by Alexandr on 29.07.13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __ShareModule_H_
#define __ShareModule_H_

#include "cocos2d.h"

#define EASY_NDK_METHOD "share_easyNDK"


class ShareModule {
public:

    static void shareText(const char* text);
    static void init(const char* applicationName, const char *applicationURL);
    static void setFacebookKeys(const char* key, const char *secret);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);

};


#endif //__ShareModule_H_
