include $(CLEAR_VARS)

LOCAL_MODULE    := libbz2

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
    $(BZLIB_LIB_PATH)

LOCAL_SRC_FILES := \
    $(BZLIB_LIB_PATH)/blocksort.c \
    $(BZLIB_LIB_PATH)/bzlib.c \
    $(BZLIB_LIB_PATH)/compress.c \
    $(BZLIB_LIB_PATH)/crctable.c \
    $(BZLIB_LIB_PATH)/decompress.c \
    $(BZLIB_LIB_PATH)/huffman.c \
    $(BZLIB_LIB_PATH)/randtable.c \

include $(BUILD_STATIC_LIBRARY)
