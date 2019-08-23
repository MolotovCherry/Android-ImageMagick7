#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/MagickCore.h>
#    include <MagickCore/morphology.h>
#else
#    include <magick/api.h>
#endif
#include "jmagick.h"


/*
 * Class:     magick_MagickImage
 * Method:    morphologyImageInternal
 * Signature: (IILjava/lang/String;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_morphologyImageInternal
  (JNIEnv *env, jobject self, jint morphologyMethod, jint iterations, jstring kernelString)
{
    KernelInfo *cKernelInfo;
    MorphologyMethod morphEnum;
    Image *cImage, *morphImage;
    jobject newImage;
    const char *cKernelString;
    ExceptionInfo *exception;
    
    cKernelString = (const char *) (*env)->GetStringUTFChars(env, kernelString, 0);
    
    ssize_t iter = (ssize_t) iterations;

    cImage = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (cImage == NULL) {
        throwMagickException(env, "Unable to obtain MagickImage handle");
        return NULL;
    }
    
    
    // morphology method
    switch (morphologyMethod) {
        case 0:  morphEnum = UndefinedMorphology;         break;
        case 1:  morphEnum = ConvolveMorphology;          break;
        case 2:  morphEnum = CorrelateMorphology;         break;
        case 3:  morphEnum = ErodeMorphology;             break;
        case 4:  morphEnum = DilateMorphology;            break;
        case 5:  morphEnum = ErodeIntensityMorphology;    break;
        case 6:  morphEnum = DilateIntensityMorphology;   break;
        case 7:  morphEnum = IterativeDistanceMorphology; break;
        case 8:  morphEnum = OpenMorphology;              break;
        case 9:  morphEnum = CloseMorphology;             break;
        case 10: morphEnum = OpenIntensityMorphology;     break;
        case 11: morphEnum = CloseIntensityMorphology;    break;
        case 12: morphEnum = SmoothMorphology;            break;
        case 13: morphEnum = EdgeInMorphology;            break;
        case 14: morphEnum = EdgeOutMorphology;           break;
        case 15: morphEnum = EdgeMorphology;              break;
        case 16: morphEnum = TopHatMorphology;            break;
        case 17: morphEnum = BottomHatMorphology;         break;
        case 18: morphEnum = HitAndMissMorphology;        break;
        case 19: morphEnum = ThinningMorphology;          break;
        case 20: morphEnum = ThickenMorphology;           break;
        case 21: morphEnum = DistanceMorphology;          break;
        case 22: morphEnum = VoronoiMorphology;           break;
        default: morphEnum = UndefinedMorphology;         break;
    }

    exception = AcquireExceptionInfo();
    cKernelInfo = AcquireKernelInfo(cKernelString, exception);
    if (cKernelInfo == NULL) {
        (*env)->ReleaseStringUTFChars(env, kernelString, cKernelString);
        throwMagickApiException(env, "Unable to acquire kernel", exception);
        DestroyKernelInfo(cKernelInfo);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    exception = AcquireExceptionInfo();
    morphImage = MorphologyImage(cImage, morphEnum, iter, cKernelInfo, exception);
    if (morphImage == NULL) {
        throwMagickApiException(env, "Unable to do morphology", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);
    
    newImage = newImageObject(env, morphImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(newImage);
#else
        DestroyImageList(newImage);
#endif
		throwMagickException(env, "Cannot create new MagickImage object");
		return NULL;
    }
    
    // cleanup
    (*env)->ReleaseStringUTFChars(env, kernelString, cKernelString);
    DestroyKernelInfo(cKernelInfo);
    
    return newImage;
}
