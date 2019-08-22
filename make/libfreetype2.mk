include $(CLEAR_VARS)

LOCAL_MODULE    := libfreetype2

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := \
    -DANDROID_NDK \
    -DFT2_BUILD_LIBRARY=1

LOCAL_C_INCLUDES := \
    $(FREETYPE_LIB_PATH)/include \
    $(FREETYPE_LIB_PATH)/src \
    $(PNG_LIB_PATH)


LOCAL_SRC_FILES += \
    $(FREETYPE_LIB_PATH)/src/base/ftbbox.c \
    $(FREETYPE_LIB_PATH)/src/base/ftbitmap.c \
    $(FREETYPE_LIB_PATH)/src/base/ftfntfmt.c \
    $(FREETYPE_LIB_PATH)/src/base/ftfstype.c \
    $(FREETYPE_LIB_PATH)/src/base/ftglyph.c \
    $(FREETYPE_LIB_PATH)/src/base/ftlcdfil.c \
    $(FREETYPE_LIB_PATH)/src/base/ftstroke.c \
    $(FREETYPE_LIB_PATH)/src/base/fttype1.c \
    $(FREETYPE_LIB_PATH)/src/base/ftbase.c \
    $(FREETYPE_LIB_PATH)/src/base/ftsystem.c \
    $(FREETYPE_LIB_PATH)/src/base/ftinit.c \
    $(FREETYPE_LIB_PATH)/src/base/ftgasp.c \
    $(FREETYPE_LIB_PATH)/src/base/ftmm.c \
    $(FREETYPE_LIB_PATH)/src/gzip/ftgzip.c \
    $(FREETYPE_LIB_PATH)/src/raster/raster.c \
    $(FREETYPE_LIB_PATH)/src/sfnt/sfnt.c \
    $(FREETYPE_LIB_PATH)/src/smooth/smooth.c \
    $(FREETYPE_LIB_PATH)/src/autofit/autofit.c \
    $(FREETYPE_LIB_PATH)/src/truetype/truetype.c \
    $(FREETYPE_LIB_PATH)/src/cff/cff.c \
    $(FREETYPE_LIB_PATH)/src/psnames/psnames.c \
    $(FREETYPE_LIB_PATH)/src/pshinter/pshinter.c \
    $(FREETYPE_LIB_PATH)/src/psaux/psaux.c \
    $(FREETYPE_LIB_PATH)/src/type1/type1.c \
    $(FREETYPE_LIB_PATH)/src/cid/type1cid.c \

ifneq ($(STATIC_BUILD),true)
    LOCAL_LDLIBS := -ldl -llog
endif

include $(BUILD_STATIC_LIBRARY)
