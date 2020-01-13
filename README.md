
# Android ImageMagick 7.0.8-63
This is a fully featured imagemagick build compatible with android. All libaries used are the absolute latest versions with the latest and greatest features.

It can be configured to both build as a binary (with shared libaries or statically linked), or as separate shared libraries (and no binary).

It comes compiled with the following features:

- OpenMP(3.1) / OpenCL (Qualcomm)
- HDRI support
- Q16 Quantum depth
- Cipher
- DPC

It comes featured with the following delegates:

 - bzlib
 - libfftw
 - libfreetype
 - libjpeg-turbo
 - libopenjpeg
 - libpng
 - libtiff
 - libwebp
 - libxml2
 - liblzma
 - liblcms2

Also comes with (**but these not delegates, only support libraries**):
- libicu4c (libicuuc and libicui18n)
- libiconv

# Android support

**Requires API >= 24 (>= Nougat)**

**Currently, only arm64-v8a is supported**

You can test it with earlier versions, but I offer no support for it.

- Includes optional jmagick support. It will patch imagemagick c files for Android/jmagick compatibility.
- Includes jmagick java code and fakeawt for your project
- You can choose to disable support for jmagick, and it will compile UNMODIFIED vanilla files (the binary / libraries will still run on Android without any problems whatsoever; android compatibility is merely to allow imagemagick to interface with java code, and also logging support in Android Studio ;) )

# Quick Setup Instructions

- Android app setup code, including gradle files, assets, binary / jmagick interface java code, etc, can all be found under the [`libjmagick-7/android`](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android) folder.
- In order to understand how to build the project, please [install](https://developer.android.com/studio/projects/install-ndk) and [setup NDK](https://developer.android.com/ndk/guides) as per Google's instructions. Make sure you read how NDK works as it is important to getting your build successfully compiling. The required gradle files for building are under [`libjmagick-7/android`](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android).
- Place your libs under the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/libs/arm64-v8a) folder. It's already setup to be noticed when your APK is built.
- Edit your build configuration under [`Application.mk`](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk) to your liking, then (next step below)
- Use your CMD in the root and execute `build-release.bat`. Sorry, the build only currently works on Windows because I didn't have time to test the make files under Linux. Contributions are welcome.

- OpenCL support is available for Qualcomm. OpenCL is recommended over OpenMP. Please [go here](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libopencl/qualcomm/lib) in order to learn how to setup OpenCL build for the project. You only need to find your own `libOpenCL.so` file and copy it over for your project. I can't host it here due to copyrights.


## How to run the binary

1. Put the generated binary in the [assets bin folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/src/main/assets/usr/bin/arm64-v8a). Put all libs in the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/libs/arm64-v8a) folder.
2. Add environment variables before you run the binary.
3. Execute binary with args.

- All example code and setup to do this is can be found in the [example android app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android).

| ENV Variable | Description | Example Value |
|--|--|--|
|`TMPDIR`|Temporary cache directory. Set to a directory writable by your app|`/data/data/com.myapp/files/TMP`|
|`MAGICK_HOME`|The directory containing imagemagick xml config files. Should be set to the base directory, e.g. `/usr` , with config files being in `/usr/etc/ImageMagick-7`.| `/data/data/com.myapp/files/usr`|
|`ICU_DATA_DIR_PREFIX`|The directory containing the folder named `icu` which contains the ICU data files (required by icuuc library). For example, a path of `/usr` will result in `/usr/icu/icu.dat` being loaded. Only required if the `libxml2` delegate is enabled.|`/data/data/com.myapp/files/usr`|
|`LD_LIBRARY_PATH`|Needed in order for the binary to find the `libc++_shared.so` library (or other libraries if you compiled them into shared libraries). Preferable to use the code `context.getApplicationInfo().nativeLibraryDir`|`/data/data/com.myapp/files/usr/lib/arm64-v8a`|
