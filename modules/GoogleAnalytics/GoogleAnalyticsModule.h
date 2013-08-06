//
// Created by Fedor Shubin on 7/1/13.
//

#ifndef __GoogleAnalyticsModule_H_
#define __GoogleAnalyticsModule_H_

#include "cocos2d.h"

class GoogleAnalyticsModule {
public:
    static void init(cocos2d::CCDictionary *initParams);
    static void sendEventWithCategory(char const *category, char const *action, char const *label, int value);
    static void sendView(char const *viewName);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};


#endif //__GoogleAnalyticsModule_H_
