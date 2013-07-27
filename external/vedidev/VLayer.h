/*
 * VLayer.h
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#ifndef VLAYER_H_
#define VLAYER_H_

#include "vedidev.h"
#include "AnimationManagerAssigner.h"

USING_NS_CC_EXT;

class VLayer : public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
    , public AnimationManagerAssigner
{
public:
    virtual ~VLayer();

	virtual void onBack(CCObject* pSender) = 0;

	virtual void keyBackClicked();
	virtual void onEnter();

    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {return false;}
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {return NULL;}
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, char const *pSelectorName) {return NULL;}
    virtual void onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader) {}

    virtual void cleanup();
protected:
    VLayer();

};

#endif /* VLAYER_H_ */

