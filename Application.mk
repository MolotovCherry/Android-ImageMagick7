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
# DO NOT BUILD MORE THAN ONE AT THE SAME TIME, OR IT WILL FAIL
# BUILD THEM ONE AT A TIME
# armeabi-v7a is currently not supported
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

APP_CFLAGS   += -O3

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

LIBBZ2_ENABLED        := false
LIBFFTW_ENABLED       := false
LIBFREETYPE2_ENABLED  := false
LIBJPEG_TURBO_ENABLED := false
LIBLZMA_ENABLED       := false
LIBOPENJPEG_ENABLED   := false
LIBPNG_ENABLED        := false
LIBTIFF_ENABLED       := false
LIBWEBP_ENABLED       := false
LIBXML2_ENABLED       := false
LIBZLIB_ENABLED       := false
LIBLCMS2_ENABLED      := false

#------------------------------------------

# fix long windows paths causing build to fail (too many sources)
LOCAL_SHORT_COMMANDS := true
APP_SHORT_COMMANDS := true

#------------------------------------------
LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/make/postconfig.mk
