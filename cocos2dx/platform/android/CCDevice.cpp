#include "platform/CCDevice.h"
#include "jni/DPIJni.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

NS_CC_BEGIN

int CCDevice::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = (int)getDPIJNI();
    }
    return dpi;
}

float CCDevice::getStatusBarHeight() {
    // TODO: It's just a mock-up. Implement it properly.
    return 20;
}

std::string CCDevice::getDeviceId() {
    return getDeviceIdJNI();
}


NS_CC_END
