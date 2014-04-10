//
// Created by Alexandr on 03.03.14.
//


#ifndef __ShareAndroid_H_
#define __ShareAndroid_H_


class ShareAndroid {
public:
    static void rateApp();
    static void showShareDialog(const char* shareText);
    static bool isAmazonStore();
};


#endif //__ShareAndroid_H_
