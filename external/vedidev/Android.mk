LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := vedidev_static

LOCAL_MODULE_FILENAME := libvedidev

LOCAL_SRC_FILES := AbstractNodeProvider.cpp \
AbstractSceneDispatcher.cpp \
AnimationManagerAssigner.cpp \
GestureDetector.cpp \
VLayer.cpp \
VNode.cpp \
VUtils.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static 
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/..
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
