//
// Created by vedi on 12/30/12.
//

#include "NativeViewNode.h"

#include "support/CCPointExtension.h"
#include "cocos-ext.h"
#include "EasyNDK/NDKHelper.h"
#include "NativeViewModule.h"

NativeViewNode *NativeViewNode::create(char const *pKey) {
    NativeViewNode *pRet = new NativeViewNode();
    if (pRet->init(pKey)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete(pRet);
        return NULL;
    }
}

NativeViewNode::~NativeViewNode() {
}

void NativeViewNode::setKey(char const *pKey) {
   // CC_ASSERT(m_sKey.empty());
    init(pKey);
}

void NativeViewNode::setViewParams(CCDictionary *viewParams) {
    CC_SAFE_RELEASE(this->mViewParams);
    this->mViewParams = viewParams;
    CC_SAFE_RETAIN(this->mViewParams);
}

void NativeViewNode::cleanup() {
    if (mShown) {
        close();
    }
    CCNode::cleanup();
}

void NativeViewNode::show() {
    CC_ASSERT(m_pParent != NULL);

    NativeViewModule::addListener(m_sKey.c_str(), m_pTarget, m_pSelector);

    CCPoint globalPos = m_pParent->convertToWorldSpace(getPosition());
    CCPoint sizePoint = ccpSub(convertToWorldSpace(ccpFromSize(getContentSize())), convertToWorldSpace(CCPointZero));

    NativeViewModule::createAndShowNative(m_sKey.c_str(), mViewParams, m_sData.c_str(),
            globalPos.x, globalPos.y, sizePoint.x, sizePoint.y);

    mShown = true;
}

bool NativeViewNode::init(char const *pKey) {
    m_sKey = std::string(pKey);
    return true;
}

NativeViewNode *NativeViewNode::create() {
    NativeViewNode *pRet = new NativeViewNode();
    if (pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete(pRet);
        return NULL;
    }
}

void NativeViewNode::setData(char const *pData) {
    CC_ASSERT(!mShown);
    m_sData = std::string(pData);
}

void NativeViewNode::sendMessage(char const *pData) {
    CC_ASSERT(mShown);

    NativeViewModule::sendMessage(m_sKey.c_str(), pData);
}

void NativeViewNode::close() {
    NativeViewModule::removeListener(m_sKey.c_str());
    mShown = false;

    NativeViewModule::closeNative(m_sKey.c_str());
}

void NativeViewNode::setSelector(CCNode *pTarget, SEL_CallFuncO pSelector) {
    m_pTarget = pTarget;
    m_pSelector = pSelector;
}

bool NativeViewNode::init() {
    m_sKey = "";

    return true;
}