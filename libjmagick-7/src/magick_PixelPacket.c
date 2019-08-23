#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#    include <MagickWand/MagickWand.h>
#else
#    include <magick/api.h>
#    include <wand/magick-wand.h>
#endif
#include "jmagick.h"
#include "magick_PixelPacket.h"

/*
 * Class:     magick_PixelPacket
 * Method:    queryColorDatabase
 * Signature: (Ljava/lang/String;)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_PixelPacket_queryColorDatabase
    (JNIEnv *env, jclass class, jstring target)
{
#if MagickLibVersion < 0x700
    PixelPacket pixel;
#else
    PixelInfo pixel;
#endif
    const char *cstr;
    unsigned int result;
    jmethodID consMethodID;
    jobject jPixelPacket;
    ExceptionInfo *exception;

    cstr = (*env)->GetStringUTFChars(env, target, 0);
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    result = QueryColorDatabase(cstr, &pixel, exception);
#else
    result = QueryColorCompliance(cstr, AllCompliance, &pixel, exception);
#endif
    (*env)->ReleaseStringUTFChars(env, target, cstr);

    if (!result) {
	throwMagickApiException(env, "Unable to locate color", exception);
        DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    consMethodID = (*env)->GetMethodID(env, class, "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

#ifdef DIAGNOSTIC
    fprintf(stderr, "Query colour %d, %d, %d, %d\n",
            pixel.red,
            pixel.green,
            pixel.blue,
#    if MagickLibVersion < 0x700
            pixel.opacity);
#    else
            pixel.alpha);
#    endif
#endif

    jPixelPacket = (*env)->NewObject(env, class, consMethodID,
				     (jint) pixel.red,
				     (jint) pixel.green,
				     (jint) pixel.blue,
#if MagickLibVersion < 0x700
				     (jint) pixel.opacity);
#else
				     (jint) pixel.alpha);
#endif
    if (jPixelPacket == NULL) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    return jPixelPacket;
}

/*
 * Class:     magick_PixelPacket
 * Method:    getColor
 * Signature: (Ljava/lang/String;)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_PixelPacket_getColor
    (JNIEnv *env, jclass class, jstring target)
{
#if MagickLibVersion < 0x700
    PixelPacket pixel;
#else
    PixelInfo pixel;
#endif
    const char *cstr;
    jmethodID consMethodID;
    jobject jPixelPacket;

    cstr = (*env)->GetStringUTFChars(env, target, 0);
	
	PixelWand *pixelWand = NewPixelWand();
	if (!pixelWand) {
		throwMagickException(env, "Failed to allocate PixelWand structure");
		(*env)->ReleaseStringUTFChars(env, target, cstr);
		return NULL;
	}
	
	if (!PixelSetColor(pixelWand, cstr)) {
		throwMagickException(env, "Unrecognized color string");
		(*env)->ReleaseStringUTFChars(env, target, cstr);
		return NULL;
	}
	
    (*env)->ReleaseStringUTFChars(env, target, cstr);
	
#if MagickLibVersion < 0x700
	PixelGetQuantumColor(pixelWand, &pixel);
#else
	PixelGetQuantumPacket(pixelWand, &pixel);
#endif

    consMethodID = (*env)->GetMethodID(env, class, "<init>", "(IIII)V");
    if (consMethodID == 0) {
		throwMagickException(env, "Unable to construct magick.PixelPacket");
		return NULL;
    }

#ifdef DIAGNOSTIC
    fprintf(stderr, "Colour %d, %d, %d, %d\n",
            pixel.red,
            pixel.green,
            pixel.blue,
#    if MagickLibVersion < 0x700
            pixel.opacity);
#    else
            pixel.alpha);
#    endif
#endif

    jPixelPacket = (*env)->NewObject(env, class, consMethodID,
				     (jint) pixel.red,
				     (jint) pixel.green,
				     (jint) pixel.blue,
#if MagickLibVersion < 0x700
				     (jint) pixel.opacity);
#else
				     (jint) pixel.alpha);
#endif
    if (jPixelPacket == NULL) {
		throwMagickException(env, "Unable to construct magick.PixelPacket");
		return NULL;
    }

    return jPixelPacket;
}
