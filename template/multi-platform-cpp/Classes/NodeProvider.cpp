/*
 * NodeProvider.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: vedi
 */

#include "NodeProvider.h"

#include "MainScreen.h"


USING_NS_CC_EXT;

V_SHARED_IMPL(NodeProvider);

V_LOADER_DEFINITION_GLUE(MainScreen, CCLayerLoader);


NodeProvider::NodeProvider() {
	CCNodeLoaderLibrary *pCCNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    V_REGISTER_LOADER_GLUE(pCCNodeLoaderLibrary, MainScreen);
}
