/*
 * SceneDispatcher.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#include "AbstractSceneDispatcher.h"

void AbstractSceneDispatcher::goToScene(CCScene *pScene) {
    if (!CCDirector::sharedDirector()->getRunningScene()) {
        CCDirector::sharedDirector()->runWithScene(pScene);
    } else {
        CCScene *defaultTransition = getDefaultTransition(pScene);
        CCDirector::sharedDirector()->replaceScene(defaultTransition);
    }
}