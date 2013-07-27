//
// Created by vedi on 1/13/13.
//

#include "GestureDetector.h"

GestureDetector::GestureDetector() {
    CCTime::gettimeofdayCocos2d(&lastTapTime, NULL);
    tapCount = 0;

    tracker = new VelocityTracker();
    tracker->autorelease();
    tracker->retain();

    mCurrentTouch = NULL;

    m_pTrackingNodes = CCArray::create();
    m_pTrackingNodes->retain();

    for (int i = 0; i < CC_MAX_TOUCHES; i++) {
        tapedFingers[i] = false;
    }
}

GestureDetector::~GestureDetector() {
    tracker->release();
    m_pTrackingNodes->release();
}

void GestureDetector::removeTrackingNode(CCNode *pNode) {
    m_pTrackingNodes->removeObject(pNode);
}

GestureDetector *GestureDetector::create(GestureListener *listener) {
    return create(20, 0.4f, 1.5f, 0.15f, listener);
}

GestureDetector *GestureDetector::create(int halfTapSquareSize, float tapCountInterval,
        float longPressDuration, float maxFlingDelay,
        GestureListener *listener) {
    GestureDetector *pGestureDetector = new GestureDetector();
    pGestureDetector->autorelease();

    pGestureDetector->tapSquareSize = halfTapSquareSize;
    pGestureDetector->tapCountInterval = (time_t) (tapCountInterval * 1000);
    pGestureDetector->longPressDuration = (time_t) (longPressDuration * 1000);
    pGestureDetector->maxFlingDelay = (time_t) (maxFlingDelay * 1000);
    pGestureDetector->listener = listener;

    return pGestureDetector;
}

void GestureDetector::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    CC_UNUSED_PARAM(pEvent);

    CCPoint tTouchPoint;
//    CCObject *pObj;
//    CCNode *pNode;
    for (CCSetIterator iter = pTouches->begin(); iter != pTouches->end(); iter++) {
        mCurrentTouch = (CCTouch *) (*iter);
        tTouchPoint = mCurrentTouch->getLocation();
        touchDown(tTouchPoint, mCurrentTouch->getID());

//        CCARRAY_FOREACH(m_pTrackingNodes, pObj) {
//            pNode = static_cast<CCNode *>(pObj);
//            if (Utils::isNodeAtPoint(pNode, tTouchPoint)) {
//                touchDown(tTouchPoint.x, tTouchPoint.y, pTouch->getID());
//                break;
//            }
//        }

    }
}

void GestureDetector::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {
    ccTouchesEnded(pTouches, pEvent);
}

void GestureDetector::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
    CC_UNUSED_PARAM(pEvent);

    CCPoint tTouchPoint;
    for (CCSetIterator iter = pTouches->begin(); iter != pTouches->end(); iter++) {
        mCurrentTouch = (CCTouch *) (*iter);
        tTouchPoint = mCurrentTouch->getLocation();
        touchDragged(tTouchPoint, mCurrentTouch->getID());
    }
}

void GestureDetector::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
    CC_UNUSED_PARAM(pEvent);

    CCPoint tTouchPoint;
    for (CCSetIterator iter = pTouches->begin(); iter != pTouches->end(); iter++) {
        mCurrentTouch = (CCTouch *) (*iter);
        tTouchPoint = mCurrentTouch->getLocation();
        touchUp(tTouchPoint, mCurrentTouch->getID());
    }
}

void GestureDetector::addTrackingNode(CCNode *pNode) {
    m_pTrackingNodes->addObject(pNode);
}

bool GestureDetector::touchDown(CCPoint &touchPoint, int pointer) {
    if (pointer > 1) {
        return false;
    }

    tapedFingers[pointer] = true;

    if (pointer == 0) {
        firstPointer.x  = touchPoint.x;
        firstPointer.y = touchPoint.y;
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        gestureStartTime = now;
        tracker->start(touchPoint.x, touchPoint.y, &gestureStartTime);
        // we are still touching with the second finger -> pinch mode
        if(tapedFingers[1]) {
            inTapSquare = false;
            pinching = true;
            initialDistance = ccpDistance(firstPointer, secondPointer);
        } else {
            inTapSquare = true;
            pinching = false;
            longPressFired = false;
            tapSquareCenterX = touchPoint.x;
            tapSquareCenterY = touchPoint.y;
        }
    } else {
        secondPointer.x = touchPoint.x;
        secondPointer.y = touchPoint.y;
        inTapSquare = false;
        pinching = true;
        initialDistance = ccpDistance(firstPointer, secondPointer);
    }
    return listener != NULL ? listener->touchDown(touchPoint, pointer) : false;
}

