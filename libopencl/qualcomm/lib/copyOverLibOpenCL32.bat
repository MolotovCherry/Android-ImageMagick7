@ECHO off

REM if your copy of opencl is located here, the script will copy it over
REM otherwise, there will be an error. You'll have to find the location yourself

mkdir 32
adb pull /system/vendor/lib/libOpenCL.so 32/libOpenCL.so
