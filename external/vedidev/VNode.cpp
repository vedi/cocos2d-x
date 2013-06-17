//
// Created by vedi on 2/17/13.
//


#include "VNode.h"

void VNode::cleanup() {
    this->setAnimationManager(NULL);
    this->setAnimationManagers(NULL);

    CCNode::cleanup();
}

void VNode::setUserObject(CCObject *pUserObject) {
    CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager *>(pUserObject);
    if (animationManager) {
        this->setAnimationManager(animationManager);
    }
}
