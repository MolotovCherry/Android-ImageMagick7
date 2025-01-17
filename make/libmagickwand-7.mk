include $(CLEAR_VARS)

LOCAL_MODULE    := libmagickwand-7

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/MagickCore \
    $(IMAGE_MAGICK)/MagickWand \
    $(PNG_LIB_PATH) \
    $(JPEG_LIB_PATH) \

# always ignored in static builds
ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif

LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)/MagickWand/animate.c \
    $(IMAGE_MAGICK)/MagickWand/compare.c \
    $(IMAGE_MAGICK)/MagickWand/composite.c \
    $(IMAGE_MAGICK)/MagickWand/conjure.c \
    $(IMAGE_MAGICK)/MagickWand/deprecate.c \
    $(IMAGE_MAGICK)/MagickWand/display.c \
    $(IMAGE_MAGICK)/MagickWand/drawing-wand.c \
    $(IMAGE_MAGICK)/MagickWand/identify.c \
    $(IMAGE_MAGICK)/MagickWand/import.c \
    $(IMAGE_MAGICK)/MagickWand/magick-cli.c \
    $(IMAGE_MAGICK)/MagickWand/magick-image.c \
    $(IMAGE_MAGICK)/MagickWand/magick-property.c \
    $(IMAGE_MAGICK)/MagickWand/magick-wand.c \
    $(IMAGE_MAGICK)/MagickWand/mogrify.c \
    $(IMAGE_MAGICK)/MagickWand/montage.c \
    $(IMAGE_MAGICK)/MagickWand/operation.c \
    $(IMAGE_MAGICK)/MagickWand/pixel-iterator.c \
    $(IMAGE_MAGICK)/MagickWand/pixel-wand.c \
    $(IMAGE_MAGICK)/MagickWand/script-token.c \
    $(IMAGE_MAGICK)/MagickWand/stream.c \
    $(IMAGE_MAGICK)/MagickWand/wand-view.c \
    $(IMAGE_MAGICK)/MagickWand/wand.c \
    $(IMAGE_MAGICK)/MagickWand/wandcli.c \


# compiling with openCL support
ifeq ($(OPENCL_BUILD),true)
    LOCAL_C_INCLUDES += \
        $(OPENCL_INCLUDE_PATH)
    LOCAL_CFLAGS += \
        -DMAGICKCORE_HAVE_CL_CL_H=1 \
        -DMAGICKCORE__OPENCL=1
    LOCAL_SHARED_LIBRARIES += libopencl
endif

ifeq ($(BUILD_MAGICKWAND),true)
    ifeq ($(STATIC_BUILD),true)
        LOCAL_STATIC_LIBRARIES := \
            libmagickcore-7
            
        include $(BUILD_STATIC_LIBRARY)
    else
        LOCAL_SHARED_LIBRARIES := \
            libmagickcore-7
            
        include $(BUILD_SHARED_LIBRARY)
    endif
endif
