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

# list of supported architectures 
# https://developer.android.com/ndk/guides/application_mk.html

# mips32 have a bug with 64bit atomic counter, so if you need 
# this platform - plz, use gcc build
APP_ABI := arm64-v8a
APP_PLATFORM := android-24
NDK_TOOLCHAIN_VERSION := clang

# list of build-in STL's supported by NDK. 
# switch to clang STL in case of using this compiler
# https://developer.android.com/ndk/guides/cpp-support.html#runtimes

# Until NDK r16, the NDK's libc++ is only of beta quality. 
# Beginning with NDK r16, libc++ will be the preferred STL. 
# A future NDK release will remove the other options.
APP_STL := c++_shared

APP_CFLAGS   += -O3 \
    -Wno-error=unused-but-set-variable \
    -Wno-error=implicit-const-int-float-conversion \
    -Wno-format \
    -Wno-integer-overflow \
    -Wno-implicit-function-declaration \
    -Wno-pointer-sign \
    -Wno-excess-initializers \
    -Wno-literal-conversion \
    -Wno-int-conversion \
    -Wno-error=int-conversion

APP_CPPFLAGS += -O3 


#------------------------------------------
# Magick options

HDRI_ENABLE   := true
# 8, 16, 32
QUANTUM_DEPTH := 16


#------------------------------------------
# Whether to do a static or shared library
# build.
#
# You can also choose to build a magick
# binary.
#

STATIC_BUILD     := true
# magick bin requires magick wand API
BUILD_MAGICK_BIN := true
BUILD_MAGICKWAND := true
# requires magickwand
BUILD_MAGICKPP   := false


#------------------------------------------
# Types of builds available. OpenMP, OpenCL, or neither
# Neither will do a vanilla build without either feature

# openCL build requires special setup. Check the libopencl
# directory for more information
OPENCL_BUILD     := false
OPENMP_BUILD     := true


#------------------------------------------
# Enable or disable specific delegates here
#

LIBBZ2_ENABLED        := true
LIBFFTW_ENABLED       := true
LIBFREETYPE2_ENABLED  := true
LIBJPEG_TURBO_ENABLED := true
LIBLZMA_ENABLED       := true
LIBOPENJPEG_ENABLED   := true
LIBPNG_ENABLED        := true
LIBTIFF_ENABLED       := true
LIBWEBP_ENABLED       := true
LIBXML2_ENABLED       := true
LIBZLIB_ENABLED       := true
LIBLCMS2_ENABLED      := true

#------------------------------------------

# fix long windows paths causing build to fail (too many sources)
LOCAL_SHORT_COMMANDS := true
APP_SHORT_COMMANDS   := true

#------------------------------------------
LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/make/postconfig.mk
