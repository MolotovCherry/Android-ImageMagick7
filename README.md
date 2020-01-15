
# Android ImageMagick 7.0.9-16
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

- **Last note**: Any precompiled binaries/libraries you see either in the project source or releases section are *old*. **BUILD** the project yourself. I **DO NOT** offer any precompiled builds for the latest versions.

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

# FAQ

**Why can't it find `libjmagick-7.so`?**

I do not build `libjmagick`. The reason is that I consider jmagick to be old, so I do not support it and any problems you encounter trying to use it. It will -probably- work, but you must build it yourself. I repeat, jmagick is not maintained by the author, and is just a bit obsolete, EVEN if it works (I've added many patches to make it work, but I can only do so much. It needs a full rewrite). Secondly, see the "Why am I getting linking errors" entry below.

**Why is the prebuilt version in the releases section / in the source code old?**

I don't have time to build the library/binary due to its multitude of possible configurations. DEBUG vs RELEASE, jmagick vs no jmagick, openCL vs openMP. Please build it yourself. I've provided the proper supporting gradle files for NDK, links to guides for setup, project structure, and source code to do so.

**Why am I getting linking errors?**

You probably didn't add the `LD_LIBRARY_PATH` environment variable, so it doesn't know where to find any required libraries. Either that, or you don't have any libraries in your project at all. In the case of jmagick, I do not build jmagick, you will need to build from source to get it. (Also, any other precompiled binaries are *old*, so please build it yourself to get the latest features). Check out the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android) for where to put your libs. Hint: put it in the `libs` folder. And MAKE sure you went through the example android app and are using the supporting gradle / java code. It's all there.

**Why won't the binary execute properly?**

Either you are using the wrong architecture (we only support armv8a), or your source code for running the binary is wrong. See the example code in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android). Everything you need is here.

**How to build using NDK..? I'm so confused**

You'll have to figure that out, but check out the Quick Setup Instructions part above. I detail it all there. Supporting code, gradle files for building, is all there in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android).

**I'm getting some errors about not being able to write TMP files..?**

Create a tmpdir in your assets folder (same level as `usr` folder), and call it `tmp` (or something similar). Point to it using the `TMPDIR` environment variable listed in the documentation.

**But please!! I don't want to build it. Can you please provide a prebuilt version?**

If you want to help me setup travis ci, or whatever other service can auto build projects, then great. I look forward to your contributions to the project!
