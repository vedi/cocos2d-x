/*
 * Copyright (c) 2013 VedideV
 *
 */
#ifndef __flurry__FlurryManager__
#define __flurry__FlurryManager__

#include "cocos2d.h"

class FlurryManager {
public:
    static void setUserId(char const *userId);
    static void setAppVersion(char const *appVersion);
    static bool init(const char * apiKey);
    static void logEvent(const char* eventId, cocos2d::CCDictionary* paramMap = NULL);
    static void logTimedEventBegin(const char* eventId, cocos2d::CCDictionary* paramMap = NULL);
    static void logTimedEventEnd(const char* eventId, cocos2d::CCDictionary* paramMap = NULL);
private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};

#endif  // __flurry__FlurryManager__