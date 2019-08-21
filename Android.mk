LOCAL_PATH := $(call my-dir)

IMAGE_MAGICK        := $(LOCAL_PATH)/ImageMagick-7.0.8-60/
JPEG_SRC_PATH       := $(LOCAL_PATH)/libjpeg-turbo-2.0.2/
PNG_SRC_PATH        := $(LOCAL_PATH)/libpng-1.6.37/
TIFF_SRC_PATH       := $(LOCAL_PATH)/libtiff-v4.0.10/libtiff/
FREETYPE_SRC_PATH   := $(LOCAL_PATH)/libfreetype2-2.10.1/
WEBP_SRC_PATH       := $(LOCAL_PATH)/libwebp-1.0.3/
OPENJPEG_SRC_PATH   := $(LOCAL_PATH)/libopenjpeg-2.3.1/
FFTW_SRC_PATH       := $(LOCAL_PATH)/libfftw-3.3.8/
XML2_SRC_PATH       := $(LOCAL_PATH)/libxml2-2.9.9/
ICONV_SRC_PATH      := $(LOCAL_PATH)/libiconv-1.16/
ICU_SRC_PATH        := $(LOCAL_PATH)/libicu4c-64-2/
LZMA_SRC_PATH       := $(LOCAL_PATH)/xz-5.2.4/
BZLIB_SRC_PATH      := $(LOCAL_PATH)/bzip-1.0.8/

#libjpeg-turbo +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
        $(JPEG_SRC_PATH)simd/x86_64/jsimd.c \
        $(JPEG_SRC_PATH)simd/x86_64/jccolext-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jccolext-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jccolor-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jccolor-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcgray-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcgray-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcgryext-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcgryext-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jchuff-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcphuff-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcsample-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jcsample-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdcolext-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdcolext-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdcolor-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdcolor-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdmerge-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdmerge-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdmrgext-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdmrgext-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdsample-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jdsample-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jfdctflt-sse.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jfdctfst-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jfdctint-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jfdctint-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jidctflt-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jidctfst-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jidctint-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jidctint-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jidctred-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jquantf-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jquanti-avx2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jquanti-sse2.asm \
        $(JPEG_SRC_PATH)simd/x86_64/jsimdcpu.asm

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=8

    LOCAL_ASMFLAGS += -D__x86_64__

else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES += \
        $(JPEG_SRC_PATH)simd/i386/jsimd.c \
        $(JPEG_SRC_PATH)simd/i386/jccolext-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jccolext-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jccolext-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jccolor-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jccolor-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jccolor-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgray-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgray-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgray-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgryext-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgryext-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jcgryext-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jchuff-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcphuff-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcsample-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jcsample-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jcsample-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolext-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolext-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolext-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolor-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolor-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jdcolor-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmerge-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmerge-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmerge-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmrgext-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmrgext-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jdmrgext-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdsample-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jdsample-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jdsample-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctflt-3dn.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctflt-sse.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctfst-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctfst-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctint-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctint-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jfdctint-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctflt-3dn.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctflt-sse.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctflt-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctfst-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctfst-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctint-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctint-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctint-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctred-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jidctred-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jquant-3dn.asm \
        $(JPEG_SRC_PATH)simd/i386/jquant-mmx.asm \
        $(JPEG_SRC_PATH)simd/i386/jquant-sse.asm \
        $(JPEG_SRC_PATH)simd/i386/jquantf-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jquanti-avx2.asm \
        $(JPEG_SRC_PATH)simd/i386/jquanti-sse2.asm \
        $(JPEG_SRC_PATH)simd/i386/jsimdcpu.asm

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=4

    LOCAL_ASMFLAGS += -DPIC

else ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard),)
    LOCAL_SRC_FILES += \
        $(JPEG_SRC_PATH)simd/arm/jsimd.c \
        $(JPEG_SRC_PATH)simd/arm/jsimd_neon.S.neon

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=4

else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_SRC_FILES += \
        $(JPEG_SRC_PATH)simd/arm64/jsimd.c \
        $(JPEG_SRC_PATH)simd/arm64/jsimd_neon.S.neon

    JCONFIGINT_FLAGS += \
        SIZEOF_SIZE_T=8

endif

LOCAL_C_INCLUDES += \
    $(JPEG_SRC_PATH)simd \
    $(JPEG_SRC_PATH)

LOCAL_EXPORT_C_INCLUDES := \
    $(JPEG_SRC_PATH)

# libjpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
    $(JPEG_SRC_PATH)jcapimin.c \
    $(JPEG_SRC_PATH)jcapistd.c \
    $(JPEG_SRC_PATH)jccoefct.c \
    $(JPEG_SRC_PATH)jccolor.c \
    $(JPEG_SRC_PATH)jcdctmgr.c \
    $(JPEG_SRC_PATH)jchuff.c \
    $(JPEG_SRC_PATH)jcicc.c \
    $(JPEG_SRC_PATH)jcinit.c \
    $(JPEG_SRC_PATH)jcmainct.c \
    $(JPEG_SRC_PATH)jcmarker.c \
    $(JPEG_SRC_PATH)jcmaster.c \
    $(JPEG_SRC_PATH)jcomapi.c \
    $(JPEG_SRC_PATH)jcparam.c \
    $(JPEG_SRC_PATH)jcphuff.c \
    $(JPEG_SRC_PATH)jcprepct.c \
    $(JPEG_SRC_PATH)jcsample.c \
    $(JPEG_SRC_PATH)jctrans.c \
    $(JPEG_SRC_PATH)jdapimin.c \
    $(JPEG_SRC_PATH)jdapistd.c \
    $(JPEG_SRC_PATH)jdatadst.c \
    $(JPEG_SRC_PATH)jdatasrc.c \
    $(JPEG_SRC_PATH)jdcoefct.c \
    $(JPEG_SRC_PATH)jdcolor.c \
    $(JPEG_SRC_PATH)jddctmgr.c \
    $(JPEG_SRC_PATH)jdhuff.c \
    $(JPEG_SRC_PATH)jdicc.c \
    $(JPEG_SRC_PATH)jdinput.c \
    $(JPEG_SRC_PATH)jdmainct.c \
    $(JPEG_SRC_PATH)jdmarker.c \
    $(JPEG_SRC_PATH)jdmaster.c \
    $(JPEG_SRC_PATH)jdmerge.c \
    $(JPEG_SRC_PATH)jdphuff.c \
    $(JPEG_SRC_PATH)jdpostct.c \
    $(JPEG_SRC_PATH)jdsample.c \
    $(JPEG_SRC_PATH)jdtrans.c \
    $(JPEG_SRC_PATH)jerror.c \
    $(JPEG_SRC_PATH)jfdctflt.c \
    $(JPEG_SRC_PATH)jfdctfst.c \
    $(JPEG_SRC_PATH)jfdctint.c \
    $(JPEG_SRC_PATH)jidctflt.c \
    $(JPEG_SRC_PATH)jidctfst.c \
    $(JPEG_SRC_PATH)jidctint.c \
    $(JPEG_SRC_PATH)jidctred.c \
    $(JPEG_SRC_PATH)jquant1.c \
    $(JPEG_SRC_PATH)jquant2.c \
    $(JPEG_SRC_PATH)jutils.c \
    $(JPEG_SRC_PATH)jmemmgr.c \
    $(JPEG_SRC_PATH)jmemnobs.c \
    $(JPEG_SRC_PATH)jaricom.c \
    $(JPEG_SRC_PATH)jcarith.c \
    $(JPEG_SRC_PATH)jdarith.c \
    $(JPEG_SRC_PATH)turbojpeg.c \
    $(JPEG_SRC_PATH)transupp.c \
    $(JPEG_SRC_PATH)jdatadst-tj.c \
    $(JPEG_SRC_PATH)jdatasrc-tj.c \
    $(JPEG_SRC_PATH)rdbmp.c \
    $(JPEG_SRC_PATH)rdppm.c \
    $(JPEG_SRC_PATH)wrbmp.c \
    $(JPEG_SRC_PATH)wrppm.c

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
$(shell echo /* autogenerated jconfig.h based on Android.mk var JCONFIG_FLAGS */ > $(JPEG_SRC_PATH)jconfig.h)
$(foreach name,$(JCONFIG_FLAGS), \
    $(if $(findstring =,$(name)), \
        $(shell >>$(JPEG_SRC_PATH)jconfig.h echo #ifndef $(firstword $(subst =, ,$(name)))) \
    , \
        $(shell >>$(JPEG_SRC_PATH)jconfig.h echo #ifndef $(name)) \
    ) \
    $(shell >>$(JPEG_SRC_PATH)jconfig.h echo #define $(subst =, ,$(name))) \
    $(shell >>$(JPEG_SRC_PATH)jconfig.h echo #endif) \
    $(shell >> $(JPEG_SRC_PATH)jconfig.h echo.) \
)

# create definition file jconfigint.h, needed in order to build
$(shell >$(JPEG_SRC_PATH)jconfigint.h echo /* autogenerated jconfigint.h based on Android.mk vars JCONFIGINT_FLAGS */)
$(foreach name,$(JCONFIGINT_FLAGS),$(shell >>$(JPEG_SRC_PATH)jconfigint.h echo #define $(subst =, ,$(name))))

include $(BUILD_STATIC_LIBRARY)
#libjpeg-turbo ---------------------------------------------------------------




#libopenjpeg +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE := libopenjpeg

LOCAL_CFLAGS := -DUSE_JPIP


# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm


LOCAL_C_INCLUDES := \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2 \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip \
    $(OPENJPEG_SRC_PATH)config

LOCAL_SRC_FILES := \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/bench_dwt.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/bio.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/cidx_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/cio.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/dwt.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/event.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/function_list.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/image.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/invert.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/j2k.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/jp2.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/mct.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/mqc.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/openjpeg.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/opj_clock.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/opj_malloc.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/phix_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/pi.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/ppix_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/sparse_array.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/t1.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/t1_generate_luts.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/t2.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/tcd.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/test_sparse_array.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/tgt.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/thix_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/thread.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2/tpix_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/auxtrans_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/box_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/boxheader_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/byte_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/cache_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/cachemodel_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/channel_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/codestream_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/dec_clientmsg_handler.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/faixbox_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/ihdrbox_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/imgreg_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/imgsock_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/index_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/j2kheader_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/jp2k_decoder.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/jp2k_encoder.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/jpip_parser.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/jpipstream_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/manfbox_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/marker_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/metadata_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/mhixbox_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/msgqueue_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/openjpip.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/placeholder_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/query_parser.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/session_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/sock_manager.c \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip/target_manager.c \

include $(BUILD_STATIC_LIBRARY)
#libopenjpeg--------------------------------------------------------------------



#libtiff +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := libtiff
LOCAL_MODULE_FILENAME := libtiffobj

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES :=  \
    $(TIFF_SRC_PATH) \
    $(JPEG_SRC_PATH) \
    $(LZMA_SRC_PATH)liblzma/api

LOCAL_CFLAGS := \
    -DLZMA_SUPPORT=1

LOCAL_SRC_FILES := \
    $(TIFF_SRC_PATH)mkg3states.c \
    $(TIFF_SRC_PATH)tif_aux.c \
    $(TIFF_SRC_PATH)tif_close.c \
    $(TIFF_SRC_PATH)tif_codec.c \
    $(TIFF_SRC_PATH)tif_color.c \
    $(TIFF_SRC_PATH)tif_compress.c \
    $(TIFF_SRC_PATH)tif_dir.c \
    $(TIFF_SRC_PATH)tif_dirinfo.c \
    $(TIFF_SRC_PATH)tif_dirread.c \
    $(TIFF_SRC_PATH)tif_dirwrite.c \
    $(TIFF_SRC_PATH)tif_dumpmode.c \
    $(TIFF_SRC_PATH)tif_error.c \
    $(TIFF_SRC_PATH)tif_extension.c \
    $(TIFF_SRC_PATH)tif_fax3.c \
    $(TIFF_SRC_PATH)tif_fax3sm.c \
    $(TIFF_SRC_PATH)tif_flush.c \
    $(TIFF_SRC_PATH)tif_getimage.c \
    $(TIFF_SRC_PATH)tif_jbig.c \
    $(TIFF_SRC_PATH)tif_jpeg.c \
    $(TIFF_SRC_PATH)tif_jpeg_12.c \
    $(TIFF_SRC_PATH)tif_luv.c \
    $(TIFF_SRC_PATH)tif_lzma.c \
    $(TIFF_SRC_PATH)tif_lzw.c \
    $(TIFF_SRC_PATH)tif_next.c \
    $(TIFF_SRC_PATH)tif_ojpeg.c \
    $(TIFF_SRC_PATH)tif_open.c \
    $(TIFF_SRC_PATH)tif_packbits.c \
    $(TIFF_SRC_PATH)tif_pixarlog.c \
    $(TIFF_SRC_PATH)tif_predict.c \
    $(TIFF_SRC_PATH)tif_print.c \
    $(TIFF_SRC_PATH)tif_read.c \
    $(TIFF_SRC_PATH)tif_strip.c \
    $(TIFF_SRC_PATH)tif_swab.c \
    $(TIFF_SRC_PATH)tif_thunder.c \
    $(TIFF_SRC_PATH)tif_tile.c \
    $(TIFF_SRC_PATH)tif_version.c \
    $(TIFF_SRC_PATH)tif_warning.c \
    $(TIFF_SRC_PATH)tif_webp.c \
    $(TIFF_SRC_PATH)tif_write.c \
    $(TIFF_SRC_PATH)tif_zip.c \
    $(TIFF_SRC_PATH)tif_zstd.c \
    $(TIFF_SRC_PATH)tif_unix.c \
    $(TIFF_SRC_PATH)../port/lfind.c


LOCAL_STATIC_LIBRARIES := \
    liblzma

include $(BUILD_STATIC_LIBRARY)
#libtiff ---------------------------------------------------------------

#libpng ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := libpng
LOCAL_MODULE_FILENAME := libpngobj

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

# only enable NEON for supported CPUs
# 32-bit NEON supports asm mode
# but not all armeabi-v7a supports NEON, we need to do a NEON check for safety
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    LOCAL_CFLAGS := \
        -DPNG_ARM_NEON_OPT=2 \
        -DPNG_ARM_NEON_CHECK_SUPPORTED \
        -DPNG_ARM_NEON_FILE=\"contrib/arm-neon/android-ndk.c\"

    LOCAL_SRC_FILES := $(PNG_SRC_PATH)arm/filter_neon.S.neon
endif # TARGET_ARCH_ABI == armeabi-v7a

# 64-bit only supports intrinsics
# no NEON check needed, all arm64-v8a supports NEON
ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
    LOCAL_CFLAGS := \
        -DPNG_ARM_NEON_OPT=1 \
        -D__ARM_NEON__

    LOCAL_SRC_FILES := $(PNG_SRC_PATH)arm/filter_neon_intrinsics.c
    LOCAL_SRC_FILES += $(PNG_SRC_PATH)arm/palette_neon_intrinsics.c
endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_C_INCLUDES := $(PNG_SRC_PATH)

LOCAL_SRC_FILES += \
    $(PNG_SRC_PATH)pngerror.c \
    $(PNG_SRC_PATH)pngwio.c \
    $(PNG_SRC_PATH)pngwrite.c \
    $(PNG_SRC_PATH)pngwutil.c \
    $(PNG_SRC_PATH)pngwtran.c \
    $(PNG_SRC_PATH)pngset.c \
    $(PNG_SRC_PATH)pngtrans.c \
    $(PNG_SRC_PATH)png.c \
    $(PNG_SRC_PATH)pngrtran.c \
    $(PNG_SRC_PATH)pngmem.c \
    $(PNG_SRC_PATH)pngpread.c \
    $(PNG_SRC_PATH)pngrutil.c \
    $(PNG_SRC_PATH)pngget.c \
    $(PNG_SRC_PATH)pngread.c \
    $(PNG_SRC_PATH)pngrio.c \
    $(PNG_SRC_PATH)pngtest.c

# cpu checks required only with armeabi-v7a
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    LOCAL_STATIC_LIBRARIES := cpufeatures
endif


# config for both NEON archs
ifneq (,$(filter $(TARGET_ARCH_ABI),armeabi-v7a arm64-v8a))
    LOCAL_SRC_FILES += $(PNG_SRC_PATH)arm/arm_init.c

    # do a NEON compilation
    LOCAL_ARM_NEON := true
endif


include $(BUILD_STATIC_LIBRARY)
# cpu checks required only with armeabi-v7a
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    # include cpu features for NEON API check
    $(call import-module,android/cpufeatures)
endif
#libpng ----------------------------------------------------------------


#libfreetype 2-----------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE    := libfreetype2

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := \
    -DANDROID_NDK \
    -DFT2_BUILD_LIBRARY=1

LOCAL_C_INCLUDES := \
    $(FREETYPE_SRC_PATH)include \
    $(FREETYPE_SRC_PATH)src \
    $(PNG_SRC_PATH)


LOCAL_SRC_FILES += \
    $(FREETYPE_SRC_PATH)src/base/ftbbox.c \
    $(FREETYPE_SRC_PATH)src/base/ftbitmap.c \
    $(FREETYPE_SRC_PATH)src/base/ftfntfmt.c \
    $(FREETYPE_SRC_PATH)src/base/ftfstype.c \
    $(FREETYPE_SRC_PATH)src/base/ftglyph.c \
    $(FREETYPE_SRC_PATH)src/base/ftlcdfil.c \
    $(FREETYPE_SRC_PATH)src/base/ftstroke.c \
    $(FREETYPE_SRC_PATH)src/base/fttype1.c \
    $(FREETYPE_SRC_PATH)src/base/ftbase.c \
    $(FREETYPE_SRC_PATH)src/base/ftsystem.c \
    $(FREETYPE_SRC_PATH)src/base/ftinit.c \
    $(FREETYPE_SRC_PATH)src/base/ftgasp.c \
    $(FREETYPE_SRC_PATH)src/base/ftmm.c \
    $(FREETYPE_SRC_PATH)src/gzip/ftgzip.c \
    $(FREETYPE_SRC_PATH)src/raster/raster.c \
    $(FREETYPE_SRC_PATH)src/sfnt/sfnt.c \
    $(FREETYPE_SRC_PATH)src/smooth/smooth.c \
    $(FREETYPE_SRC_PATH)src/autofit/autofit.c \
    $(FREETYPE_SRC_PATH)src/truetype/truetype.c \
    $(FREETYPE_SRC_PATH)src/cff/cff.c \
    $(FREETYPE_SRC_PATH)src/psnames/psnames.c \
    $(FREETYPE_SRC_PATH)src/pshinter/pshinter.c \
    $(FREETYPE_SRC_PATH)src/psaux/psaux.c \
    $(FREETYPE_SRC_PATH)src/type1/type1.c \
    $(FREETYPE_SRC_PATH)src/cid/type1cid.c \

ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS := -ldl -llog
endif

include $(BUILD_STATIC_LIBRARY)

#libreetype 2-----------------------------------------------------------


#libwebp ---------------------------------------------------------------

WEBP_CFLAGS := -Wall -DANDROID -DHAVE_MALLOC_H -DHAVE_PTHREAD -DWEBP_USE_THREAD
WEBP_CFLAGS += -fvisibility=hidden

ifeq ($(APP_OPTIM),release)
  WEBP_CFLAGS += -finline-functions -ffast-math \
                 -ffunction-sections -fdata-sections
  ifeq ($(findstring clang,$(NDK_TOOLCHAIN_VERSION)),)
    WEBP_CFLAGS += -frename-registers -s
  endif
endif

# mips32 fails to build with clang from r14b
# https://bugs.chromium.org/p/webp/issues/detail?id=343
ifeq ($(findstring clang,$(NDK_TOOLCHAIN_VERSION)),clang)
  ifeq ($(TARGET_ARCH),mips)
    clang_version := $(shell $(TARGET_CC) --version)
    ifneq ($(findstring clang version 3,$(clang_version)),)
      WEBP_CFLAGS += -no-integrated-as
    endif
  endif
endif

ifneq ($(findstring armeabi-v7a, $(TARGET_ARCH_ABI)),)
  # Setting LOCAL_ARM_NEON will enable -mfpu=neon which may cause illegal
  # instructions to be generated for armv7a code. Instead target the neon code
  # specifically.
  NEON := c.neon
  USE_CPUFEATURES := yes
  WEBP_CFLAGS += -DHAVE_CPU_FEATURES_H
else
  NEON := c
endif

dec_srcs := \
    $(WEBP_SRC_PATH)src/dec/alpha_dec.c \
    $(WEBP_SRC_PATH)src/dec/buffer_dec.c \
    $(WEBP_SRC_PATH)src/dec/frame_dec.c \
    $(WEBP_SRC_PATH)src/dec/idec_dec.c \
    $(WEBP_SRC_PATH)src/dec/io_dec.c \
    $(WEBP_SRC_PATH)src/dec/quant_dec.c \
    $(WEBP_SRC_PATH)src/dec/tree_dec.c \
    $(WEBP_SRC_PATH)src/dec/vp8_dec.c \
    $(WEBP_SRC_PATH)src/dec/vp8l_dec.c \
    $(WEBP_SRC_PATH)src/dec/webp_dec.c \

demux_srcs := \
    $(WEBP_SRC_PATH)src/demux/anim_decode.c \
    $(WEBP_SRC_PATH)src/demux/demux.c \

dsp_dec_srcs := \
    $(WEBP_SRC_PATH)src/dsp/alpha_processing.c \
    $(WEBP_SRC_PATH)src/dsp/alpha_processing_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/alpha_processing_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/alpha_processing_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/alpha_processing_sse41.c \
    $(WEBP_SRC_PATH)src/dsp/cpu.c \
    $(WEBP_SRC_PATH)src/dsp/dec.c \
    $(WEBP_SRC_PATH)src/dsp/dec_clip_tables.c \
    $(WEBP_SRC_PATH)src/dsp/dec_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/dec_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/dec_msa.c \
    $(WEBP_SRC_PATH)src/dsp/dec_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/dec_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/dec_sse41.c \
    $(WEBP_SRC_PATH)src/dsp/filters.c \
    $(WEBP_SRC_PATH)src/dsp/filters_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/filters_msa.c \
    $(WEBP_SRC_PATH)src/dsp/filters_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/filters_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/lossless.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_msa.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/lossless_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/rescaler.c \
    $(WEBP_SRC_PATH)src/dsp/rescaler_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/rescaler_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/rescaler_msa.c \
    $(WEBP_SRC_PATH)src/dsp/rescaler_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/rescaler_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/upsampling.c \
    $(WEBP_SRC_PATH)src/dsp/upsampling_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/upsampling_msa.c \
    $(WEBP_SRC_PATH)src/dsp/upsampling_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/upsampling_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/upsampling_sse41.c \
    $(WEBP_SRC_PATH)src/dsp/yuv.c \
    $(WEBP_SRC_PATH)src/dsp/yuv_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/yuv_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/yuv_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/yuv_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/yuv_sse41.c \

dsp_enc_srcs := \
    $(WEBP_SRC_PATH)src/dsp/cost.c \
    $(WEBP_SRC_PATH)src/dsp/cost_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/cost_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/cost_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/cost_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/enc.c \
    $(WEBP_SRC_PATH)src/dsp/enc_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/enc_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/enc_msa.c \
    $(WEBP_SRC_PATH)src/dsp/enc_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/enc_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/enc_sse41.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_mips32.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_mips_dsp_r2.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_msa.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_neon.$(NEON) \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_sse2.c \
    $(WEBP_SRC_PATH)src/dsp/lossless_enc_sse41.c \
    $(WEBP_SRC_PATH)src/dsp/ssim.c \
    $(WEBP_SRC_PATH)src/dsp/ssim_sse2.c \

enc_srcs := \
    $(WEBP_SRC_PATH)src/enc/alpha_enc.c \
    $(WEBP_SRC_PATH)src/enc/analysis_enc.c \
    $(WEBP_SRC_PATH)src/enc/backward_references_cost_enc.c \
    $(WEBP_SRC_PATH)src/enc/backward_references_enc.c \
    $(WEBP_SRC_PATH)src/enc/config_enc.c \
    $(WEBP_SRC_PATH)src/enc/cost_enc.c \
    $(WEBP_SRC_PATH)src/enc/filter_enc.c \
    $(WEBP_SRC_PATH)src/enc/frame_enc.c \
    $(WEBP_SRC_PATH)src/enc/histogram_enc.c \
    $(WEBP_SRC_PATH)src/enc/iterator_enc.c \
    $(WEBP_SRC_PATH)src/enc/near_lossless_enc.c \
    $(WEBP_SRC_PATH)src/enc/picture_enc.c \
    $(WEBP_SRC_PATH)src/enc/picture_csp_enc.c \
    $(WEBP_SRC_PATH)src/enc/picture_psnr_enc.c \
    $(WEBP_SRC_PATH)src/enc/picture_rescale_enc.c \
    $(WEBP_SRC_PATH)src/enc/picture_tools_enc.c \
    $(WEBP_SRC_PATH)src/enc/predictor_enc.c \
    $(WEBP_SRC_PATH)src/enc/quant_enc.c \
    $(WEBP_SRC_PATH)src/enc/syntax_enc.c \
    $(WEBP_SRC_PATH)src/enc/token_enc.c \
    $(WEBP_SRC_PATH)src/enc/tree_enc.c \
    $(WEBP_SRC_PATH)src/enc/vp8l_enc.c \
    $(WEBP_SRC_PATH)src/enc/webp_enc.c \

mux_srcs := \
    $(WEBP_SRC_PATH)src/mux/anim_encode.c \
    $(WEBP_SRC_PATH)src/mux/muxedit.c \
    $(WEBP_SRC_PATH)src/mux/muxinternal.c \
    $(WEBP_SRC_PATH)src/mux/muxread.c \

utils_dec_srcs := \
    $(WEBP_SRC_PATH)src/utils/bit_reader_utils.c \
    $(WEBP_SRC_PATH)src/utils/color_cache_utils.c \
    $(WEBP_SRC_PATH)src/utils/filters_utils.c \
    $(WEBP_SRC_PATH)src/utils/huffman_utils.c \
    $(WEBP_SRC_PATH)src/utils/quant_levels_dec_utils.c \
    $(WEBP_SRC_PATH)src/utils/random_utils.c \
    $(WEBP_SRC_PATH)src/utils/rescaler_utils.c \
    $(WEBP_SRC_PATH)src/utils/thread_utils.c \
    $(WEBP_SRC_PATH)src/utils/utils.c \

utils_enc_srcs := \
    $(WEBP_SRC_PATH)src/utils/bit_writer_utils.c \
    $(WEBP_SRC_PATH)src/utils/huffman_encode_utils.c \
    $(WEBP_SRC_PATH)src/utils/quant_levels_utils.c \

################################################################################
# libwebpdecoder

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    $(dec_srcs) \
    $(dsp_dec_srcs) \
    $(utils_dec_srcs) \

LOCAL_CFLAGS := $(WEBP_CFLAGS)
LOCAL_EXPORT_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

ifeq ($(USE_CPUFEATURES),yes)
  LOCAL_STATIC_LIBRARIES := cpufeatures
endif

LOCAL_MODULE := webpdecoder_static

include $(BUILD_STATIC_LIBRARY)

################################################################################

################################################################################
# libwebp

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebp

LOCAL_SRC_FILES := \
    $(dsp_enc_srcs) \
    $(enc_srcs) \
    $(utils_enc_srcs) \

LOCAL_CFLAGS := $(WEBP_CFLAGS)
LOCAL_EXPORT_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_WHOLE_STATIC_LIBRARIES := webpdecoder_static


include $(BUILD_STATIC_LIBRARY)


#################################################################################

################################################################################
# libwebpmux

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(mux_srcs)

LOCAL_CFLAGS := $(WEBP_CFLAGS)
LOCAL_EXPORT_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_SRC_PATH)src \
    $(WEBP_SRC_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_MODULE := libwebpmux

LOCAL_STATIC_LIBRARIES := libwebp
include $(BUILD_STATIC_LIBRARY)

################################################################################

ifeq ($(USE_CPUFEATURES),yes)
  $(call import-module,android/cpufeatures)
endif

#libwebp ---------------------------------------------------------------


#libfftw---------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE := libfftw3

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm


LOCAL_C_INCLUDES := \
        $(FFTW_SRC_PATH) \
        $(FFTW_SRC_PATH)api \
		$(FFTW_SRC_PATH)dft \
        $(FFTW_SRC_PATH)dft/scalar \
        $(FFTW_SRC_PATH)dft/scalar/codelets \
        $(FFTW_SRC_PATH)kernel \
        $(FFTW_SRC_PATH)libbench2 \
        $(FFTW_SRC_PATH)rdft \
		$(FFTW_SRC_PATH)rdft/scalar \
        $(FFTW_SRC_PATH)rdft/scalar/r2cb \
        $(FFTW_SRC_PATH)rdft/scalar/r2r \
        $(FFTW_SRC_PATH)rdft/scalar/r2cf \
		$(FFTW_SRC_PATH)reodft \
        $(FFTW_SRC_PATH)simd-support \
        $(FFTW_SRC_PATH)dft/simd \
        $(FFTW_SRC_PATH)rdft/simd \



ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_SRC_PATH)configs/arm64
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)configs/arm64
    
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)dft/simd/neon
    include $(FFTW_SRC_PATH)dft/simd/neon/sources.mk
    include $(FFTW_SRC_PATH)rdft/simd/neon/sources.mk
    
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)  
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_SRC_PATH)configs/arm
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)configs/arm
    
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)dft/simd/neon
    include $(FFTW_SRC_PATH)dft/simd/neon/sources.mk
    include $(FFTW_SRC_PATH)rdft/simd/neon/sources.mk
    
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_SRC_PATH)configs/x86
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)configs/x86
    
    LOCAL_C_INCLUDES += \
        $(FFTW_SRC_PATH)dft/simd/altivec \
        $(FFTW_SRC_PATH)dft/simd/avx \
        $(FFTW_SRC_PATH)dft/simd/avx-128-fma \
        $(FFTW_SRC_PATH)dft/simd/avx2 \
        $(FFTW_SRC_PATH)dft/simd/avx2-128 \
        $(FFTW_SRC_PATH)dft/simd/avx512 \
        $(FFTW_SRC_PATH)dft/simd/common \
        $(FFTW_SRC_PATH)dft/simd/generic-simd128 \
        $(FFTW_SRC_PATH)dft/simd/generic-simd256 \
        $(FFTW_SRC_PATH)dft/simd/kcvi \
        $(FFTW_SRC_PATH)dft/simd/sse2 \
        $(FFTW_SRC_PATH)dft/simd/vsx \
        $(FFTW_SRC_PATH)rdft/simd/altivec \
        $(FFTW_SRC_PATH)rdft/simd/avx \
        $(FFTW_SRC_PATH)rdft/simd/avx-128-fma \
        $(FFTW_SRC_PATH)rdft/simd/avx2 \
        $(FFTW_SRC_PATH)rdft/simd/avx2-128 \
        $(FFTW_SRC_PATH)rdft/simd/avx512 \
        $(FFTW_SRC_PATH)rdft/simd/common \
        $(FFTW_SRC_PATH)rdft/simd/generic-simd128 \
        $(FFTW_SRC_PATH)rdft/simd/generic-simd256 \
        $(FFTW_SRC_PATH)rdft/simd/kcvi \
        $(FFTW_SRC_PATH)rdft/simd/neon \
        $(FFTW_SRC_PATH)rdft/simd/sse2 \
        $(FFTW_SRC_PATH)rdft/simd/vsx \
    
        include $(FFTW_SRC_PATH)dft/simd/altivec/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx-128-fma/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx2/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx2-128/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx512/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/common/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/generic-simd128/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/generic-simd256/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/kcvi/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/sse2/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/vsx/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/altivec/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx-128-fma/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx2/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx2-128/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx512/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/common/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/generic-simd128/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/generic-simd256/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/kcvi/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/sse2/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/vsx/sources.mk
    
