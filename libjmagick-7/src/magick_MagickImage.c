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

// detect Android debug build
#ifdef NDEBUG
#define DIAGNOSTIC 1
#endif


/*
 * Class:     magick_MagickImage
 * Method:    initMultiImage
 * Signature: ([Lmagick/MagickImage;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_initMultiImage
  (JNIEnv *env, jobject self, jobjectArray images)
{
    Image *image, *newImage, *lastImage, *p;
    jsize arrayLen;
    jobject obj;
    jfieldID fieldID = 0;
    ExceptionInfo *exception;
    int i;

    arrayLen = (*env)->GetArrayLength(env, images);
    if (arrayLen < 1) {
        throwMagickException(env, "No images specified");
        return;
    }

    /* Get the first element in the array and clone it. */
    obj = (*env)->GetObjectArrayElement(env, images, 0);
    if (obj == NULL) {
        throwMagickException(env, "First image in array null");
        return;
    }
    image = (Image*) getHandle(env, obj, "magickImageHandle", &fieldID);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return;
    }

    exception=AcquireExceptionInfo();
    newImage = CloneImage(image, 0, 0, 0, exception);
    if (newImage == NULL) {
        throwMagickApiException(env, "Unable to clone image", exception);
        DestroyExceptionInfo(exception);
        return;
    }
    DestroyExceptionInfo(exception);

    /* Move the lastImage pointer to the last image of the list. */
    for (lastImage = newImage;
         lastImage->next != NULL;
         lastImage = lastImage->next)
        ;

    /* Move the newImage pointer to the head of the list. */
    for (; newImage->previous != NULL; newImage = newImage->previous)
        ;

    /* Clone the other images in the array and append to list */
    for (i = 1; i < arrayLen; i++) {

        /* Get the next image in the array */
        obj = (*env)->GetObjectArrayElement(env, images, i);
        if (obj == NULL) {
            throwMagickException(env, "Image in array index null");
            return;
        }
        image = (Image*) getHandle(env, obj, "magickImageHandle", &fieldID);
        if (image == NULL) {
            throwMagickException(env, "Unable to obtain image handle");
            return;
        }

        /* Clone the image */
        exception=AcquireExceptionInfo();
        image = CloneImage(image, 0, 0, 0, exception);
        if (image == NULL) {
            throwMagickApiException(env, "Unable to clone image", exception);
            DestroyExceptionInfo(exception);
#if MagickLibVersion < 0x700
            DestroyImages(newImage);
#else
            DestroyImageList(newImage);
#endif
            return;
        }
        DestroyExceptionInfo(exception);

        /* Find the head of the list */
        for (p = image; p->previous != NULL; p = p->previous)
            ;

        /* Link it up */
        lastImage->next = p;
        p->previous = lastImage;

        /* Move lastImage to the end of the list */
        for (lastImage = image;
             lastImage->next != NULL;
             lastImage = lastImage->next)
            ;
    }

    /* Set the image handle */
    image = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (image != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(image);
#else
        DestroyImageList(image);
#endif
    }
    setHandle(env, self, "magickImageHandle", (void*) newImage, &fieldID);
}




/*
 * Class:     magick_MagickImage
 * Method:    allocateImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_allocateImage
  (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    /* Allocate the image object. */
#if MagickLibVersion < 0x700
    image = AllocateImage(imageInfo);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    image = AcquireImage(imageInfo, exception);
    DestroyExceptionInfo(exception);
#endif

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}



/*
 * Class:     magick_MagickImage
 * Method:    readImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_readImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    ExceptionInfo *exception;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    /* Read the image. */
#ifdef DIAGNOSTIC
    //fprintf(stderr, "Attempting to read from file %s\n", imageInfo->filename);
    LOG2("Attempting to read from file %s\n", imageInfo->filename);
#endif
    
    exception=AcquireExceptionInfo();
    image = ReadImage(imageInfo, exception);
    if (image == NULL) {
        LOG("MagickImage: unable to read image");
        throwMagickApiException(env, "Unable to read image", exception);
	DestroyExceptionInfo(exception);
	return;
    }
    DestroyExceptionInfo(exception);

#ifdef DIAGNOSTIC
    //fprintf(stderr, "ReadImage completed\n");
    LOG("ReadImage completed\n");
#endif

    
    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}


/*
 * Class:     magick_MagickImage
 * Method:    pingImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_pingImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    ExceptionInfo *exception;


    // Obtain the ImageInfo pointer
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    // Read the image.
#ifdef DIAGNOSTIC
    fprintf(stderr, "Attempting to read from file %s\n", imageInfo->filename);
#endif

    exception=AcquireExceptionInfo();

    image = PingImage(imageInfo, exception);
    if (image == NULL) {
        throwMagickApiException(env, "Unable to ping image", exception);
	DestroyExceptionInfo(exception);
	return;
    }

    DestroyExceptionInfo(exception);

#ifdef DIAGNOSTIC
    fprintf(stderr, "PingImage completed\n");
#endif

    // Get the old image handle and deallocate it (if required).
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    // Store the image into the handle.
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}


/*
 * Class:     magick_MagickImage
 * Method:    writeImage
 * Signature: (Lmagick/ImageInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_writeImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL;
    int status;

    /* Obtain the ImageInfo pointer. */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to write");
	return JNI_FALSE;
    }

    /* Write the image. */
#if MagickLibVersion < 0x700
    status = WriteImage(imageInfo, image);
#else
	ExceptionInfo *exception = AcquireExceptionInfo();
	status = WriteImage(imageInfo, image, exception);
	DestroyExceptionInfo(exception);
#endif

    return (status) ? (JNI_TRUE) : (JNI_FALSE);
}




/*
 * Class:     magick_MagickImage
 * Method:    getFileName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getFileName
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get file name");
	return NULL;
    }

    return (*env)->NewStringUTF(env, image->filename);
}




/*
 * Class:     magick_MagickImage
 * Method:    setFileName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setFileName
    (JNIEnv *env, jobject self, jstring fileName)
{
    Image *image = NULL;
    const char *cstr;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return;
    }

    cstr = (*env)->GetStringUTFChars(env, fileName, 0);
    strcpy(image->filename, cstr);
    (*env)->ReleaseStringUTFChars(env, fileName, cstr);
}




/*
 * Class:     magick_MagickImage
 * Method:    setFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setFilter
  (JNIEnv *env, jobject self, jint filter)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return;
    }

    image->filter = filter;
}


/*
 * Class:     magick_MagickImage
 * Method:    getFilter
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getFilter
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return -1;
    }

    return image->filter;
}




/*
 * Class:     magick_MagickImage
 * Method:    getDimension
 * Signature: ()Lfakeawt/Dimension;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getDimension
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jclass dimensionClass;
    jmethodID consMethodID;
    jobject dimension;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return NULL;
    }
    dimensionClass = (*env)->FindClass(env, "fakeawt/Dimension");
    if (dimensionClass == 0) {
	throwMagickException(env, "Unable to locate class fakeawt.Dimension");
	return NULL;
    }
    consMethodID = (*env)->GetMethodID(env, dimensionClass,
				       "<init>", "(II)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct fakeawt.Dimension");
	return NULL;
    }
    dimension = (*env)->NewObject(env, dimensionClass, consMethodID,
				  image->columns, image->rows);
    if (dimension == NULL) {
	throwMagickException(env, "Unable to construct fakeawt.Dimension");
	return NULL;
    }
    return dimension;
}


/*
 * Class:     magick_MagickImage
 * Method:    addNoiseImage
 * Signature: (I)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_addNoiseImage__I
    (JNIEnv *env, jobject self, jint noiseType)
{
    NoiseType noiseEnum;
    jobject newImage;
    Image *noisyImage;
    ExceptionInfo *exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    switch (noiseType) {
        case 0:  noiseEnum = UndefinedNoise;              break;
        case 1:  noiseEnum = UniformNoise;                break;
        case 2:  noiseEnum = GaussianNoise;               break;
        case 3:  noiseEnum = MultiplicativeGaussianNoise; break;
        case 4:  noiseEnum = ImpulseNoise;                break;
        case 5:  noiseEnum = LaplacianNoise;              break;
        case 6:  noiseEnum = PoissonNoise;                break;
        case 7:  noiseEnum = RandomNoise;                 break;
        default: noiseEnum = UndefinedNoise;              break;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    noisyImage = AddNoiseImage(image, noiseEnum, exception);
#else
    // From the 6.x branch of ImageMagick
    double attenuate=1.0;
    const char *option=GetImageArtifact(image,"attenuate");
    if (option != (char *) NULL)
        attenuate = InterpretLocaleValue(option,(char **) NULL);
    noisyImage = AddNoiseImage(image, noiseEnum, attenuate, exception);
#endif
    if (noisyImage == NULL) {
	throwMagickApiException(env, "Unable to add noise", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, noisyImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(noisyImage);
#else
	DestroyImageList(noisyImage);
#endif
		throwMagickException(env, "Cannot create new MagickImage object");
		return NULL;
    }

    return newImage;
}

/*
 * Class:     magick_MagickImage
 * Method:    addNoiseImage
 * Signature: (ID)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_addNoiseImage__ID
    (JNIEnv *env, jobject self, jint noiseType, jdouble attenuate)
{
    NoiseType noiseEnum;
    jobject newImage;
    Image *noisyImage;
    ExceptionInfo *exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    switch (noiseType) {
        case 0:  noiseEnum = UndefinedNoise;              break;
        case 1:  noiseEnum = UniformNoise;                break;
        case 2:  noiseEnum = GaussianNoise;               break;
        case 3:  noiseEnum = MultiplicativeGaussianNoise; break;
        case 4:  noiseEnum = ImpulseNoise;                break;
        case 5:  noiseEnum = LaplacianNoise;              break;
        case 6:  noiseEnum = PoissonNoise;                break;
        case 7:  noiseEnum = RandomNoise;                 break;
        default: noiseEnum = UndefinedNoise;              break;
    }

    exception = AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    // Pass the parameter through the artifact, then restore the old artifact
    const char *oldOption=GetImageArtifact(image,"attenuate");

	char newOption[23] = "";
	dtoa(newOption, attenuate);
    SetImageArtifact(image, "attenuate", newOption);
	
    noisyImage = AddNoiseImage(image, noiseEnum, exception);
	
	SetImageArtifact(image, "attenuate", oldOption);
#else
    noisyImage = AddNoiseImage(image, noiseEnum, attenuate, exception);
#endif
    if (noisyImage == NULL) {
	throwMagickApiException(env, "Unable to add noise", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, noisyImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(noisyImage);
#else
	DestroyImageList(noisyImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}


/*
 * Class:     magick_MagickImage
 * Method:    getDepth
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDepth,
    depth,
    "magickImageHandle",
    Image)


/*
 * Class:     magick_MagickImage
 * Method:    setDepth
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDepth,
    depth,
    "magickImageHandle",
    Image)


/*
 * Class:     magick_MagickImage
 * Method:    blurImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_blurImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    blurredImage = BlurImage(image, radius, sigma, exception);
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(blurredImage);
#else
	DestroyImageList(blurredImage);
#endif
	throwMagickException(env, "Unable to create new blurred image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    getStorageClass
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getStorageClass
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return -1;
    }

    return image->storage_class;
}





/*
 * Class:     magick_MagickImage
 * Method:    annotateImage
 * Signature: (Lmagick/AnnotateInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_annotateImage
    (JNIEnv *env, jobject self, jobject drawInfo)
{
    Image *image;
    DrawInfo *dInfo;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    dInfo = (DrawInfo*) getHandle(env, drawInfo,
				  "drawInfoHandle", NULL);

#if MagickLibVersion < 0x700
    AnnotateImage(image, dInfo);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    AnnotateImage(image, dInfo, exception);
    DestroyExceptionInfo(exception);
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    charcoalImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_charcoalImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *charcoalImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    charcoalImage = CharcoalImage(image, radius, sigma, exception);
    if (charcoalImage == NULL) {
	throwMagickApiException(env, "Cannot charcoal image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, charcoalImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(charcoalImage);
#else
	DestroyImageList(charcoalImage);
#endif
	throwMagickException(env, "Unable to create new charcoal image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    borderImage
 * Signature: (Lfakeawt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_borderImage__Lfakeawt_Rectangle_2
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *borderedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception = AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    borderedImage = BorderImage(image, &iRect, exception);
#else
    borderedImage = BorderImage(image, &iRect, image->compose, exception);
#endif
    if (borderedImage == NULL) {
	throwMagickApiException(env, "Cannot border image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, borderedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(borderedImage);
#else
	DestroyImageList(borderedImage);
#endif
	throwMagickException(env, "Unable to create border image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    borderImage
 * Signature: (Lfakeawt/Rectangle;I)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_borderImage__Lfakeawt_Rectangle_2I
    (JNIEnv *env, jobject self, jobject jRect, jint compositeOperator)
{
    RectangleInfo iRect;
    Image *image = NULL, *borderedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    if (!getRectangle(env, jRect, &iRect)) {
		throwMagickException(env, "Cannot retrieve rectangle information");
		return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
		throwMagickException(env, "Cannot retrieve image handle");
		return NULL;
    }

    exception = AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    int oldCompositeOperator = image->compose;
    image->compose = compositeOperator;

    borderedImage = BorderImage(image, &iRect, exception);

    image->compose = oldCompositeOperator;
#else
    borderedImage = BorderImage(image, &iRect, compositeOperator, exception);
#endif
    if (borderedImage == NULL) {
        throwMagickApiException(env, "Cannot border image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, borderedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(borderedImage);
#else
        DestroyImageList(borderedImage);
#endif
        throwMagickException(env, "Unable to create border image");
        return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    raiseImage
 * Signature: (Lfakeawt/Rectangle;Z)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_raiseImage
    (JNIEnv *env, jobject self, jobject jRect, jboolean raise)
{
    RectangleInfo iRect;
    Image *image = NULL;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return RaiseImage(image, &iRect, raise);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = RaiseImage(image, &iRect, raise, exception);
	DestroyExceptionInfo(exception);
	return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    chopImage
 * Signature: (Lfakeawt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_chopImage
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *choppedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    choppedImage = ChopImage(image, &iRect, exception);
    if (choppedImage == NULL) {
	throwMagickApiException(env, "Cannot chop image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, choppedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(choppedImage);
#else
	DestroyImageList(choppedImage);
#endif
	throwMagickException(env, "Unable to chop image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    colorizeImage
 * Signature: (Ljava/lang/String;Lmagick/PixelPacket;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_colorizeImage
  (JNIEnv *env, jobject self, jstring opacity, jobject target)
{
    Image *image = NULL;
    Image *newImage = NULL;
    const char *cstrOpacity = NULL;
    ExceptionInfo *exception;
#if MagickLibVersion < 0x700
    PixelPacket pixel;
#else
    PixelInfo pixel;
#endif
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return NULL;
    }

    if (!getPixelPacket(env, target, &pixel)) {
	throwMagickException(env, "Unable to get pixel values");
	return NULL;
    }

    cstrOpacity = (*env)->GetStringUTFChars(env, opacity, 0);
    if (cstrOpacity == NULL) {
	throwMagickException(env, "Unable to get opacity value");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    newImage = ColorizeImage(image, cstrOpacity, &pixel, exception);
    (*env)->ReleaseStringUTFChars(env, opacity, cstrOpacity);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to colorize image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(newImage);
#else
	DestroyImageList(newImage);
#endif
	throwMagickException(env, "Unable to create colorized image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    compositeImage
 * Signature: (ILmagick/MagickImage;ZII)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_compositeImage__ILmagick_MagickImage_2ZII
    (JNIEnv *env, jobject self, jint compOp,
     jobject compImage, jboolean clipToSelf, jint xOffset, jint yOffset)
{
    Image *image = NULL, *comp = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve image handle");
	return JNI_FALSE;
    }

    comp = (Image*) getHandle(env, compImage, "magickImageHandle", NULL);
    if (comp == NULL) {
	throwMagickException(env, "Unable to retrieve composite image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return CompositeImage(image, compOp, comp, xOffset, yOffset);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = CompositeImage(image, comp, compOp, clipToSelf, xOffset, yOffset, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}

/*
 * Class:     magick_MagickImage
 * Method:    compositeImage
 * Signature: (ILmagick/MagickImage;II)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_compositeImage__ILmagick_MagickImage_2II
    (JNIEnv *env, jobject self, jint compOp,
     jobject compImage, jint xOffset, jint yOffset)
{
    return Java_magick_MagickImage_compositeImage__ILmagick_MagickImage_2ZII(env, self, compOp, compImage, JNI_TRUE, xOffset, yOffset);
}


/*
 * Class:     magick_MagickImage
 * Method:    contrastImage
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_contrastImage
    (JNIEnv *env, jobject self, jboolean sharpen)
{
    Image *image = NULL;

    image = getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return ContrastImage(image, sharpen);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = ContrastImage(image, sharpen, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    cloneImage
 * Signature: (IIZ)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_cloneImage
    (JNIEnv *env, jobject self, jint columns, jint rows, jboolean clonePixels)
{
    Image *image = NULL, *clone = NULL;
    jfieldID handleFid = 0;
    jobject clonedImage;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", &handleFid);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    clone = CloneImage(image, columns, rows, clonePixels, exception);
    if (clone == NULL) {
	throwMagickApiException(env, "Unable to clone image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    clonedImage = newImageObject(env, clone);
    if (clonedImage == NULL) {
	throwMagickException(env, "Unable to create clone image instance");
	return NULL;
    }

    return clonedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[B)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3B
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map,
     jbyteArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
    jbyte *pixelArray;
    const char *mapStr;
    ExceptionInfo *exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

    pixelArray = (*env)->GetByteArrayElements(env, pixels, 0);

#ifdef DIAGNOSTIC
    fprintf(stderr, "Image width is %d, height is %d\n", width, height);
#endif

    /* Create that image. */
    exception=AcquireExceptionInfo();
    image = ConstituteImage(width, height, mapStr,
			    CharPixel, pixelArray, exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	(*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);
	DestroyExceptionInfo(exception);
	return;
    }
    DestroyExceptionInfo(exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);
}

