
# Android ImageMagick 7.0.9-17

[![Build](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/main.yml/badge.svg?event=push)](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/main.yml)

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

Also comes with (**but these are not delegates, only support libraries**):
- libicu4c (libicuuc and libicui18n)
- libiconv
- libltdl (required for libOpenCL)

# Android support

**Requires API >= 24 (>= Nougat)**

**Currently, only arm64-v8a is supported**

You can test it with earlier versions, but I offer no support for it. If you're using only the binary, you almost certainly can compile for earlier versions. The API limit pertains mostly to the Java code, however nothing is stopping you from theoterically making it compatible with earlier Android versions too. If you get it working for earlier versions, let me know

- Includes optional jmagick support. It will patch imagemagick c files for Android/jmagick compatibility.
- Includes jmagick java code and fakeawt for your project
- You can choose to disable support for jmagick, and it will compile UNMODIFIED vanilla files (the binary / libraries will still run on Android without any problems whatsoever; android compatibility is merely to allow imagemagick to interface with java code, and also logging support in Android Studio ;) )

# Binaries

Check out the release page for the [latest built binaries](https://github.com/cherryleafroad/Android-ImageMagick7/releases). This is built using the [default configuration](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk). If you need a special configuration (for example OpenCL), you will need to build it for yourself from source.

- OpenCL support is available for Qualcomm. OpenCL is recommended over OpenMP. Please [go here](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libopencl/qualcomm/lib) in order to learn how to setup OpenCL build for the project. You only need to find your own `libOpenCL.so` file and copy it over for your project. I can't host it here due to copyrights. **For OpenCL support, you need to build the library yourself because of copyright issues (I can't host the OpenCL lib here, so GitHub can't build it for me)**

# Quick Setup Instructions

- Android app setup code, including gradle files, assets, binary / jmagick interface java code, etc, can all be found under the [app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app). This is not a 100% complete Android app, but rather it contains all the code examples needed for you to adapt it to your own project. Just copy / rewrite / delete code you want / don't need and combine it with your Android Studio project.
- Place your libs under the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/libs/arm64-v8a) folder. It's already setup to be noticed when your APK is built.

## How to run the binary

1. Put the generated binary in the [assets bin folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/src/main/assets/usr/bin/arm64-v8a). Put all libs in the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app/libs/arm64-v8a) folder.
2. Add environment variables before you run the binary.
3. Execute binary with args.

- All example code and setup to do this is can be found in the [example android app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app).

| ENV Variable | Description | Example Value |
|--|--|--|
|`TMPDIR`|Temporary cache directory. Set to a directory writable by your app|`/data/data/com.myapp/files/TMP`|
|`MAGICK_HOME`|The directory containing imagemagick xml config files. Should be set to the base directory, e.g. `/usr` , with config files being in `/usr/etc/ImageMagick-7`.| `/data/data/com.myapp/files/usr`|
|`ICU_DATA_DIR_PREFIX`|The directory containing the folder named `icu` which contains the ICU data files (required by icuuc library). For example, a path of `/usr` will result in `/usr/icu/icu.dat` being loaded. Only required if the `libxml2` delegate is enabled.|`/data/data/com.myapp/files/usr`|
|`LD_LIBRARY_PATH`|Needed in order for the binary to find the `libc++_shared.so` library (or other libraries if you compiled them into shared libraries). Preferable to use the code `context.getApplicationInfo().nativeLibraryDir`|`/data/data/com.myapp/files/usr/lib/arm64-v8a`|

# Building from Source

