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
<!MAGICKWAND!>

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
