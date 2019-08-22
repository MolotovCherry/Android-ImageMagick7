include $(CLEAR_VARS)

LOCAL_MODULE    := libmagick++-7
LOCAL_CFLAGS += -fexceptions
LOCAL_LDFLAGS += -fexceptions

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/MagickCore \
    $(IMAGE_MAGICK)/MagickWand \
    $(IMAGE_MAGICK)/Magick++/lib \
    $(PNG_LIB_PATH) \
    $(JPEG_LIB_PATH) \

ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif

LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)/Magick++/lib/Blob.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/BlobRef.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/CoderInfo.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Color.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Drawable.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Exception.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Functions.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Geometry.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Image.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/ImageRef.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Montage.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Options.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Pixels.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/ResourceLimits.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Statistic.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/STL.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Thread.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/TypeMetric.cpp \


LOCAL_SHARED_LIBRARIES := \
    libmagickcore-7 \
    libmagickwand-7

#20170412 disable due to crash
#include $(BUILD_SHARED_LIBRARY)
