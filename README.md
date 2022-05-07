
# Android ImageMagick 7.1.0-33

[![Build](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/build.yml/badge.svg?event=push)](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/build.yml) [![CodeQL](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/cherryleafroad/Android-ImageMagick7/actions/workflows/codeql-analysis.yml) ![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/cherryleafroad/Android-ImageMagick7?style=plastic)

This is a fully featured imagemagick build compatible with android [__and has Kotlin bindings__](https://github.com/cherryleafroad/kmagick) (check out KMagick below). All libaries used are the absolute latest versions with the latest and greatest features. ___This repo automatically updates itself with the latest imagemagick releases and issues full binary releases!___

It can be configured to both build as a binary (with shared libaries or statically linked), or as separate shared libraries (and no binary).

MagickWand and Magick++ are both available for compilation as well.

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

You can test it with earlier versions, but I offer no support for it. If you're using only the binary, you almost certainly can compile for earlier versions. Nothing is stopping you from theoterically making it compatible with earlier Android versions too. If you get it working for earlier versions, let me know

# Binaries

Check out the release page for the [latest built binaries](https://github.com/cherryleafroad/Android-ImageMagick7/releases). This is built using the [default configuration](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk). If you need a special configuration (for example OpenCL), you will need to build it for yourself from source.

- OpenCL support is available for Qualcomm. OpenCL is recommended over OpenMP. Please [go here](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/libopencl/qualcomm/lib) in order to learn how to setup OpenCL build for the project. You only need to find your own `libOpenCL.so` file and copy it over for your project. I can't host it here due to copyrights. **For OpenCL support, you need to build the library yourself because of copyright issues (I can't host the OpenCL lib here, so GitHub can't build it for me)**. >Btw, Github Actions can do the build for you too, change the config file, and manually run the action.<

# KMagick

Check out the [KMagick](https://github.com/cherryleafroad/kmagick) repo for instructions on how to use ImageMagick with Kotlin in your project (instead of the binary).

# Quick Setup Instructions

- Android app setup code, including gradle files, assets, binary / java code, etc, can all be found under the [app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app). This is not a 100% complete Android app, but rather it contains all the code examples needed for you to adapt it to your own project. Just copy / rewrite / delete code you want / don't need and combine it with your Android Studio project.
- Place your libs under the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app/libs/arm64-v8a) folder. It's already setup to be noticed when your APK is built.

## How to run the binary

1. Put the generated binary in the [assets bin folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app/src/main/assets/usr/bin/arm64-v8a). Put all libs in the [libs/arch](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app/libs/arm64-v8a) folder.
2. Add environment variables before you run the binary.
3. Execute binary with args.

- All example code and setup to do this is can be found in the [example android app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app).

| ENV Variable | Description | Example Value |
|--|--|--|
|`TMPDIR`|Temporary cache directory. Set to a directory writable by your app|`/data/data/com.myapp/files/TMP`|
|`MAGICK_HOME`|The directory containing imagemagick xml config files. Should be set to the base directory, e.g. `/usr` , with config files being in `/usr/etc/ImageMagick-7`.| `/data/data/com.myapp/files/usr`|
|`ICU_DATA_DIR_PREFIX`|The directory containing the folder named `icu` which contains the ICU data files (required by icuuc library). For example, a path of `/usr` will result in `/usr/icu/icu.dat` being loaded. Only required if the `libxml2` delegate is enabled.|`/data/data/com.myapp/files/usr`|
|`LD_LIBRARY_PATH`|Needed in order for the binary to find the `libc++_shared.so` library (or other libraries if you compiled them into shared libraries). Preferable to use the code `context.getApplicationInfo().nativeLibraryDir`|`/data/data/com.myapp/files/usr/lib/arm64-v8a`|

# Building from Source

- In order to understand how to build the project, please [install](https://developer.android.com/studio/projects/install-ndk) and [setup NDK](https://developer.android.com/ndk/guides) as per Google's instructions. Make sure you read how NDK works as it is important to getting your build successfully compiling. The required gradle files for building inside the [app folder](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app).
- Edit your build configuration under [`Application.mk`](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk) to your liking, then (next step below)
- Use your CMD in the root and execute `build-release.bat`. Sorry, the build only currently works on Windows because I didn't have time to test the make files under Linux. Contributions are welcome.

# Building with Docker

- Install Docker
- Run the build-with-docker script :)

Use `-r` for release, or `-d` for debug build. No arguments means release mode

Docker image:
https://hub.docker.com/repository/docker/cherryleafroad/imbuild

The script will ask you to download or build it yourself. It may be faster for you to build the image (cause there's less to download)

No Linux shell script currently exists, but there's nothing stopping you from setting it up yourself (just read the build-with-docker file).

# Building with Github

- Fork the repo, change the config file (if you want), then use github actions to build it, and download the build artifacts. Pretty much almost no setup required in order to build. :)

# FAQ

### Always latest builds? Are you serious?

Indeed I am!! I just took a bunch of time to write a program that automatically edits my source code, updates imagemagick, builds it, merges it into the main branch, and creates an automated release WITH updated binaries! All without any input from me at all! Unless the bot breaks and I have to take time to fix it*, ___this repo will automatically update itself!___ 

The bot checks for updates every day on the 0, 6, 12, and 18'th hour UTC time, so if there's a new update, you can expect it to take maybe 30 minutes or so to automatically compile everything.

\* that's unlikely to happen for a long time, and even if it does, it won't be hard to fix

### What is the recommended way to build/run this?

Build it with OpenCL support (note, probably not all devices support OpenCL), statically linked, as a binary. HDRI on, quantum depth at 16. Make sure to use an AsyncTask to run it. Running it on your main thread WILL lock up your main UI. I can't host an OpenCL build here because I can't put the OpenCL lib here for an automatic build. So, only OpenMP builds are released.

### Can I customize the build features?

Yes you can. Just go to [Application.mk](https://github.com/cherryleafroad/Android-ImageMagick7/blob/master/Application.mk) in the root directory and alter the variables inside to your desired configuration. Build configuration has been made very simple! Piece of cake!

### Is there an easier way to build this without so much work?

Actually there is! Fork my repo, change the config to what you want, then use Github Actions to build it. Since I already have the build scripts configured, it's minimal work for you. In the case of wanting to do a openCL build, just follow the openCl instructions, change the config, then use Github Actions like before.

### Why am I getting linking errors?

You probably didn't add the `LD_LIBRARY_PATH` environment variable, so it doesn't know where to find any required libraries. Either that, or you don't have any libraries in your project at all. Check out the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app) for where to put your libs. Hint: put it in the `libs` folder. And MAKE sure you went through the example android app and are using the supporting gradle / java code. It's all there.

### Why won't the binary execute properly?

Either you are using the wrong architecture (we only support armv8a), or your source code for running the binary is wrong. Please make sure all the files in the assets are there and you're using the env variables properly. Please also see the example code in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app). Everything you need is here. In the case of API >= 29, see the below answer.

### On API >= 29, I am getting permission denied errors!

[Starting with API 29, Android disallows binary execution in the home directory](https://developer.android.com/about/versions/10/behavior-changes-10#execute-permission). The only remaining location for executable code is the native lib directory.

There are 2 solutions for you on Android 10+:

#### Solution 1 - run the ELF binary from the native libs directory
1. rename your binary file to something like `libmagick.so` and place it in the `jniLibs` folder.
2. Make sure you have `android:extractNativeLibs=true` in your manifest.
3. After this, you can make a bunch of symlinks to the `libmagick.so` binary in your native lib folder from your apps data homedirectory (e.g. `magick`, `convert`, etc). The symlinks allow you to act like you're using the normal `magick` binary.
4. As usual, make sure that your `libmagick.so` has the executable bit set on it `chmod +x`. (This might or might not be the case by default)

Note: This `libmagick.so` is NOT a real shared library. It is the ELF `magick` binary with a different filename, that's all. The naming allows us to copy the binary over with the other real libs.

#### Solution 2 - Use [KMagick](https://github.com/cherryleafroad/kmagick)
Since it is a jni lib, you won't have to try executing anything, thereby bypassing all the problems. :) Also, it's easier to use and setup than a binary, although you should probably still run it in a separate thread regardless (don't block your main thread!). You can find KMagick [here](https://github.com/cherryleafroad/kmagick).

#### Solution 3 - use this project to create your own JNI lib which links against/integrates with the native imagemagick lib
Note: You should just use [kmagick](https://github.com/cherryleafroad/kmagick) instead since I already made a Kotlin library for this.
1. [Read Oracle's documentation for how JNI works](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/jniTOC.html).
2. [Read the official Android mk guide](https://developer.android.com/ndk/guides/android_mk). You can also study the make file setup I already have going. Specifically `Android.mk`, `Application.mk`, and the files under the `make` directory. After you're familiar enough with how it works, you can create your own `mk` file and integrate it into the project and tell it to build and link/integrate your own JNI lib against the real `libmagick.so` lib. You can do a static or shared library build (static meaning that there will be only 1 lib, which is yours, and all other libs like imagemagick will be inside it). Building a native imagemagick lib (shared or static) is already supported with a switch in the settings, so it will take minimal effort for you to integrate your build into it.
3. Program all your C code / Rust code. I STRONGLY recommend using Rust as it's a better and much safer low level language compared to C. [It has JNI bindings support already](https://crates.io/crates/jni), and even [imagemagick magick wand bindings](https://crates.io/crates/magick_rust). I STRONGLY recommend you use the [imagemagick magick wand API](https://imagemagick.org/script/magick-wand.php) instead of the other ones since it's much easier to do what you want using it. In the case of Rust, you're probably better off just using `release.bat` to build the project with static libs, then add a line below that for building your rust/jni lib against the generated static lib(s). Trust me, it's not as hard as one might think it would be (you can see here that I already have a [kmagick script which links against the android lib](https://github.com/cherryleafroad/kmagick/blob/main/rust/build-android.ps1))
4. Do a bunch of Googling for any JNI, make file, imagemagick wand API, or C / Rust errors errors you encounter (as is always the case with programming!)
5. Profit!

### Kmagick? Why not Jmagick?

Well, you see. The thing is that the [jmagick project](https://github.com/techblue/jmagick) hasn't been updated since 2018. Imagemagick has grown and changed so much that it's not even compatible with it anymore. Furthermore, they aren't even using the better magick wand API. Jmagick is mostly compatible with IM6, which is an older version. It's just not up to par.

So... I made a completely new one called [Kmagick](https://github.com/cherryleafroad/kmagick)!! Yup, I really did make an entire ImageMagick API in Kotlin from the ground up! It's made to be compatible with the latest versions of ImageMagick, AND it uses Kotlin instead of Java! How cool is that?

### I'm getting some errors about not being able to write TMP files..?

Create a tmpdir in your assets folder (same level as `usr` folder), and call it `tmp` (or something similar). Point to it using the `TMPDIR` environment variable listed in the documentation.

### Why do you only support arm64-v8a?

I didn't have time to test x86, x64, mips, armv7. There are a lot of specific configurations that need to take place such as ssize and so on that are specific to the different architectures. I don't know their required values. I'd also need to overhaul the make system to use different versions of these files in order for it to build properly. *I'd love some contributions to this so we can get more archs working!!*

### It won't build on Linux!!

Only Windows is supported by the build system. The make files assume you have Windows. Use Windows. Or, you could also contribute to testing and fixing the makefile code that only supports Windows. If you want to help with Linux build support, then make a issue and we can work together on it.

### Do you have any examples? / Where are the examples?

You can see all the example code you need for running the binary in the [example android app](https://github.com/cherryleafroad/Android-ImageMagick7/tree/master/example-app/android/app). It also has an entire sample project setup to get you started quick.

Note: This is not a "copy all the files"-"change nothing"-"run it directly without figuring it out"-solution, but rather an example template to help you get yours right with copyable code examples. This won't work directly out of the box. But it is also generally complete, more than enough to even copy over and fix whatever needs fixing if you wanted to. So, you should be using your own project, then just gut out the example project into yours as needed.

# Did this library help you?

[![Donate](./readme_files/donate.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=BKDN933UM444J)

If you found this library useful, please consider showing appreciation and help fund it by sending a donation my way.  
All donations help this project continue to be supported for longer and receive more frequent updates! Thanks for your support! <3
