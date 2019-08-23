#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#    include <MagickCore/resource_.h>
#else
#    include <magick/api.h>
#endif
#include "jmagick.h"

///////////////////////////////////////////////////
//
// 	magick_Cache.c
//
//	2016/04/22 D.Slamnig created
//
///////////////////////////////////////////////////

#include <android/log.h>
#define APPNAME "Magick"
#define LOG(a) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a);
#define LOG2(a,b) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b);

// pass native cache dir to ImageMagick:
JNIEXPORT void JNICALL Java_magick_Magick_setCacheDir
  (JNIEnv *env, jobject self, jstring _dir)
{
	char *dir;

	dir = (char *) (*env)->GetStringUTFChars(env, _dir, 0);
	SetCacheDir(dir);
    (*env)->ReleaseStringUTFChars(env, _dir, dir);
}
