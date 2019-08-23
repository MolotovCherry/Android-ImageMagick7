package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/pixel.h
 */
public interface InterpolatePixelMethod {
	public final int UndefinedInterpolatePixel = 0;
	public final int AverageInterpolatePixel = 1;		/* Average 4 nearest neighbours */
	public final int Average9InterpolatePixel = 2;		/* Average 9 nearest neighbours */
	public final int Average16InterpolatePixel = 3;		/* Average 16 nearest neighbours */
	public final int BackgroundInterpolatePixel = 4;	/* Just return background color */
	public final int BilinearInterpolatePixel = 5;		/* Triangular filter interpolation */
	public final int BlendInterpolatePixel = 6;			/* blend of nearest 1, 2 or 4 pixels */
	public final int CatromInterpolatePixel = 7;		/* Catmull-Rom interpolation */
	public final int IntegerInterpolatePixel = 8;		/* Integer (floor) interpolation */
	public final int MeshInterpolatePixel = 9;			/* Triangular Mesh interpolation */
	public final int NearestInterpolatePixel = 10;		/* Nearest Neighbour Only */
	public final int SplineInterpolatePixel = 11;		/* Cubic Spline (blurred) interpolation */
	/*public final int FilterInterpolatePixel = 12;		** Use resize filter - (very slow) */
}