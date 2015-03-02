//
// Created by Fedor Shubin on 7/1/13.
//

#ifndef __ScoreloopModule_H_
#define __ScoreloopModule_H_

#include "cocos2d.h"

using namespace cocos2d;

class ScoreloopModule {
public:
    static void submitScore(int Score);
    static void showLeaderboard();
private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};


#endif //__HasAppModule_H_
