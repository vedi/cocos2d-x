/*
 * SceneDispatcher.h
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#ifndef SCENEDISPATCHER_H_
#define SCENEDISPATCHER_H_

#include "MainScreen.h"
#include "vedidev/AbstractSceneDispatcher.h"

class SceneDispatcher: public AbstractSceneDispatcher {
public:
    V_SHARED_DCL(SceneDispatcher);

    SCENE_DISPATCHER_GETTER_GLUE(MainScreen);

    virtual CCScene *getDefaultTransition(CCScene *pScene);
    virtual void goToStartScene();
protected:
private:
    SceneDispatcher();
};

#endif /* SCENEDISPATCHER_H_ */
