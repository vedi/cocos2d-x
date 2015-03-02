//
// Created by Fedor Shubin on 7/1/13.
//


#include "ScoreloopModule.h"
#include "NDKHelper.h"
//#include "vedidev.h"

USING_NS_CC;

#define EASY_NDK_METHOD "scoreloop_easyNDK"

void ScoreloopModule::submitScore(int Score)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("submitScore"), "method");
    params->setObject(CCString::createWithFormat("%d", Score), "scoreResult");
    callNative(params);
}

void ScoreloopModule::showLeaderboard() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("showLeaderboard"), "method");
    callNative(params);
}

CCObject *ScoreloopModule::callNative(CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}