else ifeq ($(TARGET_ARCH_ABI),x86_64)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_SRC_PATH)configs/x86-64
    LOCAL_C_INCLUDES += $(FFTW_SRC_PATH)configs/x86-64
    
    ifneq ($(STATIC_BUILD),true)
        LOCAL_LDFLAGS += -latomic
    endif
    
    LOCAL_C_INCLUDES += \
        $(FFTW_SRC_PATH)dft/simd/altivec \
        $(FFTW_SRC_PATH)dft/simd/avx \
        $(FFTW_SRC_PATH)dft/simd/avx-128-fma \
        $(FFTW_SRC_PATH)dft/simd/avx2 \
        $(FFTW_SRC_PATH)dft/simd/avx2-128 \
        $(FFTW_SRC_PATH)dft/simd/avx512 \
        $(FFTW_SRC_PATH)dft/simd/common \
        $(FFTW_SRC_PATH)dft/simd/generic-simd128 \
        $(FFTW_SRC_PATH)dft/simd/generic-simd256 \
        $(FFTW_SRC_PATH)dft/simd/kcvi \
        $(FFTW_SRC_PATH)dft/simd/sse2 \
        $(FFTW_SRC_PATH)dft/simd/vsx \
        $(FFTW_SRC_PATH)rdft/simd/altivec \
        $(FFTW_SRC_PATH)rdft/simd/avx \
        $(FFTW_SRC_PATH)rdft/simd/avx-128-fma \
        $(FFTW_SRC_PATH)rdft/simd/avx2 \
        $(FFTW_SRC_PATH)rdft/simd/avx2-128 \
        $(FFTW_SRC_PATH)rdft/simd/avx512 \
        $(FFTW_SRC_PATH)rdft/simd/common \
        $(FFTW_SRC_PATH)rdft/simd/generic-simd128 \
        $(FFTW_SRC_PATH)rdft/simd/generic-simd256 \
        $(FFTW_SRC_PATH)rdft/simd/kcvi \
        $(FFTW_SRC_PATH)rdft/simd/neon \
        $(FFTW_SRC_PATH)rdft/simd/sse2 \
        $(FFTW_SRC_PATH)rdft/simd/vsx \
    
        include $(FFTW_SRC_PATH)dft/simd/altivec/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx-128-fma/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx2/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx2-128/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/avx512/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/common/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/generic-simd128/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/generic-simd256/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/kcvi/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/sse2/sources.mk
        include $(FFTW_SRC_PATH)dft/simd/vsx/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/altivec/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx-128-fma/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx2/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx2-128/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/avx512/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/common/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/generic-simd128/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/generic-simd256/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/kcvi/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/sse2/sources.mk
        include $(FFTW_SRC_PATH)rdft/simd/vsx/sources.mk
    
endif


include $(FFTW_SRC_PATH)api/sources.mk
include $(FFTW_SRC_PATH)dft/sources.mk
include $(FFTW_SRC_PATH)dft/scalar/sources.mk
include $(FFTW_SRC_PATH)dft/scalar/codelets/sources.mk
include $(FFTW_SRC_PATH)kernel/sources.mk
include $(FFTW_SRC_PATH)libbench2/sources.mk
include $(FFTW_SRC_PATH)rdft/sources.mk
include $(FFTW_SRC_PATH)rdft/scalar/sources.mk
include $(FFTW_SRC_PATH)rdft/scalar/r2cb/sources.mk
include $(FFTW_SRC_PATH)rdft/scalar/r2cf/sources.mk
include $(FFTW_SRC_PATH)rdft/scalar/r2r/sources.mk
include $(FFTW_SRC_PATH)reodft/sources.mk
include $(FFTW_SRC_PATH)simd-support/sources.mk


include $(BUILD_STATIC_LIBRARY)

#libfftw---------------------------------------------------------------


#libxml2---------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE := libxml2

LOCAL_CFLAGS := \
    -DLIBXML_THREAD_ENABLED=1 \
    -DLIBXML_ICU_ENABLED=YES \
    -D__ANDROID__ \
    -DLIBXML_ICONV_ENABLED=YES \
    -DLIBXML_LEGACY_ENABLED=NO \
    -DLIBXML_FTP_ENABLED=NO \
    -DLIBXML_HTML_ENABLED=NO \
    -DLIBXML_HTTP_ENABLED=NO \
    -DLIBXML_LZMA_ENABLED=NO \
    -DLIBXML_ZLIB_ENABLED=NO \
    -Wall \
    -Werror \
    -Wno-error=ignored-attributes \
    -Wno-missing-field-initializers \
    -Wno-self-assign \
    -Wno-sign-compare \
    -Wno-tautological-pointer-compare \
    -Wno-unused-function \
    -Wno-unused-parameter \

