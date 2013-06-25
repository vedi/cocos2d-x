//
// Created by Alexandr on 21.06.13.
// Copyright (c) 2013 VedideV. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Parse_H_
#define __Parse_H_

#include "cocos2d.h"


#define EASY_NDK_METHOD "parse_easyNDK"


class Parse {
    public:

    static void setKeys(const char *applicationID, const char* clientKey);
    static void initParsePush(bool pushNotificationState);
    static void sendParseObject(const char* objectName);

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);
};

#endif //__Parse_H_
