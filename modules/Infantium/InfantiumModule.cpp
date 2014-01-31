//
// Created by Fedor Shubin on 7/1/13.
//


#include "InfantiumModule.h"
#include "NDKHelper.h"

USING_NS_CC;

#define EASY_NDK_METHOD "infantium_easyNDK"

bool sActiveGamePlay = false;
bool sHasRawData = false;

void InfantiumModule::init(char const *apiUser, char const *apiKey, char const *contentAppUuid) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("init"), "method");
    params->setObject(CCString::create(apiUser), "apiUser");
    params->setObject(CCString::create(apiKey), "apiKey");
    params->setObject(CCString::create(contentAppUuid), "contentAppUuid");
    callNative(params);
}

void InfantiumModule::createGameplay(char const *subContentUuid) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("createGameplay"), "method");
    params->setObject(CCString::create(subContentUuid), "subContentUuid");
    callNative(params);

    sActiveGamePlay = true;
    sHasRawData = false;
}

void InfantiumModule::startPlaying() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("startPlaying"), "method");
    callNative(params);
}

void InfantiumModule::setSuccesses(int successes) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setSuccesses"), "method");
    params->setObject(CCInteger::create(successes), "successes");
    callNative(params);

    sHasRawData = true;
}

void InfantiumModule::setFailures(int failures) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setFailures"), "method");
    params->setObject(CCInteger::create(failures), "failures");
    callNative(params);

    sHasRawData = true;
}

void InfantiumModule::sendGameRawData() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("sendGameRawData"), "method");
    callNative(params);
}

void InfantiumModule::closeGameplay() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("closeGameplay"), "method");
    callNative(params);
    sActiveGamePlay = false;
}

void InfantiumModule::setSubContentUUID(char const *subContentUuid) {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("setSubContentUUID"), "method");
    params->setObject(CCString::create(subContentUuid), "subContentUuid");
    callNative(params);
}

void InfantiumModule::returnToInfantiumApp() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("returnToInfantiumApp"), "method");
    callNative(params);
}

bool InfantiumModule::isActiveGamePlay() {
    return sActiveGamePlay;
}

bool InfantiumModule::hasRawData() {
    return sHasRawData;
}

CCObject *InfantiumModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

