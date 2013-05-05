/*
 * Utils.cpp
 *
 *  Created on: Jul 14, 2012
 *      Author: vedi
 */

#include "VUtils.h"

USING_NS_CC;

float VUtils::applyScaleForNode(cocos2d::CCNode* node) {
	cocos2d::CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float scale = std::min(winSize.width / node->getContentSize().width,
			winSize.height / node->getContentSize().height);
    node->setScale(scale);
    node->setPosition(ccp((winSize.width - node->getContentSize().width * scale) / 2,
    		(winSize.height - node->getContentSize().height * scale) / 2));

    return scale;
}

void VUtils::setStateForMenuItem(CCMenuItemImage *pMenuItemImage, bool bState) {
    CCSprite *pSprite = VUtils::createSpriteWithCopy(
            (CCSprite *) (bState ? pMenuItemImage->getSelectedImage() : pMenuItemImage->getDisabledImage()));

    pMenuItemImage->setNormalImage(pSprite);
}

const char*VUtils::toPChar(int value) {
    return toStr(value).c_str();
}

std::string VUtils::toStr(int value) {
	std::ostringstream o;
	o << value;
    return o.str();
}

bool VUtils::isNodeAtPoint(cocos2d::CCNode* node,
		cocos2d::CCPoint& touchLocation) {
    CCPoint nodePoint = node->convertToNodeSpace(touchLocation);
    CCRect rect = CCRect(0, 0, node->getContentSize().width, node->getContentSize().height);
    return rect.containsPoint(nodePoint);
}

cocos2d::CCPoint VUtils::convertToGlobalCoos(cocos2d::CCTouch* touch) {
    return touch->getLocation();
}

cocos2d::CCPoint VUtils::convertToGlobalCoos(cocos2d::CCPoint& point) {
	return CCDirector::sharedDirector()->convertToGL(point);
}

cocos2d::CCLabelTTF*VUtils::createLabelTTFWithCopy(cocos2d::CCLabelTTF* pSource) {
	
	CCLabelTTF* pRet = CCLabelTTF::create(pSource->getString(),
			pSource->getFontName(), pSource->getFontSize());

	pRet->setColor(pSource->getColor());

	copyNode(pSource, pRet);

	return pRet;
}

cocos2d::CCSprite*VUtils::createSpriteWithCopy(cocos2d::CCSprite* pSource) {

	CCSprite* pRet = CCSprite::createWithSpriteFrame(pSource->displayFrame());

	copyNode(pSource, pRet);

	return pRet;
}

void VUtils::alignCenterTop(cocos2d::CCNode* node) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    node->setPosition(node->getParent()->convertToNodeSpace(ccp(winSize.width / 2, winSize.height)));
}

void VUtils::alignCenterBottom(CCNode* node) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	node->setPosition(node->getParent()->convertToNodeSpace(ccp(winSize.width / 2, 0)));
}

void VUtils::copySprite(CCSprite *pSource, CCSprite *pDest) {
    copyNode(pSource, pDest);
    pDest->setDisplayFrame(pSource->displayFrame());
}


void VUtils::shiftToLeftTop(cocos2d::CCNode* targetNode) {
	targetNode->setPosition(targetNode->getParent()->convertToNodeSpace(
            ccp(0, CCDirector::sharedDirector()->getWinSize().height)));
}

void VUtils::shiftToLeftBottom(cocos2d::CCNode* targetNode) {
	CCPoint position = targetNode->getParent()->convertToNodeSpace(ccp(0, 0));
	targetNode->setPosition(position);
}

void VUtils::shiftToRightBottom(CCNode *targetNode) {

    CCPoint position = targetNode->getParent()->convertToNodeSpace(
            ccp(CCDirector::sharedDirector()->getWinSize().width, 0));
    targetNode->setPosition(position);
}

void VUtils::split(std::string src, char const *token, std::vector<std::string>  & vect) {
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

void VUtils::shiftToTop(cocos2d::CCNode* targetNode) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint position =
			targetNode->getParent()->convertToNodeSpace(ccp(winSize.width, winSize.height));
	targetNode->setPositionY(position.y);
}

void VUtils::shiftToBottom(cocos2d::CCNode* targetNode) {
	CCPoint position = targetNode->getParent()->convertToNodeSpace(ccp(0, 0));
	targetNode->setPositionY(position.y);
}

