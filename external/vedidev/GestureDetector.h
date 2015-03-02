//
// Created by vedi on 1/13/13.
//

#ifndef __GestureDetector_H_
#define __GestureDetector_H_

#include "cocos2d.h"

#define VELOCITY_TRACKER_SAMPLE_SIZE 10

USING_NS_CC;

class GestureListener;
class VelocityTracker;

class GestureDetector: public CCObject, public CCTouchDelegate {
    CC_SYNTHESIZE_READONLY(CCTouch *, mCurrentTouch, CurrentTouch);
    CC_SYNTHESIZE(bool, mIgnoreProceeded, IgnoreProceeded);
public:
    static GestureDetector *create(GestureListener *listener);
    static GestureDetector *create(int halfTapSquareSize, float tapCountInterval,
            float longPressDuration, float maxFlingDelay,
            GestureListener *listener);

    bool isPinching() {return pinching;}
    bool isPanning() {return panning;}

    virtual ~GestureDetector();

    virtual void addTrackingNode(CCNode *pNode);
    virtual void removeTrackingNode(CCNode *pNode);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {CC_ASSERT(false); return false;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {CC_ASSERT(false);};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {CC_ASSERT(false);};
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {CC_ASSERT(false);};
private:
    CCArray *m_pTrackingNodes;

    int tapSquareSize;
    time_t tapCountInterval;
    time_t longPressDuration;
    time_t maxFlingDelay;
    bool inTapSquare;
    int tapCount;
    cc_timeval lastTapTime;
    bool longPressFired;
    bool pinching;
    bool panning;

    bool tapedFingers[CC_MAX_TOUCHES];

    VelocityTracker *tracker;
    float tapSquareCenterX;
    float tapSquareCenterY;
    cc_timeval gestureStartTime;
    CCPoint firstPointer;
    CCPoint secondPointer;

    float initialDistance;

    GestureListener *listener;

    GestureDetector();

    bool touchDown(CCPoint &touchPoint, int pointer);
    bool touchDragged(CCPoint &touchPoint, int pointer);
    bool touchUp(CCPoint &touchPoint, int pointer);
};

class GestureListener {
public:
    virtual bool touchDown(CCPoint &touchPoint, int pointer) {return false;};
    virtual bool touchDragged(CCPoint &touchPoint, int pointer) {return false;};
    virtual bool touchUp (CCPoint &touchPoint, int pointer) {return false;};
    virtual bool tap(CCPoint &touchPoint, int count) {return false;};
    virtual bool longPress(CCPoint &touchPoint) {return false;};
    virtual bool fling(float velocityX, float velocityY) {return false;};
    virtual bool pan(CCPoint &touchPoint, float deltaX, float deltaY) {return false;};
    virtual bool zoom(float originalDistance, float currentDistance) {return false;};
    virtual bool rotate(float angle) {return false;};
};

class VelocityTracker: public CCObject {
public:
    float lastX;
    float lastY;
    float deltaX;
    float deltaY;
    cc_timeval lastTime;
    int numSamples;
    float meanX[VELOCITY_TRACKER_SAMPLE_SIZE];
    float meanY[VELOCITY_TRACKER_SAMPLE_SIZE];
    double meanTime[VELOCITY_TRACKER_SAMPLE_SIZE];

    void start(float x, float y, cc_timeval *timeStamp);
    void update(float x, float y, cc_timeval *timeStamp);

    float getVelocityX();
    float getVelocityY();
private:
    float getAverage(float *values, int numSamples);
    double getAverage(double *values, int numSamples);
    float getSum(float *values, int numSamples);
};

#endif //__GestureDetector_H_