/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[I)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3I
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map,
     jintArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
#if MagickLibVersion < 0x700
    jint *pixelArray;
#else
    jlong *pixelArray;
#endif
    const char *mapStr;
    ExceptionInfo *exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

#if MagickLibVersion < 0x700
    pixelArray = (*env)->GetIntArrayElements(env, pixels, 0);
#else
    pixelArray = (*env)->GetLongArrayElements(env, pixels, 0);
#endif

    /* Create that image. */
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    image = ConstituteImage(width, height, mapStr, IntegerPixel,
#else
    image = ConstituteImage(width, height, mapStr, LongPixel,
#endif
			    pixelArray, exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
#if MagickLibVersion < 0x700
	(*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);
#else
	(*env)->ReleaseLongArrayElements(env, pixels, pixelArray, 0);
#endif
	DestroyExceptionInfo(exception);
	return;
    }
    DestroyExceptionInfo(exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);

#if MagickLibVersion < 0x700
    (*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);
#else
    (*env)->ReleaseLongArrayElements(env, pixels, pixelArray, 0);
#endif
}

/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[F)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3F
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map, jfloatArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
    jfloat *pixelArray;
    const char *mapStr;
    ExceptionInfo *exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

    pixelArray = (*env)->GetFloatArrayElements(env, pixels, 0);

    /* Create that image. */
    exception=AcquireExceptionInfo();
    image = ConstituteImage(width, height, mapStr,
			    FloatPixel, pixelArray, exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	(*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);
	DestroyExceptionInfo(exception);
	return;
    }
    DestroyExceptionInfo(exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
	DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);
}




/*
 * Class:     magick_MagickImage
 * Method:    cropImage
 * Signature: (Lfakeawt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_cropImage
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *croppedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    croppedImage = CropImage(image, &iRect, exception);
    if (croppedImage == NULL) {
	throwMagickApiException(env, "Cannot crop image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, croppedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(croppedImage);
#else
	DestroyImageList(croppedImage);
#endif
	throwMagickException(env, "Unable to crop image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    cycleColormapImage
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_cycleColormapImage
    (JNIEnv *env, jobject self, jint amount)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve handle");
	return;
    }

#if MagickLibVersion < 0x700
    CycleColormapImage(image, amount);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    CycleColormapImage(image, amount, exception);
    DestroyExceptionInfo(exception);
#endif
}


/*
 * Class:     magick_MagickImage
 * Method:    edgeImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_edgeImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *edgedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    edgedImage = EdgeImage(image, radius, exception);
    if (edgedImage == NULL) {
	throwMagickApiException(env, "Cannot edge image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, edgedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(edgedImage);
#else
	DestroyImageList(edgedImage);
#endif
	throwMagickException(env, "Unable to create new edged image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    embossImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_embossImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *embossedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    embossedImage = EmbossImage(image, radius, sigma, exception);
    if (embossedImage == NULL) {
	throwMagickApiException(env, "Cannot emboss image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, embossedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(embossedImage);
#else
	DestroyImageList(embossedImage);
#endif
	throwMagickException(env, "Unable to create new embossed image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    enhanceImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_enhanceImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *enhancedImage;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    enhancedImage = EnhanceImage(image, exception);
    if (enhancedImage == NULL) {
	throwMagickApiException(env, "Cannot enhance image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, enhancedImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(enhancedImage);
#else
	DestroyImageList(enhancedImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    destroyImages
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_destroyImages
    (JNIEnv *env, jobject self)
{
    jfieldID handleFid = 0;
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", &handleFid);
    if (image != NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(image);
#else
	DestroyImageList(image);
#endif
    }
    setHandle(env, self, "magickImageHandle", NULL, &handleFid);
}




/*
 * Class:     magick_MagickImage
 * Method:    drawImage
 * Signature: (Lmagick/DrawInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_drawImage
    (JNIEnv *env, jobject self, jobject drawInfoObj)
{
    DrawInfo *drawInfo;
    Image *image;

    drawInfo = (DrawInfo*) getHandle(env, drawInfoObj,
				     "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
	throwMagickException(env, "Cannot obtain DrawInfo handle");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#ifdef DIAGNOSTIC
    printf("Primitive: %s\n", drawInfo->primitive);
    printf("Font: %s\n", drawInfo->font);
    printf("encoding: %s\n", drawInfo->encoding);
#endif

#if MagickLibVersion < 0x700
    return DrawImage(image, drawInfo);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = DrawImage(image, drawInfo, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    getTypeMetric
 * Signature: (Lmagick/DrawInfo;)Lmagick/TypeMetric;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getTypeMetrics
    (JNIEnv *env, jobject self, jobject drawInfoObj)
{
    TypeMetric typeMetric;
    jclass typeMetricClass;
    jmethodID consMethodID;
    jobject typeMetricObject;

    DrawInfo *drawInfo;
    Image *image;

    drawInfo = (DrawInfo*) getHandle(env, drawInfoObj,
				     "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
	throwMagickException(env, "Cannot obtain DrawInfo handle");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    MagickBooleanType ret = GetTypeMetrics(image, drawInfo, &typeMetric);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    MagickBooleanType ret = GetTypeMetrics(image, drawInfo, &typeMetric, exception);
    DestroyExceptionInfo(exception);
#endif

#ifdef DIAGNOSTIC
    fprintf(stderr, "Metrics: text: %s; "
	    "width: %g; height: %g; ascent: %g; descent: %g; max advance: %g; "
	    "bounds: %g,%g  %g,%g; origin: %g,%g; pixels per em: %g,%g; "
	    "underline position: %g; underline thickness: %g\n",drawInfo->text,
	    typeMetric.width,typeMetric.height,typeMetric.ascent,typeMetric.descent,
	    typeMetric.max_advance,typeMetric.bounds.x1,typeMetric.bounds.y1,
	    typeMetric.bounds.x2,typeMetric.bounds.y2,typeMetric.origin.x,typeMetric.origin.y,
	    typeMetric.pixels_per_em.x,typeMetric.pixels_per_em.y,
	    typeMetric.underline_position,typeMetric.underline_thickness);
#endif


    typeMetricClass = (*env)->FindClass(env, "magick/TypeMetric");
    if (typeMetricClass == 0) {
        throwMagickException(env, "Unable to locate class magick/TypeMetric");
        return NULL;
    }
    consMethodID = (*env)->GetMethodID(env, typeMetricClass,
				       "<init>", "(DD" "DDDDDDD" "DDDD" "DD)V");
    if (consMethodID == 0) {
        throwMagickException(env, "Unable to construct magick/TypeMetric");
        return NULL;
    }
    typeMetricObject = (*env)->NewObject(env, typeMetricClass, consMethodID,
    	typeMetric.pixels_per_em.x, typeMetric.pixels_per_em.y,
        typeMetric.ascent, typeMetric.descent,
        typeMetric.width, typeMetric.height, typeMetric.max_advance,
        typeMetric.underline_position, typeMetric.underline_thickness,
        typeMetric.bounds.x1, typeMetric.bounds.y1, typeMetric.bounds.x2, typeMetric.bounds.y2,
        typeMetric.origin.x, typeMetric.origin.y);
    if (typeMetricObject == NULL) {
        throwMagickException(env, "Unable to construct magick/TypeMetric");
        return NULL;
    }
    return typeMetricObject;
}

/*
 * Class:     magick_MagickImage
 * Method:    equalizeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_equalizeImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return EqualizeImage(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = EqualizeImage(image, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    flipImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_flipImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *flippedImage;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    flippedImage = FlipImage(image, exception);
    if (flippedImage == NULL) {
	throwMagickApiException(env, "Cannot flip image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, flippedImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(flippedImage);
#else
	DestroyImageList(flippedImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    flopImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_flopImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *floppedImage;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    floppedImage = FlopImage(image, exception);
    if (floppedImage == NULL) {
	throwMagickApiException(env, "Cannot flop image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, floppedImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(floppedImage);
#else
	DestroyImageList(floppedImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    gaussianBlurImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_gaussianBlurImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    blurredImage = GaussianBlurImage(image, radius, sigma, exception);
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(blurredImage);
#else
	DestroyImageList(blurredImage);
#endif
	throwMagickException(env, "Unable to create Gaussian blurred image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    implodeImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_implodeImage__D
  (JNIEnv *env, jobject self, jdouble amount)
{
    return Java_magick_MagickImage_implodeImage__DI(env, self, amount, UndefinedInterpolatePixel);
}

/*
 * Class:     magick_MagickImage
 * Method:    implodeImage
 * Signature: (DI)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_implodeImage__DI
  (JNIEnv *env, jobject self, jdouble amount, jint pixelInterpolateMethod)
{
    Image *image = NULL, *implodedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    implodedImage = ImplodeImage(image, amount, exception);
#else
    implodedImage = ImplodeImage(image, amount, pixelInterpolateMethod, exception);
#endif
    if (implodedImage == NULL) {
	throwMagickApiException(env, "Cannot implode image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, implodedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(implodedImage);
#else
	DestroyImageList(implodedImage);
#endif
	throwMagickException(env, "Unable to create imploded image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    gammaImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_gammaImage
    (JNIEnv *env, jobject self, jstring gamma)
{
    const char *cstr;
    unsigned int result;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, gamma, 0);
#if MagickLibVersion < 0x700
    result = GammaImage(image, (char*) cstr);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();

    GeometryInfo geometryInfo;
    MagickStatusType flags = ParseGeometry(cstr, &geometryInfo);
    GammaImage(image, (double) geometryInfo.rho, exception);

    DestroyExceptionInfo(exception);
#endif
    (*env)->ReleaseStringUTFChars(env, gamma, cstr);
    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    isGrayImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isGrayImage
    (JNIEnv *env, jobject self)
{
    int result;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    exception=AcquireExceptionInfo();
    result = IsGrayImage(image, exception);
    DestroyExceptionInfo(exception);
#else
    result = IsImageGray(image);
#endif

    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    isMonochromeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isMonochromeImage
    (JNIEnv *env, jobject self)
{
    ExceptionInfo *exception;
    int result;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    /* Problem here is that although we have an error, how */
    /* do we know that an error has occur? */
