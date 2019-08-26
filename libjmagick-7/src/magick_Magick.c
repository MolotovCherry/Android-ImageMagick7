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
#include "magick_Magick.h"

/*
 * Class:     magick_Magick
 * Method:    parseImageGeometry
 * Signature: (Ljava/lang/String;Lfakeawt/Rectangle;)I
 */
JNIEXPORT void JNICALL Java_magick_Magick_init
  (JNIEnv *env, jclass magickClass)
{
	MagickCoreGenesis(NULL, MagickFalse);
}

/*
 * Class:     magick_Magick
 * Method:    terminus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_Magick_terminus
  (JNIEnv *env, jclass magickClass)
{
    MagickCoreTerminus();
}

/*
 * Class:     magick_Magick
 * Method:    parseImageGeometry
 * Signature: (Ljava/lang/String;Lfakeawt/Rectangle;)I
 */
JNIEXPORT jint JNICALL Java_magick_Magick_parseImageGeometry
  (JNIEnv *env, jclass magickClass, jstring geometry, jobject rect)
{
    unsigned long x, y, width, height;
    jint flags;
    const char *cstr;

    if (!getIntFieldValue(env, rect, "width", NULL, (jint *) &width) ||
	!getIntFieldValue(env, rect, "height", NULL, (jint *) &height) ||
	!getIntFieldValue(env, rect, "x", NULL, (jint *) &x) ||
	!getIntFieldValue(env, rect, "y", NULL, (jint *) &y)) {
        throwMagickException(env, "Unable to obtain Rectangle values");
        return 0;
    }

    cstr = (const char *) (*env)->GetStringUTFChars(env, geometry, 0);
#if MagickLibVersion < 0x700
    flags = ParseImageGeometry(cstr, &x, &y, &width, &height);
#else
    flags = ParseMetaGeometry(cstr, (ssize_t *) &x, (ssize_t *) &y, (size_t *) &width, (size_t *) &height);
#endif
    (*env)->ReleaseStringUTFChars(env, geometry, cstr);

    if (!setIntFieldValue(env, rect, "width", NULL, width) ||
	!setIntFieldValue(env, rect, "height", NULL, height) ||
	!setIntFieldValue(env, rect, "x", NULL, x) ||
	!setIntFieldValue(env, rect, "y", NULL, y)) {
        throwMagickException(env, "Unable to set Rectangle values");
        return 0;
    }

    return flags;
}

/*
 * Class:     magick_Magick
 * Method:    queryFonts
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_magick_Magick_queryFonts
  (JNIEnv *env, jclass magickClass, jstring pattern)
{
	char **fonts;
	size_t number_fonts;
	int i;
	ExceptionInfo *exception;
	jobjectArray fontArray;
	exception = AcquireExceptionInfo();
	fonts = GetTypeList((*env)->GetStringUTFChars(env, pattern, 0), &number_fonts, exception);
	DestroyExceptionInfo(exception);
	fontArray = (*env)->NewObjectArray(env, number_fonts, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
	for(i = 0; i < number_fonts; i++) {
		(*env)->SetObjectArrayElement(env, fontArray, i, (*env)->NewStringUTF(env, fonts[i]));
	}
	return fontArray;
}
