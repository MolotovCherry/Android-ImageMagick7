package magick;

public interface MorphologyMethod {
    /*
        Important! Constant values should correspond to:
        http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/morphology.h
    */

    public final static int UndefinedMorphology = 0;
/* Convolve / Correlate weighted sums */
    public final static int ConvolveMorphology = 1;           /* Weighted Sum with reflected kernel */
    public final static int CorrelateMorphology = 2;          /* Weighted Sum using a sliding window */
/* Low-level Morphology methods */
    public final static int ErodeMorphology = 3;              /* Minimum Value in Neighbourhood */
    public final static int DilateMorphology = 4;             /* Maximum Value in Neighbourhood */
    public final static int ErodeIntensityMorphology = 5;     /* Pixel Pick using GreyScale Erode */
    public final static int DilateIntensityMorphology = 6;    /* Pixel Pick using GreyScale Dialate */
    public final static int IterativeDistanceMorphology = 7;  /* Add Kernel Value, take Minimum */
/* Second-level Morphology methods */
    public final static int OpenMorphology = 8;               /* Dilate then Erode */
    public final static int CloseMorphology = 9;              /* Erode then Dilate */
    public final static int OpenIntensityMorphology = 10;     /* Pixel Pick using GreyScale Open */
    public final static int CloseIntensityMorphology = 11;    /* Pixel Pick using GreyScale Close */
    public final static int SmoothMorphology = 12;            /* Open then Close */
/* Difference Morphology methods */
    public final static int EdgeInMorphology = 13;            /* Dilate difference from Original */
    public final static int EdgeOutMorphology = 14;           /* Erode difference from Original */
    public final static int EdgeMorphology = 15;              /* Dilate difference with Erode */
    public final static int TopHatMorphology = 16;            /* Close difference from Original */
    public final static int BottomHatMorphology = 17;         /* Open difference from Original */
/* Recursive Morphology methods */
    public final static int HitAndMissMorphology = 18;        /* Foreground/Background pattern matching */
    public final static int ThinningMorphology = 19;          /* Remove matching pixels from image */
    public final static int ThickenMorphology = 20;           /* Add matching pixels from image */
/* Directly Applied Morphology methods */
    public final static int DistanceMorphology = 21;          /* Add Kernel Value, take Minimum */
    public final static int VoronoiMorphology = 22;           /* Distance matte channel copy nearest color */
  
}
