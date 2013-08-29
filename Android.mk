

LOCAL_PATH  := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := test.c
LOCAL_MODULE    := uart
LOCAL_SHARED_LIBRARIES  := libc


include $(BUILD_EXECUTABLE)