#if MagickLibVersion < 0x700
    exception=AcquireExceptionInfo();
    result = IsMonochromeImage(image, exception);
    DestroyExceptionInfo(exception);
#else
    result = IsImageMonochrome(image);
#endif

    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    magnifyImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_magnifyImage
  (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *magnifiedImage;
    ExceptionInfo *exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    magnifiedImage = MagnifyImage(image, exception);
    if (magnifiedImage == NULL) {
	throwMagickApiException(env, "Unable to magnify image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, magnifiedImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(magnifiedImage);
#else
	DestroyImageList(magnifiedImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}



/*
 * Class:     magick_MagickImage
 * Method:    matteFloodfillImage
 * Signature: (Lmagick/RunlengthPacket;IIII)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_matteFloodfillImage
  (JNIEnv *env, jobject self,
   jobject target, jint matte, jint x, jint y, jint method)
{
#if MagickLibVersion < 0x700
    PixelPacket pixPack;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return -1;
    }

    if (!getPixelPacket(env, target, &pixPack)) {
	throwMagickException(env, "Unable get target PixelPacket");
	return -1;
    }

    return MatteFloodfillImage(image, pixPack, matte, x, y, method);
#else
    return JNI_TRUE;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    medianFilterImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_medianFilterImage
  (JNIEnv *env, jobject self, jdouble radius)
{
#if MagickLibVersion < 0x700
    Image *image = NULL, *filteredImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    filteredImage = MedianFilterImage(image, radius, exception);
    if (filteredImage == NULL) {
	throwMagickApiException(env, "Cannot median-filter image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, filteredImage);
    if (newObj == NULL) {
	DestroyImages(filteredImage);
	throwMagickException(env, "Unable to create median-filtered image");
	return NULL;
    }

    return newObj;
#else
    return self;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    colorFloodfillImage
 * Signature: (Lmagick/DrawInfo;Lmagick/PixelPacket;III)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_colorFloodfillImage
  (JNIEnv *env, jobject self, jobject drawInfo, jobject target,
   jint x, jint y, jint paintMethod)
{
#if MagickLibVersion < 0x700
    PixelPacket pix;
#else
    PixelInfo pix;
#endif
    Image *image =
        (Image*) getHandle(env, self, "magickImageHandle", NULL);
    DrawInfo *dInfo;
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return -1;
    }

    dInfo = (DrawInfo*) getHandle(env, drawInfo, "drawInfoHandle", NULL);
    if (dInfo == NULL) {
        throwMagickException(env, "Cannot obtain DrawInfo handle");
        return -1;
    }

    if (!getPixelPacket(env, target, &pix)) {
	throwMagickException(env, "Unable get target pixel");
	return -1;
    }
#if MagickLibVersion < 0x700
    return ColorFloodfillImage(image, dInfo, pix, x, y, paintMethod);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = FloodfillPaintImage(image, dInfo, &pix, x, y, paintMethod == FillToBorderMethod, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    minifyImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_minifyImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *minifiedImage;
    ExceptionInfo *exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    minifiedImage = MinifyImage(image, exception);
    if (minifiedImage == NULL) {
	throwMagickApiException(env, "Unable to minify image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, minifiedImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(minifiedImage);
#else
	DestroyImageList(minifiedImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    modulateImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_modulateImage
    (JNIEnv *env, jobject self, jstring modulate)
{
    const char *cstr;
    int result;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, modulate, 0);
#if MagickLibVersion < 0x700
    result = ModulateImage(image, (char*) cstr);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    result = ModulateImage(image, (char*) cstr, exception);
    DestroyExceptionInfo(exception);
#endif
    (*env)->ReleaseStringUTFChars(env, modulate, cstr);
    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    oilPaintImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_oilPaintImage__D
  (JNIEnv *env, jobject self, jdouble radius)
{
    return Java_magick_MagickImage_oilPaintImage__DD(env, self, radius, 0.5);
}

/*
 * Class:     magick_MagickImage
 * Method:    oilPaintImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_oilPaintImage__DD
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *paintedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    paintedImage = OilPaintImage(image, radius, exception);
#else
    paintedImage = OilPaintImage(image, radius, sigma, exception);
#endif
    if (paintedImage == NULL) {
	throwMagickApiException(env, "Cannot oil-paint image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, paintedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(paintedImage);
#else
	DestroyImageList(paintedImage);
#endif
	throwMagickException(env, "Unable to create oil-paint image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    negateImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_negateImage
    (JNIEnv *env, jobject self, jint grayscale)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return NegateImage(image, grayscale);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = NegateImage(image, grayscale, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif    
}

/*
 * Class:     magick_MagickImage
 * Method:    reduceNoiseImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_reduceNoiseImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *filteredImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    filteredImage = ReduceNoiseImage(image, radius, exception);
#else
    filteredImage = StatisticImage(image, NonpeakStatistic, (size_t) radius, (size_t) radius, exception);
#endif
    if (filteredImage == NULL) {
	throwMagickApiException(env, "Cannot peak-filter image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, filteredImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(filteredImage);
#else
	DestroyImageList(filteredImage);
#endif
	throwMagickException(env, "Unable to create peak-filtered image");
	return NULL;
    }

    return newObj;
}





/*
 * Class:     magick_MagickImage
 * Method:    normalizeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_normalizeImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return NormalizeImage(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = NormalizeImage(image, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    opaqueImage
 * Signature: (Lmagick/PixelPacket;Lmagick/PixelPacket;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_opaqueImage
    (JNIEnv *env, jobject self, jobject target, jobject penColor)
{
#if MagickLibVersion < 0x700
    PixelPacket ppTarget, ppPenColor;
#else
    PixelInfo ppTarget, ppPenColor;
#endif

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    if (!getPixelPacket(env, target, &ppTarget) ||
	!getPixelPacket(env, penColor, &ppPenColor)) {
	throwMagickException(env, "Unable to obtain pixel values");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return OpaqueImage(image, ppTarget, ppPenColor);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = OpaquePaintImage(image, &ppTarget, &ppPenColor, MagickFalse, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    rgbTransformImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_rgbTransformImage
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return RGBTransformImage(image, colorspace);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = TransformImageColorspace(image, colorspace, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    rollImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_rollImage
    (JNIEnv *env, jobject self, jint xOffset, jint yOffset)
{
    jobject newImage;
    Image *rolledImage;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    rolledImage = RollImage(image, xOffset, yOffset, exception);
    if (rolledImage == NULL) {
	throwMagickApiException(env, "Unable to roll image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, rolledImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(rolledImage);
#else
	DestroyImageList(rolledImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    sampleImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_sampleImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    jobject newImage;
    Image *sampledImage;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    sampledImage = SampleImage(image, cols, rows, exception);
    if (sampledImage == NULL) {
	throwMagickApiException(env, "Unable to sample image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newImage = newImageObject(env, sampledImage);
    if (newImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(sampledImage);
#else
	DestroyImageList(sampledImage);
#endif
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}


/*
 * Class:     magick_MagickImage
 * Method:    segmentImage
 * Signature: (IDD)I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_segmentImage
    (JNIEnv *env, jobject self, jint colorspace, jdouble cluster_threshold,
                                                 jdouble smoothing_threshold)
{
    ColorspaceType colorspaceEnum;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    switch (colorspace) {
        case  0: colorspaceEnum = UndefinedColorspace;   break;
        case  1: colorspaceEnum = CMYColorspace;         break;
        case  2: colorspaceEnum = CMYKColorspace;        break;
        case  3: colorspaceEnum = GRAYColorspace;        break;
        case  4: colorspaceEnum = HCLColorspace;         break;
        case  5: colorspaceEnum = HCLpColorspace;        break;
        case  6: colorspaceEnum = HSBColorspace;         break;
        case  7: colorspaceEnum = HSIColorspace;         break;
        case  8: colorspaceEnum = HSLColorspace;         break;
        case  9: colorspaceEnum = HSVColorspace;         break;
        case 10: colorspaceEnum = HWBColorspace;         break;
        case 11: colorspaceEnum = LabColorspace;         break;
        case 12: colorspaceEnum = LCHColorspace;         break;
        case 13: colorspaceEnum = LCHabColorspace;       break;
        case 14: colorspaceEnum = LCHuvColorspace;       break;
        case 15: colorspaceEnum = LogColorspace;         break;
        case 16: colorspaceEnum = LMSColorspace;         break;
        case 17: colorspaceEnum = LuvColorspace;         break;
        case 18: colorspaceEnum = OHTAColorspace;        break;
        case 19: colorspaceEnum = Rec601YCbCrColorspace; break;
        case 20: colorspaceEnum = Rec709YCbCrColorspace; break;
        case 21: colorspaceEnum = RGBColorspace;         break;
        case 22: colorspaceEnum = scRGBColorspace;       break;
        case 23: colorspaceEnum = sRGBColorspace;        break;
        case 24: colorspaceEnum = TransparentColorspace; break;
        case 25: colorspaceEnum = xyYColorspace;         break;
        case 26: colorspaceEnum = XYZColorspace;         break;
        case 27: colorspaceEnum = YCbCrColorspace;       break;
        case 28: colorspaceEnum = YCCColorspace;         break;
        case 29: colorspaceEnum = YDbDrColorspace;       break;
        case 30: colorspaceEnum = YIQColorspace;         break;
        case 31: colorspaceEnum = YPbPrColorspace;       break;
        case 32: colorspaceEnum = YUVColorspace;         break;
        default: colorspaceEnum = RGBColorspace;         break;
    }

#if MagickLibVersion < 0x700
    return SegmentImage(image, colorspaceEnum, 0, cluster_threshold,
                                                  smoothing_threshold);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = SegmentImage(image, colorspaceEnum, 0, cluster_threshold,
                                                  smoothing_threshold, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    solarizeImage
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_solarizeImage
    (JNIEnv *env, jobject self, jdouble threshold)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

#if MagickLibVersion < 0x700
    SolarizeImage(image, threshold);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    SolarizeImage(image, threshold, exception);
    DestroyExceptionInfo(exception);
#endif
}


/*
 * Class:     magick_MagickImage
 * Method:    setColorFuzz
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setColorFuzz
    (JNIEnv *env, jobject self, jdouble fuzz)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    image->fuzz= QuantumRange * fuzz;
}


/*
 * Class:     magick_MagickImage
 * Method:    getBoundingBox
 * Signature: ()Lfakeawt/Rectangle;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getBoundingBox
  (JNIEnv *env, jobject self)
{
    ExceptionInfo *exception;
    Image *image = NULL;
    jclass rectangleClass;
    jmethodID consMethodID;
    jobject rectangle;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
    throwMagickException(env, "Unable to retrieve handle");
    return NULL;
    }

    rectangleClass = (*env)->FindClass(env, "fakeawt/Rectangle");
    if (rectangleClass == 0) {
    throwMagickException(env, "Unable to locate class fakeawt.Rectangle");
    return NULL;
    }
    consMethodID = (*env)->GetMethodID(env, rectangleClass,
                       "<init>", "(IIII)V");
    if (consMethodID == 0) {
    throwMagickException(env, "Unable to construct fakeawt.Rectangle");
    return NULL;
    }

    exception=AcquireExceptionInfo();
    RectangleInfo info = GetImageBoundingBox(image, exception);
    rectangle = (*env)->NewObject(env, rectangleClass, consMethodID,
                  info.x, info.y, info.width, info.height);
    if (rectangle == NULL) {
    throwMagickException(env, "Unable to construct fakeawt.Rectangle");
    DestroyExceptionInfo(exception);
    return NULL;
    }
    DestroyExceptionInfo(exception);

    return rectangle;
}


/*
 * Class:     magick_MagickImage
 * Method:    scaleImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_scaleImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    Image *image = NULL;
    Image *scaledImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle",
			       &magickImageHandleFid);
    if (image == NULL) {
	throwMagickException(env, "No image to scale");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    scaledImage = ScaleImage(image,
			     (unsigned int) cols,
			     (unsigned int) rows,
			     exception);
    if (scaledImage == NULL) {
	throwMagickApiException(env, "Unable to scale image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    returnedImage = newImageObject(env, scaledImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(scaledImage);
#else
	DestroyImageList(scaledImage);
#endif
	throwMagickException(env, "Unable to construct magick.MagickImage");
	return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
	      (void*) scaledImage, &magickImageHandleFid);

    return returnedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    resizeImage
 * Signature: (IID)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_resizeImage__IID
  (JNIEnv *env, jobject self, jint cols, jint rows, jdouble blur)
{
    Image *image = NULL;
    Image *resizedImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;
    int i, numImages;

    image = (Image*) getHandle(env, self, "magickImageHandle",
                   &magickImageHandleFid);
    if (image == NULL) {
    throwMagickException(env, "No image to resize");
    return NULL;
    }

    exception=AcquireExceptionInfo();
    resizedImage = ResizeImage(image,
                 (unsigned int) cols,
                 (unsigned int) rows,
                             image->filter,
#if MagickLibVersion < 0x700
                 (double)    blur,
#endif
                 exception);
    if (resizedImage == NULL) {
        throwMagickApiException(env, "Unable to resize image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    returnedImage = newImageObject(env, resizedImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(resizedImage);
#else
        DestroyImageList(resizedImage);
#endif
        throwMagickException(env, "Unable to construct magick.MagickImage");
        return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
          (void*) resizedImage, &magickImageHandleFid);

    return returnedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    extentImage
 * Signature: (III)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_extentImage
  (JNIEnv *env, jobject self, jint cols, jint rows, jint gravity)
{
    Image *image = NULL;
    Image *extendedImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;
    int i, numImages;

    image = (Image*) getHandle(env, self, "magickImageHandle",
                   &magickImageHandleFid);
    if (image == NULL) {
    throwMagickException(env, "No image to extent");
    return NULL;
    }

    RectangleInfo geometry;
    SetGeometry(image,&geometry);
    geometry.width=cols;
    geometry.height=rows;
    GravityAdjustGeometry(image->columns,image->rows,gravity,&geometry);

    exception=AcquireExceptionInfo();
    extendedImage = ExtentImage(image, &geometry, exception);
    if (extendedImage == NULL) {
    throwMagickApiException(env, "Unable to extent image", exception);
    DestroyExceptionInfo(exception);
    return NULL;
    }
    DestroyExceptionInfo(exception);

    returnedImage = newImageObject(env, extendedImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(extendedImage);
#else
    DestroyImageList(extendedImage);
#endif
    throwMagickException(env, "Unable to construct magick.MagickImage");
    return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
          (void*) extendedImage, &magickImageHandleFid);

    return returnedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    spreadImage
 * Signature: (I)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_spreadImage__I
  (JNIEnv *env, jobject self, jint radius)
{
    return Java_magick_MagickImage_spreadImage__II(env, self, radius, UndefinedInterpolatePixel);
}

/*
 * Class:     magick_MagickImage
 * Method:    spreadImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_spreadImage__II
  (JNIEnv *env, jobject self, jint radius, jint pixelInterpolateMethod)
{
    Image *image = NULL, *randomizedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    randomizedImage = SpreadImage(image, radius, exception);
#else
    randomizedImage = SpreadImage(image, radius, pixelInterpolateMethod, exception);
#endif
    if (randomizedImage == NULL) {
	throwMagickApiException(env, "Cannot spread image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, randomizedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(randomizedImage);
#else
	DestroyImageList(randomizedImage);
#endif
	throwMagickException(env, "Unable to create spread image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    swirlImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_swirlImage__D
  (JNIEnv *env, jobject self, jdouble degrees)
{
    return Java_magick_MagickImage_swirlImage__DI(env, self, degrees, UndefinedInterpolatePixel);
}

/*
 * Class:     magick_MagickImage
 * Method:    swirlImage
 * Signature: (DI)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_swirlImage__DI
  (JNIEnv *env, jobject self, jdouble degrees, jint pixelInterpolateMethod)
{
    Image *image = NULL, *swirledImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    swirledImage = SwirlImage(image, degrees, exception);
#else
    swirledImage = SwirlImage(image, degrees, pixelInterpolateMethod, exception);
#endif
    if (swirledImage == NULL) {
	throwMagickApiException(env, "Cannot swirl image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, swirledImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(swirledImage);
#else
	DestroyImageList(swirledImage);
#endif
	throwMagickException(env, "Unable to create swirled image");
	return NULL;
    }

    return newObj;
}





/*
 * Class:     magick_MagickImage
 * Method:    sortColormapByIntensity
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_sortColormapByIntensity
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return SortColormapByIntensity(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = SortColormapByIntensity(image, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    syncImage
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_syncImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

#if MagickLibVersion <  0x700
    SyncImage(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    SyncImage(image, exception);
    DestroyExceptionInfo(exception);
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    textureImage
 * Signature: (Lmagick/MagickImage;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_textureImage
  (JNIEnv *env, jobject self, jobject texture)
{
    Image *textureImage;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    textureImage = (Image*) getHandle(env, texture, "magickImageHandle", NULL);
    if (textureImage == NULL) {
	throwMagickException(env, "Cannot obtain texture image handle");
	return;
    }

#if MagickLibVersion < 0x700
    TextureImage(image, textureImage);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    TextureImage(image, textureImage, exception);
    DestroyExceptionInfo(exception);
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    thresholdImage
 * Signature: (D)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_thresholdImage
    (JNIEnv *env, jobject self, jdouble threshold)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion <= 0x557
    return ThresholdImage(image, threshold);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = BilevelImage(image, threshold, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    transformImage
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_transformImage
    (JNIEnv *env, jobject self, jstring cropGeometry, jstring imageGeometry)
{
    const char *cropStr, *imageStr;
    jfieldID fieldID = 0;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    if (cropGeometry == NULL) {
        cropStr = NULL;
    } else {
        cropStr = (*env)->GetStringUTFChars(env, cropGeometry, 0);
    }

    if (imageGeometry == NULL) {
        imageStr = NULL;
    } else {
        imageStr = (*env)->GetStringUTFChars(env, imageGeometry, 0);
    }

#if MagickLibVersion < 0x700
    TransformImage(&image, cropStr, imageStr);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();

    Image *transformImage = image;
    if (cropStr != (const char *) NULL)
    {
        Image *cropImage;

        /*
         Crop image to a user specified size.
         */
        cropImage=CropImageToTiles(image,cropStr,exception);
        if (cropImage != (Image *) NULL)
        {
            transformImage=DestroyImage(transformImage);
            transformImage=cropImage;
            image=transformImage;
        }
    }
    if (imageStr != (const char *) NULL)
    {
        Image *resizeImage;

        /*
         Scale image to a user specified size.
         */
        RectangleInfo geometry;
        MagickStatusType flags=ParseRegionGeometry(transformImage,imageStr,&geometry,exception);
        (void) flags;
        if ((transformImage->columns != geometry.width) || (transformImage->rows != geometry.height))
        {
            resizeImage=ResizeImage(transformImage,geometry.width,geometry.height,transformImage->filter,exception);
            if (resizeImage != (Image *) NULL)
            {
                transformImage=DestroyImage(transformImage);
                transformImage=resizeImage;
                image=transformImage;
            }
        }
    }

    DestroyExceptionInfo(exception);
#endif
    if (imageGeometry != NULL) {
        (*env)->ReleaseStringUTFChars(env, imageGeometry, imageStr);
    }
    if (cropGeometry != NULL) {
        (*env)->ReleaseStringUTFChars(env, cropGeometry, cropStr);
    }

    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}




/*
 * Class:     magick_MagickImage
 * Method:    unsharpMaskImage
 * Signature: (DDDD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_unsharpMaskImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma,
                              jdouble amount, jdouble threshold)
{
    Image *image = NULL, *unsharpedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    #ifdef DIAGNOSTIC
        fprintf(stderr, "Kalder UnsharpMaskImage() !!\n");
    #endif
    unsharpedImage = UnsharpMaskImage(image, radius, sigma,
                                             amount, threshold, exception);
     #ifdef DIAGNOSTIC
         fprintf(stderr, "Kalder UnsharpMaskImage() færdig!!\n");
     #endif
    if (unsharpedImage == NULL) {
	throwMagickApiException(env, "Cannot unsharp image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, unsharpedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(unsharpedImage);
#else
	DestroyImageList(unsharpedImage);
#endif
	throwMagickException(env, "Unable to create unsharped image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    waveImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_waveImage__DD
  (JNIEnv *env, jobject self, jdouble amplitude, jdouble wavelength)
{
    return Java_magick_MagickImage_waveImage__DDI(env, self, amplitude, wavelength, UndefinedInterpolatePixel);
}

/*
 * Class:     magick_MagickImage
 * Method:    waveImage
 * Signature: (DDI)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_waveImage__DDI
  (JNIEnv *env, jobject self, jdouble amplitude, jdouble wavelength, jint pixelInterpolateMethod)
{
    Image *image = NULL, *wavedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    wavedImage = WaveImage(image, amplitude, wavelength, exception);
#else
    wavedImage = WaveImage(image, amplitude, wavelength, pixelInterpolateMethod, exception);
#endif
    if (wavedImage == NULL) {
	throwMagickApiException(env, "Cannot wave image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, wavedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(wavedImage);
#else
	DestroyImageList(wavedImage);
#endif
	throwMagickException(env, "Unable to create waved image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    transformRgbImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_transformRgbImage
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    return TransformRGBImage(image, colorspace);
#else
    ExceptionInfo* exception = AcquireExceptionInfo();
    jboolean result = TransformImageColorspace(image, RGBColorspace, exception);
    DestroyExceptionInfo(exception);
    
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    transparentImage
 * Signature: (Lmagick/PixelPacket;I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_transparentImage
    (JNIEnv *env, jobject self, jobject color, jint opacity)
{
#if MagickLibVersion < 0x700
    PixelPacket pixel;
#else
    PixelInfo pixel;
#endif
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    getPixelPacket(env, color, &pixel);
#if MagickLibVersion < 0x700
    return TransparentImage(image, pixel, (unsigned int) opacity);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = TransparentPaintImage(image, &pixel, (Quantum) opacity, MagickFalse, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    uniqueImageColors
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_uniqueImageColors
    (JNIEnv *env, jobject self)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo *exception;
    Image *image =
    (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if(image == NULL) {
        throwMagickException(env, "Cannot obtain image handle");
        return NULL;
    }

    exception=AcquireExceptionInfo();
    newImage = UniqueImageColors(image, exception);

    if (newImage == NULL) {
        throwMagickApiException(env, "Unable to generate unique image colors image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(newImage);
#else
        DestroyImageList(newImage);
#endif
        throwMagickException(env, "Unable to create a new MagickImage object");
        return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    zoomImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_zoomImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    newImage = ZoomImage(image, cols, rows, exception);
#else
    newImage = ResizeImage(image, cols, rows, image->filter, exception);
#endif
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to zoom image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(newImage);
#else
	DestroyImageList(newImage);
#endif
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[B)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3B
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jbyteArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
    jbyte *pixelArray;
    int result;
    ExceptionInfo *exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
    pixelArray = (*env)->GetByteArrayElements(env, pixels, 0);
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    result = DispatchImage(image, x, y, width, height,
#else
    result = ExportImagePixels(image, x, y, width, height,
#endif
			   mapStr, CharPixel, pixelArray, exception);

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);

    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", exception);
    }

    DestroyExceptionInfo(exception);
    return result;
}


/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[I)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3I
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jintArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
#if MagickLibVersion < 0x700
    jint *pixelArray;
#else
    jlong *pixelArray;
#endif
    int result;
    ExceptionInfo *exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
#if MagickLibVersion < 0x700
    pixelArray = (*env)->GetIntArrayElements(env, pixels, 0);
#else
    pixelArray = (*env)->GetLongArrayElements(env, pixels, 0);
#endif
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    result = DispatchImage(image, x, y, width, height,
			   mapStr, IntegerPixel, pixelArray, exception);
#else
    result = ExportImagePixels(image, x, y, width, height,
			   mapStr, LongPixel, pixelArray, exception);
#endif

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
#if MagickLibVersion < 0x700
    (*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);
#else
    (*env)->ReleaseLongArrayElements(env, pixels, pixelArray, 0);
#endif
    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", exception);
    }

    DestroyExceptionInfo(exception);
    return result;
}



/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[F)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3F
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jfloatArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
    jfloat *pixelArray;
    int result;
    ExceptionInfo *exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
    pixelArray = (*env)->GetFloatArrayElements(env, pixels, 0);
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    result = DispatchImage(image, x, y, width, height,
			   mapStr, FloatPixel, pixelArray, exception);
#else
    result = ExportImagePixels(image, x, y, width, height,
			   mapStr, FloatPixel, pixelArray, exception);
#endif

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);

    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", exception);
    }

    DestroyExceptionInfo(exception);
    return result;
}


/*
 * Class:     magick_MagickImage
 * Method:    getMagick
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getMagick
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get image format");
	return NULL;
    }

    return (*env)->NewStringUTF(env, image->magick);
}

/*
 * Class:     magick_MagickImage
 * Method:    setMagick
 * Signature: (Ljava/lang/String;)V
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setMagick
    (JNIEnv *env, jobject self, jstring imageFormat)
{
    Image *image = NULL;
    const char *cstr;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set image Format");
	return;
    }
    cstr = (*env)->GetStringUTFChars(env, imageFormat, 0);
    strcpy(image->magick, cstr);
    (*env)->ReleaseStringUTFChars(env, imageFormat, cstr);
}

/*
 * Class:     magick_MagickImage
 * Method:    getNumberColors
 * Signature: ()Ljava/lang/int;
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getNumberColors
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jint numberColors=0;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get the number of unique colors");
	return -1;
    }

    exception=AcquireExceptionInfo();
    numberColors=GetNumberColors(image, (FILE *) NULL, exception);

    if (numberColors == 0) {
        throwMagickApiException(env, "Error in GetNumberColors", exception);
    }

    DestroyExceptionInfo(exception);
    return numberColors;
}

/*
 * Class:     magick_MagickImage
 * Method:    setNumberColors
 * Signature: (()Ljava/lang/int)V;
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setNumberColors
    (JNIEnv *env, jobject self, jint numberColors)
{
    Image *image = NULL;
    QuantizeInfo quantize_info;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env,
                             "No image to set the number of unique colors");
	return;
    }

  GetQuantizeInfo(&quantize_info);
  quantize_info.number_colors=numberColors;
#if MagickLibVersion < 0x700
  (void) QuantizeImage(&quantize_info,image);
#else
  ExceptionInfo *exception = AcquireExceptionInfo();
  (void) QuantizeImage(&quantize_info,image,exception);
  DestroyExceptionInfo(exception);
#endif
}

/*
 * Class:     magick_MagickImage
 * Method:    isAnimatedImage
 * Signature: ()Z
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isAnimatedImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return (image->next != (Image *) NULL) ? (JNI_TRUE) : (JNI_FALSE);
}



/*
 * Class:     magick_MagickImage
 * Method:    rotateImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_rotateImage
  (JNIEnv *env, jobject self, jdouble degrees)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    newImage = RotateImage(image, degrees, exception);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to rotate image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(newImage);
#else
	DestroyImageList(newImage);
#endif
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    shearImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_shearImage
  (JNIEnv *env, jobject self, jdouble x_shear, jdouble y_shear)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo *exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    newImage = ShearImage(image, x_shear, y_shear, exception);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to shear image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(newImage);
#else
	DestroyImageList(newImage);
#endif
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }


    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    quantizeImage
 * Signature: (Lmagick/QuantizeInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_quantizeImage
  (JNIEnv *env, jobject self, jobject quantizeInfo)
{
    QuantizeInfo *qInfo;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    qInfo = (QuantizeInfo*) getHandle(env, quantizeInfo,
				     "quantizeInfoHandle", NULL);
    if (qInfo == NULL) {
	throwMagickException(env, "Cannot obtain QuantizeInfo handle");
	return JNI_FALSE;
    }

#ifdef DIAGNOSTIC
    fprintf(stderr, "qInfo.number_colors = %lu\n", qInfo->number_colors);
    fprintf(stderr, "qInfo.tree_depth = %lu\n", qInfo->tree_depth);
    fprintf(stderr, "qInfo.dither_method = %u\n", qInfo->dither_method);
    fprintf(stderr, "qInfo.colorspace = %u\n", qInfo->colorspace);
    fprintf(stderr, "qInfo.measure_error = %u\n", qInfo->measure_error);
#endif

#if MagickLibVersion < 0x700
    return QuantizeImage(qInfo, image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = QuantizeImage(qInfo, image, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    getColorspace
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getColorspace,
	     colorspace,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    sharpenImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_sharpenImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *sharpenedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    sharpenedImage = SharpenImage(image, radius, sigma, exception);
    if (sharpenedImage == NULL) {
	throwMagickApiException(env, "Cannot sharpen image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, sharpenedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(sharpenedImage);
#else
	DestroyImageList(sharpenedImage);
#endif
	throwMagickException(env, "Unable to create sharpened image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    despeckleImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_despeckleImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL, *despeckledImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    despeckledImage = DespeckleImage(image, exception);
    if (despeckledImage == NULL) {
	throwMagickApiException(env, "Cannot despeckle image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, despeckledImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(despeckledImage);
#else
	DestroyImageList(despeckledImage);
#endif
	throwMagickException(env, "Unable to create despeckle image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    convolveImage
 * Signature: (I[D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_convolveImage
  (JNIEnv *env, jobject self, jint order, jdoubleArray kernel)
{
    Image *image = NULL, *convolvedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;
    double *karray;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    karray = (*env)->GetDoubleArrayElements(env, kernel, NULL);
    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    convolvedImage = ConvolveImage(image, order, karray, exception);
#else
    KernelInfo *kernelInfo;
    kernelInfo=AcquireKernelInfo(NULL, exception);
    if (kernelInfo == (KernelInfo *) NULL) {
        throwMagickApiException(env, "Cannot retrieve kernel info", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }

    int i;
    kernelInfo->values = (MagickRealType *) AcquireAlignedMemory(order, order*sizeof(MagickRealType));
    for (i = 0; i < order*order; i++) {
        kernelInfo->values[i] = karray[i];
    }

    convolvedImage = ConvolveImage(image, kernelInfo, exception);

    RelinquishAlignedMemory(kernelInfo->values);
    kernelInfo->values = (MagickRealType *) NULL;
    DestroyKernelInfo(kernelInfo);
#endif

    (*env)->ReleaseDoubleArrayElements(env, kernel, karray, JNI_ABORT);
    if (convolvedImage == NULL) {
	throwMagickApiException(env, "Cannot convolve image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, convolvedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(convolvedImage);
#else
	DestroyImageList(convolvedImage);
#endif
	throwMagickException(env, "Unable to create convolved image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    getImageAttribute
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getImageAttribute
    (JNIEnv *env, jobject self, jstring key)
{
#if MagickLibVersion < 0x700
    Image *image;
    const char *iKey;
    const ImageAttribute *attrib;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    iKey = (*env)->GetStringUTFChars(env, key, 0);
    attrib = GetImageAttribute(image, iKey);
    (*env)->ReleaseStringUTFChars(env, key, iKey);

    if (attrib == NULL || attrib->value == NULL) {
	return NULL;
    }

    return (*env)->NewStringUTF(env, attrib->value);
#else
    return NULL;
#endif
}


/*
 * Class:     magick_MagickImage
 * Method:    setImageAttribute
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageAttribute
    (JNIEnv *env, jobject self, jstring key, jstring value)
{
#if MagickLibVersion < 0x700
    Image *image;
    const char *iKey, *iValue;
    jboolean result;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return JNI_FALSE;
    }

    if (key == NULL) {
        throwMagickException(env, "Image attribute key is null");
        return JNI_FALSE;
    }

    iKey = (*env)->GetStringUTFChars(env, key, 0);
    iValue = (value == NULL) ? NULL : (*env)->GetStringUTFChars(env, value, 0);
    result = SetImageAttribute(image, iKey, iValue);
    if (iValue != NULL) {
	(*env)->ReleaseStringUTFChars(env, value, iValue);
    }
    (*env)->ReleaseStringUTFChars(env, key, iKey);

    return result;
#else
    return JNI_TRUE;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    blobToImage
 * Signature: (Lmagick/ImageInfo;[B)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_blobToImage
    (JNIEnv *env, jobject self, jobject imageInfoObj, jbyteArray blob)
{
    size_t blobSiz;
    jbyte *blobMem;
    ExceptionInfo *exception;
    Image *image, *oldImage;
    jfieldID fieldID = 0;
    ImageInfo *imageInfo;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
                                       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
        throwMagickException(env, "Cannot obtain ImageInfo object");
        return;
    }

    /* Check that we do have a blob */
    if (blob == NULL) {
        throwMagickException(env, "Blob is null");
        return;
    }

    /* Get the array size and array elements */
    blobSiz = (*env)->GetArrayLength(env, blob);
    blobMem = (*env)->GetByteArrayElements(env, blob, 0);

    /* Create that image. */
    exception=AcquireExceptionInfo();
    image = BlobToImage(imageInfo, blobMem, blobSiz, exception);
    (*env)->ReleaseByteArrayElements(env, blob, blobMem, 0);
    if (image == NULL) {
        throwMagickApiException(env, "Unable to convert blob to image",
                                exception);
        DestroyExceptionInfo(exception);
        return;
    }
    DestroyExceptionInfo(exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(oldImage);
#else
        DestroyImageList(oldImage);
#endif
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}



/*
 * Class:     magick_MagickImage
 * Method:    imageToBlob
 * Signature: (Lmagick/ImageInfo;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_magick_MagickImage_imageToBlob
 (JNIEnv *env, jobject self, jobject imageInfoObj)
{
  ImageInfo *imageInfo;
  Image *image;
  size_t blobSiz = 0;
  ExceptionInfo *exception;
  void *blobMem = NULL;
  jbyteArray blob;

  /* Obtain the ImageInfo pointer */
  if (imageInfoObj != NULL) {
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
                                       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
      throwMagickException(env, "Cannot obtain ImageInfo object");
      return NULL;
    }
  }
  else {
    imageInfo = NULL;
  }

  /* Get the Image pointer */
  image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
  if (image == NULL) {
    throwMagickException(env, "No image to get file name");
    return NULL;
  }


  /* Do the conversion */
  exception=AcquireExceptionInfo();
  blobMem = ImageToBlob(imageInfo, image, &blobSiz, exception);
  if (blobMem == NULL) {
    throwMagickApiException(env, "Unable to convert image to blob", exception);
    DestroyExceptionInfo(exception);
    return NULL;
  }
  DestroyExceptionInfo(exception);


  /* Create a new Java array. */
  blob = (*env)->NewByteArray(env, blobSiz);
  if (blob == NULL) {
    throwMagickException(env, "Unable to allocate array");
    return NULL;
  }
  (*env)->SetByteArrayRegion(env, blob, 0, blobSiz, blobMem);

  RelinquishMagickMemory(blobMem);

  return blob;
}

