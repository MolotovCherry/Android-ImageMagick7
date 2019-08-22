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
    $(XML2_LIB_PATH) \
    $(XML2_LIB_PATH)/include \
    $(ICONV_LIB_PATH) \
    $(ICONV_LIB_PATH)/include \
    $(ICONV_LIB_PATH)/lib \
    $(ICONV_LIB_PATH)/libcharset \
    $(ICONV_LIB_PATH)/libcharset/include \
    $(ICU_LIB_PATH) \
    $(ICU_LIB_PATH)/common \
    $(ICU_LIB_PATH)/i18n \
    $(ICU_LIB_PATH)/common/unicode \
    $(ICU_LIB_PATH)/i18n/unicode \
    $(LZMA_LIB_PATH)/liblzma/api
LOCAL_EXPORT_C_INCLUDES := \
    $(XML2_LIB_PATH) \
    $(XML2_LIB_PATH)/include \
    $(ICONV_LIB_PATH) \
    $(ICONV_LIB_PATH)/include \
    $(ICONV_LIB_PATH)/lib \
    $(ICONV_LIB_PATH)/libcharset \
    $(ICONV_LIB_PATH)/libcharset/include \
    $(ICU_LIB_PATH) \
    $(ICU_LIB_PATH)/common \
    $(ICU_LIB_PATH)/i18n \
    $(ICU_LIB_PATH)/common/unicode \
    $(ICU_LIB_PATH)/i18n/unicode \
    $(LZMA_LIB_PATH)/liblzma/api

# prefer arm over thumb mode for performance gains
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
    $(XML2_LIB_PATH)/SAX.c \
    $(XML2_LIB_PATH)/entities.c \
    $(XML2_LIB_PATH)/encoding.c \
    $(XML2_LIB_PATH)/error.c \
    $(XML2_LIB_PATH)/parserInternals.c \
    $(XML2_LIB_PATH)/parser.c \
    $(XML2_LIB_PATH)/tree.c \
    $(XML2_LIB_PATH)/hash.c \
    $(XML2_LIB_PATH)/list.c \
    $(XML2_LIB_PATH)/xmlIO.c \
    $(XML2_LIB_PATH)/xmlmemory.c \
    $(XML2_LIB_PATH)/uri.c \
    $(XML2_LIB_PATH)/valid.c \
    $(XML2_LIB_PATH)/xlink.c \
    $(XML2_LIB_PATH)/debugXML.c \
    $(XML2_LIB_PATH)/xpath.c \
    $(XML2_LIB_PATH)/xpointer.c \
    $(XML2_LIB_PATH)/xinclude.c \
    $(XML2_LIB_PATH)/DOCBparser.c \
    $(XML2_LIB_PATH)/catalog.c \
    $(XML2_LIB_PATH)/globals.c \
    $(XML2_LIB_PATH)/threads.c \
    $(XML2_LIB_PATH)/c14n.c \
    $(XML2_LIB_PATH)/xmlstring.c \
    $(XML2_LIB_PATH)/buf.c \
    $(XML2_LIB_PATH)/xmlregexp.c \
    $(XML2_LIB_PATH)/xmlschemas.c \
    $(XML2_LIB_PATH)/xmlschemastypes.c \
    $(XML2_LIB_PATH)/xmlunicode.c \
    $(XML2_LIB_PATH)/xmlreader.c \
    $(XML2_LIB_PATH)/relaxng.c \
    $(XML2_LIB_PATH)/dict.c \
    $(XML2_LIB_PATH)/SAX2.c \
    $(XML2_LIB_PATH)/xmlwriter.c \
    $(XML2_LIB_PATH)/legacy.c \
    $(XML2_LIB_PATH)/chvalid.c \
    $(XML2_LIB_PATH)/pattern.c \
    $(XML2_LIB_PATH)/xmlsave.c \
    $(XML2_LIB_PATH)/xmlmodule.c \
    $(XML2_LIB_PATH)/schematron.c \

LOCAL_STATIC_LIBRARIES := \
    libiconv \
    libicuuc \
    libicui18n \
    liblzma


include $(BUILD_STATIC_LIBRARY)
