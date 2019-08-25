include $(CLEAR_VARS)

# Force enable shared library building with jmagick
ifeq ($(JMAGICK_ENABLED),true)
    ifeq ($(STATIC_BUILD),true)
        $(info [ JMagick build enabled: Force enabling shared library build ])
        STATIC_BUILD := false
    endif
endif


LOCAL_MODULE    := libjmagick-7
LOCAL_CFLAGS += -DIMAGEMAGICK_HEADER_STYLE_7 -fopenmp

ifeq ($(LIBXML2_ENABLED),true)
    LOCAL_CFLAGS += -DJ_ICU4C
endif

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK_PATCH_INCLUDE_PATH) \
    $(IMAGE_MAGICK_PATCH_PATH) \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/MagickCore \
    $(PNG_LIB_PATH) \
    $(JPEG_LIB_PATH) \
    $(TIFF_LIB_PATH) \
    $(ICU_LIB_PATH)/common


LOCAL_SRC_FILES := \
    $(JMAGICK_LIB_PATH)/jmagick.c \
    $(JMAGICK_LIB_PATH)/magick_DrawInfo.c \
    $(JMAGICK_LIB_PATH)/magick_ImageInfo.c \
    $(JMAGICK_LIB_PATH)/magick_Magick.c \
    $(JMAGICK_LIB_PATH)/magick_MagickImage.c \
    $(JMAGICK_LIB_PATH)/magick_MagickInfo.c \
    $(JMAGICK_LIB_PATH)/magick_MontageInfo.c \
    $(JMAGICK_LIB_PATH)/magick_PixelPacket.c \
    $(JMAGICK_LIB_PATH)/magick_QuantizeInfo.c \
    $(JMAGICK_LIB_PATH)/magick_Cache.c \
    $(JMAGICK_LIB_PATH)/magick_AppDataDir.c \
    $(JMAGICK_LIB_PATH)/magick_Morphology.c \
    $(JMAGICK_LIB_PATH)/magick_ICUDataDir.c \
    $(JMAGICK_LIB_PATH)/magick_Channel.c \

LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog

# these shared libraries will always be available,
# because a force shared build is enabled with jmagick
LOCAL_SHARED_LIBRARIES := \
    libmagickcore-7 \
    libmagickwand-7

ifeq ($(JMAGICK_ENABLED),true)
    include $(BUILD_SHARED_LIBRARY)
endif
