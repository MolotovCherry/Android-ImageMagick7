include $(CLEAR_VARS)

LOCAL_MODULE    := libtiff
LOCAL_MODULE_FILENAME := libtiffobj

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES :=  \
    $(TIFF_LIB_PATH) \
    $(JPEG_LIB_PATH) \
    $(LZMA_LIB_PATH)/liblzma/api

LOCAL_CFLAGS := \
    -DLZMA_SUPPORT=1

LOCAL_SRC_FILES := \
    $(TIFF_LIB_PATH)/mkg3states.c \
    $(TIFF_LIB_PATH)/tif_aux.c \
    $(TIFF_LIB_PATH)/tif_close.c \
    $(TIFF_LIB_PATH)/tif_codec.c \
    $(TIFF_LIB_PATH)/tif_color.c \
    $(TIFF_LIB_PATH)/tif_compress.c \
    $(TIFF_LIB_PATH)/tif_dir.c \
    $(TIFF_LIB_PATH)/tif_dirinfo.c \
    $(TIFF_LIB_PATH)/tif_dirread.c \
    $(TIFF_LIB_PATH)/tif_dirwrite.c \
    $(TIFF_LIB_PATH)/tif_dumpmode.c \
    $(TIFF_LIB_PATH)/tif_error.c \
    $(TIFF_LIB_PATH)/tif_extension.c \
    $(TIFF_LIB_PATH)/tif_fax3.c \
    $(TIFF_LIB_PATH)/tif_fax3sm.c \
    $(TIFF_LIB_PATH)/tif_flush.c \
    $(TIFF_LIB_PATH)/tif_getimage.c \
    $(TIFF_LIB_PATH)/tif_jbig.c \
    $(TIFF_LIB_PATH)/tif_jpeg.c \
    $(TIFF_LIB_PATH)/tif_jpeg_12.c \
    $(TIFF_LIB_PATH)/tif_luv.c \
    $(TIFF_LIB_PATH)/tif_lzma.c \
    $(TIFF_LIB_PATH)/tif_lzw.c \
    $(TIFF_LIB_PATH)/tif_next.c \
    $(TIFF_LIB_PATH)/tif_ojpeg.c \
    $(TIFF_LIB_PATH)/tif_open.c \
    $(TIFF_LIB_PATH)/tif_packbits.c \
    $(TIFF_LIB_PATH)/tif_pixarlog.c \
    $(TIFF_LIB_PATH)/tif_predict.c \
    $(TIFF_LIB_PATH)/tif_print.c \
    $(TIFF_LIB_PATH)/tif_read.c \
    $(TIFF_LIB_PATH)/tif_strip.c \
    $(TIFF_LIB_PATH)/tif_swab.c \
    $(TIFF_LIB_PATH)/tif_thunder.c \
    $(TIFF_LIB_PATH)/tif_tile.c \
    $(TIFF_LIB_PATH)/tif_version.c \
    $(TIFF_LIB_PATH)/tif_warning.c \
    $(TIFF_LIB_PATH)/tif_webp.c \
    $(TIFF_LIB_PATH)/tif_write.c \
    $(TIFF_LIB_PATH)/tif_zip.c \
    $(TIFF_LIB_PATH)/tif_zstd.c \
    $(TIFF_LIB_PATH)/tif_unix.c \
    $(TIFF_LIB_PATH)/../port/lfind.c


LOCAL_STATIC_LIBRARIES := \
    liblzma

include $(BUILD_STATIC_LIBRARY)
