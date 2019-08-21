# autoregenerated sources makefile. DO NOT EDIT, EDITS WILL BE OVERWRITTEN
sources := altivec.c avx-128-fma.c avx.c avx2.c avx512.c kcvi.c neon.c sse2.c taint.c vsx.c 
LOCAL_SRC_FILES += $(addprefix libfftw-3.3.8/simd-support/, $(sources))
