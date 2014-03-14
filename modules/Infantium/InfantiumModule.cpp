//
// Created by Fedor Shubin on 7/1/13.
//


#include "InfantiumModule.h"
#include "NDKHelper.h"
//#include "vedidev.h"

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

/*void InfantiumModule::setSuccesses(int successes) {
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
*/
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

//===== Elements =============================

void InfantiumModule::addElement(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addElement"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addPaintedElement(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addPaintedElement"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addPictureElement(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addPictureElement"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addShapeElement(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addShapeElement"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addNumberElement(const char *ID, int value)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addNumberElement"), "method");
    params->setObject(CCString::create(ID), "ID");
    params->setObject(CCString::createWithFormat("%d", value), "value");
    callNative(params);
}


void InfantiumModule::addGoal(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addGoal"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addSelectionGoal(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addSelectionGoal"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}

void InfantiumModule::addMatchingGoal(const char *ID, const char *matching_element)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addMatchingGoal"), "method");
    params->setObject(CCString::create(ID), "ID");
    params->setObject(CCString::create(matching_element), "matching_element");
    callNative(params);
}
/*
void InfantiumModule::addMatchingGoalArray(const char *ID, CCArray *list)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addMatchingGoalArray"), "method");
    params->setObject(CCString::create(ID), "ID");
    params->setObject(CCString::createWithFormat("%d", list->count()), "list_size");
    int i = 0;
    V_CCARRAY_FOREACH_BEG(list, CCString*, var)
    {
        params->setObject(var, CCString::createWithFormat("matching_element %d",i)->getCString());
        i++;
    }V_CCARRAY_FOREACH_END
    callNative(params);
}
*/
void InfantiumModule::addTappingGoal(const char *ID)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addTappingGoal"), "method");
    params->setObject(CCString::create(ID), "ID");
    callNative(params);
}
/*
void InfantiumModule::addTappingGoalArray(const char *ID, CCArray *list)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("addTappingGoalArray"), "method");
    params->setObject(CCString::create(ID), "ID");
    params->setObject(CCString::createWithFormat("%d", list->count()), "list_size");
    int i = 0;
    
    V_CCARRAY_FOREACH_BEG(list, CCString*, var)
    {
        params->setObject(var, CCString::createWithFormat("targets_element %d", i)->getCString());
        i++;
    }V_CCARRAY_FOREACH_END
    callNative(params);
}
*/

void InfantiumModule::newBasicInteraction(char const *ID, char const *object_type, char const *goal_type)
{
    CCDictionary *params = CCDictionary::create();
    params->setObject(CCString::create("newBasicInteraction"), "method");
    params->setObject(CCString::create(ID), "ID");
    params->setObject(CCString::create(object_type), "object_type");
    params->setObject(CCString::create(goal_type), "goal_type");
    callNative(params);
}
