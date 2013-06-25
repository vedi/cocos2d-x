/*
 * Copyright (c) 2013 VedideV
 *
 */

#include "FlurryManager.h"
#include "NDKHelper.h"

USING_NS_CC;

#define EASY_NDK_METHOD "flurry_easyNDK"


void FlurryManager::setUserId(char const *userId) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setUserId"), "method");
    params->setObject(CCString::create(userId), "userId");
    callNative(params);
}

void FlurryManager::setAppVersion(char const *appVersion) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setAppVersion"), "method");
    params->setObject(CCString::create(appVersion), "appVersion");
    callNative(params);
}

bool FlurryManager::init(const char * apiKey) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(CCString::create(apiKey), "apiKey");
    CCDictionary *retParams = (CCDictionary *) callNative(params);

    CCBool *retResult = dynamic_cast<CCBool *>(retParams->objectForKey("return"));
    CC_ASSERT(retResult);

    return retResult->getValue();
}

void FlurryManager::logEvent(char const *eventId, cocos2d::CCDictionary *paramMap) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("logEvent"), "method");
    params->setObject(CCString::create(eventId), "eventId");
    params->setObject(paramMap, "paramMap");
    callNative(params);
}

void FlurryManager::logTimedEventBegin(char const *eventId, cocos2d::CCDictionary* paramMap) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("logTimedEventBegin"), "method");
    params->setObject(CCString::create(eventId), "eventId");
    params->setObject(paramMap, "paramMap");
    callNative(params);
}

void FlurryManager::logTimedEventEnd(char const *eventId, cocos2d::CCDictionary* paramMap) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("logTimedEventEnd"), "method");
    params->setObject(CCString::create(eventId), "eventId");
    params->setObject(paramMap, "paramMap");
    callNative(params);
}

CCObject *FlurryManager::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

