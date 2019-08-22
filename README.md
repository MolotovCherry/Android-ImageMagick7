
# Android ImageMagick 7.0.8-60
This is a fully featured imagemagick build compatible with android. All libaries used are the absolute latest versions with the latest and greatest features.

It can be configured to both build as a binary (with shared libaries or statically linked), or as separate shared libraries (and no binary).

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

Also comes with (**but these not delegates, only support libraries**):
- libicu4c (libicuuc and libicui18n)
- libiconv

# How to run the binary


1. Put all generated binary and library files in same folder.
2. Add environment variables before you run the binary.

| ENV Variable | Description | Example Value |
|--|--|--|
|`TMPDIR`|Temporary cache directory. Set to a directory writable by your app|`/data/data/com.myapp/files/TMP`|
|`MAGICK_HOME`|The directory containing imagemagick xml config files. Should be set to the base directory, e.g. `/usr` , with config files being in `/usr/etc`.| `/data/data/com.myapp/files/usr`|
|`ICU_DATA_DIR`|The directory containing the ICU data file (required by icuuc library)|`/data/data/com.myapp/files/usr/icu`|
|`LD_LIBRARY_PATH`|Needed in order for the binary to find the `libc++_shared.so` library (or other libraries if you compiled them into shared instead of static libraries)|`/data/data/com.myapp/files/usr/bin/arm64-v8a`|
