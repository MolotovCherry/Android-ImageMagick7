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
#include "magick_MagickImage.h"
#include "jmagick.h"


#include <android/log.h>

#define APPNAME "Magick"

#define LOG(a) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a);
#define LOG2(a,b) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b);


/*
 * Class:     magick_MagickImage
 * Method:    getImageAlphaChannel
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_getImageAlphaChannel
  (JNIEnv *env, jobject self)
{
    Image *cImage;

    cImage = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (cImage == NULL) {
        throwMagickException(env, "Unable to obtain MagickImage handle");
        return MagickFalse;
    }
    
    return GetImageAlphaChannel(cImage);
}

/*
 * Class:     magick_MagickImage
 * Method:    setImageAlphaChannel
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageAlphaChannel
  (JNIEnv *env, jobject self, jint alphaChannelOption)
{
    Image *cImage;
    AlphaChannelOption alphaChannelOptionEnum;
    ExceptionInfo *exception;

    cImage = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (cImage == NULL) {
        throwMagickException(env, "Unable to obtain MagickImage handle");
        return MagickFalse;
    }
    
    switch (alphaChannelOption) {
        case 0:  alphaChannelOptionEnum = UndefinedAlphaChannel;
        case 1:  alphaChannelOptionEnum = ActivateAlphaChannel;
        case 2:  alphaChannelOptionEnum = AssociateAlphaChannel;
        case 3:  alphaChannelOptionEnum = BackgroundAlphaChannel;
        case 4:  alphaChannelOptionEnum = CopyAlphaChannel;
        case 5:  alphaChannelOptionEnum = DeactivateAlphaChannel;
        case 6:  alphaChannelOptionEnum = DiscreteAlphaChannel;
        case 7:  alphaChannelOptionEnum = DisassociateAlphaChannel;
        case 8:  alphaChannelOptionEnum = ExtractAlphaChannel;
        case 9:  alphaChannelOptionEnum = OffAlphaChannel;
        case 10: alphaChannelOptionEnum = OnAlphaChannel;
        case 11: alphaChannelOptionEnum = OpaqueAlphaChannel;
        case 12: alphaChannelOptionEnum = RemoveAlphaChannel;
        case 13: alphaChannelOptionEnum = SetAlphaChannel;
        case 14: alphaChannelOptionEnum = ShapeAlphaChannel;
        case 15: alphaChannelOptionEnum = TransparentAlphaChannel;
        default: alphaChannelOptionEnum = UndefinedAlphaChannel;
    }
    
    exception = AcquireExceptionInfo();
    MagickBooleanType result = SetImageAlphaChannel(cImage, alphaChannelOptionEnum, exception);

    if (result == MagickFalse) {
        throwMagickApiException(env, "Unable to set image alpha channel", exception);
        DestroyExceptionInfo(exception);
        return MagickFalse;
    }
    DestroyExceptionInfo(exception);
    
    return result;
}
