/*
 * NodeProvider.h
 *
 *  Created on: Sep 5, 2012
 *      Author: vedi
 */

#ifndef NODEPROVIDER_H_
#define NODEPROVIDER_H_


#include "vedidev/AbstractNodeProvider.h"

#define MAIN_SCREEN_CCB "ccb/MainScreen.ccbi"

#define NODE_PROVIDER_GETTER_GLUE(CLASS, CCB) CCNode* get##CLASS##Node() { \
	return getNodeFromCcbFile(CCB); \
}

class NodeProvider: public AbstractNodeProvider {
public:
    V_SHARED_DCL(NodeProvider);

    NODE_PROVIDER_GETTER_GLUE(MainScreen, MAIN_SCREEN_CCB);
private:
    NodeProvider();
};

#endif /* NODEPROVIDER_H_ */
