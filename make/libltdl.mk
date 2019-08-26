include $(CLEAR_VARS)

LOCAL_MODULE    := libltdl

LOCAL_C_INCLUDES := \
    $(LTDL_LIB_PATH) \
    $(LTDL_LIB_PATH)/libltdl
LOCAL_EXPORT_C_INCLUDES := \
    $(LTDL_LIB_PATH) \
    $(LTDL_LIB_PATH)/libltdl
    
LOCAL_CFLAGS := \
    -DLTDL \
    -Wno-constant-logical-operand
    
LOCAL_SRC_FILES := \
    $(LTDL_LIB_PATH)/loaders/preopen.c \
    $(LTDL_LIB_PATH)/lt__alloc.c \
    $(LTDL_LIB_PATH)/lt_dlloader.c \
    $(LTDL_LIB_PATH)/lt_error.c \
    $(LTDL_LIB_PATH)/ltdl.c \
    $(LTDL_LIB_PATH)/slist.c \
    $(LTDL_LIB_PATH)/loaders/dlopen.c \
    $(LTDL_LIB_PATH)/lt__strl.c \
    $(LTDL_LIB_PATH)/lt__argz.c \
    $(LTDL_LIB_PATH)/lt__dirent.c

ifeq ($(OPENCL_BUILD),true)
    include $(BUILD_STATIC_LIBRARY)
endif