void VUtils::shuffleArray(int *array, int count) {
    int swapIdx;
    int tmp;
    for (int i = 1; i < count; i++) {
        swapIdx = rand() % i;
        tmp = array[i];
        array[i] = array[swapIdx];
        array[swapIdx] = tmp;
    }
}

void VUtils::shuffleArray(CCArray *pArr) {
    CCObject *pObj;
    for (unsigned int i = 1; i < pArr->count(); i++) {
        pObj = pArr->randomObject();
        pArr->removeObject(pObj, false);
        pArr->insertObject(pObj, i);
    }
}

void VUtils::fitToRect(float* x, float* y) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRect rect = CCRectMake(0, 0, size.width, size.height);
    fitToRect(rect, x, y);
}


void VUtils::fitToRect(CCRect rect, float *x, float *y) {
    if (*x < rect.getMinX()) {
        *x = rect.getMinX();
    } else if (*x > rect.getMaxX()) {
        *x = rect.getMaxX();
    }
    if (*y< rect.getMinY()) {
        *y = rect.getMinY();
    } else if (*y > rect.getMaxY()) {
        *y = rect.getMaxY();
    }
}

void VUtils::fillWidth(cocos2d::CCNode* targetNode) {
	CCPoint leftBottom =
			targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
	CCPoint rightTop =
			targetNode->getParent()->convertToWorldSpace(
					ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	targetNode->setScale(winSize.width / (rightTop.x - leftBottom.x));
}

void VUtils::shiftToRightTop(CCNode *targetNode) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint position = targetNode->getParent()->convertToNodeSpace(ccpFromSize(winSize));
    targetNode->setPosition(position);
}

void VUtils::putToVCenterOf(cocos2d::CCNode* targetNode,
		cocos2d::CCNode* anchorNode) {

	CCPoint leftBottom =
			anchorNode->convertToWorldSpaceAR(
					ccpSub(CCPointZero, ccpCompMult(
							ccp(anchorNode->getAnchorPoint().x, anchorNode->getAnchorPoint().y),
							ccpFromSize(anchorNode->getContentSize()))));
	CCPoint rightTop =
			anchorNode->convertToWorldSpaceAR(
					ccpAdd(CCPointZero, ccpCompMult(
                            ccp(1 - anchorNode->getAnchorPoint().x, 1 - anchorNode->getAnchorPoint().y),
							ccpFromSize(anchorNode->getContentSize()))));

	CCPoint globalPosition = ccp(targetNode->getPosition().x, leftBottom.y + (rightTop.y - leftBottom.y) / 2);

	targetNode->setPosition(targetNode->getParent()->convertToNodeSpace(globalPosition));
}

void VUtils::putToCenterMiddleOf(cocos2d::CCNode* targetNode,
        cocos2d::CCNode* anchorNode) {

    CCPoint leftBottom =
            anchorNode->convertToWorldSpaceAR(
                    ccpSub(CCPointZero, ccpCompMult(
                            ccp(anchorNode->getAnchorPoint().x, anchorNode->getAnchorPoint().y),
                            ccpFromSize(anchorNode->getContentSize()))));
    CCPoint rightTop =
            anchorNode->convertToWorldSpaceAR(
                    ccpAdd(CCPointZero, ccpCompMult(
                            ccp(1 - anchorNode->getAnchorPoint().x, 1 - anchorNode->getAnchorPoint().y),
                            ccpFromSize(anchorNode->getContentSize()))));

    CCPoint globalPosition = ccp(leftBottom.x + (rightTop.x - leftBottom.x) / 2, leftBottom.y + (rightTop.y - leftBottom.y) / 2);

    targetNode->setPosition(targetNode->getParent()->convertToNodeSpace(globalPosition));
}

void VUtils::copyNode(cocos2d::CCNode* pSource,
		cocos2d::CCNode* pDest) {

    pDest->ignoreAnchorPointForPosition(pSource->isIgnoreAnchorPointForPosition());
    pDest->setAnchorPoint(pSource->getAnchorPoint());
    pDest->setContentSize(pSource->getContentSize());
    pDest->setPosition(pSource->getPosition());
    pDest->setRotationX(pSource->getRotationX());
    pDest->setRotationY(pSource->getRotationY());
    pDest->setScaleX(pSource->getScaleX());
    pDest->setScaleY(pSource->getScaleY());
    pDest->setTag(pSource->getTag());
    pDest->setZOrder(pSource->getZOrder());
}

