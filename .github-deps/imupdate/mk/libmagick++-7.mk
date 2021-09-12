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
<!MAGICK++!>


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
