#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#else
#    include <magick/api.h>
#endif
#include "jmagick.h"
#include "magick_ImageInfo.h"



/*
 * Class:     magick_QuantizeInfo
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_QuantizeInfo_init
  (JNIEnv *env, jobject self)
{
    QuantizeInfo *quantizeInfo = NULL;
    jfieldID fid = 0;

    quantizeInfo =
	(QuantizeInfo*) getHandle(env, self, "quantizeInfoHandle", &fid);

    if (quantizeInfo == NULL) {
#if MagickLibVersion < 0x700
	quantizeInfo = (QuantizeInfo *) AcquireMemory(sizeof(QuantizeInfo));
#else
	AcquireMemoryHandler acquire_memory_handler;
	ResizeMemoryHandler resize_memory_handler;
	DestroyMemoryHandler destroy_memory_handler;
	GetMagickMemoryMethods(&acquire_memory_handler, &resize_memory_handler, &destroy_memory_handler);
	quantizeInfo = (QuantizeInfo *) acquire_memory_handler(sizeof(QuantizeInfo));
#endif
	if (quantizeInfo == NULL) {
	    throwMagickException(env, "Unable to allow memory for handle");
	    return;
	}
    }
    GetQuantizeInfo(quantizeInfo);

    setHandle(env, self, "quantizeInfoHandle", (void*) quantizeInfo, &fid);
}



/*
 * Class:     magick_QuantizeInfo
 * Method:    destroyQuantizeInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_QuantizeInfo_destroyQuantizeInfo
  (JNIEnv *env, jobject self)
{
    QuantizeInfo *quantizeInfo = NULL;
    jfieldID handleFid = 0;

    quantizeInfo = (QuantizeInfo*) getHandle(env, self,
				       "quantizeInfoHandle", &handleFid);

    if (quantizeInfo != NULL) {
	setHandle(env, self, "quantizeInfoHandle", NULL, &handleFid);
	DestroyQuantizeInfo(quantizeInfo);
    }
}



/*
 * Class:     magick_QuantizeInfo
 * Method:    setNumberColors
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setNumberColors,
	     number_colors,
	     "quantizeInfoHandle",
	     QuantizeInfo)

/*
 * Class:     magick_QuantizeInfo
 * Method:    getNumberColors
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getNumberColors,
	     number_colors,
	     "quantizeInfoHandle",
	     QuantizeInfo)

/*
 * Class:     magick_QuantizeInfo
 * Method:    setTreeDepth
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setTreeDepth,
	     tree_depth,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getTreeDepth
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getTreeDepth,
	     tree_depth,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    setDither
 * Signature: (I)V
 */
#if MagickLibVersion < 0x700
setIntMethod(Java_magick_QuantizeInfo_setDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo)
#else
setDeprecatedMethod(Java_magick_QuantizeInfo_setDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo,
	     jint)
#endif


/*
 * Class:     magick_QuantizeInfo
 * Method:    getDither
 * Signature: ()I
 */
#if MagickLibVersion < 0x700
getIntMethod(Java_magick_QuantizeInfo_getDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo)
#else
getDeprecatedMethod(Java_magick_QuantizeInfo_getDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo,
	     jint)
#endif


/*
 * Class:     magick_QuantizeInfo
 * Method:    setColorspace
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setColorspace,
	     colorspace,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getColorspace
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getColorspace,
	     colorspace,
	     "quantizeInfoHandle",
	     QuantizeInfo)



/*
 * Class:     magick_QuantizeInfo
 * Method:    setMeasureError
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setMeasureError,
	     measure_error,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getMeasureError
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getMeasureError,
	     measure_error,
	     "quantizeInfoHandle",
	     QuantizeInfo)

