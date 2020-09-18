libopencl is not allowed to be distributed.

You have to find your own copy to link against.
Go to the play store and download "OpenCL-Z" to see if you have openCL on your device.
If you do, then you can copy the opencl lib from your device.

Create a folder, 32 or 64 respectively (based on the arch of the shared library), then place the copy "libOpenCL.so" into the folder

Make sure to copy over the right lib, 32 or 64bit, depending on which arch you are compiling for
