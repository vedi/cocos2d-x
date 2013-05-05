/*
 * Utils.h
 *
 *  Created on: Jul 14, 2012
 *      Author: vedi
 */

#ifndef VUTILS_H_
#define VUTILS_H_

#include <string>
#include "cocos2d.h"

class VUtils {
public:

    static float applyScaleForNode(cocos2d::CCNode *node);

    static const char *toPChar(int value);

    static void format(std::string &ret, int size, const char *pszFormat, ...);

    static std::string toStr(int value);

    static bool isNodeAtPoint(cocos2d::CCNode *node, cocos2d::CCPoint& touchLocation);

    static cocos2d::CCPoint convertToGlobalCoos(cocos2d::CCTouch *touch);

    static cocos2d::CCPoint convertToGlobalCoos(cocos2d::CCPoint& point);

    static cocos2d::CCLabelTTF *createLabelTTFWithCopy(cocos2d::CCLabelTTF *pSource);

    static cocos2d::CCSprite *createSpriteWithCopy(cocos2d::CCSprite *pSource);

    static cocos2d::CCMenu *createMenuWithCopy(cocos2d::CCMenu *pSource);

    static cocos2d::CCMenuItemImage *createMenuItemImageWithCopy(cocos2d::CCMenuItemImage *pSource);

    static void copySprite(cocos2d::CCSprite *pSource, cocos2d::CCSprite *pDest);

    static void copyNode(cocos2d::CCNode *pSource, cocos2d::CCNode *pDest);

    static void alignCenterTop(cocos2d::CCNode *node);

    static void alignCenterBottom(cocos2d::CCNode *node);

    static void alignCenterMiddle(cocos2d::CCNode *pNode);

    static void shiftToLeftTop(cocos2d::CCNode *targetNode);

    static void shiftToRightTop(cocos2d::CCNode *targetNode);

    static void shiftToRightBottom(cocos2d::CCNode *targetNode);

    static void shiftToTop(cocos2d::CCNode *targetNode);

    static void shiftToBottom(cocos2d::CCNode *targetNode);

    static void shiftToLeftBottom(cocos2d::CCNode *targetNode);

    static void shiftToLeftCenter(cocos2d::CCNode *targetNode);

    static void shiftToRightCenter(cocos2d::CCNode *targetNode);

    static void fillWidth(cocos2d::CCNode *targetNode);

    static void fillHeight(cocos2d::CCNode *targetNode);

    static void fill(cocos2d::CCNode *targetNode);

    static void putToCenterMiddleOf(cocos2d::CCNode *targetNode, cocos2d::CCNode *anchorNode);

    static void putToVCenterOf(cocos2d::CCNode *targetNode, cocos2d::CCNode *anchorNode);

    static void putUpperOf(cocos2d::CCNode *targetNode, cocos2d::CCNode *anchorNode);

    static void fitToRect(float* x, float* y);

    static void fitToRect(cocos2d::CCRect rect, float* x, float* y);

    static void shuffleArray(int* array, int count);

    static void shuffleArray(cocos2d::CCArray *pArr);

    static void stretchRanged(cocos2d::CCNode *pNode);

    static void split(std::string src, const char* token, std::vector<std::string>& vect);

    static void setStateForMenuItem(cocos2d::CCMenuItemImage *pMenuItemImage, bool bState);
};

#endif /* VUTILS_H_ */
