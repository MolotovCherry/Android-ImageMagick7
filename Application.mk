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
# armeabi-v7a
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

STATIC_BUILD := true
BUILD_MAGICK_BIN := true


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

#------------------------------------------

# fix long windows paths causing build to fail (too many sources)
LOCAL_SHORT_COMMANDS := true
APP_SHORT_COMMANDS := true
