include $(CLEAR_VARS)

LOCAL_MODULE    := libmagickcore-7

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm


ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)/configs/arm64
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)/configs/arm64
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)  
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)/configs/arm
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)/configs/arm
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)/configs/x86
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)/configs/x86
else ifeq ($(TARGET_ARCH_ABI),x86_64)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)/configs/x86-64
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)/configs/x86-64
    
    ifneq ($(STATIC_BUILD),true)
        LOCAL_LDFLAGS += -latomic
    endif
    
endif


LOCAL_C_INCLUDES  += \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)/MagickCore \
    $(PNG_LIB_PATH) \
    $(JPEG_LIB_PATH) \
    $(TIFF_LIB_PATH) \
    $(FREETYPE_LIB_PATH)/include \
    $(FREETYPE_LIB_PATH)/src \
    $(FREETYPE_LIB_PATH) \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2 \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip \
    $(OPENJPEG_LIB_PATH)/config \
    $(FFTW_LIB_PATH)/api \
    $(XML2_INCLUDE_PATH) \
    $(XML2_INCLUDE_PATH)/include \
    $(LZMA_LIB_PATH)/liblzma/api \
    $(BZLIB_LIB_PATH) \
    $(LCMS_LIB_PATH)/include


ifneq ($(STATIC_BUILD),true)
# ignored in static library builds
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif


LOCAL_SRC_FILES += \
    $(IMAGE_MAGICK)/coders/aai.c \
    $(IMAGE_MAGICK)/coders/art.c \
    $(IMAGE_MAGICK)/coders/ashlar.c \
    $(IMAGE_MAGICK)/coders/avs.c \
    $(IMAGE_MAGICK)/coders/bgr.c \
    $(IMAGE_MAGICK)/coders/bmp.c \
    $(IMAGE_MAGICK)/coders/braille.c \
    $(IMAGE_MAGICK)/coders/cals.c \
    $(IMAGE_MAGICK)/coders/caption.c \
    $(IMAGE_MAGICK)/coders/yuv.c \
    $(IMAGE_MAGICK)/filters/analyze.c \
    $(IMAGE_MAGICK)/MagickCore/accelerate.c \
   


# compiling with openCL support
ifeq ($(OPENCL_BUILD),true)
    LOCAL_C_INCLUDES += \
        $(OPENCL_INCLUDE_PATH) \
        $(LTDL_LIB_PATH) \
        $(LTDL_LIB_PATH)/libltdl
    LOCAL_CFLAGS += \
        -DMAGICKCORE_HAVE_CL_CL_H=1 \
        -DMAGICKCORE__OPENCL=1 \
        -DMAGICKCORE_LTDL_DELEGATE=1
    LOCAL_SHARED_LIBRARIES += libopencl
    LOCAL_STATIC_LIBRARIES += libltdl
endif

ifeq ($(LIBZLIB_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_ZLIB_DELEGATE=1
endif

ifeq ($(LIBPNG_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_PNG_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libpng
endif

ifeq ($(LIBJPEG_TURBO_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_JPEG_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libjpeg-turbo
endif

ifeq ($(LIBTIFF_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_TIFF_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libtiff
endif

ifeq ($(LIBFREETYPE2_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_FREETYPE_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libfreetype2
endif

ifeq ($(LIBWEBP_ENABLED),true)
    LOCAL_CFLAGS += \
        -DMAGICKCORE_WEBP_DELEGATE=1 \
        -DMAGICKCORE_WEBPMUX_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libwebp libwebpmux
endif

ifeq ($(LIBOPENJPEG_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_OPENJP2_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libopenjpeg
endif

ifeq ($(LIBFFTW_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_FFTW_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libfftw3
endif

ifeq ($(LIBXML2_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_XML_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libxml2
endif

ifeq ($(LIBLZMA_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_LZMA_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += liblzma
endif

ifeq ($(LIBBZ2_ENABLED),true)
    LOCAL_CFLAGS += -DMAGICKCORE_BZLIB_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += libbz2
endif

ifeq ($(LIBLCMS2_ENABLED),true)
    LOCAL_CFLAGS += \
        -DMAGICKCORE_HAVE_LCMS2_H=1 \
        -DMAGICKCORE_LCMS_DELEGATE=1
    LOCAL_STATIC_LIBRARIES += liblcms2
endif


ifeq ($(STATIC_BUILD),true)
    include $(BUILD_STATIC_LIBRARY)
else
    include $(BUILD_SHARED_LIBRARY)
endif
