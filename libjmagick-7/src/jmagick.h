#ifndef __JMAGICK__
#define __JMAGICK__

#include <float.h>
#include <string.h>
#if defined (IMAGEMAGICK_HEADER_STYLE_7)
#    include <MagickCore/image.h>
#else
#    include <magick/image.h>
#endif
#if MagickLibVersion >= 0x700
MagickBooleanType LevelImageShim(Image *image,const char *levels);

// This should be kept in sync with the struct defined in MagickCore/profile.c
struct _ProfileInfo
{
  char
    *name;

  size_t
    length;

  unsigned char
    *info;

  size_t
    signature;
};
#endif


/*
 * Convenience function to help throw an MagickException.
 */
void throwMagickException(JNIEnv *env, const char *mesg);


/*
 * Convenience function to help throw an MagickApiException.
 *
 * Input:
 *   mesg       JMagick message
 *   exception  points to a ImageMagick ExceptionInfo structure
 */
void throwMagickApiException(JNIEnv *env,
			     const char *mesg,
			     const ExceptionInfo *exception);

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
		jfieldID *fieldId);


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
	      jfieldID *fieldId);


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
		     jint *value);

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
                     jint value);

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
                                      int *size);

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
int getRectangle(JNIEnv *env, jobject jRect, RectangleInfo *iRect);


/*
 * From a magick.PixelPacket object, construct a ImageMagick
 * PixelPacket, as passed in from the parameter.
 *
 * Input:
 *   env           Java VM environment
 *   jPixelPacket  an instance of magick.PixelPacket
 *
 * Output:
 *   iPixelPacket  to be initilised by values in jPixelPacket
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getPixelPacket(JNIEnv *env,
		   jobject jPixelPacket,
#if MagickLibVersion < 0x700
		   PixelPacket *iPixelPacket);
#else
		   PixelInfo *iPixelInfo);
#endif

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
jobject newImageObject(JNIEnv *env, Image* image);



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
void setHandleAttribute(JNIEnv *env, char **attribVar, jstring jstr);




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
void setProfileInfo(JNIEnv *env,
                    ProfileInfo *profileInfo,
                    jobject profileObj);



/*
 * Given the C ProfileInfo structure, construct a Java ProfileInfo
 * object with values obtained from the C ProfileInfo structure.
 * Input:
 *   env           JNI environment
 *   profileInfo   C ProfileInfo structure
 * Return:
 *   Java ProfileInfo object
 */
jobject getProfileInfo(JNIEnv *env, ProfileInfo *profileInfo);

// Return whether a string represents the given double.
static inline int aisd(double f, char* s) {
  double r;
  sscanf(s, "%lf", &r);
  return r == f;
}
// Return the shortest lossless string representation of an IEEE double.
// Guaranteed to fit in 23 characters (including the final '\0').
static inline char* dtoa(char* res, double f) {
  int i, j, lenF = 1e9;
  char fmt[8];
  int e = floor(log10(f)) + 1;

  if (f > DBL_MAX) { sprintf(res, "1e999"); return res; }  // converts to Inf
  if (f < -DBL_MAX) { sprintf(res, "-1e999"); return res; }  // converts to -Inf
  if (isnan(f)) { sprintf(res, "NaN"); return res; }  // NaNs don't work under MSVCRT

  // compute the shortest representation without exponent ("123000", "0.15")
  if (!f || (e>-4 && e<21)) {
    for (i=0; i<=20; i++) {
      sprintf(fmt, "%%.%dlf", i);
      sprintf(res, fmt, f);
      if (aisd(f, res)) { lenF = strlen(res); break; }
    }
  }

  if (!f) return res;

  // compute the shortest representation with exponent ("123e3", "15e-2")
  for (i=0; i<19; i++) {
    sprintf(res, "%.0lfe%d", f * pow(10,-e), e); if (aisd(f, res)) break;
    j = strlen(res); if (j >= lenF) break;
    while (res[j] != 'e') j--;
    res[j-1]--; if (aisd(f, res)) break;   // try mantissa -1
    res[j-1]+=2; if (aisd(f, res)) break;  // try mantissa +1
    e--;
  }
  if (lenF <= strlen(res)) sprintf(res, fmt, f);
  return res;
}

/*
 * Convenience macro to set an attribute in the object handle.
 */
#define setMethod(funcName, fieldName, handleName, handleType, fieldType)     \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, fieldType value)                              \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    info->fieldName = value;                                                  \
}



/*
 * Convenience macro to get an attribute of an object handle.
 */
#define getMethod(funcName, fieldName, handleName, handleType, fieldType)     \
JNIEXPORT fieldType JNICALL funcName                                          \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return (fieldType) 0;                                                 \
    }                                                                         \
                                                                              \
    return info->fieldName;                                                   \
}

//	throwMagickException(env, "Unable to retrieve handle " funcName+fieldName);               \

/*
 * Convenience macro to set an integer attribute in the object handle.
 */
#define setIntMethod(funcName, fieldName, handleName, handleType)             \
        setMethod(funcName, fieldName, handleName, handleType, jint)


/*
 * Convenience macro to get an integer attribute of an object handle.
 */
#define getIntMethod(funcName, fieldName, handleName, handleType)             \
        getMethod(funcName, fieldName, handleName, handleType, jint)


/*
 * Convenience macro to set an boolean attribute in the object handle.
 */
#define setBoolMethod(funcName, fieldName, handleName, handleType)            \
        setMethod(funcName, fieldName, handleName, handleType, jboolean)


/*
 * Convenience macro to get an boolean attribute of an object handle.
 */
#define getBoolMethod(funcName, fieldName, handleName, handleType)            \
        getMethod(funcName, fieldName, handleName, handleType, jboolean)


/*
 * Convenience macro to set an short attribute in the object handle.
 */
#define setShortMethod(funcName, fieldName, handleName, handleType)           \
        setMethod(funcName, fieldName, handleName, handleType, jshort)


/*
 * Convenience macro to get an byte attribute of an object handle.
 */
#define getByteMethod(funcName, fieldName, handleName, handleType)            \
        getMethod(funcName, fieldName, handleName, handleType, jbyte)


/*
 * Convenience macro to set an byte attribute in the object handle.
 */
#define setByteMethod(funcName, fieldName, handleName, handleType)            \
        setMethod(funcName, fieldName, handleName, handleType, jbyte)


/*
 * Convenience macro to get a double attribute of an object handle.
 */
#define getDoubleMethod(funcName, fieldName, handleName, handleType)          \
        getMethod(funcName, fieldName, handleName, handleType, jdouble)


/*
 * Convenience macro to set an double attribute in the object handle.
 */
#define setDoubleMethod(funcName, fieldName, handleName, handleType)          \
        setMethod(funcName, fieldName, handleName, handleType, jdouble)

// Fix memory leak bug. Below was:	RelinquishMagickMemory((void**) &info->fieldName);                            \
//  info->fieldName = NULL;                                               \

/*
 * Convenience macro to set a string attribute in the object handle.
 */
#define setStringMethod(funcName, fieldName, handleName, handleType)          \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, jstring value)                                \
{                                                                             \
    handleType *info = NULL;                                                  \
    const char *cstr = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    if (info->fieldName != NULL) {                                            \
	info->fieldName=(char *) RelinquishMagickMemory((void*) info->fieldName); \
    }                                                                         \
                                                                              \
    cstr = (*env)->GetStringUTFChars(env, value, 0);                          \
    if (cstr == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve Java string chars");    \
	return;                                                               \
    }                                                                         \
    info->fieldName = (char *) AcquireString(cstr);                           \
    if (info->fieldName == NULL) {                                            \
	throwMagickException(env, "Unable to allocate memory");               \
    }                                                                         \
    (*env)->ReleaseStringUTFChars(env, value, cstr);                          \
}

/*
 * Convenience macro which does nothing. Used for removed attributes with no analog.
 */
#define setDeprecatedMethod(funcName, fieldName, handleName, handleType, fieldType)          \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, fieldType value)                                \
{}

/*
 * Convenience macro to get a string attribute which has been removed with no analog.
 */
#define getStringDeprecatedMethod(funcName, fieldName, handleName, handleType) \
JNIEXPORT jstring JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    return NULL;                                                              \
}

/*
 * Convenience macro to get a string attribute which has been removed with no analog.
 */
#define getDeprecatedMethod(funcName, fieldName, handleName, handleType, fieldType)          \
JNIEXPORT fieldType JNICALL funcName                                          \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    return (fieldType) 0;                                                     \
}

/*
 * Convenience macro to get a string attribute in the object handle.
 */
#define getStringMethod(funcName, fieldName, handleName, handleType)          \
JNIEXPORT jstring JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
    jstring jstr = NULL;                                                      \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    if (info->fieldName == NULL) {                                            \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    jstr = (*env)->NewStringUTF(env, info->fieldName);                        \
    if (jstr == NULL) {                                                       \
	throwMagickException(env, "Unable to construct new string");          \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    return jstr;                                                              \
}


/*
 * Convenience macro to set a PixelPacket attribute in the object handle.
 */
#define setPixelPacketMethod(funcName, fieldName, handleName, handleType)     \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, jobject jPixelPacket)                         \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    if (!getPixelPacket(env, jPixelPacket, &info->fieldName)) {               \
	throwMagickException(env, "Unable to set PixelPacket");               \
	return;                                                               \
    }                                                                         \
}



/*
 * Convenience macro to get a PixelPacket attribute in the object handle.
 */
#if MagickLibVersion < 0x700
#define getPixelPacketMethod(funcName, fieldName, handleName, handleType)     \
JNIEXPORT jobject JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
    jobject jPixelPacket = NULL;                                              \
    jclass pixelPacketClass;                                                  \
    jmethodID consMethodID;                                                   \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");          \
    if (pixelPacketClass == 0) {                                              \
	throwMagickException(env,                                             \
			     "Unable to locate class magick.PixelPacket");    \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,                 \
				       "<init>", "(IIII)V");                  \
    if (consMethodID == 0) {                                                  \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,     \
		                     (jint) info->fieldName.red,              \
		                     (jint) info->fieldName.green,            \
		                     (jint) info->fieldName.blue,             \
		                     (jint) info->fieldName.opacity);         \
    if (jPixelPacket == NULL) {                                               \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    return jPixelPacket;                                                      \
}
#else
#define getPixelPacketMethod(funcName, fieldName, handleName, handleType)     \
JNIEXPORT jobject JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
    jobject jPixelPacket = NULL;                                              \
    jclass pixelPacketClass;                                                  \
    jmethodID consMethodID;                                                   \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");          \
    if (pixelPacketClass == 0) {                                              \
	throwMagickException(env,                                             \
			     "Unable to locate class magick.PixelPacket");    \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,                 \
				       "<init>", "(IIII)V");                  \
    if (consMethodID == 0) {                                                  \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,     \
		                     (jint) info->fieldName.red,              \
		                     (jint) info->fieldName.green,            \
		                     (jint) info->fieldName.blue,             \
		                     (jint) info->fieldName.alpha);         \
    if (jPixelPacket == NULL) {                                               \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    return jPixelPacket;                                                      \
}
#endif




#endif /* __JMAGICK__ */
