include $(CLEAR_VARS)

LOCAL_MODULE    := libpng
LOCAL_MODULE_FILENAME := libpngobj

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

# 32-bit
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    LOCAL_CFLAGS := \
        -DPNG_ARM_NEON_OPT=2 \
        -D__ARM_NEON__

    LOCAL_SRC_FILES := $(PNG_LIB_PATH)/arm/filter_neon.S.neon
    LOCAL_SRC_FILES := $(PNG_LIB_PATH)/arm/filter_neon_intrinsics.c
    LOCAL_SRC_FILES += $(PNG_LIB_PATH)/arm/palette_neon_intrinsics.c
endif # TARGET_ARCH_ABI == armeabi-v7a

# 64-bit
ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
    LOCAL_CFLAGS := \
        -DPNG_ARM_NEON_OPT=1 \
        -D__ARM_NEON__

    LOCAL_SRC_FILES := $(PNG_LIB_PATH)/arm/filter_neon_intrinsics.c
    LOCAL_SRC_FILES += $(PNG_LIB_PATH)/arm/palette_neon_intrinsics.c
endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_C_INCLUDES := $(PNG_LIB_PATH)

LOCAL_SRC_FILES += \
    $(PNG_LIB_PATH)/pngerror.c \
    $(PNG_LIB_PATH)/pngwio.c \
    $(PNG_LIB_PATH)/pngwrite.c \
    $(PNG_LIB_PATH)/pngwutil.c \
    $(PNG_LIB_PATH)/pngwtran.c \
    $(PNG_LIB_PATH)/pngset.c \
    $(PNG_LIB_PATH)/pngtrans.c \
    $(PNG_LIB_PATH)/png.c \
    $(PNG_LIB_PATH)/pngrtran.c \
    $(PNG_LIB_PATH)/pngmem.c \
    $(PNG_LIB_PATH)/pngpread.c \
    $(PNG_LIB_PATH)/pngrutil.c \
    $(PNG_LIB_PATH)/pngget.c \
    $(PNG_LIB_PATH)/pngread.c \
    $(PNG_LIB_PATH)/pngrio.c \
    $(PNG_LIB_PATH)/pngtest.c


# config for both NEON archs
ifneq (,$(filter $(TARGET_ARCH_ABI),armeabi-v7a arm64-v8a))
    LOCAL_SRC_FILES += $(PNG_LIB_PATH)/arm/arm_init.c

    # do a NEON compilation
    LOCAL_ARM_NEON := true
endif


ifeq ($(LIBPNG_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif
