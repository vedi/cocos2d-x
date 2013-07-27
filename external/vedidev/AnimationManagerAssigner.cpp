//
// Created by vedi on 12/27/12.
//


#include "AnimationManagerAssigner.h"

void AnimationManagerAssigner::setAnimationManagers(CCDictionary *pManagers) {
    if (m_pAnimationManagers != NULL) {
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(m_pAnimationManagers, pElement) {
            CCBAnimationManager * pAnimationManage = (CCBAnimationManager *)pElement->getObject();
            pAnimationManage->setDelegate(NULL);
        }
        m_pAnimationManagers->release();
    }

    m_pAnimationManagers = pManagers;

    if (m_pAnimationManagers != NULL) {
        m_pAnimationManagers->retain();
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(m_pAnimationManagers, pElement) {
            CCBAnimationManager * pAnimationManage = (CCBAnimationManager *)pElement->getObject();
            pAnimationManage->setDelegate(this);
        }
    }
}

void AnimationManagerAssigner::setAnimationManager(CCBAnimationManager *pManager) {
    if (m_pAnimationManager != NULL) {
        m_pAnimationManager->setDelegate(NULL);
        m_pAnimationManager->setRootNode(NULL);
        m_pAnimationManager->release();
    }
    m_pAnimationManager = pManager;
    if (m_pAnimationManager != NULL) {
        m_pAnimationManager->retain();
        m_pAnimationManager->setDelegate(this);
    }
}

CCBAnimationManager *AnimationManagerAssigner::getAnimationManager() {
    return m_pAnimationManager;
}

CCBAnimationManager *AnimationManagerAssigner::getAnimationManagerForNode(CCNode *pNode) {
    CC_ASSERT(pNode);
    return dynamic_cast<CCBAnimationManager *>(m_pAnimationManagers->objectForKey((int) pNode));;
}

AnimationManagerAssigner::AnimationManagerAssigner() {
    m_pAnimationManager = NULL;
    m_pAnimationManagers = NULL;
}

AnimationManagerAssigner::~AnimationManagerAssigner() {
    CC_SAFE_RELEASE(m_pAnimationManager);
    CC_SAFE_RELEASE(m_pAnimationManagers);
}