/*
 * Class:     magick_MagickImage
 * Method:    imagesToBlob
 * Signature: (Lmagick/ImageInfo;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_magick_MagickImage_imagesToBlob
 (JNIEnv *env, jobject self, jobject imageInfoObj)
{
  ImageInfo *imageInfo;
  Image *image;
  size_t blobSiz = 0;
  ExceptionInfo *exception;
  void *blobMem = NULL;
  jbyteArray blob;

  /* Obtain the ImageInfo pointer */
  if (imageInfoObj != NULL) {
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
                                       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
      throwMagickException(env, "Cannot obtain ImageInfo object");
      return NULL;
    }
  }
  else {
    imageInfo = NULL;
  }

  /* Get the Image pointer */
  image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
  if (image == NULL) {
    throwMagickException(env, "No image to get file name");
    return NULL;
  }


  /* Do the conversion */
  exception=AcquireExceptionInfo();
  blobMem = ImagesToBlob(imageInfo, image, &blobSiz, exception);
  if (blobMem == NULL) {
    throwMagickApiException(env, "Unable to convert image to blob", exception);
    DestroyExceptionInfo(exception);
    return NULL;
  }
  DestroyExceptionInfo(exception);


  /* Create a new Java array. */
  blob = (*env)->NewByteArray(env, blobSiz);
  if (blob == NULL) {
    throwMagickException(env, "Unable to allocate array");
    return NULL;
  }
  (*env)->SetByteArrayRegion(env, blob, 0, blobSiz, blobMem);

  RelinquishMagickMemory(blobMem);

  return blob;
}

