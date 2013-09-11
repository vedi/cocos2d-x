#include "CCDevice.h"
#import <UIKit/UIKit.h>
#import <UIKit/UIDevice.h>
#import "UIDevice-IdentifierAddition.h"

NS_CC_BEGIN

int CCDevice::getDPI()
{
    static int dpi = -1;

    if (dpi == -1)
    {
        float scale= getScreenScale();

        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            dpi = 132 * scale;
        } else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            dpi = 163 * scale;
        } else {
            dpi = 160 * scale;
        }
    }
    return dpi;
}


float CCDevice::getStatusBarHeight() {
    return 20 * getScreenScale();
}

std::string CCDevice::getDeviceId() {
    return [[[UIDevice currentDevice] uniqueDeviceIdentifier] UTF8String];
}

float CCDevice::getScreenScale() {
    float scale = 1.0f;

    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        scale = [[UIScreen mainScreen] scale];
    }
    return scale;
}

NS_CC_END
