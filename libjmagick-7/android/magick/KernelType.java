package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/morphology.h
 */
public interface KernelType {

    public static final int UndefinedKernel = 0;      /* equivalent to UnityKernel */
    public static final int UnityKernel = 1;          /* The no-op or 'original image' kernel */
    public static final int GaussianKernel = 2;       /* Convolution Kernels, Gaussian Based */
    public static final int DoGKernel = 3;
    public static final int LoGKernel = 4;
    public static final int BlurKernel = 5;
    public static final int CometKernel = 6;
    public static final int BinomialKernel = 7;
    public static final int LaplacianKernel = 8;      /* Convolution Kernels, by Name */
    public static final int SobelKernel = 9;
    public static final int FreiChenKernel = 10;
    public static final int RobertsKernel = 11;
    public static final int PrewittKernel = 12;
    public static final int CompassKernel = 13;
    public static final int KirschKernel = 14;
    public static final int DiamondKernel = 15;       /* Shape Kernels */
    public static final int SquareKernel = 16;
    public static final int RectangleKernel = 17;
    public static final int OctagonKernel = 18;
    public static final int DiskKernel = 19;
    public static final int PlusKernel = 20;
    public static final int CrossKernel = 21;
    public static final int RingKernel = 22;
    public static final int PeaksKernel = 23;         /* Hit And Miss Kernels */
    public static final int EdgesKernel = 24;
    public static final int CornersKernel = 25;
    public static final int DiagonalsKernel = 26;
    public static final int LineEndsKernel = 27;
    public static final int LineJunctionsKernel = 28;
    public static final int RidgesKernel = 29;
    public static final int ConvexHullKernel = 30;
    public static final int ThinSEKernel = 31;
    public static final int SkeletonKernel = 32;
    public static final int ChebyshevKernel = 33;     /* Distance Measuring Kernels */
    public static final int ManhattanKernel = 34;
    public static final int OctagonalKernel = 35;
    public static final int EuclideanKernel = 36;
    public static final int UserDefinedKernel = 37;   /* User Specified Kernel Array */

}
