//
// Created by Fedor Shubin on 7/1/13.
//


#include "HasAppModule.h"
#include "NDKHelper.h"

USING_NS_CC;

#define EASY_NDK_METHOD "hasApp_easyNDK"

void HasAppModule::init(CCDictionary *initParams) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(initParams, "initParams");
    callNative(params);
}

void HasAppModule::setListener(CCObject *target, SEL_CallFuncO selector) {
    NDKHelper::addSelector("HasApp", "HasApp_callback", target, selector);
}

void HasAppModule::hasApp(char const *appId) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("hasApp"), "method");
    params->setObject(CCString::create(appId), "appId");

    callNative(params);
}

void HasAppModule::openApp(char const *appId) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("openApp"), "method");
    params->setObject(CCString::create(appId), "appId");

    callNative(params);
}

CCObject *HasAppModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

