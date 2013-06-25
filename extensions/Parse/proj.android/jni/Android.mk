LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_parse_static

LOCAL_MODULE_FILENAME := libcocos2dxparse

LOCAL_SRC_FILES := ../../cocos2d-x_Parse/Parse.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d-x_Parse

LOCAL_WHOLE_STATIC_LIBRARIES += easyndk_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../cocos2d-x_Parse

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/EasyNDK/proj.android/jni)

