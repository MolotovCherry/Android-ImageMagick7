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

APP_CFLAGS += \
    -DMAGICKCORE_HDRI_ENABLE=1 \
    -DMAGICKCORE_QUANTUM_DEPTH=16 \
    -O3 \
    -fopenmp

APP_CPPFLAGS += \
    -DMAGICKCORE_HDRI_ENABLE=1 \
    -DMAGICKCORE_QUANTUM_DEPTH=16 \
    -O3 \
    -fopenmp

APP_LDFLAGS += \
    -fopenmp


#------------------------------------------
# Whether to do a static or shared library
# build. Shared library builds are mandatory
# for jmagick builds.
#
# You can also choose to build a magick
# binary (NOT recommended to build a magick)
# binary when using jmagick. Because special
# paths must be set via code
#

STATIC_BUILD     := true
# magick bin requires magick wand API
BUILD_MAGICK_BIN := true
BUILD_MAGICKWAND := true


#------------------------------------------
# Enable or disable jmagick build
#
# - Enabling this will patch imagemagick for
# jmagick and android compatibility
#
# - Disabling this will compile the vanilla
# (unmodified) imagemagick source code
#
# -> If this is enabled, it will force enable
# a shared library build (because it is required)
#
# -> Requires a MagickWand build as well
#

JMAGICK_ENABLED := false


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
APP_SHORT_COMMANDS := true
