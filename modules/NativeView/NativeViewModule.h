//
// Created by Fedor Shubin on 7/1/13.
//

#ifndef __NativeViewModule_H_
#define __NativeViewModule_H_

#include "cocos2d.h"

#define WEB_VIEW_KEY "WEB_VIEW_KEY"

class NativeViewModule {
public:
    static void init();
    static void addListener(char const *key,
            cocos2d::CCObject *target, cocos2d::SEL_CallFuncO selector);
    static void removeListener(char const *key);
    static void createAndShowNative(char const *viewKey, cocos2d::CCDictionary *viewParams,
            char const *viewData, float x, float y, float w, float h);
    static void sendMessage(char const *key, const char *messageData);
    static void closeNative(char const *key);
private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};


#endif //__NativeViewModule_H_
