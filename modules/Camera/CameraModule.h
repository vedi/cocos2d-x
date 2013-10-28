//
// Created by Alexandr on 06.10.13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __CameraModule_H_
#define __CameraModule_H_

#include "cocos2d.h"


class CameraModule {
public:
    static void getPhoto();
    static void getPhotoFromGallery();

protected:

private:
    static cocos2d::CCObject *callNative(cocos2d::CCDictionary *pDictionary);

};


#endif //__CameraModule_H_
