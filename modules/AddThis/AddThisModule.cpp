//
// Created by Alexandr on 29.07.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "AddThisModule.h"
#include "NDKHelper.h"


void AddThisModule::init(CCDictionary *initParams) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(initParams, "initParams");
    callNative(params);
}

void AddThisModule::setFacebookKeys(const char *key, const char *serviceName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setFacebookKeys"), "method");
    params->setObject(CCString::create(key), "key");
    params->setObject(CCString::create(serviceName), "serviceName");
    callNative(params);
}

void AddThisModule::shareText(const char *text, const char*serviceName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("shareText"), "method");
    if (text) {
        params->setObject(CCString::create(text), "text");
    }
    if (serviceName) {
        params->setObject(CCString::create(serviceName), "serviceName");
    }
    callNative(params);
}


void AddThisModule::shareUrl(const char *urlStr, char const *title, const char*serviceName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("shareUrl"), "method");
    if (urlStr) {
        params->setObject(CCString::create(urlStr), "urlStr");
    }
    if (title) {
        params->setObject(CCString::create(title), "title");
    }
    if (serviceName) {
        params->setObject(CCString::create(serviceName), "serviceName");
    }
    callNative(params);
}

void AddThisModule::shareImage(const char *imagePath, char const *title, const char*serviceName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("shareImage"), "method");
    if (imagePath) {
        params->setObject(CCString::create(imagePath), "imagePath");
    }
    if (imagePath) {
        params->setObject(CCString::create(title), "title");
    }
    if (serviceName) {
        params->setObject(CCString::create(serviceName), "serviceName");
    }
    callNative(params);
}

void AddThisModule::share(char const *text, char const *urlStr, char const *imagePath, char const *title, const char*serviceName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("share"), "method");
    if (text) {
        params->setObject(CCString::create(text), "text");
    }
    if (urlStr) {
        params->setObject(CCString::create(urlStr), "urlStr");
    }
    if (imagePath) {
        params->setObject(CCString::create(imagePath), "imagePath");
    }
    if (title) {
        params->setObject(CCString::create(title), "title");
    }
    if (serviceName) {
        params->setObject(CCString::create(serviceName), "serviceName");
    }
    callNative(params);
}

CCObject *AddThisModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

