include $(CLEAR_VARS)

LOCAL_MODULE    := liblcms2

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
    $(LCMS_LIB_PATH) \
    $(LCMS_LIB_PATH)/include \
    $(LCMS_LIB_PATH)/src


LOCAL_CFLAGS := \
    -DHAVE_FUNC_ATTRIBUTE_VISIBILITY=1 \
    -DHasTHREADS=1

LOCAL_SRC_FILES := \
    $(LCMS_LIB_PATH)/src/cmsalpha.c \
    $(LCMS_LIB_PATH)/src/cmscam02.c \
    $(LCMS_LIB_PATH)/src/cmscgats.c \
    $(LCMS_LIB_PATH)/src/cmscnvrt.c \
    $(LCMS_LIB_PATH)/src/cmserr.c \
    $(LCMS_LIB_PATH)/src/cmsgamma.c \
    $(LCMS_LIB_PATH)/src/cmsgmt.c \
    $(LCMS_LIB_PATH)/src/cmshalf.c \
    $(LCMS_LIB_PATH)/src/cmsintrp.c \
    $(LCMS_LIB_PATH)/src/cmsio0.c \
    $(LCMS_LIB_PATH)/src/cmsio1.c \
    $(LCMS_LIB_PATH)/src/cmslut.c \
    $(LCMS_LIB_PATH)/src/cmsmd5.c \
    $(LCMS_LIB_PATH)/src/cmsmtrx.c \
    $(LCMS_LIB_PATH)/src/cmsnamed.c \
    $(LCMS_LIB_PATH)/src/cmsopt.c \
    $(LCMS_LIB_PATH)/src/cmspack.c \
    $(LCMS_LIB_PATH)/src/cmspcs.c \
    $(LCMS_LIB_PATH)/src/cmsplugin.c \
    $(LCMS_LIB_PATH)/src/cmsps2.c \
    $(LCMS_LIB_PATH)/src/cmssamp.c \
    $(LCMS_LIB_PATH)/src/cmssm.c \
    $(LCMS_LIB_PATH)/src/cmstypes.c \
    $(LCMS_LIB_PATH)/src/cmsvirt.c \
    $(LCMS_LIB_PATH)/src/cmswtpnt.c \
    $(LCMS_LIB_PATH)/src/cmsxform.c \

ifeq ($(LIBLCMS2_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif
