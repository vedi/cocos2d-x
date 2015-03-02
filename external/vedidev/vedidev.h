//
// Created by vedi on 12/13/12.
//

#ifndef __vedidev_H_
#define __vedidev_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

using namespace std;

#define V_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) { \
    T *pRet = T::create(); \
    return pRet; \
}

#define V_WO_RETAIN_CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, (MEMBERVARIABLENAME))) { \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        return true; \
    }NULL

#define V_CCB_MEMBERVARIABLEASSIGNER_GLUE(MEMBERVARIABLETYPE, MEMBERVARIABLE) V_WO_RETAIN_CCB_MEMBERVARIABLEASSIGNER_GLUE(this, #MEMBERVARIABLE, MEMBERVARIABLETYPE, MEMBERVARIABLE);

#define V_CCB_ARR_MEMBERVARIABLEASSIGNER_GLUE(MEMBERVARIABLETYPE, MEMBER_ARR, IDX, FROM_INC, TO_EXC) \
    if (pTarget == this && 0 == strcmp(pMemberVariableName, (#MEMBER_ARR))) { \
        MEMBERVARIABLETYPE var = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(var); \
        CC_ASSERT((IDX) >= (FROM_INC) && (IDX) < (TO_EXC)); \
        MEMBER_ARR[(IDX)] = var; \
        return true; \
    }NULL


#define V_CCB_CCARR_MEMBERVARIABLEASSIGNER_GLUE(MEMBER_ARR) \
    if (pTarget == this && 0 == strcmp(pMemberVariableName, (#MEMBER_ARR))) { \
        MEMBER_ARR->addObject(pNode); \
        return true; \
    }NULL

#define V_CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(CLASSNAME, METHOD) CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, #METHOD, CLASSNAME::METHOD);

#define V_CCB_SELECTORRESOLVER_CALLFUNC_GLUE(CLASSNAME, METHOD) CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, #METHOD, CLASSNAME::METHOD);

#define V_SCENE_GLUE(CLASS) static cocos2d::CCScene* scene() { \
    CCScene *scene = CCScene::create(); \
    CC_ASSERT(scene); \
    CLASS * pNode = dynamic_cast<CLASS *>( \
    		NodeProvider::sharedNodeProvider()->get##CLASS##Node()); \
    CC_ASSERT(pNode); \
    scene->addChild(pNode); \
    return scene; \
}

#define V_LOADER_DEFINITION_GLUE(CLASS, PARENT_LOADER) class CLASS##Loader : public PARENT_LOADER { \
public: \
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CLASS##Loader, loader); \
protected: \
    V_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CLASS); \
}

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

#define V_CCARRAY_FOREACH_BEG(__array__, __class__, __var__) \
{ \
    CCObject *pObj;\
    __class__ __var__;\
    CCARRAY_FOREACH(__array__, pObj) {\
        __var__ = dynamic_cast<__class__>(pObj);\
        CC_ASSERT(__var__);\

#define V_CCARRAY_FOREACH_REVERSE_BEG(__array__, __class__, __var__) \
{ \
    CCObject *pObj;\
    __class__ __var__;\
    CCARRAY_FOREACH_REVERSE(__array__, pObj) {\
        __var__ = dynamic_cast<__class__>(pObj);\
        CC_ASSERT(__var__);\


#define V_CCARRAY_FOREACH_END\
    }\
}\

#define V_SHARED(CLASS) CLASS::shared##CLASS()

#define V_CCSHARED(CLASS) CC##CLASS::shared##CLASS()


#define V_SHARED_DCL(CLASS) static CLASS * shared##CLASS();


#define V_SHARED_IMPL(CLASS) static CLASS* sShared##CLASS = NULL; \
CLASS *CLASS::shared##CLASS() { \
    if (sShared##CLASS== NULL) { \
        sShared##CLASS = new CLASS(); \
    } \
    return sShared##CLASS; \
}

// for the subclass of CCLayer, each has to implement the static "create" method
#define LAYER_CREATE_FUNC(layer) \
static layer* create() \
{ \
layer *pRet = new layer(); \
if (pRet && pRet->init()) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#endif //__common_H_
