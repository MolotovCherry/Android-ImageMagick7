include $(CLEAR_VARS)

LOCAL_MODULE    := libopencl

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_SRC_FILES := $(OPENCL_LIB_PATH)/64/libOpenCL.so
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := $(OPENCL_LIB_PATH)/32/libOpenCL.so
endif

ifeq ($(OPENCL_BUILD),true)
    include $(PREBUILT_SHARED_LIBRARY)
endif
