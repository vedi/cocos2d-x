//
// Created by Fedor Shubin on 7/1/13.
//


#include "NativeViewModule.h"
#include "NDKHelper.h"

USING_NS_CC;

#define EASY_NDK_METHOD "nativeView_easyNDK"

void NativeViewModule::init() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    callNative(params);
}

void NativeViewModule::addListener(char const *key, CCObject *target, SEL_CallFuncO selector) {
    NDKHelper::addSelector(key, key, target, selector);
}

void NativeViewModule::removeListener(char const *key) {
    NDKHelper::removeSelectorsInGroup(key);
}

void NativeViewModule::createAndShowNative(char const *viewKey, CCDictionary *viewParams, char const *viewData,
        float x, float y, float w, float h) {

    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("createAndShowNative"), "method");
    params->setObject(viewParams, "viewParams");
    params->setObject(CCString::create(viewKey), "viewKey");
    params->setObject(CCString::create(viewData), "viewData");
    params->setObject(CCFloat::create(x), "x");
    params->setObject(CCFloat::create(y), "y");
    params->setObject(CCFloat::create(w), "w");
    params->setObject(CCFloat::create(h), "h");

    callNative(params);
}

void NativeViewModule::sendMessage(char const *key, const char *messageData) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("sendMessage"), "method");
    params->setObject(CCString::create(key), "viewKey");
    params->setObject(CCString::create(messageData), "messageData");

    callNative(params);
}

void NativeViewModule::closeNative(char const *key) {
    CCDictionary *params = CCDictionary::create();

    params->setObject(CCString::create("closeNative"), "method");
    params->setObject(CCString::create(key), "viewKey");

    callNative(params);
}

CCObject *NativeViewModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

