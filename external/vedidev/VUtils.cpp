/*
 * Utils.cpp
 *
 *  Created on: Jul 14, 2012
 *      Author: vedi
 */

#include "VUtils.h"

void VUtils::align(CCNode *targetNode, CCPoint anchor) {
    CCRect rect;
    rect.origin = CCPointZero;
    rect.size = CCDirector::sharedDirector()->getWinSize();
    VUtils::align(targetNode, rect, anchor);
}

void VUtils::align(CCNode *targetNode, CCRect rect, CCPoint anchor) {
    CC_ASSERT(targetNode->getParent());
    CCPoint newSize = ccpAdd(ccpCompMult(rect.size, anchor), rect.origin);
    CCPoint position = targetNode->getParent()->convertToNodeSpace(newSize);
    if (anchor.x < 0) {
        position.x = targetNode->getPositionX();
    }
    if (anchor.y < 0) {
        position.y = targetNode->getPositionY();
    }
    targetNode->setPosition(position);
}

void VUtils::alignRelative(CCNode *targetNode, CCNode *anchorNode, CCPoint anchor) {
    CC_ASSERT(targetNode->getParent());
    CCPoint newSize = ccpCompMult(ccpFromSize(anchorNode->getContentSize()), anchor);
    CCPoint position = targetNode->getParent()->convertToNodeSpace(anchorNode->convertToWorldSpace(newSize));

    if (anchor.x < 0) {
        position.x = targetNode->getPositionX();
    }
    if (anchor.y < 0) {
        position.y = targetNode->getPositionY();
    }
    targetNode->setPosition(position);
}

void VUtils::fill(CCNode *targetNode, CCPoint fill, int fillStrategy) {
    CCRect rect;
    rect.origin = CCPointZero;
    rect.size = CCDirector::sharedDirector()->getWinSize();
    VUtils::fill(targetNode, rect, fill, fillStrategy);
}

void VUtils::fill(CCNode *targetNode, CCRect rect, CCPoint fill, int fillStrategy) {
    rect.size = ccpCompMult(rect.size, fill);
    CCRect nodeRect = CCRectApplyAffineTransform(rect,
                                             targetNode->worldToNodeTransform());

    CCPoint newSize = ccp(nodeRect.size.width, nodeRect.size.height);
    CCPoint scale = ccp(targetNode->getScaleX(), targetNode->getScaleY());
    if (fill.x >= 0) {
        scale.x *= newSize.x / targetNode->getContentSize().width;
    }
    if (fill.y >= 0) {
        scale.y *= newSize.y/ targetNode->getContentSize().height;
    }
    
    if (fillStrategy == V_FILL_STRATEGY_CROP) {
        targetNode->setScale(MAX(scale.x, scale.y));
    } else if (fillStrategy == V_FILL_STRATEGY_FIT) {
        targetNode->setScale(MIN(scale.x, scale.y));
    } else if (fillStrategy == V_FILL_STRATEGY_STRETCH) {
        targetNode->setScaleX(scale.x);
        targetNode->setScaleY(scale.y);
    } else {
        CC_ASSERT(false);
    }
}

void VUtils::applyScaleForNode(CCNode *targetNode, CCRect rect) {
    VUtils::fill(targetNode, V_FILL_BOTH, V_FILL_STRATEGY_FIT);
    float scaleX = rect.size.width / targetNode->getContentSize().width;
    float scaleY = rect.size.height / targetNode->getContentSize().height;
    float scale = MIN(scaleX, scaleY);
    targetNode->setScale(scale);

    targetNode->setPosition(ccp(
    (rect.size.width - targetNode->getScaledContentSize().width) / 2,
    (rect.size.height - targetNode->getScaledContentSize().height) / 2));
//    targetNode->setPosition(ccp(
//            rect.origin.x + (rect.size.width - targetNode->getScaledContentSize().width) / 2,
//            rect.origin.y + (rect.size.height - targetNode->getScaledContentSize().height * scale) / 2)
//    );
}

void VUtils::applyScaleForNode(CCNode *targetNode) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    applyScaleForNode(targetNode, CCRectMake(0, 0, winSize.width, winSize.height));
}

