/*
 * SceneDispatcher.h
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#ifndef ABSTRACT_SCENEDISPATCHER_H_
#define ABSTRACT_SCENEDISPATCHER_H_

#include "vedidev.h"

#define SCENE_DISPATCHER_GETTER_GLUE(__CLASS__) cocos2d::CCScene *get##__CLASS__() { \
        return __CLASS__::scene();\
    }\
    \
    void goTo##__CLASS__() {\
        goToScene(get##__CLASS__());\
    }\


class AbstractSceneDispatcher : public CCObject {
public:
    void goToScene(CCScene *pScene);
    virtual void goToStartScene() = 0;
    virtual CCScene *getDefaultTransition(CCScene *pScene) = 0;
};

#endif /* ABSTRACT_SCENEDISPATCHER_H_ */
