//
// Created by Fedor on 03/06/14.
//


#ifndef __CCRandomReward_H_
#define __CCRandomReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCRandomReward : public CCAggregateReward {
        CC_SYNTHESIZE_RETAIN(CCReward *, mLastGivenReward, LastGivenReward);
    public:
        CCRandomReward() : CCAggregateReward(), mLastGivenReward(NULL) {
        };

        static CCRandomReward *create(
                cocos2d::CCString *id,
                cocos2d::CCString *name,
                cocos2d::CCArray *rewards,
                CCSchedule *schedule
        );

        SL_CREATE_WITH_DICTIONARY(CCRandomReward);

        virtual ~CCRandomReward();

        virtual const char *getType() const;

    protected:
        virtual bool takeInner();

        virtual bool giveInner();
    };
}

#endif //__CCRandomReward_H_
