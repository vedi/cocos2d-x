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

USING_NS_CC;

#define V_ALIGN_LEFT_TOP ccp(0, 1)
#define V_ALIGN_LEFT_MIDDLE ccp(0, 0.5)
#define V_ALIGN_LEFT_BOTTOM ccp(0, 0)

#define V_ALIGN_RIGHT_TOP ccp(1, 1)
#define V_ALIGN_RIGHT_MIDDLE ccp(1, 0.5)
#define V_ALIGN_RIGHT_BOTTOM ccp(1, 0)

#define V_ALIGN_CENTER_TOP ccp(0.5, 1)
#define V_ALIGN_CENTER_MIDDLE ccp(0.5, 0.5)
#define V_ALIGN_CENTER_BOTTOM ccp(0.5, 0)

#define V_ALIGN_LEFT ccp(0, -1)
#define V_ALIGN_CENTER ccp(0.5, -1)
#define V_ALIGN_RIGHT ccp(1, -1)
#define V_ALIGN_TOP ccp(-1, 1)
#define V_ALIGN_MIDDLE ccp(-1, 0.5)
#define V_ALIGN_BOTTOM ccp(-1, 0)

#define V_FILL_HORIZONTALLY ccp(1, -1)
#define V_FILL_VERTICALLY ccp(-1, 1)
#define V_FILL_BOTH ccp(1, 1)

enum {
    V_FILL_STRATEGY_CROP,
    V_FILL_STRATEGY_FIT,
    V_FILL_STRATEGY_STRETCH
};

class VUtils {
public:

    static void align(CCNode *targetNode, CCPoint anchor);

    static void align(CCNode *targetNode, CCRect rect, CCPoint anchor);

    static void alignRelative(CCNode *targetNode, CCNode *anchorNode, CCPoint anchor);

    static void fill(CCNode *targetNode, CCPoint fill, int fillStrategy);

    static void fill(CCNode *targetNode, CCRect rect, CCPoint fill, int fillStrategy);

    static void applyScaleForNode(CCNode *targetNode, CCRect rect);
    static void applyScaleForNode(CCNode *targetNode);


    static void fitToRect(CCRect rect, float &x, float &y);

    static void fitToRect(float &x, float &y);


    static bool isNodeAtPoint(CCNode *node, CCPoint& touchLocation);


    static CCSprite *createSpriteWithCopy(CCSprite *pSource);

    static CCLabelTTF *createLabelTTFWithCopy(CCLabelTTF *pSource);

    static CCLabelBMFont *createLabelBMFontWithCopy(CCLabelBMFont *source);

    static CCMenu *createMenuWithCopy(CCMenu *pSource);

    static CCMenuItemImage *createMenuItemImageWithCopy(CCMenuItemImage *pSource);

    static void copyNode(CCNode *pSource, CCNode *pDest);

    static void copySprite(CCSprite *pSource, CCSprite *pDest);


    static void shuffleArray(int* array, int count);

    static void shuffleArray(CCArray *pArr);

    static void split(std::string src, const char* token, std::vector<std::string>& vect);


    static void setStateForMenuItem(CCMenuItemImage *pMenuItemImage, bool bState);

    static bool adjustFontSize(CCLabelTTF *target, float initialSize, CCSize constraint);
    
    static bool isPixelTransparentAtLocation(CCSprite *sprite, CCPoint loc);

};

#endif /* VUTILS_H_ */
