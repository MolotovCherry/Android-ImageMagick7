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


// 2016/04/17 D.Slamnig added:
#include <android/log.h>
#define APPNAME "Magick"
#define LOG(a) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a);
#define LOG2(a,b) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b);
#define LOG3(a,b,c) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b, c);

// detect Android debug build
#ifdef NDEBUG
#define DIAGNOSTIC 1
#endif

#if MagickLibVersion >= 0x700
MagickBooleanType LevelImageShim(Image *image,const char *levels)
{
    double black_point, gamma, white_point;

    GeometryInfo geometry_info;

    MagickBooleanType status;

    MagickStatusType flags;

    /*
     Parse levels.
     */
    if (levels == (char *) NULL)
        return(MagickFalse);

    flags=ParseGeometry(levels,&geometry_info);
    black_point=geometry_info.rho;
    white_point=(double) QuantumRange;
    if ((flags & SigmaValue) != 0)
        white_point=geometry_info.sigma;

    gamma=1.0;
    if ((flags & XiValue) != 0)
        gamma=geometry_info.xi;

    if ((flags & PercentValue) != 0)
    {
        black_point*=(double) image->columns*image->rows/100.0;
        white_point*=(double) image->columns*image->rows/100.0;
    }

    if ((flags & SigmaValue) == 0)
        white_point=(double) QuantumRange-black_point;

    ExceptionInfo *exception = AcquireExceptionInfo();

    if ((flags & AspectValue ) == 0)
    {
        ChannelType channel_mask=SetImageChannelMask(image, DefaultChannels);
        status=LevelImage(image,black_point,white_point,gamma,exception);
        (void) SetImageChannelMask(image,channel_mask);
    }
    else
    {
        status=LevelizeImage(image,black_point,white_point,gamma,exception);
    }

    DestroyExceptionInfo(exception);

    return status;
}
#endif


/*
 * Convenience function to help throw an MagickException.
 */
void throwMagickException(JNIEnv *env, const char *mesg)
{
    jclass magickExceptionClass;

    magickExceptionClass = (*env)->FindClass(env, "magick/MagickException");
    if (magickExceptionClass == 0) {
	//fprintf(stderr, "Cannot find MagickException class\n");
	LOG("Cannot find MagickException class\n");
	return;
    }
    (*env)->ThrowNew(env, magickExceptionClass, mesg);
}



/*
 * Convenience function to help throw an MagickApiException.
 *
 * Input:
 *   mesg       JMagick message
 *   exception  points to a ImageMagick ExceptionInfo structure
 */
void throwMagickApiException(JNIEnv *env,
			     const char *mesg,
			     const ExceptionInfo *exception)
{
    jclass magickApiExceptionClass;
    jmethodID consMethodID = 0;
    jobject newObj;
    jstring jreason, jdescription;
    int result;

#ifdef DIAGNOSTIC
	//fprintf(stderr, "throwMagickApiException reason: %s - desc: %s \n", exception->reason, exception->description);
	LOG2("throwMagickApiException info: %s", mesg);
	LOG3("throwMagickApiException reason: %s - desc: %s \n", exception->reason, exception->description);
#endif

    /* Find the class ID */
    magickApiExceptionClass =
	(*env)->FindClass(env, "magick/MagickApiException");
    if (magickApiExceptionClass == 0) {
#ifdef DIAGNOSTIC
	//fprintf(stderr, "Cannot find MagickApiException class\n");
	LOG("Cannot find MagickApiException class\n");
#endif
	return;
    }

    /* Find the constructor ID */
    consMethodID =
	(*env)->GetMethodID(env, magickApiExceptionClass,
			    "<init>",
			    "(ILjava/lang/String;Ljava/lang/String;)V");
    if (consMethodID == 0) {
	return;
    }

    /* Obtain the string objects */
    jreason = (*env)->NewStringUTF(env, exception->reason != NULL ? exception->reason : "");
    if (jreason == NULL) {
#ifdef DIAGNOSTIC
	//fprintf(stderr,
	//	"throwMagickApiException: "
	//	"Unable to create reason string\n");
	LOG("throwMagickApiException: \nUnable to create reason string\n");
#endif
	return;
    }

    jdescription = (*env)->NewStringUTF(env,  exception->description != NULL ? exception->description : "");
    if (jdescription == NULL) {
#ifdef DIAGNOSTIC
	//fprintf(stderr,
	//	"throwMagickApiException: "
	//	"Unable to create description string\n");
	LOG("throwMagickApiException: \nUnable to create description string\n");
#endif
	return;
    }

    /* Create the MagickApiException object */
    newObj = (*env)->NewObject(env, magickApiExceptionClass, consMethodID,
			       exception->severity,
                               jreason, jdescription);
    if (newObj == NULL) {
#ifdef DIAGNOSTIC
	//fprintf(stderr,
	//	"throwMagickApiException: "
	//	"Unable to create MagickApiException object\n");
	LOG("throwMagickApiException: \nUnable to create MagickApiException object\n");
#endif
	return;
    }

    /* Throw the exception. */
    result = (*env)->Throw(env, newObj);
#ifdef DIAGNOSTIC
    if (result != 0) {
        //fprintf(stderr,
        //	"throwMagickApiException: "
        //	"Fail to throw MagickApiException");
        LOG("throwMagickApiException: \nFailed to throw MagickApiException");
    }
#endif
}



