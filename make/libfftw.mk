include $(CLEAR_VARS)

LOCAL_MODULE := libfftw3

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm


LOCAL_C_INCLUDES := \
        $(FFTW_LIB_PATH) \
        $(FFTW_LIB_PATH)/api \
		$(FFTW_LIB_PATH)/dft \
        $(FFTW_LIB_PATH)/dft/scalar \
        $(FFTW_LIB_PATH)/dft/scalar/codelets \
        $(FFTW_LIB_PATH)/kernel \
        $(FFTW_LIB_PATH)/libbench2 \
        $(FFTW_LIB_PATH)/rdft \
		$(FFTW_LIB_PATH)/rdft/scalar \
        $(FFTW_LIB_PATH)/rdft/scalar/r2cb \
        $(FFTW_LIB_PATH)/rdft/scalar/r2r \
        $(FFTW_LIB_PATH)/rdft/scalar/r2cf \
		$(FFTW_LIB_PATH)/reodft \
        $(FFTW_LIB_PATH)/simd-support \
        $(FFTW_LIB_PATH)/dft/simd \
        $(FFTW_LIB_PATH)/rdft/simd \



ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_LIB_PATH)/configs/arm64
    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/configs/arm64

    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/dft/simd/neon
    include $(FFTW_LIB_PATH)/dft/simd/neon/sources.mk
    include $(FFTW_LIB_PATH)/rdft/simd/neon/sources.mk

else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_LIB_PATH)/configs/arm
    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/configs/arm

    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/dft/simd/neon
    include $(FFTW_LIB_PATH)/dft/simd/neon/sources.mk
    include $(FFTW_LIB_PATH)/rdft/simd/neon/sources.mk

else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_LIB_PATH)/configs/x86
    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/configs/x86

    # Add required compiler flags for SIMD optimizations on x86
    LOCAL_CFLAGS += -mavx -mavx2 -DHAVE_AVX2 -mfma -mfma4 \
                    -mavx512f -mavx512dq -mavx512bw -mavx512vl \
                    -msse2 -msse4.2 -mpopcnt \

    LOCAL_C_INCLUDES += \
        $(FFTW_LIB_PATH)/dft/simd/avx \
        $(FFTW_LIB_PATH)/dft/simd/avx-128-fma \
        $(FFTW_LIB_PATH)/dft/simd/avx2 \
        $(FFTW_LIB_PATH)/dft/simd/avx2-128 \
        $(FFTW_LIB_PATH)/dft/simd/avx512 \
        $(FFTW_LIB_PATH)/dft/simd/generic-simd128 \
        $(FFTW_LIB_PATH)/dft/simd/generic-simd256 \
        $(FFTW_LIB_PATH)/dft/simd/sse2 \
        $(FFTW_LIB_PATH)/rdft/simd/avx \
        $(FFTW_LIB_PATH)/rdft/simd/avx-128-fma \
        $(FFTW_LIB_PATH)/rdft/simd/avx2 \
        $(FFTW_LIB_PATH)/rdft/simd/avx2-128 \
        $(FFTW_LIB_PATH)/rdft/simd/avx512 \
        $(FFTW_LIB_PATH)/rdft/simd/generic-simd128 \
        $(FFTW_LIB_PATH)/rdft/simd/generic-simd256 \
        $(FFTW_LIB_PATH)/rdft/simd/sse2

        include $(FFTW_LIB_PATH)/dft/simd/avx/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx-128-fma/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx2/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx2-128/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx512/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/generic-simd128/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/generic-simd256/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/sse2/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx-128-fma/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx2/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx2-128/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx512/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/generic-simd128/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/generic-simd256/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/sse2/sources.mk

else ifeq ($(TARGET_ARCH_ABI),x86_64)
    LOCAL_EXPORT_C_INCLUDES += $(FFTW_LIB_PATH)/configs/x86-64
    LOCAL_C_INCLUDES += $(FFTW_LIB_PATH)/configs/x86-64

    # Add required compiler flags for full SIMD optimizations on x86_64
    LOCAL_CFLAGS += -mavx -mavx2 -DHAVE_AVX2 -mfma -mfma4 \
                    -mavx512f -mavx512dq -mavx512bw -mavx512vl \
                    -msse2 -msse4.2 -mpopcnt \

    ifneq ($(STATIC_BUILD),true)
        LOCAL_LDFLAGS += -latomic
    endif

    LOCAL_C_INCLUDES += \
        $(FFTW_LIB_PATH)/dft/simd/avx \
        $(FFTW_LIB_PATH)/dft/simd/avx-128-fma \
        $(FFTW_LIB_PATH)/dft/simd/avx2 \
        $(FFTW_LIB_PATH)/dft/simd/avx2-128 \
        $(FFTW_LIB_PATH)/dft/simd/avx512 \
        $(FFTW_LIB_PATH)/dft/simd/generic-simd128 \
        $(FFTW_LIB_PATH)/dft/simd/generic-simd256 \
        $(FFTW_LIB_PATH)/dft/simd/sse2 \
        $(FFTW_LIB_PATH)/rdft/simd/avx \
        $(FFTW_LIB_PATH)/rdft/simd/avx-128-fma \
        $(FFTW_LIB_PATH)/rdft/simd/avx2 \
        $(FFTW_LIB_PATH)/rdft/simd/avx2-128 \
        $(FFTW_LIB_PATH)/rdft/simd/avx512 \
        $(FFTW_LIB_PATH)/rdft/simd/generic-simd128 \
        $(FFTW_LIB_PATH)/rdft/simd/generic-simd256 \
        $(FFTW_LIB_PATH)/rdft/simd/sse2 

        include $(FFTW_LIB_PATH)/dft/simd/avx/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx-128-fma/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx2/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx2-128/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/avx512/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/generic-simd128/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/generic-simd256/sources.mk
        include $(FFTW_LIB_PATH)/dft/simd/sse2/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx-128-fma/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx2/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx2-128/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/avx512/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/generic-simd128/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/generic-simd256/sources.mk
        include $(FFTW_LIB_PATH)/rdft/simd/sse2/sources.mk

endif


include $(FFTW_LIB_PATH)/api/sources.mk
include $(FFTW_LIB_PATH)/dft/sources.mk
include $(FFTW_LIB_PATH)/dft/scalar/sources.mk
include $(FFTW_LIB_PATH)/dft/scalar/codelets/sources.mk
include $(FFTW_LIB_PATH)/kernel/sources.mk
include $(FFTW_LIB_PATH)/libbench2/sources.mk
include $(FFTW_LIB_PATH)/rdft/sources.mk
include $(FFTW_LIB_PATH)/rdft/scalar/sources.mk
include $(FFTW_LIB_PATH)/rdft/scalar/r2cb/sources.mk
include $(FFTW_LIB_PATH)/rdft/scalar/r2cf/sources.mk
include $(FFTW_LIB_PATH)/rdft/scalar/r2r/sources.mk
include $(FFTW_LIB_PATH)/reodft/sources.mk
include $(FFTW_LIB_PATH)/simd-support/sources.mk

ifeq ($(LIBFFTW_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif

