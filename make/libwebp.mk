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
    $(WEBP_LIB_PATH)/src/dec/alpha_dec.c \
    $(WEBP_LIB_PATH)/src/dec/buffer_dec.c \
    $(WEBP_LIB_PATH)/src/dec/frame_dec.c \
    $(WEBP_LIB_PATH)/src/dec/idec_dec.c \
    $(WEBP_LIB_PATH)/src/dec/io_dec.c \
    $(WEBP_LIB_PATH)/src/dec/quant_dec.c \
    $(WEBP_LIB_PATH)/src/dec/tree_dec.c \
    $(WEBP_LIB_PATH)/src/dec/vp8_dec.c \
    $(WEBP_LIB_PATH)/src/dec/vp8l_dec.c \
    $(WEBP_LIB_PATH)/src/dec/webp_dec.c \

demux_srcs := \
    $(WEBP_LIB_PATH)/src/demux/anim_decode.c \
    $(WEBP_LIB_PATH)/src/demux/demux.c \

dsp_dec_srcs := \
    $(WEBP_LIB_PATH)/src/dsp/alpha_processing.c \
    $(WEBP_LIB_PATH)/src/dsp/alpha_processing_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/alpha_processing_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/alpha_processing_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/alpha_processing_sse41.c \
    $(WEBP_LIB_PATH)/src/dsp/cpu.c \
    $(WEBP_LIB_PATH)/src/dsp/dec.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_clip_tables.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/dec_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/dec_sse41.c \
    $(WEBP_LIB_PATH)/src/dsp/filters.c \
    $(WEBP_LIB_PATH)/src/dsp/filters_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/filters_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/filters_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/filters_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/lossless_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/rescaler.c \
    $(WEBP_LIB_PATH)/src/dsp/rescaler_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/rescaler_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/rescaler_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/rescaler_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/rescaler_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/upsampling.c \
    $(WEBP_LIB_PATH)/src/dsp/upsampling_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/upsampling_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/upsampling_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/upsampling_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/upsampling_sse41.c \
    $(WEBP_LIB_PATH)/src/dsp/yuv.c \
    $(WEBP_LIB_PATH)/src/dsp/yuv_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/yuv_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/yuv_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/yuv_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/yuv_sse41.c \

dsp_enc_srcs := \
    $(WEBP_LIB_PATH)/src/dsp/cost.c \
    $(WEBP_LIB_PATH)/src/dsp/cost_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/cost_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/cost_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/cost_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/enc.c \
    $(WEBP_LIB_PATH)/src/dsp/enc_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/enc_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/enc_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/enc_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/enc_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/enc_sse41.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_mips32.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_mips_dsp_r2.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_msa.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_neon.$(NEON) \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_sse2.c \
    $(WEBP_LIB_PATH)/src/dsp/lossless_enc_sse41.c \
    $(WEBP_LIB_PATH)/src/dsp/ssim.c \
    $(WEBP_LIB_PATH)/src/dsp/ssim_sse2.c \

enc_srcs := \
    $(WEBP_LIB_PATH)/src/enc/alpha_enc.c \
    $(WEBP_LIB_PATH)/src/enc/analysis_enc.c \
    $(WEBP_LIB_PATH)/src/enc/backward_references_cost_enc.c \
    $(WEBP_LIB_PATH)/src/enc/backward_references_enc.c \
    $(WEBP_LIB_PATH)/src/enc/config_enc.c \
    $(WEBP_LIB_PATH)/src/enc/cost_enc.c \
    $(WEBP_LIB_PATH)/src/enc/filter_enc.c \
    $(WEBP_LIB_PATH)/src/enc/frame_enc.c \
    $(WEBP_LIB_PATH)/src/enc/histogram_enc.c \
    $(WEBP_LIB_PATH)/src/enc/iterator_enc.c \
    $(WEBP_LIB_PATH)/src/enc/near_lossless_enc.c \
    $(WEBP_LIB_PATH)/src/enc/picture_enc.c \
    $(WEBP_LIB_PATH)/src/enc/picture_csp_enc.c \
    $(WEBP_LIB_PATH)/src/enc/picture_psnr_enc.c \
    $(WEBP_LIB_PATH)/src/enc/picture_rescale_enc.c \
    $(WEBP_LIB_PATH)/src/enc/picture_tools_enc.c \
    $(WEBP_LIB_PATH)/src/enc/predictor_enc.c \
    $(WEBP_LIB_PATH)/src/enc/quant_enc.c \
    $(WEBP_LIB_PATH)/src/enc/syntax_enc.c \
    $(WEBP_LIB_PATH)/src/enc/token_enc.c \
    $(WEBP_LIB_PATH)/src/enc/tree_enc.c \
    $(WEBP_LIB_PATH)/src/enc/vp8l_enc.c \
    $(WEBP_LIB_PATH)/src/enc/webp_enc.c \

mux_srcs := \
    $(WEBP_LIB_PATH)/src/mux/anim_encode.c \
    $(WEBP_LIB_PATH)/src/mux/muxedit.c \
    $(WEBP_LIB_PATH)/src/mux/muxinternal.c \
    $(WEBP_LIB_PATH)/src/mux/muxread.c \

utils_dec_srcs := \
    $(WEBP_LIB_PATH)/src/utils/bit_reader_utils.c \
    $(WEBP_LIB_PATH)/src/utils/color_cache_utils.c \
    $(WEBP_LIB_PATH)/src/utils/filters_utils.c \
    $(WEBP_LIB_PATH)/src/utils/huffman_utils.c \
    $(WEBP_LIB_PATH)/src/utils/quant_levels_dec_utils.c \
    $(WEBP_LIB_PATH)/src/utils/random_utils.c \
    $(WEBP_LIB_PATH)/src/utils/rescaler_utils.c \
    $(WEBP_LIB_PATH)/src/utils/thread_utils.c \
    $(WEBP_LIB_PATH)/src/utils/utils.c \

utils_enc_srcs := \
    $(WEBP_LIB_PATH)/src/utils/bit_writer_utils.c \
    $(WEBP_LIB_PATH)/src/utils/huffman_encode_utils.c \
    $(WEBP_LIB_PATH)/src/utils/quant_levels_utils.c \

################################################################################
# libwebpdecoder

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    $(dec_srcs) \
    $(dsp_dec_srcs) \
    $(utils_dec_srcs) \

LOCAL_CFLAGS := $(WEBP_CFLAGS)
LOCAL_EXPORT_C_INCLUDES := \
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

ifeq ($(USE_CPUFEATURES),yes)
  LOCAL_STATIC_LIBRARIES := cpufeatures
endif

LOCAL_MODULE := webpdecoder_static

ifeq ($(LIBWEBP_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif

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
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_WHOLE_STATIC_LIBRARIES := webpdecoder_static


ifeq ($(LIBWEBP_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif


#################################################################################

################################################################################
# libwebpmux

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    $(mux_srcs) \
    $(demux_srcs)

LOCAL_CFLAGS := $(WEBP_CFLAGS)
LOCAL_EXPORT_C_INCLUDES := \
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)
LOCAL_C_INCLUDES := \
    $(WEBP_LIB_PATH)/src \
    $(WEBP_LIB_PATH)

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_MODULE := libwebpmux

LOCAL_STATIC_LIBRARIES := libwebp
ifeq ($(LIBWEBP_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif

################################################################################

ifeq ($(USE_CPUFEATURES),yes)
  $(call import-module,android/cpufeatures)
endif