ifeq ($(STATIC_BUILD),true)
    LOCAL_CFLAGS += -DSTATIC_LIBXML=1
endif

LOCAL_C_INCLUDES := \
    $(XML2_SRC_PATH) \
    $(XML2_SRC_PATH)include \
    $(ICONV_SRC_PATH) \
    $(ICONV_SRC_PATH)include \
    $(ICONV_SRC_PATH)lib \
    $(ICONV_SRC_PATH)libcharset \
    $(ICONV_SRC_PATH)libcharset/include \
    $(ICU_SRC_PATH) \
    $(ICU_SRC_PATH)common \
    $(ICU_SRC_PATH)i18n \
    $(ICU_SRC_PATH)common/unicode \
    $(ICU_SRC_PATH)i18n/unicode \
    $(LZMA_SRC_PATH)liblzma/api
LOCAL_EXPORT_C_INCLUDES := \
    $(XML2_SRC_PATH) \
    $(XML2_SRC_PATH)include \
    $(ICONV_SRC_PATH) \
    $(ICONV_SRC_PATH)include \
    $(ICONV_SRC_PATH)lib \
    $(ICONV_SRC_PATH)libcharset \
    $(ICONV_SRC_PATH)libcharset/include \
    $(ICU_SRC_PATH) \
    $(ICU_SRC_PATH)common \
    $(ICU_SRC_PATH)i18n \
    $(ICU_SRC_PATH)common/unicode \
    $(ICU_SRC_PATH)i18n/unicode \
    $(LZMA_SRC_PATH)liblzma/api

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
    $(XML2_SRC_PATH)SAX.c \
    $(XML2_SRC_PATH)entities.c \
    $(XML2_SRC_PATH)encoding.c \
    $(XML2_SRC_PATH)error.c \
    $(XML2_SRC_PATH)parserInternals.c \
    $(XML2_SRC_PATH)parser.c \
    $(XML2_SRC_PATH)tree.c \
    $(XML2_SRC_PATH)hash.c \
    $(XML2_SRC_PATH)list.c \
    $(XML2_SRC_PATH)xmlIO.c \
    $(XML2_SRC_PATH)xmlmemory.c \
    $(XML2_SRC_PATH)uri.c \
    $(XML2_SRC_PATH)valid.c \
    $(XML2_SRC_PATH)xlink.c \
    $(XML2_SRC_PATH)debugXML.c \
    $(XML2_SRC_PATH)xpath.c \
    $(XML2_SRC_PATH)xpointer.c \
    $(XML2_SRC_PATH)xinclude.c \
    $(XML2_SRC_PATH)DOCBparser.c \
    $(XML2_SRC_PATH)catalog.c \
    $(XML2_SRC_PATH)globals.c \
    $(XML2_SRC_PATH)threads.c \
    $(XML2_SRC_PATH)c14n.c \
    $(XML2_SRC_PATH)xmlstring.c \
    $(XML2_SRC_PATH)buf.c \
    $(XML2_SRC_PATH)xmlregexp.c \
    $(XML2_SRC_PATH)xmlschemas.c \
    $(XML2_SRC_PATH)xmlschemastypes.c \
    $(XML2_SRC_PATH)xmlunicode.c \
    $(XML2_SRC_PATH)xmlreader.c \
    $(XML2_SRC_PATH)relaxng.c \
    $(XML2_SRC_PATH)dict.c \
    $(XML2_SRC_PATH)SAX2.c \
    $(XML2_SRC_PATH)xmlwriter.c \
    $(XML2_SRC_PATH)legacy.c \
    $(XML2_SRC_PATH)chvalid.c \
    $(XML2_SRC_PATH)pattern.c \
    $(XML2_SRC_PATH)xmlsave.c \
    $(XML2_SRC_PATH)xmlmodule.c \
    $(XML2_SRC_PATH)schematron.c \

LOCAL_STATIC_LIBRARIES := \
    libiconv \
    libicuuc \
    libicui18n \
    liblzma


include $(BUILD_STATIC_LIBRARY)
#libxml2---------------------------------------------------------------


#liblzma -------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE := liblzma

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
    $(LZMA_SRC_PATH) \
    $(LZMA_SRC_PATH)liblzma/api \
    $(LZMA_SRC_PATH)liblzma/common \
    $(LZMA_SRC_PATH)liblzma \
    $(LZMA_SRC_PATH)liblzma/lz \
    $(LZMA_SRC_PATH)liblzma/rangecoder \
    $(LZMA_SRC_PATH)liblzma/delta \
    $(LZMA_SRC_PATH)liblzma/simple \
    $(LZMA_SRC_PATH)liblzma/check \
    $(LZMA_SRC_PATH)liblzma/lzma \
    $(LZMA_SRC_PATH)common \
    $(ICONV_SRC_PATH) \
    $(ICONV_SRC_PATH)include \
    $(ICONV_SRC_PATH)lib \
    $(ICONV_SRC_PATH)libcharset \
    $(ICONV_SRC_PATH)libcharset/include \
    $(ICONV_SRC_PATH)srclib

LOCAL_CFLAGS := \
    -DTUKLIB_SYMBOL_PREFIX=lzma_ \
    -DHAVE_CONFIG_H