/*
 * Class:     magick_MagickImage
 * Method:    coalesceImages
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_coalesceImages
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    Image *coalescedImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle",
                   &magickImageHandleFid);
    if (image == NULL) {
    throwMagickException(env, "No image to coalesce");
    return NULL;
    }

    exception=AcquireExceptionInfo();
    coalescedImage = CoalesceImages(image, exception);
    if (coalescedImage == NULL) {
        throwMagickApiException(env, "Unable to coalesce image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    returnedImage = newImageObject(env, coalescedImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(coalescedImage);
#else
        DestroyImageList(coalescedImage);
#endif
        throwMagickException(env, "Unable to construct magick.MagickImage");
        return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
          (void*) coalescedImage, &magickImageHandleFid);

    return returnedImage;
}

/*
 * Class:     magick_MagickImage
 * Method:    disposeImages
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_disposeImages
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    Image *disposedImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle",
                   &magickImageHandleFid);
    if (image == NULL) {
        throwMagickException(env, "No image to dispose");
        return NULL;
    }

    exception=AcquireExceptionInfo();
    disposedImage = DisposeImages(image, exception);
    if (disposedImage == NULL) {
        throwMagickApiException(env, "Unable to dispose image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    returnedImage = newImageObject(env, disposedImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(disposedImage);
#else
        DestroyImageList(disposedImage);
#endif
        throwMagickException(env, "Unable to construct magick.MagickImage");
        return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
          (void*) disposedImage, &magickImageHandleFid);

    return returnedImage;
}


JNIEXPORT jobject JNICALL Java_magick_MagickImage_nextImage
  (JNIEnv *env, jobject self)
{
    jobject newObj;
    Image *nextImage;
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }

    if (image->next == NULL) {
        return NULL;
    }

    nextImage = image->next;
    /* unlink image from sequence */
    image->next = NULL;
    nextImage->previous = NULL;

    newObj = newImageObject(env, nextImage);
    if (newObj == NULL) {
       throwMagickException(env, "Unable to create a new MagickImage object");
       return NULL;
    }

    return newObj;
}

