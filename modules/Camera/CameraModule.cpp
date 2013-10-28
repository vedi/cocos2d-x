//
// Created by Alexandr on 06.10.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "CameraModule.h"
#include "NDKHelper.h"

#define EASY_NDK_METHOD "camera_easyNDK"


cocos2d::CCObject *CameraModule::callNative(cocos2d::CCDictionary *pDictionary) {
    return NDKHelper::sendMessageWithParams(EASY_NDK_METHOD, pDictionary);
}

void CameraModule::getPhoto() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("getPhoto"), "method");
    params->setObject(CCString::create("imagesPath"), CCFileUtils::sharedFileUtils()->getWritablePath() + "pictures");
    callNative(params);
}

void CameraModule::getPhotoFromGallery() {
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("getPhotoFromGallery"), "method");
    params->setObject(CCString::create("imagesPath"), CCFileUtils::sharedFileUtils()->getWritablePath() + "pictures");
    callNative(params);
}