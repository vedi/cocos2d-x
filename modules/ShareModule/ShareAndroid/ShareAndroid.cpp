//
// Created by Alexandr on 03.03.14.
//

#include "ShareAndroid.h"
#include "ShareAndroidJNI.h"

void ShareAndroid::rateApp() {
    ShareAndroid_rateAppJNI();
}

void ShareAndroid::showShareDialog(const char *shareText) {
    ShareAndroid_showShareDialogJNI(shareText);
}

bool ShareAndroid::isAmazonStore() {
    return ShareAndroid_isAmazonStore();
}
