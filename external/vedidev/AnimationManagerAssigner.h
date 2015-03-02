//
// Created by vedi on 12/27/12.
//



#ifndef __AnimationManagerAssigner_H_
#define __AnimationManagerAssigner_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AnimationManagerAssigner: public CCBAnimationManagerDelegate {
public:
    AnimationManagerAssigner();
    virtual ~AnimationManagerAssigner();

    void setAnimationManager(CCBAnimationManager *pManager);
    void setAnimationManagers(CCDictionary *pManagers);
    virtual void completedAnimationSequenceNamed(CCNode *pRootNode, const char *name) {
        completedAnimationSequenceNamed(name);
    };
    virtual void completedAnimationSequenceNamed(const char *name) {};
protected:
    CCBAnimationManager *m_pAnimationManager;
    CCDictionary *m_pAnimationManagers;

    CCBAnimationManager *getAnimationManager();
    virtual CCBAnimationManager *getAnimationManagerForNode(CCNode *pNode);
};

#endif //__AnimationManagerAssigner_H_
