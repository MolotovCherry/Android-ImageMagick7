include $(CLEAR_VARS)

LOCAL_MODULE := liblzma

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
    $(LZMA_LIB_PATH) \
    $(LZMA_LIB_PATH)/liblzma/api \
    $(LZMA_LIB_PATH)/liblzma/common \
    $(LZMA_LIB_PATH)/liblzma \
    $(LZMA_LIB_PATH)/liblzma/lz \
    $(LZMA_LIB_PATH)/liblzma/rangecoder \
    $(LZMA_LIB_PATH)/liblzma/delta \
    $(LZMA_LIB_PATH)/liblzma/simple \
    $(LZMA_LIB_PATH)/liblzma/check \
    $(LZMA_LIB_PATH)/liblzma/lzma \
    $(LZMA_LIB_PATH)/common \
    $(ICONV_LIB_PATH) \
    $(ICONV_LIB_PATH)/include \
    $(ICONV_LIB_PATH)/lib \
    $(ICONV_LIB_PATH)/libcharset \
    $(ICONV_LIB_PATH)/libcharset/include \
    $(ICONV_LIB_PATH)/srclib

LOCAL_CFLAGS := \
    -DTUKLIB_SYMBOL_PREFIX=lzma_ \
    -DHAVE_CONFIG_H

# Define HAVE_IMMINTRIN_H if building for x86
ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_CFLAGS += -DHAVE_IMMINTRIN_H
endif

LOCAL_SRC_FILES := \
    $(LZMA_LIB_PATH)/common/tuklib_physmem.c \
    $(LZMA_LIB_PATH)/common/tuklib_cpucores.c \
    $(LZMA_LIB_PATH)/liblzma/common/common.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_util.c \
    $(LZMA_LIB_PATH)/liblzma/common/easy_preset.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_common.c \
    $(LZMA_LIB_PATH)/liblzma/common/hardware_physmem.c \
    $(LZMA_LIB_PATH)/liblzma/common/index.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_flags_common.c \
    $(LZMA_LIB_PATH)/liblzma/common/vli_size.c \
    $(LZMA_LIB_PATH)/liblzma/common/hardware_cputhreads.c \
    $(LZMA_LIB_PATH)/liblzma/common/alone_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_buffer_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_header_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/easy_buffer_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/easy_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/easy_encoder_memusage.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_buffer_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_flags_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/index_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_buffer_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_flags_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/vli_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/outqueue.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_encoder_mt.c \
    $(LZMA_LIB_PATH)/liblzma/common/alone_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/auto_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_buffer_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/block_header_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/easy_decoder_memusage.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_buffer_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/filter_flags_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/index_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/index_hash.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_buffer_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/stream_flags_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/common/vli_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/check/check.c \
    $(LZMA_LIB_PATH)/liblzma/check/crc32_table.c \
    $(LZMA_LIB_PATH)/liblzma/check/crc32_fast.c \
    $(LZMA_LIB_PATH)/liblzma/check/crc64_table.c \
    $(LZMA_LIB_PATH)/liblzma/check/crc64_fast.c \
    $(LZMA_LIB_PATH)/liblzma/check/sha256.c \
    $(LZMA_LIB_PATH)/liblzma/lz/lz_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/lz/lz_encoder_mf.c \
    $(LZMA_LIB_PATH)/liblzma/lz/lz_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma_encoder_presets.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma_encoder_optimum_fast.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma_encoder_optimum_normal.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/fastpos_table.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma2_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/lzma/lzma2_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/rangecoder/price_table.c \
    $(LZMA_LIB_PATH)/liblzma/delta/delta_common.c \
    $(LZMA_LIB_PATH)/liblzma/delta/delta_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/delta/delta_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/simple/simple_coder.c \
    $(LZMA_LIB_PATH)/liblzma/simple/simple_encoder.c \
    $(LZMA_LIB_PATH)/liblzma/simple/simple_decoder.c \
    $(LZMA_LIB_PATH)/liblzma/simple/x86.c \
    $(LZMA_LIB_PATH)/liblzma/simple/powerpc.c \
    $(LZMA_LIB_PATH)/liblzma/simple/ia64.c \
    $(LZMA_LIB_PATH)/liblzma/simple/arm.c \
    $(LZMA_LIB_PATH)/liblzma/simple/armthumb.c \
    $(LZMA_LIB_PATH)/liblzma/simple/sparc.c \

LOCAL_STATIC_LIBRARIES := \
    libiconv

ifeq ($(LIBLZMA_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif
