#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#else
#    include <magick/api.h>
#endif
#include "jmagick.h"

#include <android/log.h>
#define APPNAME "Magick"
#define LOG(a) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a);
#define LOG2(a,b) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b);

#ifdef J_ICU4C

#include <unicode/putil.h>

// pass native data dir to UnicodeDataDir
JNIEXPORT void JNICALL Java_magick_Magick_setICUDataDir
  (JNIEnv *env, jobject self, jstring _dir)
{
    const char *dir;

    // u_setDataDirectory(const char *directory);
	dir = (const char *) (*env)->GetStringUTFChars(env, _dir, 0);
	
	LOG2("setICUDataDir(): setting Android ICU data directory to %s\n", dir);
	u_setDataDirectory(dir);
    (*env)->ReleaseStringUTFChars(env, _dir, dir);
}

#else

// pass native data dir to UnicodeDataDir
JNIEXPORT void JNICALL Java_magick_Magick_setICUDataDir
  (JNIEnv *env, jobject self, jstring _dir)
{
	LOG("setICUDataDir(): This is a NO-OP - ICU support is not compiled in\n");
}

#endif