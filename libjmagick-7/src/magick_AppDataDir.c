//
// Set the App data path, so that Imagemagick knows
// where to get the config.xml files from
//

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#    include <MagickCore/configure.h>
#else
#    include <magick/api.h>
#endif
#include "jmagick.h"

// pass native data directory to ImageMagick:
JNIEXPORT void JNICALL Java_magick_Magick_setAppConfigDataDir
  (JNIEnv *env, jobject self, jstring _dir)
{
    char *dir;

	dir = (char *) (*env)->GetStringUTFChars(env, _dir, 0);
	SetAppConfigDataDir(dir);
    (*env)->ReleaseStringUTFChars(env, _dir, dir);
}