void VUtils::alignCenterMiddle(CCNode *pNode) {
    pNode->setPosition(pNode->getParent()->convertToNodeSpace(
            ccpMult(ccpFromSize(CCDirector::sharedDirector()->getWinSize()), 0.5)));
}

void VUtils::fill(cocos2d::CCNode* targetNode) {
	CCPoint leftBottom =
			targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
	CCPoint rightTop =
			targetNode->getParent()->convertToWorldSpace(
					ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float scaleX = winSize.width / (rightTop.x - leftBottom.x);
	float scaleY = winSize.height / (rightTop.y - leftBottom.y);

	targetNode->setScale(MAX(scaleX, scaleY));
}

void VUtils::format(std::string &ret, int size, const char* pszFormat, ...) {
    char buf[size];

    va_list args;
    va_start(args, pszFormat);
    vsprintf(buf, pszFormat, args);
    va_end(args);

    ret.clear();
    ret.append(buf);
}

void VUtils::fillHeight(CCNode *targetNode) {
    CCPoint leftBottom =
            targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
    CCPoint rightTop =
            targetNode->getParent()->convertToWorldSpace(
                    ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    targetNode->setScale(winSize.height / (rightTop.y - leftBottom.y));
}

void VUtils::shiftToLeftCenter(cocos2d::CCNode* targetNode) {
	CC_ASSERT(targetNode->getParent());
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint position = targetNode->getParent()->convertToNodeSpace(
			ccp(0, size.height / 2));
	targetNode->setPosition(position);
}

void VUtils::stretchRanged(CCNode *pNode) {
    CCPoint leftBottom =
            pNode->getParent()->convertToWorldSpace(pNode->getPosition());
    CCPoint rightTop =
            pNode->getParent()->convertToWorldSpace(
                    ccpAdd(pNode->getPosition(), ccpFromSize(pNode->getContentSize())));

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    if (winSize.width / winSize.height > 3.0 / 2.0) {
        winSize.width = winSize.height * 3.0 / 2.0;
    } else if (winSize.width / winSize.height < 4.0 / 3.0) {
        winSize.height = winSize.width * 4.0 / 3.0;
    }
    float scaleX = winSize.width / (rightTop.x - leftBottom.x);
    float scaleY = winSize.height / (rightTop.y - leftBottom.y);

    pNode->setScaleX(scaleX);
    pNode->setScaleY(scaleY);
}

void VUtils::shiftToRightCenter(cocos2d::CCNode* targetNode) {
	CC_ASSERT(targetNode->getParent());
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint position = targetNode->getParent()->convertToNodeSpace(
			ccp(size.width, size.height / 2));
	targetNode->setPosition(position);
}

void VUtils::putUpperOf(cocos2d::CCNode* targetNode,
		cocos2d::CCNode* anchorNode) {
	CCPoint rightTop =
			anchorNode->convertToWorldSpaceAR(
					ccpAdd(CCPointZero, ccpCompMult(
                            ccp(1 - anchorNode->getAnchorPoint().x, 1 - anchorNode->getAnchorPoint().y),
							ccpFromSize(anchorNode->getContentSize()))));

	CCPoint globalPosition = ccp(0, rightTop.y);

//	targetNode->setPositionY(targetNode->getParent()->convertToNodeSpace(globalPosition).y);
}

CCMenu *VUtils::createMenuWithCopy(CCMenu *pSource) {
    CCMenu *pRet = CCMenu::create();

    copyNode(pSource, pRet);

    return pRet;
}


CCMenuItemImage *VUtils::createMenuItemImageWithCopy(CCMenuItemImage *pSource) {
    CCMenuItemImage* pRet = CCMenuItemImage::create();

    CCSprite *pSprite;

    if (pSource->getNormalImage()) {
        pSprite = createSpriteWithCopy((CCSprite *) pSource->getNormalImage());
        pRet->setNormalImage(pSprite);
    }
    if (pSource->getSelectedImage()) {
        pSprite = createSpriteWithCopy((CCSprite *) pSource->getSelectedImage());
        pRet->setSelectedImage(pSprite);
    }
    if (pSource->getDisabledImage()) {
        pSprite = createSpriteWithCopy((CCSprite *) pSource->getDisabledImage());
        pRet->setDisabledImage(pSprite);
    }

    copyNode(pSource, pRet);

    return pRet;
}