/*
 * Convenience function to retreive a handle from an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which handle is to be retrieved
 *   handleName  name of the handle in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the handle on output.
 */
void *getHandle(JNIEnv *env,
		jobject obj,
		const char *handleName,
		jfieldID *fieldId)
{
    jclass objClass;
    jfieldID handleFid;

    /* Retrieve the field ID of the handle */
    if (fieldId == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	handleFid = (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else if (*fieldId == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	handleFid = *fieldId =
	    (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else {
	handleFid = *fieldId;
    }

    return (void*) (*env)->GetLongField(env, obj, handleFid);
}




/*
 * Convenience function to set a handle in an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which handle is to be retrieved
 *   handleName  name of the handle in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the handle on output.
 *
 * Return:
 *   non-zero    if successful
 *   zero        if failure
 */
int setHandle(JNIEnv *env,
	      jobject obj,
	      const char *handleName,
	      void *handle,
	      jfieldID *fieldId)
{
    jclass objClass;
    jfieldID handleFid;

    /* Retrieve the field ID of the handle */
    if (fieldId == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	handleFid = (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else if (fieldId == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	handleFid = *fieldId =
	    (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else {
	handleFid = *fieldId;
    }
    if (handleFid == 0) {
	return 0;
    }

    (*env)->SetLongField(env, obj, handleFid, (jlong) handle);

    return 1;
}





/*
 * Retrieve the int value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getIntFieldValue(JNIEnv *env,
		     jobject obj,
		     const char *fieldName,
		     jfieldID *fieldID,
		     jint *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetIntField(env, obj, objFieldID);
    return 1;
}




/*
 * Store the int value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *   value      to contain the value to be stored.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int setIntFieldValue(JNIEnv *env,
                     jobject obj,
                     const char *fieldName,
                     jfieldID *fieldID,
                     jint value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    (*env)->SetIntField(env, obj, objFieldID, value);
    return 1;
}




/*
 * Retrieve the byte value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getByteFieldValue(JNIEnv *env,
		      jobject obj,
		      const char *fieldName,
		      jfieldID *fieldID,
		      jbyte *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "B");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "B");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetByteField(env, obj, objFieldID);
    return 1;
}




/*
 * Retrieve the short value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getShortFieldValue(JNIEnv *env,
		       jobject obj,
		       const char *fieldName,
		       jfieldID *fieldID,
		       jshort *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "S");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "S");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetShortField(env, obj, objFieldID);
    return 1;
}




/*
 * Retrieve the string value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *
 * Return:
 *   The string value requested. The caller is responsible for
 *   deallocating this string.
 */
char* getStringFieldValue(JNIEnv *env,
                          jobject obj,
                          const char *fieldName,
                          jfieldID *fieldID)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;
    jobject stringObj = 0;
    char *stringVal = NULL;
    char *stringCpy = NULL;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID =
            (*env)->GetFieldID(env, objClass, fieldName, "Ljava/lang/String;");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "Ljava/lang/String;");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return NULL;
    }
    stringObj = (*env)->GetObjectField(env, obj, objFieldID);
    if (stringObj == NULL) {
        return NULL;
    }
    stringVal = (char *) (*env)->GetStringUTFChars(env, stringObj, 0);
    stringCpy = (char *) AcquireString(stringVal);
    (*env)->ReleaseStringUTFChars(env, stringObj, stringVal);
    return stringCpy;
}



/*
 * Retrieve the byte array from the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *   size       the size of the array is returned here. Must not be NULL.
 *
 * Return:
 *   The byte array requested. The caller is responsible for
 *   deallocating this byte array.
 */
unsigned char* getByteArrayFieldValue(JNIEnv *env,
                                      jobject obj,
                                      const char *fieldName,
                                      jfieldID *fieldID,
                                      int *size)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;
    jobject byteArrayObj = 0;
    unsigned char *byteArray = NULL;
    signed char *byteArrayCpy = NULL;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID =
            (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return NULL;
    }

    /* Get the array object */
    byteArrayObj = (*env)->GetObjectField(env, obj, objFieldID);
    if (byteArrayObj == NULL) {
        return NULL;
    }

    /* Determine the size of the array */
    *size = (*env)->GetArrayLength(env, byteArrayObj);
    if (*size == 0) {
        return NULL;
    }

    /* Get and copy the array elements */
    byteArray = (jboolean *) (*env)->GetByteArrayElements(env, byteArrayObj, 0);
    byteArrayCpy = (signed char *) AcquireMagickMemory(*size);
    if (byteArray == NULL) {
        return NULL;
    }
    memcpy(byteArrayCpy, byteArray, *size);
    (*env)->ReleaseByteArrayElements(env, byteArrayObj, byteArrayCpy, JNI_ABORT);

    return (unsigned char*) byteArrayCpy;
}



/*
 * From a fakeawt.Rectangle object, construct a ImageMagick
 * RectangleInfo, as passed in from the parameter.
 *
 * Input:
 *   env        Java VM environment
 *   jRect      an instance of fakeawt.Rectangle
 *
 * Output:
 *   iRect      to be initilised by values in jRect
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getRectangle(JNIEnv *env, jobject jRect, RectangleInfo *iRect)
{
	jint width, height, x, y;
    int retVal =
		getIntFieldValue(env, jRect, "width", NULL, (jint *) &width) &&
		getIntFieldValue(env, jRect, "height", NULL, (jint *) &height) &&
		getIntFieldValue(env, jRect, "x", NULL, (jint *) &x) &&
		getIntFieldValue(env, jRect, "y", NULL, (jint *) &y);
	if (retVal) {
		iRect->width = width;
		iRect->height = height;
		iRect->x = x;
		iRect->y = y;
	}
	return retVal;
}



/*
 * From a magick.PixelPacket object, construct a ImageMagick
 * PixelPacket, as passed in from the parameter.
 *
 * Input:
 *   env           Java VM environment
 *   jPixel  an instance of magick.PixelPacket
 *
 * Output:
 *   iPixel  to be initilised by values in jPixel
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getPixelPacket(JNIEnv *env,
		   jobject jPixel,
#if MagickLibVersion < 0x700
		   PixelPacket *iPixel)
#else
		   PixelInfo *iPixel)
#endif
{
  jint red, green, blue, transparency;

  int successful =
	getIntFieldValue(env, jPixel, "red", NULL,
                         &red) &&
	getIntFieldValue(env, jPixel, "green", NULL,
                         &green) &&
        getIntFieldValue(env, jPixel, "blue", NULL,
                         &blue) &&
	getIntFieldValue(env, jPixel, "opacity", NULL,
                         &transparency);
  if (!successful) {
      return successful;
  }
  iPixel->red = (Quantum) red;
  iPixel->green = (Quantum) green;
  iPixel->blue = (Quantum) blue;
#if MagickLibVersion < 0x700
  iPixel->opacity =
#else
  iPixel->alpha =
#endif
    (Quantum) transparency;
  return successful;
}







/*
 * Construct a new Java magick.MagickImage object and set the
 * handle.
 *
 * Input:
 *   env     Java VM environment
 *   image   ImageMagick image handle
 *
 * Return:
 *   A new instance of magick.MagickImage object.
 *
 */
jobject newImageObject(JNIEnv *env, Image* image)
{
    jclass magickImageClass = 0;
    jmethodID consMethodID = 0;
    jobject newObj;

    magickImageClass = (*env)->FindClass(env, "magick/MagickImage");
    if (magickImageClass == 0) {
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, magickImageClass,
				       "<init>", "()V");
    if (consMethodID == 0) {
	return NULL;
    }

    newObj = (*env)->NewObject(env, magickImageClass, consMethodID);
    if (newObj == NULL) {
	return NULL;
    }

    if (!setHandle(env, newObj, "magickImageHandle", (void*) image, NULL)) {
#ifdef DIAGNOSTIC
	fprintf(stderr, "newImageObject: Unable to set handle\n");
#endif
	return NULL;
    }

    return newObj;
}




/*
 * Set a attribute in a generic handle to string.
 *
 * Input:
 *   env        Java VM environment
 *   attribVar  points to a C string so as to set the value
 *   jstr       Java string for which to set the attrib
 *
 * Output:
 *   attribVar  points to a new C string with content from jstr
 */
void setHandleAttribute(JNIEnv *env, char **attribVar, jstring jstr)
{
    const char *cstr = NULL;
    if (*attribVar != NULL) {
	RelinquishMagickMemory(*attribVar);
    }
    cstr = (*env)->GetStringUTFChars(env, jstr, 0);
    *attribVar = (char *) AcquireString(cstr);
    (*env)->ReleaseStringUTFChars(env, jstr, cstr);
}



/*
 * Given the C ProfileInfo structure and the Java ProfileInfo object,
 * acquire the contents of the Java ProfileInfo object and store it in
 * the C ProfileInfo structure.
 *
 * Input:
 *   env            JNI environment
 *   profileObj     Java ProfileInfo object for which field values are to be
 *                  obtain to store into the C ProfileInfo structure
 * Output:
 *   profileInfo    C ProfileINfo structure to store field values
 */
void setProfileInfo(JNIEnv *env, ProfileInfo *profileInfo, jobject profileObj)
{
    char *name;
    char *info;
    int infoSize = 0;

    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
        return;
    }

    name = getStringFieldValue(env, profileObj, "name", NULL);
    info = (char *) getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);
    if (profileInfo->name != NULL) {
        RelinquishMagickMemory(profileInfo->name);
    }
    profileInfo->name = name;
    if (profileInfo->info != NULL) {
        RelinquishMagickMemory(profileInfo->info);
    }
    profileInfo->info = (unsigned char *) info;
    profileInfo->length = infoSize;
}



/*
 * Given the C ProfileInfo structure, construct a Java ProfileInfo
 * object with values obtained from the C ProfileInfo structure.
 * Input:
 *   env           JNI environment
 *   profileInfo   C ProfileInfo structure
 * Return:
 *   Java ProfileInfo object
 */
jobject getProfileInfo(JNIEnv *env, ProfileInfo *profileInfo)
{
    jclass profileInfoClass;
    jmethodID consMethodID;
    jobject profileObject;
    jstring name;
    jbyteArray byteArray;
    signed char *byteElements;

    /* Get the ProfileInfo class ID */
    profileInfoClass = (*env)->FindClass(env, "magick/ProfileInfo");
    if (profileInfoClass == 0) {
        throwMagickException(env, "Unable to locate class "
                                   "magick.ProfileInfo");
        return NULL;
    }

    /* Get the constructor method ID */
    consMethodID = (*env)->GetMethodID(env, profileInfoClass,
                                       "<init>", "(Ljava/lang/String;[B)V");
    if (consMethodID == 0) {
        throwMagickException(env, "Unable to locate constructor "
                                  "ProfileInfo(String, byte[])");
        return NULL;
    }

    /* Construct the name */
    if (profileInfo->name != NULL) {
        name = (*env)->NewStringUTF(env, profileInfo->name);
        if (name == NULL) {
            throwMagickException(env, "Unable to allocate Java String "
                                      "for profile name");
            return NULL;
        }
    }
    else {
        name = NULL;
    }

    /* Construct the byte array */
    if (profileInfo->length > 0) {
        byteArray = (*env)->NewByteArray(env, profileInfo->length);
        if (byteArray == NULL) {
            throwMagickException(env, "Unable to allocate byte array "
                                      "for profile info");
            return NULL;
        }
        byteElements =
            (signed char*) (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
        if (byteElements == NULL) {
            throwMagickException(env, "Unable to obtain byte array elements "
                                      "for profile info");
            return NULL;
        }
        memcpy(byteElements,
               profileInfo->info,
               profileInfo->length);
        (*env)->ReleaseByteArrayElements(env, byteArray, byteElements, 0);
    }
    else {
        byteArray = NULL;
    }

    /* Construct the ProfileInfo object */
    profileObject = (*env)->NewObject(env, profileInfoClass, consMethodID,
                                      name, byteArray);
    if (profileObject == NULL) {
        throwMagickException(env, "Unable to construct ProfileInfo object");
        return NULL;
    }

    return profileObject;
}
