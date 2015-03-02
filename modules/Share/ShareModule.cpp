//
// Created by Alexandr on 29.07.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ShareModule.h"
#include "NDKHelper.h"


void ShareModule::shareText(const char *text) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("shareText"), "method");
    params->setObject(CCString::create(text), "text");
    callNative(params);
}

void ShareModule::init(const char *applicationName, const char *applicationURL) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(CCString::create(applicationName), "applicationName");
    params->setObject(CCString::create(applicationURL), "applicationURL");
    callNative(params);
}

void ShareModule::setFacebookKeys(const char *key, const char *secret) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setFacebookKeys"), "method");
    params->setObject(CCString::create(key), "key");
    params->setObject(CCString::create(secret), "secret");
    callNative(params);
}

CCObject *ShareModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

