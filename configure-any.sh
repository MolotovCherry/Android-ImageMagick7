export ANDROID_HOST=aarch64-linux-android
export ANDROID_BUILD=linux-x86_64
export ANDROID_ARCH=arm64
export ANDROID_NDK=/your/path/
export ANDROID_VERSION=24
export ANDROID_TOOLCHAIN_VERSION=4.9
export ANDROID_SYSROOT=$ANDROID_NDK/platforms/android-$ANDROID_VERSION/arch-$ANDROID_ARCH
export NDK_TOOLCHAIN=$ANDROID_NDK/toolchains/$ANDROID_HOST-$ANDROID_TOOLCHAIN_VERSION/prebuilt/$ANDROID_BUILD/bin
export ANDROID_LLVM_ROOT=$ANDROID_NDK/toolchains/llvm/prebuilt/$ANDROID_BUILD/bin
export CFLAGS=--sysroot=$ANDROID_SYSROOT
export CXXFLAGS=--sysroot=$ANDROID_SYSROOT
export AR=$NDK_TOOLCHAIN/$ANDROID_HOST-ar
export RANLIB=$NDK_TOOLCHAIN/$ANDROID_HOST-ranlib
export LD=$NDK_TOOLCHAIN/$ANDROID_HOST-ld
export STRIP=$NDK_TOOLCHAIN/$ANDROID_HOST-strip
export CC=$ANDROID_LLVM_ROOT/${ANDROID_HOST}${ANDROID_VERSION}-clang
export CXX=$ANDROID_LLVM_ROOT/${ANDROID_HOST}${ANDROID_VERSION}-clang++
export ac_cv_func_malloc_0_nonnull=yes
export ac_cv_func_realloc_0_nonnull=yes
export PATH=$ANDROID_NDK/toolchains/$ANDROID_HOST-$ANDROID_TOOLCHAIN_VERSION/prebuilt/$ANDROID_BUILD/bin:$PATH
./configure --host=$ANDROID_HOST --target=$ANDROID_HOST --with-sysroot=$ANDROID_SYSROOT

# liblzma configure
--disable-xzdec --disable-lzmadec --disable-lzmainfo --disable-lzma-links --disable-scripts --host=$ANDROID_HOST --target=$ANDROID_HOST --with-sysroot=$ANDROID_SYSROOT