JNIEXPORT jboolean JNICALL Java_magick_MagickImage_hasFrames
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return JNI_FALSE;
    }

    if (image->next == NULL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}

JNIEXPORT jint JNICALL Java_magick_MagickImage_getNumFrames
  (JNIEnv *env, jobject self)
{
    int count = 0;
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return 0;
    }

    while (image != NULL) {
        count++;
        image = image->next;
    }

    return count;
}

/*
 * Class:     magick_MagickImage
 * Method:    setUnits
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setUnits,
	     units,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    getUnits
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getUnits,
	     units,
	     "magickImageHandle",
	     Image)




/*
 * Class:     magick_MagickImage
 * Method:    setXResolution
 * Signature: (D)V
 */
#if MagickLibVersion < 0x700
setDoubleMethod(Java_magick_MagickImage_setXResolution,
                x_resolution,
                "magickImageHandle",
                Image)
#else
setDoubleMethod(Java_magick_MagickImage_setXResolution,
                resolution.x,
                "magickImageHandle",
                Image)
#endif



/*
 * Class:     magick_MagickImage
 * Method:    setYResolution
 * Signature: (D)V
 */
#if MagickLibVersion < 0x700
setDoubleMethod(Java_magick_MagickImage_setYResolution,
                y_resolution,
                "magickImageHandle",
                Image)
#else
setDoubleMethod(Java_magick_MagickImage_setYResolution,
                resolution.y,
                "magickImageHandle",
                Image)
#endif


/*
 * Class:     magick_MagickImage
 * Method:    getXResolution
 * Signature: ()D
 */
#if MagickLibVersion < 0x700
getDoubleMethod(Java_magick_MagickImage_getXResolution,
                x_resolution,
                "magickImageHandle",
                Image)
#else
getDoubleMethod(Java_magick_MagickImage_getXResolution,
                resolution.x,
                "magickImageHandle",
                Image)
#endif

/*
 * Class:     magick_MagickImage
 * Method:    getYResolution
 * Signature: ()D
 */
#if MagickLibVersion < 0x700
getDoubleMethod(Java_magick_MagickImage_getYResolution,
                y_resolution,
                "magickImageHandle",
                Image)
#else
getDoubleMethod(Java_magick_MagickImage_getYResolution,
                resolution.y,
                "magickImageHandle",
                Image)
#endif

/*
 * Class:     magick_MagickImage
 * Method:    setColorProfile
 * Signature: (Lmagick/ProfileInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setColorProfile
  (JNIEnv *env, jobject self, jobject profileObj)
{
    unsigned char *info;
    int infoSize = 0;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "setColorProfile: Cannot obtain image handle");
       return;
    }
    // setProfileInfo() is broken, dont use
    //setProfileInfo(env, &image->color_profile, profileObj);


    if (profileObj == NULL) {
        throwMagickException(env, "setColorProfile: ProfileInfo cannot be null");
       return;
    }

    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);

#ifdef DIAGNOSTIC
    fprintf(stderr, "setColorProfile infoSize = %d  info = %p\n\n", infoSize, info);
#endif

    if (info==NULL) {
        RemoveImageProfile(image,"icc");
    } else {
        StringInfo* profile_info;
        profile_info = AcquireStringInfo(infoSize);
        SetStringInfoDatum(profile_info, info);
#if MagickLibVersion < 0x700
        SetImageProfile(image,"icc",profile_info);
#else
        ExceptionInfo *exception = AcquireExceptionInfo();
        SetImageProfile(image,"icc",profile_info,exception);
        DestroyExceptionInfo(exception);
#endif
        profile_info=DestroyStringInfo(profile_info);
    }
}

/*
 * Class:     magick_MagickImage
 * Method:    getColorProfile
 * Signature: ()Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getColorProfile
  (JNIEnv *env, jobject self)
{
#if MagickLibVersion < 0x700
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }
    return getProfileInfo(env, &image->color_profile);
#else
    return NULL;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    setIptcProfile
 * Signature: (Lmagick/ProfileInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setIptcProfile
  (JNIEnv *env, jobject self, jobject profileObj)
{
#if MagickLibVersion < 0x700
    unsigned char *info;
    int infoSize = 0;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return;
    }

    // setProfileInfo() is broken, dont use
    //setProfileInfo(env, &image->iptc_profile, profileObj);


    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
        return;
    }

    //name = getStringFieldValue(env, profileObj, "name", NULL);
    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);

#ifdef DIAGNOSTIC
    fprintf(stderr, "setIptcProfile 8BIM infoSize = %d  info = %p\n\n", infoSize, info);
#endif

    if (info==NULL) {
//        RemoveImageProfile(image,"iptc");
	RemoveImageProfile(image,"8bim");
    } else {
        StringInfo* profile_info;
        profile_info = AcquireStringInfo(infoSize);
        SetStringInfoDatum(profile_info, info);
//        SetImageProfile(image,"iptc",profile_info);
	SetImageProfile(image,"8bim",profile_info);
        profile_info=DestroyStringInfo(profile_info);
    }
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    getGenericProfileCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getGenericProfileCount
  (JNIEnv *env, jobject self)
{
#if MagickLibVersion < 0x700
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return -1;
    }

    return image->generic_profiles;
#else
    return 0;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    getGenericProfile
 * Signature: (I)Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getGenericProfile
  (JNIEnv *env, jobject self, jint index)
{
#if MagickLibVersion < 0x700
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }

    if (image->generic_profiles >= index) {
        return NULL;
    }

    return getProfileInfo(env, &image->generic_profile[index]);
#else
    return NULL;
#endif
}




/*
 * Class:     magick_MagickImage
 * Method:    getIptcProfile
 * Signature: ()Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getIptcProfile
  (JNIEnv *env, jobject self)
{
#if MagickLibVersion < 0x700
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }
    return getProfileInfo(env, &image->iptc_profile);
#else
    return NULL;
#endif
}



/*
 * Class:     magick_MagickImage
 * Method:    profileImage
 * Signature: (Ljava/lang/String;[B)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_profileImage
  (JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
{
    Image *image = NULL;
    const char *cstrProfileName;
    jbyte *cProfileData;
    size_t cProfileSize;
    unsigned int retVal;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return JNI_FALSE;
    }

    if (profileName == NULL) {
        cstrProfileName = NULL;
    }
    else {
        cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
    }

    if (profileData == NULL) {
        cProfileData = NULL;
        cProfileSize = 0;
    }
    else {
        cProfileSize = (*env)->GetArrayLength(env, profileData);
        cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
    }

#if MagickLibVersion < 0x700
    /* Note that the clone parameter in ProfileImage is always true
     * for JMagick because once the byte array is released, the memory
     * is recovered by the JVM.
     */
    retVal =
      ProfileImage(image, cstrProfileName, cProfileData, cProfileSize, 1);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    retVal=
      ProfileImage(image, cstrProfileName, cProfileData, cProfileSize, exception);
    DestroyExceptionInfo(exception);
