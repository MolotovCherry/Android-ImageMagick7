include $(CLEAR_VARS)

LOCAL_MODULE    := magick
#LOCAL_CFLAGS += -fexceptions
#LOCAL_LDFLAGS += -fexceptions

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/MagickCore \
    $(IMAGE_MAGICK)/MagickWand \
    $(IMAGE_MAGICK)/Magick++/lib \
    $(PNG_LIB_PATH) \
    $(JPEG_LIB_PATH) \
    $(TIFF_LIB_PATH) \
    $(FREETYPE_LIB_PATH)/include


LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)/utilities/magick.c \

ifeq ($(STATIC_BUILD),true)
    LOCAL_STATIC_LIBRARIES := \
        libmagickcore-7 \
        libmagickwand-7
else
    LOCAL_SHARED_LIBRARIES := \
        libmagickcore-7 \
        libmagickwand-7
endif

# compiling with openCL support
ifeq ($(OPENCL_BUILD),true)
    # bunch of undefined errors without this..
    LOCAL_LDLIBS += -fuse-ld=gold
endif

ifeq ($(BUILD_MAGICK_BIN),true)
    include $(BUILD_EXECUTABLE)
endif
