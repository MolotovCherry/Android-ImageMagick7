#----------------------------------------------------------------------------#
#                                  _           _     _                       #
#                  /\             | |         (_)   | |                      #
#                 /  \   _ __   __| |_ __ ___  _  __| |                      #
#                / /\ \ | '_ \ / _` | '__/ _ \| |/ _` |                      #
#               / ____ \| | | | (_| | | | (_) | | (_| |                      #
#              /_/    \_\_| |_|\__,_|_|  \___/|_|\__,_|                      #
#                                                                            #
#  _____                            __  __             _      _      ______  #
# |_   _|                          |  \/  |           (_)    | |    |____  | #
#   | |  _ __ ___   __ _  __ _  ___| \  / | __ _  __ _ _  ___| | __     / /  #
#   | | | '_ ` _ \ / _` |/ _` |/ _ \ |\/| |/ _` |/ _` | |/ __| |/ /    / /   #
#  _| |_| | | | | | (_| | (_| |  __/ |  | | (_| | (_| | | (__|   <    / /    #
# |_____|_| |_| |_|\__,_|\__, |\___|_|  |_|\__,_|\__, |_|\___|_|\_\  /_/     #
#                         __/ |                   __/ |                      #
#                        |___/                   |___/                       #
#                                                                            #
#----------------------------------------------------------------------------#
# Module Vars                                                                #
#----------------------------------------------------------------------------#

LOCAL_PATH                      := $(call my-dir)


MAKE_PATH                       := $(LOCAL_PATH)/make

OPENCL_PATH                     := $(LOCAL_PATH)/libopencl
OPENCL_LIB_PATH                 := $(OPENCL_PATH)/qualcomm/lib
OPENCL_INCLUDE_PATH             := $(OPENCL_PATH)/qualcomm/include

LTDL_LIB_PATH                   := $(LOCAL_PATH)/libltdl-2.4.6

IMAGE_MAGICK_BASEDIR            := ImageMagick-7.1.1-45
IMAGE_MAGICK                    := $(LOCAL_PATH)/$(IMAGE_MAGICK_BASEDIR)

JPEG_LIB_PATH                   := $(LOCAL_PATH)/libjpeg-turbo-2.0.2
PNG_LIB_PATH                    := $(LOCAL_PATH)/libpng-1.6.37
TIFF_LIB_PATH                   := $(LOCAL_PATH)/libtiff-v4.0.10/libtiff
FREETYPE_LIB_PATH               := $(LOCAL_PATH)/libfreetype2-2.10.1
WEBP_LIB_PATH                   := $(LOCAL_PATH)/libwebp-1.0.3
OPENJPEG_LIB_PATH               := $(LOCAL_PATH)/libopenjpeg-2.3.1
FFTW_LIB_PATH                   := $(LOCAL_PATH)/libfftw-3.3.8
XML2_LIB_PATH                   := $(LOCAL_PATH)/libxml2-2.9.9
ICONV_LIB_PATH                  := $(LOCAL_PATH)/libiconv-1.16

ICU_LIB_PATH                    := $(LOCAL_PATH)/libicu4c-64-2
ICU_COMMON_PATH                 := $(ICU_LIB_PATH)/common
ICU_I18N_PATH                   := $(ICU_LIB_PATH)/i18n
ICU_STUBDATA_PATH               := $(ICU_LIB_PATH)/stubdata

LZMA_LIB_PATH                   := $(LOCAL_PATH)/xz-5.2.4
BZLIB_LIB_PATH                  := $(LOCAL_PATH)/bzip-1.0.8
LCMS_LIB_PATH                   := $(LOCAL_PATH)/liblcms2-2.9

#-------------------------------------------------------------
# Include all modules
#-------------------------------------------------------------

# libltdl
include $(MAKE_PATH)/libltdl.mk

# libopencl
include $(MAKE_PATH)/libopencl.mk

# libjpeg-turbo
include $(MAKE_PATH)/libjpeg-turbo.mk

# libopenjpeg
include $(MAKE_PATH)/libopenjpeg.mk

# libtiff
include $(MAKE_PATH)/libtiff.mk

# libpng
include $(MAKE_PATH)/libpng.mk

# libfreetype2
include $(MAKE_PATH)/libfreetype2.mk

# libwebp
include $(MAKE_PATH)/libwebp.mk

# libfftw
include $(MAKE_PATH)/libfftw.mk

# libxml2
include $(MAKE_PATH)/libxml2.mk

# liblzma
include $(MAKE_PATH)/liblzma.mk

# libbz2
include $(MAKE_PATH)/libbz2.mk

# libiconv
include $(MAKE_PATH)/libiconv.mk

# libicu4c
include $(MAKE_PATH)/libicu4c.mk

# liblcms2
include $(MAKE_PATH)/liblcms2.mk

#-------------------------------------------------------------
# Magick
#-------------------------------------------------------------

# magick
include $(MAKE_PATH)/magick.mk

# libmagickcore-7
include $(MAKE_PATH)/libmagickcore-7.mk

# libmagickwand-7
include $(MAKE_PATH)/libmagickwand-7.mk

# libmagick++-7
include $(MAKE_PATH)/libmagick++-7.mk
