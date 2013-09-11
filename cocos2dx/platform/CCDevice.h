#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"
#include <string>

NS_CC_BEGIN

class CC_DLL CCDevice
{
private:
    CCDevice();
public:
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    static int getDPI();
    static float getStatusBarHeight();
    static std::string getDeviceId();

    static float getScreenScale();
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
