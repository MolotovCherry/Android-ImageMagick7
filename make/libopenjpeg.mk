include $(CLEAR_VARS)

LOCAL_MODULE := libopenjpeg

LOCAL_CFLAGS := -DUSE_JPIP


# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm


LOCAL_C_INCLUDES := \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2 \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip \
    $(OPENJPEG_LIB_PATH)/config

LOCAL_SRC_FILES := \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/bench_dwt.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/bio.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/cidx_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/cio.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/dwt.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/event.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/function_list.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/image.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/invert.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/j2k.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/jp2.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/mct.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/mqc.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/openjpeg.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/opj_clock.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/opj_malloc.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/phix_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/pi.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/ppix_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/sparse_array.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/t1.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/t1_generate_luts.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/t2.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/tcd.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/test_sparse_array.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/tgt.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/thix_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/thread.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjp2/tpix_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/auxtrans_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/box_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/boxheader_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/byte_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/cache_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/cachemodel_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/channel_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/codestream_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/dec_clientmsg_handler.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/faixbox_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/ihdrbox_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/imgreg_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/imgsock_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/index_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/j2kheader_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/jp2k_decoder.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/jp2k_encoder.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/jpip_parser.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/jpipstream_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/manfbox_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/marker_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/metadata_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/mhixbox_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/msgqueue_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/openjpip.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/placeholder_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/query_parser.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/session_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/sock_manager.c \
    $(OPENJPEG_LIB_PATH)/src/lib/openjpip/target_manager.c \

ifeq ($(LIBOPENJPEG_ENABLED),true)
    include $(BUILD_STATIC_LIBRARY)
endif