LOCAL_SRC_FILES := \
    $(LZMA_SRC_PATH)common/tuklib_physmem.c \
    $(LZMA_SRC_PATH)common/tuklib_cpucores.c \
    $(LZMA_SRC_PATH)liblzma/common/common.c \
    $(LZMA_SRC_PATH)liblzma/common/block_util.c \
    $(LZMA_SRC_PATH)liblzma/common/easy_preset.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_common.c \
    $(LZMA_SRC_PATH)liblzma/common/hardware_physmem.c \
    $(LZMA_SRC_PATH)liblzma/common/index.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_flags_common.c \
    $(LZMA_SRC_PATH)liblzma/common/vli_size.c \
    $(LZMA_SRC_PATH)liblzma/common/hardware_cputhreads.c \
    $(LZMA_SRC_PATH)liblzma/common/alone_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_buffer_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_header_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/easy_buffer_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/easy_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/easy_encoder_memusage.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_buffer_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_flags_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/index_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_buffer_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_flags_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/vli_encoder.c \
    $(LZMA_SRC_PATH)liblzma/common/outqueue.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_encoder_mt.c \
    $(LZMA_SRC_PATH)liblzma/common/alone_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/auto_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_buffer_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/block_header_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/easy_decoder_memusage.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_buffer_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/filter_flags_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/index_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/index_hash.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_buffer_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/stream_flags_decoder.c \
    $(LZMA_SRC_PATH)liblzma/common/vli_decoder.c \
    $(LZMA_SRC_PATH)liblzma/check/check.c \
    $(LZMA_SRC_PATH)liblzma/check/crc32_table.c \
    $(LZMA_SRC_PATH)liblzma/check/crc32_fast.c \
    $(LZMA_SRC_PATH)liblzma/check/crc64_table.c \
    $(LZMA_SRC_PATH)liblzma/check/crc64_fast.c \
    $(LZMA_SRC_PATH)liblzma/check/sha256.c \
    $(LZMA_SRC_PATH)liblzma/lz/lz_encoder.c \
    $(LZMA_SRC_PATH)liblzma/lz/lz_encoder_mf.c \
    $(LZMA_SRC_PATH)liblzma/lz/lz_decoder.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma_encoder_presets.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma_encoder.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma_encoder_optimum_fast.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma_encoder_optimum_normal.c \
    $(LZMA_SRC_PATH)liblzma/lzma/fastpos_table.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma_decoder.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma2_encoder.c \
    $(LZMA_SRC_PATH)liblzma/lzma/lzma2_decoder.c \
    $(LZMA_SRC_PATH)liblzma/rangecoder/price_table.c \
    $(LZMA_SRC_PATH)liblzma/delta/delta_common.c \
    $(LZMA_SRC_PATH)liblzma/delta/delta_encoder.c \
    $(LZMA_SRC_PATH)liblzma/delta/delta_decoder.c \
    $(LZMA_SRC_PATH)liblzma/simple/simple_coder.c \
    $(LZMA_SRC_PATH)liblzma/simple/simple_encoder.c \
    $(LZMA_SRC_PATH)liblzma/simple/simple_decoder.c \
    $(LZMA_SRC_PATH)liblzma/simple/x86.c \
    $(LZMA_SRC_PATH)liblzma/simple/powerpc.c \
    $(LZMA_SRC_PATH)liblzma/simple/ia64.c \
    $(LZMA_SRC_PATH)liblzma/simple/arm.c \
    $(LZMA_SRC_PATH)liblzma/simple/armthumb.c \
    $(LZMA_SRC_PATH)liblzma/simple/sparc.c \

LOCAL_STATIC_LIBRARIES := \
    libiconv

include $(BUILD_STATIC_LIBRARY)
#liblzma------------------------------------------------------------------S

#libiconv ----------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE    := libiconv

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := \
    -Wno-multichar \
    -Wno-parentheses-equality \
    -DLIBDIR=\"c\" \
    -D_ANDROID \
    -DBUILDING_LIBICONV \
    -DIN_LIBRARY \
    -DENABLE_RELOCATABLE

LOCAL_C_INCLUDES := \
    $(ICONV_SRC_PATH) \
    $(ICONV_SRC_PATH)include \
    $(ICONV_SRC_PATH)lib \
    $(ICONV_SRC_PATH)libcharset \
    $(ICONV_SRC_PATH)libcharset/include \
    $(ICONV_SRC_PATH)srclib

LOCAL_SRC_FILES := \
    $(ICONV_SRC_PATH)lib/iconv.c \
    $(ICONV_SRC_PATH)lib/relocatable.c \
    $(ICONV_SRC_PATH)libcharset/lib/localcharset.c

include $(BUILD_STATIC_LIBRARY)

#libiconv ----------------------------------------------------------


#libicuuc---------------------------------------------------------------
include libicuuc.mk
#----------------------------------------------------------------



#libbzlib----------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_MODULE    := libbz2

LOCAL_C_INCLUDES := \
    $(BZLIB_SRC_PATH)

LOCAL_SRC_FILES := \
    $(BZLIB_SRC_PATH)blocksort.c \
    $(BZLIB_SRC_PATH)bzlib.c \
    $(BZLIB_SRC_PATH)compress.c \
    $(BZLIB_SRC_PATH)crctable.c \
    $(BZLIB_SRC_PATH)decompress.c \
    $(BZLIB_SRC_PATH)huffman.c \
    $(BZLIB_SRC_PATH)randtable.c \

include $(BUILD_STATIC_LIBRARY)

#libbzlb-----------------------------------------------------------


#Image Magick dynamic +++++++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := libmagickcore-7
#LOCAL_CFLAGS += -fopenmp
# ignored in static library builds
#LOCAL_LDFLAGS += -fopenmp

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  := \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)MagickCore \
    $(PNG_SRC_PATH) \
    $(JPEG_SRC_PATH) \
    $(TIFF_SRC_PATH) \
    $(FREETYPE_SRC_PATH)include \
    $(FREETYPE_SRC_PATH)src \
    $(FREETYPE_SRC_PATH) \
    $(OPENJPEG_SRC_PATH)src/lib/openjp2 \
    $(OPENJPEG_SRC_PATH)src/lib/openjpip \
    $(OPENJPEG_SRC_PATH)config \
    $(FFTW_SRC_PATH)/api \
    $(XML2_INCLUDE_PATH) \
    $(XML2_INCLUDE_PATH)include \
    $(LZMA_SRC_PATH)liblzma/api \
    $(BZLIB_SRC_PATH)


ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)configs/arm64
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)configs/arm64
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)  
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)configs/arm
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)configs/arm
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)configs/x86
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)configs/x86
else ifeq ($(TARGET_ARCH_ABI),x86_64)
    LOCAL_EXPORT_C_INCLUDES += $(IMAGE_MAGICK)configs/x86-64
    LOCAL_C_INCLUDES += $(IMAGE_MAGICK)configs/x86-64
    
    ifneq ($(STATIC_BUILD),true)
        LOCAL_LDFLAGS += -latomic
    endif
    
endif

ifneq ($(STATIC_BUILD),true)
# ignored in static library builds
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif

LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)coders/aai.c \
    $(IMAGE_MAGICK)coders/art.c \
    $(IMAGE_MAGICK)coders/avs.c \
    $(IMAGE_MAGICK)coders/bgr.c \
    $(IMAGE_MAGICK)coders/bmp.c \
    $(IMAGE_MAGICK)coders/braille.c \
    $(IMAGE_MAGICK)coders/cals.c \
    $(IMAGE_MAGICK)coders/caption.c \
    $(IMAGE_MAGICK)coders/cin.c \
    $(IMAGE_MAGICK)coders/cip.c \
    $(IMAGE_MAGICK)coders/clip.c \
    $(IMAGE_MAGICK)coders/clipboard.c \
    $(IMAGE_MAGICK)coders/cmyk.c \
    $(IMAGE_MAGICK)coders/cut.c \
    $(IMAGE_MAGICK)coders/cube.c \
    $(IMAGE_MAGICK)coders/dcm.c \
    $(IMAGE_MAGICK)coders/dds.c \
    $(IMAGE_MAGICK)coders/debug.c \
    $(IMAGE_MAGICK)coders/dib.c \
    $(IMAGE_MAGICK)coders/dng.c \
    $(IMAGE_MAGICK)coders/dps.c \
    $(IMAGE_MAGICK)coders/dpx.c \
    $(IMAGE_MAGICK)coders/emf.c \
    $(IMAGE_MAGICK)coders/ept.c \
    $(IMAGE_MAGICK)coders/exr.c \
    $(IMAGE_MAGICK)coders/fax.c \
    $(IMAGE_MAGICK)coders/fits.c \
    $(IMAGE_MAGICK)coders/fpx.c \
    $(IMAGE_MAGICK)coders/gif.c \
    $(IMAGE_MAGICK)coders/gradient.c \
    $(IMAGE_MAGICK)coders/gray.c \
    $(IMAGE_MAGICK)coders/hald.c \
    $(IMAGE_MAGICK)coders/hdr.c \
    $(IMAGE_MAGICK)coders/heic.c \
    $(IMAGE_MAGICK)coders/histogram.c \
    $(IMAGE_MAGICK)coders/hrz.c \
    $(IMAGE_MAGICK)coders/html.c \
    $(IMAGE_MAGICK)coders/icon.c \
    $(IMAGE_MAGICK)coders/info.c \
    $(IMAGE_MAGICK)coders/inline.c \
    $(IMAGE_MAGICK)coders/ipl.c \
    $(IMAGE_MAGICK)coders/jbig.c \
    $(IMAGE_MAGICK)coders/jp2.c \
    $(IMAGE_MAGICK)coders/jpeg.c \
    $(IMAGE_MAGICK)coders/label.c \
    $(IMAGE_MAGICK)coders/mac.c \
    $(IMAGE_MAGICK)coders/magick.c \
    $(IMAGE_MAGICK)coders/map.c \
    $(IMAGE_MAGICK)coders/mat.c \
    $(IMAGE_MAGICK)coders/matte.c \
    $(IMAGE_MAGICK)coders/meta.c \
    $(IMAGE_MAGICK)coders/mono.c \
    $(IMAGE_MAGICK)coders/mpc.c \
    $(IMAGE_MAGICK)coders/mpeg.c \
    $(IMAGE_MAGICK)coders/mpr.c \
    $(IMAGE_MAGICK)coders/msl.c \
    $(IMAGE_MAGICK)coders/mtv.c \
    $(IMAGE_MAGICK)coders/mvg.c \
    $(IMAGE_MAGICK)coders/null.c \
    $(IMAGE_MAGICK)coders/otb.c \
    $(IMAGE_MAGICK)coders/palm.c \
    $(IMAGE_MAGICK)coders/pattern.c \
    $(IMAGE_MAGICK)coders/pcd.c \
    $(IMAGE_MAGICK)coders/pcl.c \
    $(IMAGE_MAGICK)coders/pcx.c \
    $(IMAGE_MAGICK)coders/pdb.c \
    $(IMAGE_MAGICK)coders/pdf.c \
    $(IMAGE_MAGICK)coders/pes.c \
    $(IMAGE_MAGICK)coders/pict.c \
    $(IMAGE_MAGICK)coders/pix.c \
    $(IMAGE_MAGICK)coders/plasma.c \
    $(IMAGE_MAGICK)coders/png.c \
    $(IMAGE_MAGICK)coders/pnm.c \
    $(IMAGE_MAGICK)coders/ps.c \
    $(IMAGE_MAGICK)coders/ps2.c \
    $(IMAGE_MAGICK)coders/ps3.c \
    $(IMAGE_MAGICK)coders/psd.c \
    $(IMAGE_MAGICK)coders/pwp.c \
    $(IMAGE_MAGICK)coders/raw.c \
    $(IMAGE_MAGICK)coders/rgb.c \
    $(IMAGE_MAGICK)coders/rla.c \
    $(IMAGE_MAGICK)coders/rle.c \
    $(IMAGE_MAGICK)coders/scr.c \
    $(IMAGE_MAGICK)coders/sct.c \
    $(IMAGE_MAGICK)coders/sfw.c \
    $(IMAGE_MAGICK)coders/sgi.c \
    $(IMAGE_MAGICK)coders/stegano.c \
    $(IMAGE_MAGICK)coders/sun.c \
    $(IMAGE_MAGICK)coders/svg.c \
    $(IMAGE_MAGICK)coders/tga.c \
    $(IMAGE_MAGICK)coders/thumbnail.c \
    $(IMAGE_MAGICK)coders/tiff.c \
    $(IMAGE_MAGICK)coders/tile.c \
    $(IMAGE_MAGICK)coders/tim.c \
    $(IMAGE_MAGICK)coders/tim2.c \
    $(IMAGE_MAGICK)coders/ttf.c \
    $(IMAGE_MAGICK)coders/txt.c \
    $(IMAGE_MAGICK)coders/uil.c \
    $(IMAGE_MAGICK)coders/xtrn.c \
    $(IMAGE_MAGICK)coders/url.c \
    $(IMAGE_MAGICK)coders/uyvy.c \
    $(IMAGE_MAGICK)coders/vicar.c \
    $(IMAGE_MAGICK)coders/vid.c \
    $(IMAGE_MAGICK)coders/viff.c \
    $(IMAGE_MAGICK)coders/wbmp.c \
    $(IMAGE_MAGICK)coders/webp.c \
    $(IMAGE_MAGICK)coders/wmf.c \
    $(IMAGE_MAGICK)coders/wpg.c \
    $(IMAGE_MAGICK)coders/x.c \
    $(IMAGE_MAGICK)coders/xbm.c \
    $(IMAGE_MAGICK)coders/xc.c \
    $(IMAGE_MAGICK)coders/xcf.c \
    $(IMAGE_MAGICK)coders/xpm.c \
    $(IMAGE_MAGICK)coders/xps.c \
    $(IMAGE_MAGICK)coders/xwd.c \
    $(IMAGE_MAGICK)coders/ycbcr.c \
    $(IMAGE_MAGICK)coders/yuv.c \
    $(IMAGE_MAGICK)coders/djvu.c \
    $(IMAGE_MAGICK)coders/jnx.c \
    $(IMAGE_MAGICK)coders/json.c \
    $(IMAGE_MAGICK)coders/mask.c \
    $(IMAGE_MAGICK)coders/miff.c \
    $(IMAGE_MAGICK)coders/pango.c \
    $(IMAGE_MAGICK)coders/rgf.c \
    $(IMAGE_MAGICK)coders/screenshot.c \
    $(IMAGE_MAGICK)coders/sixel.c \
    $(IMAGE_MAGICK)coders/vips.c \
    $(IMAGE_MAGICK)coders/pgx.c \
    $(IMAGE_MAGICK)filters/analyze.c \
    $(IMAGE_MAGICK)MagickCore/accelerate.c \
    $(IMAGE_MAGICK)MagickCore/animate.c \
    $(IMAGE_MAGICK)MagickCore/annotate.c \
    $(IMAGE_MAGICK)MagickCore/artifact.c \
    $(IMAGE_MAGICK)MagickCore/attribute.c \
    $(IMAGE_MAGICK)MagickCore/blob.c \
    $(IMAGE_MAGICK)MagickCore/cache.c \
    $(IMAGE_MAGICK)MagickCore/cache-view.c \
    $(IMAGE_MAGICK)MagickCore/channel.c \
    $(IMAGE_MAGICK)MagickCore/cipher.c \
    $(IMAGE_MAGICK)MagickCore/client.c \
    $(IMAGE_MAGICK)MagickCore/coder.c \
    $(IMAGE_MAGICK)MagickCore/color.c \
    $(IMAGE_MAGICK)MagickCore/colormap.c \
    $(IMAGE_MAGICK)MagickCore/colorspace.c \
    $(IMAGE_MAGICK)MagickCore/compare.c \
    $(IMAGE_MAGICK)MagickCore/composite.c \
    $(IMAGE_MAGICK)MagickCore/compress.c \
    $(IMAGE_MAGICK)MagickCore/configure.c \
    $(IMAGE_MAGICK)MagickCore/constitute.c \
    $(IMAGE_MAGICK)MagickCore/decorate.c \
    $(IMAGE_MAGICK)MagickCore/delegate.c \
    $(IMAGE_MAGICK)MagickCore/deprecate.c \
    $(IMAGE_MAGICK)MagickCore/display.c \
    $(IMAGE_MAGICK)MagickCore/distort.c \
    $(IMAGE_MAGICK)MagickCore/distribute-cache.c \
    $(IMAGE_MAGICK)MagickCore/draw.c \
    $(IMAGE_MAGICK)MagickCore/effect.c \
    $(IMAGE_MAGICK)MagickCore/enhance.c \
    $(IMAGE_MAGICK)MagickCore/exception.c \
    $(IMAGE_MAGICK)MagickCore/feature.c \
    $(IMAGE_MAGICK)MagickCore/fourier.c \
    $(IMAGE_MAGICK)MagickCore/fx.c \
    $(IMAGE_MAGICK)MagickCore/gem.c \
    $(IMAGE_MAGICK)MagickCore/geometry.c \
    $(IMAGE_MAGICK)MagickCore/histogram.c \
    $(IMAGE_MAGICK)MagickCore/identify.c \
    $(IMAGE_MAGICK)MagickCore/image.c \
    $(IMAGE_MAGICK)MagickCore/image-view.c \
    $(IMAGE_MAGICK)MagickCore/layer.c \
    $(IMAGE_MAGICK)MagickCore/linked-list.c \
    $(IMAGE_MAGICK)MagickCore/list.c \
    $(IMAGE_MAGICK)MagickCore/locale.c \
    $(IMAGE_MAGICK)MagickCore/log.c \
    $(IMAGE_MAGICK)MagickCore/magic.c \
    $(IMAGE_MAGICK)MagickCore/magick.c \
    $(IMAGE_MAGICK)MagickCore/matrix.c \
    $(IMAGE_MAGICK)MagickCore/memory.c \
    $(IMAGE_MAGICK)MagickCore/mime.c \
    $(IMAGE_MAGICK)MagickCore/module.c \
    $(IMAGE_MAGICK)MagickCore/monitor.c \
    $(IMAGE_MAGICK)MagickCore/montage.c \
    $(IMAGE_MAGICK)MagickCore/morphology.c \
    $(IMAGE_MAGICK)MagickCore/nt-base.c \
    $(IMAGE_MAGICK)MagickCore/nt-feature.c \
    $(IMAGE_MAGICK)MagickCore/opencl.c \
    $(IMAGE_MAGICK)MagickCore/option.c \
    $(IMAGE_MAGICK)MagickCore/paint.c \
    $(IMAGE_MAGICK)MagickCore/pixel.c \
    $(IMAGE_MAGICK)MagickCore/policy.c \
    $(IMAGE_MAGICK)MagickCore/prepress.c \
    $(IMAGE_MAGICK)MagickCore/profile.c \
    $(IMAGE_MAGICK)MagickCore/property.c \
    $(IMAGE_MAGICK)MagickCore/quantize.c \
    $(IMAGE_MAGICK)MagickCore/quantum.c \
    $(IMAGE_MAGICK)MagickCore/quantum-export.c \
    $(IMAGE_MAGICK)MagickCore/quantum-import.c \
    $(IMAGE_MAGICK)MagickCore/random.c \
    $(IMAGE_MAGICK)MagickCore/registry.c \
    $(IMAGE_MAGICK)MagickCore/resample.c \
    $(IMAGE_MAGICK)MagickCore/resize.c \
    $(IMAGE_MAGICK)MagickCore/resource.c \
    $(IMAGE_MAGICK)MagickCore/segment.c \
    $(IMAGE_MAGICK)MagickCore/semaphore.c \
    $(IMAGE_MAGICK)MagickCore/shear.c \
    $(IMAGE_MAGICK)MagickCore/signature.c \
    $(IMAGE_MAGICK)MagickCore/splay-tree.c \
    $(IMAGE_MAGICK)MagickCore/static.c \
    $(IMAGE_MAGICK)MagickCore/statistic.c \
    $(IMAGE_MAGICK)MagickCore/stream.c \
    $(IMAGE_MAGICK)MagickCore/string.c \
    $(IMAGE_MAGICK)MagickCore/thread.c \
    $(IMAGE_MAGICK)MagickCore/threshold.c \
    $(IMAGE_MAGICK)MagickCore/timer.c \
    $(IMAGE_MAGICK)MagickCore/token.c \
    $(IMAGE_MAGICK)MagickCore/transform.c \
    $(IMAGE_MAGICK)MagickCore/type.c \
    $(IMAGE_MAGICK)MagickCore/utility.c \
    $(IMAGE_MAGICK)MagickCore/version.c \
    $(IMAGE_MAGICK)MagickCore/vision.c \
    $(IMAGE_MAGICK)MagickCore/widget.c \
    $(IMAGE_MAGICK)MagickCore/xml-tree.c \
    $(IMAGE_MAGICK)MagickCore/xwindow.c \

LOCAL_STATIC_LIBRARIES := \
    libpng \
    libjpeg-turbo \
    libtiff \
    libfreetype2 \
    libwebp \
    libwebpmux \
    libopenjpeg \
    libfftw3 \
    libxml2 \
    liblzma \
    libbz2

ifeq ($(STATIC_BUILD),true)
    include $(BUILD_STATIC_LIBRARY)
else
    include $(BUILD_SHARED_LIBRARY)
endif
#Image Magick dynamic --------------------------------------------------


#Image MagickWand dynamic ++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := libmagickwand-7

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)MagickCore \
    $(IMAGE_MAGICK)MagickWand \
    $(PNG_SRC_PATH) \
    $(JPEG_SRC_PATH) \

# always ignored in static builds
ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif

LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)MagickWand/animate.c \
    $(IMAGE_MAGICK)MagickWand/compare.c \
    $(IMAGE_MAGICK)MagickWand/composite.c \
    $(IMAGE_MAGICK)MagickWand/conjure.c \
    $(IMAGE_MAGICK)MagickWand/convert.c \
    $(IMAGE_MAGICK)MagickWand/deprecate.c \
    $(IMAGE_MAGICK)MagickWand/display.c \
    $(IMAGE_MAGICK)MagickWand/drawing-wand.c \
    $(IMAGE_MAGICK)MagickWand/identify.c \
    $(IMAGE_MAGICK)MagickWand/import.c \
    $(IMAGE_MAGICK)MagickWand/magick-cli.c \
    $(IMAGE_MAGICK)MagickWand/magick-image.c \
    $(IMAGE_MAGICK)MagickWand/magick-property.c \
    $(IMAGE_MAGICK)MagickWand/magick-wand.c \
    $(IMAGE_MAGICK)MagickWand/mogrify.c \
    $(IMAGE_MAGICK)MagickWand/montage.c \
    $(IMAGE_MAGICK)MagickWand/operation.c \
    $(IMAGE_MAGICK)MagickWand/pixel-iterator.c \
    $(IMAGE_MAGICK)MagickWand/pixel-wand.c \
    $(IMAGE_MAGICK)MagickWand/script-token.c \
    $(IMAGE_MAGICK)MagickWand/stream.c \
    $(IMAGE_MAGICK)MagickWand/wand.c \
    $(IMAGE_MAGICK)MagickWand/wandcli.c \
    $(IMAGE_MAGICK)MagickWand/wand-view.c \

ifeq ($(STATIC_BUILD),true)
    LOCAL_STATIC_LIBRARIES := \
        libmagickcore-7
        
    include $(BUILD_STATIC_LIBRARY)
else
    LOCAL_SHARED_LIBRARIES := \
        libmagickcore-7
        
    include $(BUILD_SHARED_LIBRARY)
endif

#Image MagickWand dynamic ----------------------------------------------


#Image Magick++ dynamic ++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := Magick++-7
LOCAL_CFLAGS += -fexceptions
LOCAL_LDFLAGS += -fexceptions

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)MagickCore \
    $(IMAGE_MAGICK)MagickWand \
    $(IMAGE_MAGICK)Magick++/lib \
    $(PNG_SRC_PATH) \
    $(JPEG_SRC_PATH) \

ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
endif

LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)Magick++/lib/Blob.cpp \
    $(IMAGE_MAGICK)Magick++/lib/BlobRef.cpp \
    $(IMAGE_MAGICK)Magick++/lib/CoderInfo.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Color.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Drawable.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Exception.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Functions.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Geometry.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Image.cpp \
    $(IMAGE_MAGICK)Magick++/lib/ImageRef.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Montage.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Options.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Pixels.cpp \
    $(IMAGE_MAGICK)Magick++/lib/ResourceLimits.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Statistic.cpp \
    $(IMAGE_MAGICK)Magick++/lib/STL.cpp \
    $(IMAGE_MAGICK)Magick++/lib/Thread.cpp \
    $(IMAGE_MAGICK)Magick++/lib/TypeMetric.cpp \


LOCAL_SHARED_LIBRARIES := \
    MagickCore-7 \
    MagickWand-7

#20170412 disable due to crash
#include $(BUILD_SHARED_LIBRARY)
#Image Magick++ dynamic ----------------------------------------------
#Image util dynamic ++++++++++++++++++++++++++++++++++++++++++++++
include $(CLEAR_VARS)

LOCAL_MODULE    := magick
#LOCAL_CFLAGS += -fexceptions
#LOCAL_LDFLAGS += -fexceptions

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES  :=  \
    $(IMAGE_MAGICK) \
    $(IMAGE_MAGICK)MagickCore \
    $(IMAGE_MAGICK)MagickWand \
    $(IMAGE_MAGICK)Magick++/lib \
    $(PNG_SRC_PATH) \
    $(JPEG_SRC_PATH) \
    $(TIFF_SRC_PATH) \
    $(FREETYPE_SRC_PATH)include


LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -lz
LOCAL_SRC_FILES := \
    $(IMAGE_MAGICK)utilities/magick.c \

ifeq ($(STATIC_BUILD),true)
    LOCAL_STATIC_LIBRARIES := \
        libmagickcore-7 \
        libmagickwand-7
else
    LOCAL_SHARED_LIBRARIES := \
        libmagickcore-7 \
        libmagickwand-7
endif

ifeq ($(BUILD_MAGICK_BIN),true)
    include $(BUILD_EXECUTABLE)
endif

#---------------
