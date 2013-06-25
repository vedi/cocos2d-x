/*
 * NodeProvider.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: vedi
 */

#include "AbstractNodeProvider.h"
#include "AnimationManagerAssigner.h"
#include "VNode.h"
#include "VLayer.h"

USING_NS_CC_EXT;

CCNode* AbstractNodeProvider::getNodeFromCcbFile(const char* pCcbFileName) {
    CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    pReader->setCCBResourcePostfix(getResourcePostfix());
	CCNode* pNode = pReader->readNodeGraphFromFile(pCcbFileName);

    AnimationManagerAssigner *pAnimationManagerAssigner = dynamic_cast<AnimationManagerAssigner *>(pNode);
    if (pAnimationManagerAssigner != NULL) {
        pAnimationManagerAssigner->setAnimationManagers(pReader->getAnimationManagers());
    }

	pReader->release();

	return pNode;
}

CCNode *VNodeLoader::loadCCNode(CCNode *node, CCBReader *pCCBReader) {
    VNode *vNode = (VNode *) CCNodeLoader::loadCCNode(node, pCCBReader);
    vNode->setAnimationManager(pCCBReader->getAnimationManager());
    return vNode;
}

CCNode *VLayerLoader::loadCCNode(CCNode *node, CCBReader *pCCBReader) {
    VLayer *vLayer = (VLayer *) CCLayerLoader::loadCCNode(node, pCCBReader);
    vLayer->setAnimationManager(pCCBReader->getAnimationManager());
    return vLayer;
}
