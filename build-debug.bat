@ECHO OFF

rem cd to current directory
cd %~dp0

ndk-build NDK_DEBUG=1 NDK_OUT=../build/ NDK_LIBS_OUT=../jniLibs -j 4
