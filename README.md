
# Android ImageMagick 7.0.8-62
This is a fully featured imagemagick build compatible with android. All libaries used are the absolute latest versions with the latest and greatest features.

It can be configured to both build as a binary (with shared libaries or statically linked), or as separate shared libraries (and no binary).

It comes compiled with the following features:

- OpenMP(3.1)
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
- Also has example android java code interfacing with imagemagick, find it in the `libjmagick-7/android` directory
- You can choose to disable support for jmagick, and it will compile UNMODIFIED vanilla files (the binary / libraries will still run on Android without any problems whatsoever; android compatibility is merely to allow imagemagick to interface with java code, and also logging support in Android Studio ;) )

# How to run the binary


1. Put all generated binary and library files in same folder.
2. Add environment variables before you run the binary.

| ENV Variable | Description | Example Value |
|--|--|--|
|`TMPDIR`|Temporary cache directory. Set to a directory writable by your app|`/data/data/com.myapp/files/TMP`|
|`MAGICK_HOME`|The directory containing imagemagick xml config files. Should be set to the base directory, e.g. `/usr` , with config files being in `/usr/etc/ImageMagick-7`.| `/data/data/com.myapp/files/usr`|
|`ICU_DATA_DIR_PREFIX`|The directory containing the folder named `icu` which contains the ICU data files (required by icuuc library). For example, a path of `/usr` will result in `/usr/icu/icu.dat` being loaded. Only required if the `libxml2` delegate is enabled.|`/data/data/com.myapp/files/usr`|
|`LD_LIBRARY_PATH`|Needed in order for the binary to find the `libc++_shared.so` library (or other libraries if you compiled them into shared libraries)|`/data/data/com.myapp/files/usr/lib/arm64-v8a`|
