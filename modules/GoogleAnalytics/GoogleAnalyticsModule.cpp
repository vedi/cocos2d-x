//
// Created by Fedor Shubin on 7/1/13.
//


#include "GoogleAnalyticsModule.h"
#include "NDKHelper.h"

USING_NS_CC;

#define EASY_NDK_METHOD "googleAnalytics_easyNDK"

void GoogleAnalyticsModule::init(CCDictionary *initParams) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(initParams, "initParams");
    callNative(params);
}


void GoogleAnalyticsModule::sendEventWithCategory(char const *category, char const *action, char const *label, int value) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("sendEventWithCategory"), "method");
    params->setObject(CCString::create(category), "category");
    params->setObject(CCString::create(action), "action");
    params->setObject(CCString::create(label), "label");
    params->setObject(CCInteger::create(value), "value");

    callNative(params);
}

void GoogleAnalyticsModule::sendView(char const *viewName) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("sendView"), "method");
    params->setObject(CCString::create(viewName), "viewName");

    callNative(params);
}

CCObject *GoogleAnalyticsModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

