//
// Created by Fedor Shubin on 7/1/13.
//

#ifndef __HasAppModule_H_
#define __HasAppModule_H_

#include "cocos2d.h"

class HasAppModule {
public:
    static void init(cocos2d::CCDictionary *initParams);
    static void setListener(cocos2d::CCObject *target, cocos2d::SEL_CallFuncO selector);

    /**
    *   Async call. Returns to the listener with "method" key "hasApp".
    */
    static void hasApp(char const *appId);

    static void openApp(char const *appId);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};


#endif //__HasAppModule_H_
