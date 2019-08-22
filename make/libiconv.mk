include $(CLEAR_VARS)

LOCAL_MODULE    := libiconv

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := \
    -Wno-multichar \
    -Wno-parentheses-equality \
    -DLIBDIR=\"c\" \
    -D_ANDROID \
    -DBUILDING_LIBICONV \
    -DIN_LIBRARY \
    -DENABLE_RELOCATABLE

LOCAL_C_INCLUDES := \
    $(ICONV_LIB_PATH) \
    $(ICONV_LIB_PATH)/include \
    $(ICONV_LIB_PATH)/lib \
    $(ICONV_LIB_PATH)/libcharset \
    $(ICONV_LIB_PATH)/libcharset/include \
    $(ICONV_LIB_PATH)/srclib

LOCAL_SRC_FILES := \
    $(ICONV_LIB_PATH)/lib/iconv.c \
    $(ICONV_LIB_PATH)/lib/relocatable.c \
    $(ICONV_LIB_PATH)/libcharset/lib/localcharset.c

# multiple dependencies
BUILD_ICONV := false
ifeq ($(LIBXML2_ENABLED),true)
    BUILD_ICONV := true
endif

ifeq ($(LIBLZMA_ENABLED),true)
    BUILD_ICONV := true
endif

ifeq ($(BUILD_ICONV),true)
    include $(BUILD_STATIC_LIBRARY)
endif