#endif

    if (profileData != NULL) {
        (*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
    }

    if (profileName != NULL) {
        (*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
    }

    return (retVal ? JNI_TRUE : JNI_FALSE);
}









	/*
	 * Class:     magick_MagickImage
	 * Method:    setImageProfile
	 */
	JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageProfile
		(JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
	{
			Image *image = NULL;
			const char *cstrProfileName;
			jbyte* cProfileData;
			size_t cProfileSize;
			unsigned int retVal;

			image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
			if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
			}

			if (profileName == NULL) {
					cstrProfileName = NULL;
			}
			else {
					cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
			}

			if (profileData == NULL) {
					cProfileData = NULL;
					cProfileSize = 0;
			}
			else {
					cProfileSize = (*env)->GetArrayLength(env, profileData);
					cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
			}


      if (cProfileData == NULL) {
				retVal = DeleteImageProfile(image,cstrProfileName);
      } else {
					StringInfo * profile_info = NULL;
					profile_info = AcquireStringInfo(cProfileSize);
					SetStringInfoDatum(profile_info, (const unsigned char*) cProfileData);

#if MagickLibVersion < 0x700
					retVal =
							SetImageProfile(image, cstrProfileName, profile_info);
#else
					ExceptionInfo *exception = AcquireExceptionInfo();
					retVal =
							SetImageProfile(image, cstrProfileName, profile_info, exception);
					 DestroyExceptionInfo(exception);
#endif

					profile_info = DestroyStringInfo(profile_info);
				}

			if (profileData != NULL) {
					(*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
			}

			if (profileName != NULL) {
					(*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
			}

			return (retVal ? JNI_TRUE : JNI_FALSE);
	}





/*
 * Class:     magick_MagickImage
 * Method:    getImageProfile
 */
JNIEXPORT jbyteArray JNICALL Java_magick_MagickImage_getImageProfile
	(JNIEnv *env, jobject self, jstring profileName)
{
  Image *image = NULL;
	const char * cstrProfileName;
	jbyteArray byteArray;
  const StringInfo* profileInfo;
  jbyte* byteElements;

	image = (Image * ) getHandle(env, self, "magickImageHandle", NULL);
	if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
	}

	if (profileName == NULL) {
		cstrProfileName = NULL;
	}
	else {
		cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
	}

	profileInfo = GetImageProfile(image, cstrProfileName);

	if (profileInfo != (const StringInfo*) NULL && profileInfo->length > 0) {

		/* Construct the byte array */
		byteArray = (*env)->NewByteArray(env, profileInfo -> length);
		if (byteArray == NULL) {
			throwMagickException(env, "Unable to allocate byte array "
													 "for profile info");
			return NULL;
		}

		byteElements = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
		if (byteElements == NULL) {
			throwMagickException(env, "Unable to obtain byte array elements "
													 "for profile info");
			return NULL;
		}
		memcpy(byteElements,
					 GetStringInfoDatum(profileInfo),
					 GetStringInfoLength(profileInfo));

		(*env) -> ReleaseByteArrayElements(env, byteArray, byteElements, 0);
	}
	else {
		byteArray = NULL;
	}

	if (profileName != NULL) {
		( * env) -> ReleaseStringUTFChars(env, profileName, cstrProfileName);
	}
	return byteArray;
}


/*
 * Class:     magick_MagickImage
 * Method:    getNextImageProfile
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getNextImageProfile
	(JNIEnv *env, jobject self)
{
	Image *image = NULL;
	const char *profileName;

	image = (Image *) getHandle(env, self, "magickImageHandle", NULL);
	if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
	}

	profileName = GetNextImageProfile(image);

	if (profileName == (char *) NULL) {
		return NULL;
	}
	
	return (*env)->NewStringUTF(env, profileName);
}


/*
 * Class:     magick_MagickImage
 * Method:    resetImageProfileIterator
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_resetImageProfileIterator
 (JNIEnv *env, jobject self)
{
    Image               *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "No image to set reset page");
        return;
    }

    ResetImageProfileIterator(image);
}


/*
 * Class:     magick_MagickImage
 * Method:    montageImages
 * Signature: (Lmagick/MontageInfo;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_montageImages
  (JNIEnv *env, jobject self, jobject montageInfo)
{
    Image *image, *montage;
    MontageInfo *info;
    ExceptionInfo *exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    info = (MontageInfo*)
        getHandle(env, montageInfo, "montageInfoHandle", NULL);
    if (info == NULL) {
        throwMagickException(env, "Unable to retrieve MontageInfo handle");
        return NULL;
    }

    exception=AcquireExceptionInfo();
    montage = MontageImages(image, info, exception);
    if (montage == NULL) {
        throwMagickApiException(env, "Failed to create montage", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, montage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(montage);
#else
        DestroyImageList(montage);
#endif
        throwMagickException(env, "Unable to create montage");
        return NULL;
    }
    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    autoOrientImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_autoOrientImage
  (JNIEnv *env, jobject self)
{
    Image *image, *orient_image;
    ExceptionInfo *exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Cannot retrieve image handle");
        return NULL;
    }

    exception=AcquireExceptionInfo();
    orient_image=NewImageList();
    switch (image->orientation)
     {
       case TopRightOrientation:
        {
          orient_image=FlopImage(image,exception);
          break;
        }
       case BottomRightOrientation:
        {
          orient_image=RotateImage(image,180.0,exception);
          break;
        }
       case BottomLeftOrientation:
        {
          orient_image=FlipImage(image,exception);
          break;
        }
       case LeftTopOrientation:
        {
          orient_image=TransposeImage(image,exception);
          break;
        }
       case RightTopOrientation:
        {
          orient_image=RotateImage(image,90.0,exception);
          break;
        }
       case RightBottomOrientation:
        {
          orient_image=TransverseImage(image,exception);
          break;
        }
       case LeftBottomOrientation:
        {
          orient_image=RotateImage(image,270.0,exception);
          break;
        }
       default:
          orient_image=CloneImage(image,0,0,MagickTrue,exception);
          image=orient_image;
          break;
     }
    if (orient_image == (Image *) NULL) {
        throwMagickApiException(env, "Failed to auto-orient image",
                                exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    if ( orient_image != image ) {
        orient_image->orientation=TopLeftOrientation;
        image=orient_image;
     }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, image);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(image);
#else
        DestroyImageList(image);
#endif
        throwMagickException(env, "Unable to auto-orient image");
        return NULL;
    }
    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    averageImages
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_averageImages
  (JNIEnv *env, jobject self)
{
    Image *image, *average;
    ExceptionInfo *exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    average = AverageImages(image, exception);
#else
    average = EvaluateImages(image, MeanEvaluateOperator, exception);
#endif

    if (average == NULL) {
        throwMagickApiException(env, "Failed to create average image",
                                exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, average);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(average);
#else
        DestroyImageList(average);
#endif
        throwMagickException(env, "Unable to create average image");
        return NULL;
    }
    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    levelImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_levelImage
  (JNIEnv *env, jobject self, jstring levels)
{
    Image *image = NULL;
    const char *cstr;
    jboolean retVal;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain Image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, levels, 0);
#if MagickLibVersion < 0x700
    retVal = LevelImage(image, cstr);
#else
    retVal = LevelImageShim(image, cstr);
#endif
    (*env)->ReleaseStringUTFChars(env, levels, cstr);

    return retVal;
}



/*
 * Class:     magick_MagickImage
 * Method:    sizeBlob
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_sizeBlob
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain Image handle");
	return -1;
    }

#if MagickLibVersion < 0x700
    return SizeBlob(image);
#else
    return GetBlobSize(image);
#endif
}


/*
 * Class:     magick_MagickImage
 * Method:    setCompression
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setCompression,
             compression,
             "magickImageHandle",
             Image)



/*
 * Class:     magick_MagickImage
 * Method:    getCompression
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getCompression,
             compression,
             "magickImageHandle",
             Image)

/*
 * Class:     magick_MagickImage
 * Method:    getImageType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getImageType
  (JNIEnv *env, jobject self)
{
    jint imageType;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return -1;
    }
    
#if MagickLibVersion < 0x700
    ExceptionInfo *exception = AcquireExceptionInfo();
    imageType = GetImageType( image, exception);
    DestroyExceptionInfo(exception);
#else
    imageType = GetImageType( image );
#endif
    return imageType;
}

#pragma clang diagnostic ignored "-Wtautological-compare"
/*
 * Class:     magick_MagickImage
 * Method:    getOnePixel
 * Signature: (II)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getOnePixel
    (JNIEnv *env, jobject self, jint xPos, jint yPos)
{
    Image *image = NULL;
    jobject jPixelPacket = NULL;
#if MagickLibVersion < 0x700
    PixelPacket pixel;
#else
    PixelInfo pixel;
#endif
    jclass pixelPacketClass;
    jmethodID consMethodID;

    image = (Image *) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to retrieve image");
        return NULL;
    }

#if MagickLibVersion < 0x700
    pixel = GetOnePixel(image, xPos, yPos);
    if (&pixel == NULL) {
        throwMagickException(env, "Unable to retrieve pixel");
    }
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    if (!GetOneAuthenticPixel(image, xPos, yPos, (Quantum*) &pixel, exception) || &pixel == NULL) {
        throwMagickApiException(env, "Unable to retrieve pixel", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    
    DestroyExceptionInfo(exception);
#endif

    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
        throwMagickException(env,
                             "Unable to locate class magick.PixelPacket");
        return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
                                       "<init>", "(IIII)V");
    if (consMethodID == 0) {
        throwMagickException(env, "Unable to construct magick.PixelPacket");
        return NULL;
    }

    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,
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
 * Class:     magick_MagickImage
 * Method:    setBorderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MagickImage_setBorderColor,
                     border_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getBorderColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_MagickImage_getBorderColor,
                     border_color,
                     "magickImageHandle",
                     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setBackgroundColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MagickImage_setBackgroundColor,
                     background_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getBackgroundColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_MagickImage_getBackgroundColor,
                     background_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    setDelay
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDelay,
	     delay,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getDelay
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDelay,
	     delay,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    setDispose
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDispose,
	     dispose,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getDispose
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDispose,
	     dispose,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setIterations
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setIterations,
	     iterations,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getIterations
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getIterations,
	     iterations,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setColors
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setColors,
	     colors,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    getColors
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getColors,
	     colors,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    getTotalColors
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getTotalColors,
	     total_colors,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    getColormap
 * Signature: (I)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getColormap__I
  (JNIEnv *env, jobject self, jint index)
{
    Image *image;
    jobject jPixelPacket = NULL;
    jclass pixelPacketClass;
    jmethodID consMethodID;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return NULL;
    }

    if (index >= image->colors) {
        throwMagickException(env, "Index out of range");
        return NULL;
    }

    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
	throwMagickException(env,
			     "Unable to locate class magick.PixelPacket");
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
				       "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,
		                     (jint) image->colormap[index].red,
		                     (jint) image->colormap[index].green,
		                     (jint) image->colormap[index].blue,
#if MagickLibVersion < 0x700
		                     (jint) image->colormap[index].opacity);
#else
		                     (jint) image->colormap[index].alpha);
#endif
    if (jPixelPacket == NULL) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    return jPixelPacket;
}



/*
 * Class:     magick_MagickImage
 * Method:    getColormap
 * Signature: ()[Lmagick/PixelPacket;
 */
JNIEXPORT jobjectArray JNICALL Java_magick_MagickImage_getColormap__
  (JNIEnv *env, jobject self)
{
    Image *image;
    jobject jPixelPacket = NULL;
    jclass pixelPacketClass;
    jmethodID consMethodID;
    jobjectArray jPPArray;
    int i;

    /* Get the image handle */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return NULL;
    }

    /* Sanity check */
    if (image->colors <= 0 || image->colormap == NULL) {
        throwMagickException(env, "Image does not have a colourmap");
        return NULL;
    }

    /* Get the PixelPacket object class */
    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
	throwMagickException(env,
			     "Unable to locate class magick.PixelPacket");
	return NULL;
    }

    /* Get the constructor ID for PixelPacket */
    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
				       "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    /* Create the PixelPacket array */
    jPPArray =
        (*env)->NewObjectArray(env, image->colors, pixelPacketClass, NULL);
    if (jPPArray == NULL) {
        throwMagickException(env, "Unable to construct PixelPacket[]");
        return NULL;
    }

    /* Construct a PixelPacket for each item in the colourmap */
    for (i = 0; i < image->colors; i++) {

        /* Create the PixelPacket */
        jPixelPacket =
            (*env)->NewObject(env, pixelPacketClass, consMethodID,
                              (jint) image->colormap[i].red,
                              (jint) image->colormap[i].green,
                              (jint) image->colormap[i].blue,
#if MagickLibVersion < 0x700
                              (jint) image->colormap[i].opacity);
#else
                              (jint) image->colormap[i].alpha);
#endif
        if (jPixelPacket == NULL) {
            throwMagickException(env, "Unable to construct magick.PixelPacket");
            return NULL;
        }

        /* Set the PixelPacket in the array */
        (*env)->SetObjectArrayElement(env, jPPArray, i, jPixelPacket);
    }

    return jPPArray;
}

