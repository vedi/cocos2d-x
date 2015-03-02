//
// Created by Alexandr on 21.06.13.
// Copyright (c) 2013 VedideV. All rights reserved.
//


#include "ParseModule.h"
#include "NDKHelper.h"


void ParseModule::setKeys(const char *applicationID, const char* clientKey) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setKeys"), "method");
    params->setObject(CCString::create(applicationID), "applicationID");
    params->setObject(CCString::create(clientKey), "clientKey");
    callNative(params);
}

void ParseModule::initParsePush(bool pushNotificationState) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("initParsePush"), "method");
    params->setObject(CCBool::create(pushNotificationState), "notificationsOn");
    callNative(params);
}

void ParseModule::sendParseObject(const char *objectName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("sendParseObject"), "method");
    params->setObject(CCString::create(objectName), "objectName");
    callNative(params);
}

CCObject *ParseModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}
