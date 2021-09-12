include $(CLEAR_VARS)

LOCAL_MODULE    := libmagick++-7
LOCAL_CFLAGS += -fexceptions

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/Magick++/lib

ifneq ($(STATIC_BUILD),true)
    LOCAL_LDFLAGS += -fexceptions
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
    $(IMAGE_MAGICK)/Magick++/lib/STL.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/SecurityPolicy.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Statistic.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/Thread.cpp \
    $(IMAGE_MAGICK)/Magick++/lib/TypeMetric.cpp \


ifeq ($(BUILD_MAGICKPP),true)
    ifeq ($(STATIC_BUILD),true)
        LOCAL_STATIC_LIBRARIES := \
          libmagickcore-7 \
          libmagickwand-7

        include $(BUILD_STATIC_LIBRARY)
    else
        LOCAL_SHARED_LIBRARIES := \
          libmagickcore-7 \
          libmagickwand-7

        include $(BUILD_SHARED_LIBRARY)
    endif
endif