/*
 * Class:     magick_MagickImage
 * Method:    trimImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_trimImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL, *trimmedImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
    trimmedImage = TrimImage(image, exception);
    if (trimmedImage == NULL) {
	throwMagickApiException(env, "Cannot trim image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, trimmedImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(trimmedImage);
#else
	DestroyImageList(trimmedImage);
#endif
	throwMagickException(env, "Unable to create trimmed image");
	return NULL;
    }

    return newObj;
}



  /*
   * Class:     magick_MagickImage
   * Method:    resetImagePage
   * Signature: ()I
   */
  JNIEXPORT jboolean JNICALL Java_magick_MagickImage_resetImagePage
   (JNIEnv *env, jobject self, jstring page)
  {
     Image               *image = NULL;
     const               char *cpage;
         jboolean        retVal;

     image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
     if (image == NULL) {
        throwMagickException(env, "No image to set reset page");
        return JNI_FALSE;
     }

     cpage = (*env)->GetStringUTFChars(env, page, 0);
         retVal = ResetImagePage(image, cpage);
     (*env)->ReleaseStringUTFChars(env, page, cpage);

     return retVal;
   }




/*
 * Class:     magick_MagickImage
 * Method:    blurImageChannel
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_blurImageChannel
  (JNIEnv *env, jobject self, jint channelType, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    exception=AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    blurredImage = BlurImageChannel(image, channelType, radius, sigma, exception);
#else
    blurredImage = BlurImage(image, radius, sigma, exception);
#endif
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", exception);
	DestroyExceptionInfo(exception);
	return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(blurredImage);
#else
	DestroyImageList(blurredImage);
#endif
	throwMagickException(env, "Unable to create new blurred image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    signatureImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_signatureImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jboolean retVal;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
      throwMagickException(env, "Cannot obtain Image handle");
      return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    retVal = SignatureImage(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    retVal = SignatureImage(image, exception);
    DestroyExceptionInfo(exception);
#endif
    return(retVal);
}


/*
 * Class:     magick_MagickImage
 * Method:    getQuality
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getQuality,
	     quality,
	     "magickImageHandle",
	     Image)

 /*
  * Class:     magick_MagickImage
  * Method:    setQuality
  * Signature: ()I
  */
setIntMethod(Java_magick_MagickImage_setQuality,
          quality,
          "magickImageHandle",
          Image)

/*
 * Class:     magick_MagickImage
 * Method:    setRenderingIntent
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setRenderingIntent,
    rendering_intent,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    getRenderingIntent
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getRenderingIntent,
    rendering_intent,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    setMatte
 * Signature: (Z)V
 */
#if MagickLibVersion < 0x700
setBoolMethod(Java_magick_MagickImage_setMatte,
    matte,
    "magickImageHandle",
    Image)
#else
setDeprecatedMethod(Java_magick_MagickImage_setMatte,
    matte,
    "magickImageHandle",
    Image,
    jboolean)
#endif

/*
 * Class:     magick_MagickImage
 * Method:    getMatte
 * Signature: ()Z
 */
#if MagickLibVersion < 0x700
getBoolMethod(Java_magick_MagickImage_getMatte,
    matte,
    "magickImageHandle",
    Image)
#else
getDeprecatedMethod(Java_magick_MagickImage_getMatte,
    matte,
    "magickImageHandle",
    Image,
    jboolean)
#endif

/*
 * Class:     magick_MagickImage
 * Method:    getNumberImages
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getNumberImages
  (JNIEnv *env, jobject self) {
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
    throwMagickException(env, "Unable to retrieve image handle");
    return -1;
    }

    return GetImageListLength(image);
}

/*
 * Class:     magick_MagickImage
 * Method:    strip
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_strip
    (JNIEnv *env, jobject self) {
    Image *image = NULL;
    jboolean retVal;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
    throwMagickException(env, "Unable to retrieve image handle");
    return JNI_FALSE;
    }

#if MagickLibVersion < 0x700
    retVal = StripImage(image);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    retVal = StripImage(image, exception);
    DestroyExceptionInfo(exception);
#endif
    return(retVal);
}

/*
 * Class:     magick_MagickImage
 * Method:    setImageColorspace
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageColorspace
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
        (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Cannot obtain image handle");
        return JNI_FALSE;
    }
#if MagickLibVersion < 0x700
    return SetImageColorspace(image, colorspace);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = SetImageColorspace(image, colorspace, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}

/*
 * Class:     magick_MagickImage
 * Method:    resizeImage
 * Signature: (IIID)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_resizeImage__IIID
    (JNIEnv *env, jobject self, jint cols, jint rows, jint filter, jdouble blur)
{
    Image *image = NULL;
    Image *resizedImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;
    image = (Image*) getHandle(env, self, "magickImageHandle",
			       &magickImageHandleFid);
    if (image == NULL) {
		throwMagickException(env, "No image to scale");
		return NULL;
    }
    exception = AcquireExceptionInfo();
    resizedImage = ResizeImage(image,
                 (unsigned int) cols,
                 (unsigned int) rows,
                 (unsigned int) filter,
#if MagickLibVersion < 0x700
                 (double)       blur,
#endif
                                exception);
    if (resizedImage == NULL) {
		throwMagickApiException(env, "Unable to resize image", exception);
		DestroyExceptionInfo(exception);
		return NULL;
    }
    DestroyExceptionInfo(exception);
    returnedImage = newImageObject(env, resizedImage);
    if (returnedImage == NULL) {
#if MagickLibVersion < 0x700
		DestroyImages(resizedImage);
#else
		DestroyImageList(resizedImage);
#endif
		throwMagickException(env, "Unable to construct magick.MagickImage");
		return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
	      (void*) resizedImage, &magickImageHandleFid);
    return returnedImage;
}

/*
 * Class:     magick_MagickImage
 * Method:    transformImageColorspace
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_transformImageColorspace
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
        (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Cannot obtain image handle");
        return JNI_FALSE;
    }
#if MagickLibVersion < 0x700
    return TransformImageColorspace(image, colorspace);
#else
    ExceptionInfo *exception = AcquireExceptionInfo();
    jboolean result = TransformImageColorspace(image, colorspace, exception);
    DestroyExceptionInfo(exception);
    return result;
#endif
}


/*
 * Class:     magick_MagickImage
 * Method:    optimizeLayer
 * Signature: (Lmagick/ImageInfo;)Lmagick/MagickImage
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_optimizeLayer
  (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *image_info = NULL, *clone_info = NULL;
    Image *image = NULL, *layers = NULL, *temp = NULL;
    QuantizeInfo *quantize_info = NULL;
    jobject newObj;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", &magickImageHandleFid);
    if (image == NULL) {
      throwMagickException(env, "Cannot retrieve image handle");
      return NULL;
    }

    /* Obtain the ImageInfo pointer */
    if (imageInfoObj != NULL) {
      image_info = (ImageInfo*) getHandle(env, imageInfoObj,
                                         "imageInfoHandle", NULL);
      if (image_info == NULL) {
        throwMagickException(env, "Cannot obtain ImageInfo object");
        return NULL;
      }
    }

    exception = AcquireExceptionInfo();
    layers = CoalesceImages(image, exception);
    if (layers == NULL) {
        throwMagickApiException(env, "Cannot coalesce image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }

    //image = DestroyImageList(image);
    temp = layers;

    layers = OptimizePlusImageLayers(temp, exception);
    if (layers == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(temp);
#else
        DestroyImageList(temp);
#endif
        throwMagickApiException(env, "Cannot optimize image layers", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }

    temp = DestroyImageList(temp);

    OptimizeImageTransparency(layers, exception);

    clone_info = CloneImageInfo(image_info);
    quantize_info = AcquireQuantizeInfo(clone_info);

    RemapImages(quantize_info, layers, NULL, exception);

    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, layers);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(layers);
#else
        DestroyImageList(layers);
#endif
        throwMagickException(env, "Unable to create optimized image");
        return NULL;
    }

    setHandle(env, newObj, "magickImageHandle",
          (void*) layers, &magickImageHandleFid);

    return newObj;
}

/*
 * Class:     magick_MagickImage
 * Method:    deconstructImages
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_deconstructImages
  (JNIEnv *env, jobject self)
{
    Image *image = NULL, *deconstructImage = NULL;
    jobject newObj;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo *exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", &magickImageHandleFid);
    if (image == NULL) {
        throwMagickException(env, "Cannot retrieve image handle");
        return NULL;
    }

    exception = AcquireExceptionInfo();
#if MagickLibVersion < 0x700
    deconstructImage = DeconstructImages(image, exception);
#else
    deconstructImage = CompareImagesLayers(image, CompareAnyLayer, exception);
#endif
    if (deconstructImage == NULL) {
        throwMagickApiException(env, "Cannot deconstruct image", exception);
        DestroyExceptionInfo(exception);
        return NULL;
    }
    DestroyExceptionInfo(exception);

    newObj = newImageObject(env, deconstructImage);
    if (newObj == NULL) {
#if MagickLibVersion < 0x700
        DestroyImages(deconstructImage);
#else
        DestroyImageList(deconstructImage);
#endif
        throwMagickException(env, "Unable to create new deconstructed image");
        return NULL;
    }

    setHandle(env, newObj, "magickImageHandle",
          (void*) deconstructImage, &magickImageHandleFid);

    return newObj;
}