void VUtils::fitToRect(CCRect rect, float &x, float &y) {
    if (x < rect.getMinX()) {
        x = rect.getMinX();
    } else if (x > rect.getMaxX()) {
        x = rect.getMaxX();
    }
    if (y< rect.getMinY()) {
        y = rect.getMinY();
    } else if (y > rect.getMaxY()) {
        y = rect.getMaxY();
    }
}

void VUtils::fitToRect(float &x, float &y) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRect rect = CCRectMake(0, 0, size.width, size.height);
    fitToRect(rect, x, y);
}

bool VUtils::isNodeAtPoint(cocos2d::CCNode* node, cocos2d::CCPoint& touchLocation) {
    CCPoint nodePoint = node->convertToNodeSpace(touchLocation);
    CCRect rect = CCRectMake(0, 0, node->getContentSize().width, node->getContentSize().height);
    return rect.containsPoint(nodePoint);
}

cocos2d::CCSprite*VUtils::createSpriteWithCopy(cocos2d::CCSprite* pSource) {

    CCSprite* pRet = CCSprite::createWithSpriteFrame(pSource->displayFrame());

    copyNode(pSource, pRet);

    return pRet;
}

cocos2d::CCLabelTTF*VUtils::createLabelTTFWithCopy(cocos2d::CCLabelTTF* pSource) {
	
	CCLabelTTF* pRet = CCLabelTTF::create(pSource->getString(),
			pSource->getFontName(), pSource->getFontSize(), pSource->getDimensions(),
            pSource->getHorizontalAlignment(), pSource->getVerticalAlignment());

	pRet->setColor(pSource->getColor());

	copyNode(pSource, pRet);

	return pRet;
}


CCLabelBMFont *VUtils::createLabelBMFontWithCopy(CCLabelBMFont *source) {
    CCLabelBMFont *ret = CCLabelBMFont::create(source->getString(), source->getFntFile(),
            source->getContentSize().width);

    copyNode(source, ret);

    return ret;
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
    pDest->setSkewX(pSource->getSkewX());
    pDest->setSkewY(pSource->getSkewY());
    pDest->setTag(pSource->getTag());
    pDest->setVisible(pSource->isVisible());
    pDest->setZOrder(pSource->getZOrder());
}

void VUtils::copySprite(CCSprite *pSource, CCSprite *pDest) {
    copyNode(pSource, pDest);
    pDest->setDisplayFrame(pSource->displayFrame());
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

void VUtils::setStateForMenuItem(CCMenuItemImage *pMenuItemImage, bool bState) {
    CCSprite *pSprite = VUtils::createSpriteWithCopy(
            (CCSprite *) (bState ? pMenuItemImage->getSelectedImage() : pMenuItemImage->getDisabledImage()));

    pMenuItemImage->setNormalImage(pSprite);
}

bool VUtils::adjustFontSize(CCLabelTTF *target, float initialSize, CCSize constraint) {
    float size = initialSize;
    do {
        target->setFontSize(size);
        target->updateTexture();
        if (target->getTextureRect().size.width <= constraint.width &&
                target->getTextureRect().size.height <= constraint.height) {
            return true;
        }
        size -= 1.0;
    } while(size > 0.0);
    target->setFontSize(initialSize);
    return false;
}

bool VUtils::isPixelTransparentAtLocation(CCSprite *sprite, CCPoint loc)
{
    //Convert the location to the node space
    CCPoint location = sprite->convertToNodeSpace(loc);
    
    //This is the pixel we will read and test
    ccColor4B pixel;
    
    //Prepare a render texture to draw the receiver on, so you are able to read the required pixel and test it
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* renderTexture = CCRenderTexture::create(screenSize.width, screenSize.height, kCCTexture2DPixelFormat_RGBA8888);
    
    renderTexture->begin();
    
    //Draw the layer
    bool visible = sprite->isVisible();
    sprite->setVisible(true);
    CCPoint oldPos = sprite->getPosition();
    CCPoint oldAnchor = sprite->getAnchorPoint();
    sprite->setAnchorPoint(ccp(0, 0));
    sprite->setPosition(ccp(-location.x, -location.y));
    sprite->visit();
    sprite->setAnchorPoint(oldAnchor);
    sprite->setPosition(oldPos);
    
    //Read the pixel
    glReadPixels(0,0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);
    
    //Cleanup
    renderTexture->end();
    renderTexture->release();
    
    sprite->setVisible(visible);
    //Test if the pixel's alpha byte is transparent
    return (pixel.a != 0);
}


