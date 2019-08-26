#!/bin/bash

# if your copy of opencl is located here, the script will copy it over
# otherwise, there will be an error. You'll have to find the location yourself

mkdir 64
adb pull /system/vendor/lib64/libOpenCL.so 64/libOpenCL.so
