#include "AppDelegate.h"

#include "vedidev/vedidev.h"
#include "consts.h"
#include "SceneDispatcher.h"
#include "AudioManager.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0/kFPS);

    // run
    SceneDispatcher *sceneDispatcher = SceneDispatcher::sharedSceneDispatcher();
    pDirector->getScheduler()->scheduleSelector(
            schedule_selector(SceneDispatcher::goToStartScene),
            sceneDispatcher, 0, 0, 0, false);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
}

void AppDelegate::applicationDidBecomeActive() {
    AudioManager::sharedAudioManager()->resumeAll();
    cocos2d::CCDirector::sharedDirector()->resume();
}

void AppDelegate::applicationWillResignActive() {
    cocos2d::CCDirector::sharedDirector()->pause();
    AudioManager::sharedAudioManager()->pauseAll();
}
