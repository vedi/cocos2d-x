/*
 * SceneDispatcher.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#include "SceneDispatcher.h"

V_SHARED_IMPL(SceneDispatcher);

SceneDispatcher::SceneDispatcher() {
}

CCScene *SceneDispatcher::getDefaultTransition(CCScene *pScene) {
    return CCTransitionFade::create(1, pScene);
}

void SceneDispatcher::goToStartScene() {
    goToMainScreen();
};




