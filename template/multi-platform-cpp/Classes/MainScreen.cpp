/*
 * MainScreen.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#include "MainScreen.h"

#include "vedidev/VUtils.h"

bool MainScreen::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode) {

    V_CCB_MEMBERVARIABLEASSIGNER_GLUE(CCNode *, mBackground);
    V_CCB_MEMBERVARIABLEASSIGNER_GLUE(CCNode *, mGameNode);

    return false;
}

void MainScreen::onNodeLoaded(CCNode* pNode, cocos2d::extension::CCNodeLoader* pNodeLoader) {

    CC_UNUSED_PARAM(pNode);
    CC_UNUSED_PARAM(pNodeLoader);

    CC_ASSERT(mBackground);
    CC_ASSERT(mGameNode);

    VUtils::applyScaleForNode(this);
    VUtils::fill(mBackground, V_FILL_BOTH, V_FILL_STRATEGY_STRETCH);
    VUtils::alignRelative(mBackground, mGameNode, V_ALIGN_CENTER_MIDDLE);
}

void MainScreen::onEnter() {
    VLayer::onEnter();

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MainScreen::onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    VLayer::onExit();
}

cocos2d::SEL_MenuHandler MainScreen::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName) {

    V_CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(MainScreen, onBack);

    return NULL;
}

void MainScreen::onBack(CCObject* pSender) {

  CC_UNUSED_PARAM(pSender);

  CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}

bool MainScreen::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
  ccTouchMoved(pTouch, pEvent);
  return true;
}

void MainScreen::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
}

void MainScreen::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
}

MainScreen::MainScreen() {
    mBackground = NULL;
    mGameNode = NULL;
}

MainScreen::~MainScreen() {

}
