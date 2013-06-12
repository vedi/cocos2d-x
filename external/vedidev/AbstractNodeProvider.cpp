/*
 * NodeProvider.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: vedi
 */

#include "AbstractNodeProvider.h"
#include "AnimationManagerAssigner.h"

USING_NS_CC_EXT;

CCNode* AbstractNodeProvider::getNodeFromCcbFile(const char* pCcbFileName) {
    CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    pReader->setCCBResourcePostfix(getResourcePostfix());
	CCNode* pNode = pReader->readNodeGraphFromFile(pCcbFileName);

	pReader->release();

	return pNode;
}
