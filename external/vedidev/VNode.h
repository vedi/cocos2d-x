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
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {return NULL;}
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, char const *pSelectorName) {return NULL;}

    virtual void cleanup();
};

#endif //__VNode_H_
