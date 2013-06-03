LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_flurry_static

LOCAL_MODULE_FILENAME := libcocos2dxflurry

LOCAL_SRC_FILES := ../../FlurryManager.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../..

LOCAL_WHOLE_STATIC_LIBRARIES += easyndk_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../..

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/EasyNDK/proj.android/jni)

