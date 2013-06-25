//
// Created by Alexandr on 21.06.13.
// Copyright (c) 2013 VedideV. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Parse.h"
#include "NDKHelper.h"


void Parse::setKeys(const char *applicationID, const char* clientKey) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setKeys"), "method");
    params->setObject(CCString::create(applicationID), "applicationID");
    params->setObject(CCString::create(clientKey), "clientKey");
    callNative(params);
}

void Parse::initParsePush(bool pushNotificationState) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("initParsePush"), "method");
    params->setObject(CCBool::create(pushNotificationState), "notificationsOn");
    callNative(params);
}

void Parse::sendParseObject(const char *objectName) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("sendParseObject"), "method");
    params->setObject(CCString::create(objectName), "objectName");
    callNative(params);
}

CCObject *Parse::callNative(CCDictionary *pDictionary) {
    return sendMessageWithParams(EASY_NDK_METHOD, pDictionary, false);
}
