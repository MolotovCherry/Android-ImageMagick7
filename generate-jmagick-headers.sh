#!/bin/bash

#
# Generate jmagick header files for compilation
#
# NOTE: This script works in both WSL and native Linux
# (BTW, I really hate batch, it is clunky and unintuitive)
#
# Copyright (C) 2018 cherryleafroad
#

# script directory
SWD=$(dirname $(realpath $0))
# java magick source code directory
JMSOURCE=$(realpath $SWD/libjmagick-7/android/magick)
# fakeawt java source code directory
FAWTSOURCE=$(realpath $SWD/libjmagick-7/android/fakeawt)
# magick c source code directory
CSOURCE=$SWD/libjmagick-7/src
# temporary directory
TMP=$SWD/tmp

# list of java files needed to generate headers for (no .java extention)
HFILES=(
	QuantizeInfo
	PixelPacket
	MontageInfo
	MagickInfo
	MagickImage
	Magick
	ImageInfo
	DrawInfo
)


# detect if using WSL or native Linux
if grep -qE 'Microsoft|WSL' /proc/version; then
  JAVAC=javac.exe
  JAVAH=javah.exe
else
  JAVAC=javac
  JAVAH=javah
fi

# switch to tmp working directory
mkdir -p $TMP
cd $TMP


# copy all java files into tmp subfolder
mkdir -p magick fakeawt
cp $JMSOURCE/*.java magick
cp $FAWTSOURCE/*.java fakeawt


# compile all magick java files
echo compiling magick java files...
echo
for file in magick/*.java; do
	echo compiling $file...
    $JAVAC $file
done
echo

# start generating headers
for i in "${HFILES[@]}"; do
	echo generating magick_$i.h...
    $JAVAH -o magick/magick_$i.h -jni magick.$i
done
echo

# copy .h files to source c directory
cp magick/*.h $CSOURCE/
echo source .h files copied into $CSOURCE

# cleanup
rm -r $TMP
