/*
 * NodeProvider.h
 *
 *  Created on: Sep 5, 2012
 *      Author: vedi
 */

#ifndef ABSTRACT_NODEPROVIDER_H_
#define ABSTRACT_NODEPROVIDER_H_

#include "vedidev.h"

#define NODE_PROVIDER_GETTER_GLUE(CLASS, CCB) CCNode* get##CLASS##Node() { \
	return getNodeFromCcbFile(CCB); \
}

class AbstractNodeProvider: public CCObject {
protected:
    CCNode * getNodeFromCcbFile(const char *pCcbFileName);
    virtual const char *getResourcePostfix() {return "";};
};

#endif /* ABSTRACT_NODEPROVIDER_H_ */
