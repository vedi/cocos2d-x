//
// Created by Fedor Shubin on 7/1/13.
//

#ifndef __HasAppModule_H_
#define __HasAppModule_H_

#include "cocos2d.h"

using namespace cocos2d;

class InfantiumModule {
public:
    static void init(char const *apiUser, char const *apiKey, char const *contentAppUuid);
    static void createGameplay(char const *subContentUuid);
    static void startPlaying();
    //static void setSuccesses(int successes);
    //static void setFailures(int failures);
    static void sendGameRawData();
    static void closeGameplay();
    static void setSubContentUUID(char const *subContentUuid);
    static bool isActiveGamePlay();
    static bool hasRawData();

    static void returnToInfantiumApp();
//======== new =======================
    static void addElement(char const *ID);
    static void addNumberElement(char const *ID, int value);
    static void addPaintedElement(char const *ID);
    static void addPictureElement(char const *ID);
    static void addShapeElement(char const *ID);
    
    static void addGoal(char const *ID);
    static void addSelectionGoal(char const *ID);
    static void addMatchingGoal(char const *ID, char const * matching_element);
    //static void addMatchingGoalArray(char const *ID, CCArray *list);
    static void addTappingGoal(char const *ID);
    //static void addTappingGoalArray(char const *ID, CCArray *list);
    
    static void newBasicInteraction(char const *ID, char const *object_type, char const *goal_type);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};


#endif //__HasAppModule_H_
