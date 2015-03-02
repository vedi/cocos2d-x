//
// Created by vedi on 2/17/13.
//


#include "VNode.h"

void VNode::cleanup() {
    this->setAnimationManager(NULL);
    this->setAnimationManagers(NULL);

    CCNode::cleanup();
}

CCBAnimationManager *VNode::getAnimationManagerForNode(CCNode *pNode) {
    return AnimationManagerAssigner::getAnimationManagerForNode(pNode);
}
