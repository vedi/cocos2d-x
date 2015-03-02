//
// Created by vedi on 12/30/12.
//

#ifndef __NativeViewNode_H_
#define __NativeViewNode_H_

#define SEL_GROUP "NativeViewNode"

#include "base_nodes/CCNode.h"

USING_NS_CC;

class NativeViewNodeDelegate;

class NativeViewNode : public CCNode {
public:
    static NativeViewNode *create();
    static NativeViewNode *create(const char *pKey);

    virtual ~NativeViewNode();

    virtual void cleanup();

    bool init();
    bool init(const char *pKey);
    void setKey(const char *pKey);
    void setViewParams(CCDictionary *viewParams);
    void setData(const char *pData);
    void sendMessage(const char *pData);
    void show();
    void close();
    bool isShown() {return mShown;}
    void setSelector(CCNode *pTarget, SEL_CallFuncO pSelector);
private:
    NativeViewNode():
        m_pTarget(NULL)
        , m_pSelector(NULL)
        , mViewParams(NULL)
        , m_sData("")
        , mShown(false)
    {}
    CCDictionary *mViewParams;
    std::string m_sData;
    bool mShown;
    std::string m_sKey;
    CCNode *m_pTarget;
    SEL_CallFuncO m_pSelector;
};

#endif //__NativeViewNode_H_
