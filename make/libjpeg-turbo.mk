include $(CLEAR_VARS)

LOCAL_MODULE := libjpeg-turbo
LDFLAGS := -pie

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS += -mfloat-abi=softfp -fprefetch-loop-arrays
endif

ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard x86),)
    LOCAL_ARM_NEON := true
    LOCAL_CFLAGS += -D__ARM_HAVE_NEON
endif

LOCAL_ASMFLAGS += -DELF

ifeq ($(TARGET_ARCH_ABI),x86_64)
    LOCAL_SRC_FILES += \
        $(JPEG_LIB_PATH)/simd/x86_64/jsimd.c \
        $(JPEG_LIB_PATH)/simd/x86_64/jccolext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jccolext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jccolor-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jccolor-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcgray-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcgray-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcgryext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcgryext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jchuff-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcphuff-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcsample-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jcsample-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdcolext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdcolext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdcolor-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdcolor-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdmerge-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdmerge-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdmrgext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdmrgext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdsample-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jdsample-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jfdctflt-sse.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jfdctfst-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jfdctint-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jfdctint-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jidctflt-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jidctfst-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jidctint-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jidctint-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jidctred-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jquantf-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jquanti-avx2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jquanti-sse2.asm \
        $(JPEG_LIB_PATH)/simd/x86_64/jsimdcpu.asm

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=8

    LOCAL_ASMFLAGS += -D__x86_64__

else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES += \
        $(JPEG_LIB_PATH)/simd/i386/jsimd.c \
        $(JPEG_LIB_PATH)/simd/i386/jccolext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jccolext-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jccolext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jccolor-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jccolor-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jccolor-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgray-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgray-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgray-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgryext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgryext-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcgryext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jchuff-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcphuff-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcsample-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcsample-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jcsample-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolext-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolor-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolor-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdcolor-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmerge-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmerge-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmerge-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmrgext-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmrgext-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdmrgext-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdsample-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdsample-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jdsample-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctflt-3dn.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctflt-sse.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctfst-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctfst-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctint-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctint-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jfdctint-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctflt-3dn.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctflt-sse.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctflt-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctfst-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctfst-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctint-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctint-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctint-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctred-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jidctred-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquant-3dn.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquant-mmx.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquant-sse.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquantf-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquanti-avx2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jquanti-sse2.asm \
        $(JPEG_LIB_PATH)/simd/i386/jsimdcpu.asm

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=4

    LOCAL_ASMFLAGS += -DPIC

else ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard),)
    LOCAL_SRC_FILES += \
        $(JPEG_LIB_PATH)/simd/arm/jsimd.c \
        $(JPEG_LIB_PATH)/simd/arm/jsimd_neon.S.neon

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=4

else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_SRC_FILES += \
        $(JPEG_LIB_PATH)/simd/arm64/jsimd.c \
        $(JPEG_LIB_PATH)/simd/arm64/jsimd_neon.S.neon

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=8

endif

LOCAL_C_INCLUDES += \
    $(JPEG_LIB_PATH)/simd \
    $(JPEG_LIB_PATH)

LOCAL_EXPORT_C_INCLUDES := \
    $(JPEG_LIB_PATH)

# libjpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
    $(JPEG_LIB_PATH)/jcapimin.c \
    $(JPEG_LIB_PATH)/jcapistd.c \
    $(JPEG_LIB_PATH)/jccoefct.c \
    $(JPEG_LIB_PATH)/jccolor.c \
    $(JPEG_LIB_PATH)/jcdctmgr.c \
    $(JPEG_LIB_PATH)/jchuff.c \
    $(JPEG_LIB_PATH)/jcicc.c \
    $(JPEG_LIB_PATH)/jcinit.c \
    $(JPEG_LIB_PATH)/jcmainct.c \
    $(JPEG_LIB_PATH)/jcmarker.c \
    $(JPEG_LIB_PATH)/jcmaster.c \
    $(JPEG_LIB_PATH)/jcomapi.c \
    $(JPEG_LIB_PATH)/jcparam.c \
    $(JPEG_LIB_PATH)/jcphuff.c \
    $(JPEG_LIB_PATH)/jcprepct.c \
    $(JPEG_LIB_PATH)/jcsample.c \
    $(JPEG_LIB_PATH)/jctrans.c \
    $(JPEG_LIB_PATH)/jdapimin.c \
    $(JPEG_LIB_PATH)/jdapistd.c \
    $(JPEG_LIB_PATH)/jdatadst.c \
    $(JPEG_LIB_PATH)/jdatasrc.c \
    $(JPEG_LIB_PATH)/jdcoefct.c \
    $(JPEG_LIB_PATH)/jdcolor.c \
    $(JPEG_LIB_PATH)/jddctmgr.c \
    $(JPEG_LIB_PATH)/jdhuff.c \
    $(JPEG_LIB_PATH)/jdicc.c \
    $(JPEG_LIB_PATH)/jdinput.c \
    $(JPEG_LIB_PATH)/jdmainct.c \
    $(JPEG_LIB_PATH)/jdmarker.c \
    $(JPEG_LIB_PATH)/jdmaster.c \
    $(JPEG_LIB_PATH)/jdmerge.c \
    $(JPEG_LIB_PATH)/jdphuff.c \
    $(JPEG_LIB_PATH)/jdpostct.c \
    $(JPEG_LIB_PATH)/jdsample.c \
    $(JPEG_LIB_PATH)/jdtrans.c \
    $(JPEG_LIB_PATH)/jerror.c \
    $(JPEG_LIB_PATH)/jfdctflt.c \
    $(JPEG_LIB_PATH)/jfdctfst.c \
    $(JPEG_LIB_PATH)/jfdctint.c \
    $(JPEG_LIB_PATH)/jidctflt.c \
    $(JPEG_LIB_PATH)/jidctfst.c \
    $(JPEG_LIB_PATH)/jidctint.c \
    $(JPEG_LIB_PATH)/jidctred.c \
    $(JPEG_LIB_PATH)/jquant1.c \
    $(JPEG_LIB_PATH)/jquant2.c \
    $(JPEG_LIB_PATH)/jutils.c \
    $(JPEG_LIB_PATH)/jmemmgr.c \
    $(JPEG_LIB_PATH)/jmemnobs.c \
    $(JPEG_LIB_PATH)/jaricom.c \
    $(JPEG_LIB_PATH)/jcarith.c \
    $(JPEG_LIB_PATH)/jdarith.c \
    $(JPEG_LIB_PATH)/turbojpeg.c \
    $(JPEG_LIB_PATH)/transupp.c \
    $(JPEG_LIB_PATH)/jdatadst-tj.c \
    $(JPEG_LIB_PATH)/jdatasrc-tj.c \
    $(JPEG_LIB_PATH)/rdbmp.c \
    $(JPEG_LIB_PATH)/rdppm.c \
    $(JPEG_LIB_PATH)/wrbmp.c \
    $(JPEG_LIB_PATH)/wrppm.c

JCONFIG_FLAGS += \
    JPEG_LIB_VERSION=62 \
    LIBJPEG_TURBO_VERSION=2.0.2 \
    LIBJPEG_TURBO_VERSION_NUMBER=202 \
    C_ARITH_CODING_SUPPORTED \
    D_ARITH_CODING_SUPPORTED \
    MEM_SRCDST_SUPPORTED \
    WITH_SIMD \
    BITS_IN_JSAMPLE=8 \
    HAVE_LOCALE_H \
    HAVE_STDDEF_H \
    HAVE_STDLIB_H \
    NEED_SYS_TYPES_H \
    HAVE_UNSIGNED_CHAR \
    HAVE_UNSIGNED_SHORT

JCONFIGINT_FLAGS += \
    BUILD="20190814" \
    PACKAGE_NAME="libjpeg-turbo" \
    VERSION="2.0.2"

# originally defined in jconfigint.h, but the substitution has problems with spaces
LOCAL_CFLAGS := \
    -DINLINE="inline __attribute__((always_inline))"

# create definition file jconfig.h, needed in order to build
$(shell echo /* autogenerated jconfig.h based on Android.mk var JCONFIG_FLAGS */ > $(JPEG_LIB_PATH)/jconfig.h)
$(foreach name,$(JCONFIG_FLAGS), \
    $(if $(findstring =,$(name)), \
        $(shell >>$(JPEG_LIB_PATH)/jconfig.h echo #ifndef $(firstword $(subst =, ,$(name)))) \
    , \
        $(shell >>$(JPEG_LIB_PATH)/jconfig.h echo #ifndef $(name)) \
    ) \
    $(shell >>$(JPEG_LIB_PATH)/jconfig.h echo #define $(subst =, ,$(name))) \
    $(shell >>$(JPEG_LIB_PATH)/jconfig.h echo #endif) \
    $(shell >> $(JPEG_LIB_PATH)/jconfig.h echo.) \
)

# create definition file jconfigint.h, needed in order to build
$(shell >$(JPEG_LIB_PATH)/jconfigint.h echo /* autogenerated jconfigint.h based on Android.mk vars JCONFIGINT_FLAGS */)
$(foreach name,$(JCONFIGINT_FLAGS),$(shell >>$(JPEG_LIB_PATH)/jconfigint.h echo #define $(subst =, ,$(name))))

include $(BUILD_STATIC_LIBRARY)
