//
// Created by vedi on 2/17/13.
//


#ifndef __VNode_H_
#define __VNode_H_

#include "vedidev.h"
#include "AnimationManagerAssigner.h"

USING_NS_CC_EXT;

class VNode : public CCNodeRGBA
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCNodeLoaderListener
, public AnimationManagerAssigner
{
public:
    virtual CCBAnimationManager *getAnimationManagerForNode(CCNode *pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {return NULL;}
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, char const *pSelectorName) {return NULL;}
    virtual bool onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {return false;};
    virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader) {};

    virtual void cleanup();
};

#endif //__VNode_H_
