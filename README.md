
# Android ImageMagick 7.1.0-54

[![Build](https://github.com/MolotovCherry/Android-ImageMagick7/actions/workflows/build.yml/badge.svg?event=push)](https://github.com/MolotovCherry/Android-ImageMagick7/actions/workflows/build.yml) [![CodeQL](https://github.com/MolotovCherry/Android-ImageMagick7/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/MolotovCherry/Android-ImageMagick7/actions/workflows/codeql-analysis.yml) ![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/MolotovCherry/Android-ImageMagick7?style=plastic)

*This is a developement libary, NOT an app. There is no "APK". There are binaries you can use however. If you want an app, termux has their own imagemagick package*

This is a fully featured imagemagick build compatible with android [__and has Kotlin bindings__](https://github.com/MolotovCherry/kmagick) (check out KMagick below). All libaries used are the absolute latest versions with the latest and greatest features. ___This repo automatically updates itself with the latest imagemagick releases and issues full binary releases!___

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

Check out the release page for the [latest built binaries](https://github.com/MolotovCherry/Android-ImageMagick7/releases). This is built using the [default configuration](https://github.com/MolotovCherry/Android-ImageMagick7/blob/master/Application.mk). If you need a special configuration (for example OpenCL), you will need to build it for yourself from source.

- OpenCL support is available for Qualcomm. OpenCL is recommended over OpenMP. Please [go here](https://github.com/MolotovCherry/Android-ImageMagick7/tree/master/libopencl/qualcomm/lib) in order to learn how to setup OpenCL build for the project.

# KMagick

Check out the [KMagick](https://github.com/MolotovCherry/kmagick) repo for instructions on how to use ImageMagick with Kotlin in your project (instead of the binary).

# Setup, testing, FAQ, and all other questions

Please visit the [wiki](https://github.com/MolotovCherry/Android-ImageMagick7/wiki) for instructions on how to use this project.

\- [Wiki home](https://github.com/MolotovCherry/Android-ImageMagick7/wiki)  
\- [Setup & building instructions](https://github.com/MolotovCherry/Android-ImageMagick7/wiki/Setup--&--building-instructions)  
\- [Running from ADB (for testing)](https://github.com/MolotovCherry/Android-ImageMagick7/wiki/Running-from-ADB-(for-testing))  
\- [FAQ](https://github.com/MolotovCherry/Android-ImageMagick7/wiki/FAQ)

# Questions and everything else
Please use [Discussions](https://github.com/MolotovCherry/Android-ImageMagick7/discussions) for everything else that doesn't fit into an issue report

# Did this library help you?

[![Donate](https://raw.githubusercontent.com/MolotovCherry/Android-ImageMagick7/master/readme_files/donate.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=BKDN933UM444J)

If you found this library useful, please consider showing appreciation and help fund it by sending a donation my way.  
All donations help this project continue to be supported for longer and receive more frequent updates! Thanks for your support! <3