bool GestureDetector::touchDragged(CCPoint &touchPoint, int pointer) {
    if (pointer > 1) {
        return false;
    }

    bool bRet = false;

    // handle pinch zoom
    if (pinching) {

        CCPoint tAPoint;
        CCPoint tB1Point;
        CCPoint tB2Point = touchPoint;
        if (pointer == 0) {
            tAPoint = secondPointer;
            tB1Point = firstPointer;
        } else {
            tAPoint = firstPointer;
            tB1Point = secondPointer;
        }

        tB1Point = ccpSub(tB1Point, tAPoint);
        tB2Point = ccpSub(tB2Point, tAPoint);

        float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(tB2Point, tB1Point));

        if (pointer == 0) {
            firstPointer.x = touchPoint.x;
            firstPointer.y = touchPoint.y;
        } else {
            secondPointer.x = touchPoint.x;
            secondPointer.y = touchPoint.y;
        }

        if (listener != NULL) {
            bRet = listener->rotate(angle);
            if (!bRet) {
                bRet = listener->zoom();
            }
        } else {
            bRet = false;
        }
    } else {
        // update tracker
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        tracker->update(touchPoint.x, touchPoint.y, &now);

        // check if we are still tapping.
        if (!(inTapSquare && fabs(touchPoint.x - tapSquareCenterX) <
                tapSquareSize && fabs(touchPoint.y - tapSquareCenterY) < tapSquareSize)) {
            inTapSquare = false;
        }

        if (!inTapSquare) {
            // handle scroll
            inTapSquare = false;
            panning = true;
            CCPoint panPoint = ccp(tracker->lastX, tracker->lastY);
            bRet = listener->pan(panPoint, tracker->deltaX, tracker->deltaY);
        } else {
            // handle longpress
            if (!longPressFired && CCTime::timersubCocos2d(&gestureStartTime, &now) > longPressDuration) {
                longPressFired = true;
                bRet = listener->longPress(touchPoint);
            }
        }
    }

    if (!bRet) {
        return listener != NULL ? listener->touchDragged(touchPoint, pointer) : false;
    } else {
        return true;
    }
}

bool GestureDetector::touchUp(CCPoint &touchPoint, int pointer) {

    if (pointer > 1) {
        return false;
    }

    bool bRet = false;

    tapedFingers[pointer] = false;

    panning = false;

    double deltaTime;
    struct cc_timeval now;
    if (CCTime::gettimeofdayCocos2d(&now, NULL) == 0) {
        deltaTime = CCTime::timersubCocos2d(&lastTapTime, &now);
        deltaTime = MAX(0, deltaTime);
    } else {
        CCLOG("error in gettimeofday");
        deltaTime = 0;
    }

    if (inTapSquare & !longPressFired) {
        // handle taps
        if (deltaTime > tapCountInterval) {
            tapCount = 0;
        }
        tapCount++;
        lastTapTime = now;
        CCPoint tapPoint = ccp(tapSquareCenterX, tapSquareCenterY);
        bRet = listener->tap(tapPoint, tapCount);
        if (bRet) {
            tapCount = 0;
        }
    } else if (pinching) {
        // handle pinch end
        pinching = false;
        panning = true;
        // we are basically in pan/scroll mode again, reset velocity tracker
        if (pointer == 0)	{
            // first pointer has lifted off, set up panning to use the second pointer...
            tracker->start((int)secondPointer.x, (int)secondPointer.y, &now);
        } else {
            // second pointer has lifted off, set up panning to use the first pointer...
            tracker->start((int)firstPointer.x, (int)firstPointer.y, &now);
        }
    } else {
        // handle fling
        if (CCTime::timersubCocos2d(&tracker->lastTime, &now) < maxFlingDelay) {
            tracker->update(touchPoint.x, touchPoint.y, &now);
            bRet = listener->fling(tracker->getVelocityX(), tracker->getVelocityY());
        }
    }

    if (!bRet) {
        return listener != NULL ? listener->touchUp(touchPoint, pointer) : false;
    } else {
        return true;
    }
}

void VelocityTracker::start(float x, float y, cc_timeval *timeStamp) {
    lastX = x;
    lastY = y;
    deltaX = 0;
    deltaY = 0;
    numSamples = 0;
    for (int i = 0; i < VELOCITY_TRACKER_SAMPLE_SIZE; i++) {
        meanX[i] = 0;
        meanY[i] = 0;
        meanTime[i] = 0;
    }
    lastTime = *timeStamp;
}

void VelocityTracker::update(float x, float y, cc_timeval *timeStamp) {
    cc_timeval currTime = *timeStamp;
    deltaX = (x - lastX);
    deltaY = (y - lastY);
    lastX = x;
    lastY = y;
    double deltaTime = CCTime::timersubCocos2d(&lastTime, &currTime);
    lastTime = currTime;
    int index = numSamples % VELOCITY_TRACKER_SAMPLE_SIZE;
    meanX[index] = deltaX;
    meanY[index] = deltaY;
    meanTime[index] = deltaTime;
    numSamples++;
}

float VelocityTracker::getVelocityX() {
    float meanX = getAverage(this->meanX, numSamples);
    float meanTime = (float) (getAverage(this->meanTime, numSamples) / 1000);
    if (meanTime == 0) {
        return 0;
    }
    else {
        return meanX / meanTime;
    }
}

float VelocityTracker::getVelocityY() {
    float meanY = getAverage(this->meanY, numSamples);
    float meanTime = (float) (getAverage(this->meanTime, numSamples) / 1000);
//    CCLog("meanY: %f, meanTime")
    if (meanTime == 0) {
        return 0;
    }
    else {
        return meanY / meanTime;
    }
}

float VelocityTracker::getAverage(float *values, int numSamples) {
    numSamples = MIN(VELOCITY_TRACKER_SAMPLE_SIZE, numSamples);
    float sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += values[i];
    }
    return sum / numSamples;
}

double VelocityTracker::getAverage(double *values, int numSamples) {
    numSamples = MIN(VELOCITY_TRACKER_SAMPLE_SIZE, numSamples);
    double sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += values[i];
    }
    if (numSamples == 0) {
        return 0;
    }
    else {
        return sum / numSamples;
    }
}

float VelocityTracker::getSum(float *values, int numSamples) {
    numSamples = MIN(VELOCITY_TRACKER_SAMPLE_SIZE, numSamples);
    float sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += values[i];
    }
    if (numSamples == 0) return 0;
    return sum;
}

