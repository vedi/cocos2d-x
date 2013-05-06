/*
 * MainScreen.h
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include "vedidev/VLayer.h"
#include "NodeProvider.h"

class MainScreen: public VLayer {
public:
	virtual ~MainScreen();

	V_SCENE_GLUE(MainScreen);
	CREATE_FUNC(MainScreen);

	void onBack(CCObject* pSender);

    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual void onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    virtual void onEnter();
    virtual void onExit();
private:
	MainScreen();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    CCNode *mBackground;
    CCNode *mGameNode;
};

#endif /* MAINSCREEN_H_ */