- In order to understand how to build the project, please [install](https://developer.android.com/studio/projects/install-ndk) and [setup NDK](https://developer.android.com/ndk/guides) as per Google's instructions. Make sure you read how NDK works as it is important to getting your build successfully compiling. The required gradle files for building inside the [app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app).
- Edit your build configuration under [`Application.mk`](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk) to your liking, then (next step below)
- Use your CMD in the root and execute `build-release.bat`. Sorry, the build only currently works on Windows because I didn't have time to test the make files under Linux. Contributions are welcome.

# FAQ

### What is the recommended way to build/run this?

Build it with OpenCL support, statically linked, as a binary. HDRI on, quantum depth at 16. Do not enable jmagick support. As far as I am concerned, jmagick is outdated, EVEN though I will keep the patches up to date with the lastest version, and you CAN build it if you desire to. Make sure to use an AsyncTask to run it. Running it on your main thread WILL lock up your main UI. I can't host an OpenCL build here because I can't put the OpenCL lib here for an automatic build. So, only OpenMP builds are released.

### Can I customize the build features?

Yes you can. Just go to [Application.mk](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk) in the root directory and alter the variables inside to your desired configuration. Build configuration has been made very simple! Piece of cake!

### Why can't it find `libjmagick-7.so`?

I do not build `libjmagick`. The reason is that I consider jmagick to be old, so I do not support it and any problems you encounter trying to use it. It will -probably- work, but you must build it yourself. I repeat, jmagick is not maintained by the author, and is just a bit obsolete, EVEN if it works (I've added many patches to make it work, but I can only do so much. It needs a full rewrite). If you want them to fix all the problems, please consider contributing to [their project](https://github.com/techblue/jmagick). Secondly, see the "Why am I getting linking errors" entry below.

### Why am I getting linking errors?

You probably didn't add the `LD_LIBRARY_PATH` environment variable, so it doesn't know where to find any required libraries. Either that, or you don't have any libraries in your project at all. In the case of jmagick, I do not build jmagick, you will need to build from source to get it. Check out the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app) for where to put your libs. Hint: put it in the `libs` folder. And MAKE sure you went through the example android app and are using the supporting gradle / java code. It's all there.

### Why won't the binary execute properly?

Either you are using the wrong architecture (we only support armv8a), or your source code for running the binary is wrong. See the example code in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app). Everything you need is here.

### How to build using NDK..? I'm so confused

Check out the Building from Source part above. Also, make sure you thoroughly read the [Google NDK docs](https://developer.android.com/studio/projects/install-ndk). Supporting code, gradle files for building, is all in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app).

### I'm getting some errors about not being able to write TMP files..?

Create a tmpdir in your assets folder (same level as `usr` folder), and call it `tmp` (or something similar). Point to it using the `TMPDIR` environment variable listed in the documentation.

### Why do you only support arm64-v8a?

I didn't have time to test x86, x64, mips, armv7. There are a lot of specific configurations that need to take place such as ssize and so on that are specific to the different architectures. I don't know their required values. I'd also need to overhaul the make system to use different versions of these files in order for it to build properly. *I'd love some contributions to this so we can get more archs working!!*

### It won't build on Linux!!

Only Windows is supported by the build system. The make files assume you have Windows. Use Windows. Or, you could also contribute to testing and fixing the makefile code that only supports Windows. If you want to help with Linux build support, then make a issue and we can work together on it.

### Do you have any examples? / Where are the examples?

You can see all the example code you need for running jmagic or the binary in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libjmagick-7/android/app). It also has an entire sample project setup to get you started quick.

Note: This is not a "copy all the files"-"change nothing"-"run it directly without figuring it out"-solution, but rather an example template to help you get yours right with copyable code examples. This won't work directly out of the box. But it is also generally complete, more than enough to even copy over and fix whatever needs fixing if you wanted to. So, you should be using your own project, then just gut out the example project into yours as needed.

### I did everything correctly and it failed ??

If you are using NDK 22+, this seems to have several incompatibilities. Try the steps in this [issue](https://github.com/cherryleafroad/Android-ImageMagick7/issues/9#issuecomment-748531617), and failing that, it \*should\* work on an earlier NDK version (21 I think). If you find/know the steps to make the build work with NDK 22+, PLEASE send a pull request!!! Thanks!

### jmagick is too old / missing features / not working properly / strange things are happening
The [official jmagick library](https://github.com/techblue/jmagick) is old, out of date, and largely unmaintained. It's not really code compatible with the newer imagemagick versions (compiles != api compatible). Considering what a huge work it would be for me to port ALL of imagemagick to java just for Android, I haven't been able to do it (it requires well over 10,000 lines of c code). This is why I suggest to never use jmagick, as any problems you encounter, missing features, or strange issues, will have no support (and you're likely to encounter them).
