package magick;

public interface FilterType {
	/*
		Important! Constant values should correspond to:
		http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/resample.h
	*/
	public static final int UndefinedFilter = 0;
	public static final int PointFilter = 1;
	public static final int BoxFilter = 2;
	public static final int TriangleFilter = 3;
	public static final int HermiteFilter = 4;
	public static final int HannFilter = 5;
	public static final int HammingFilter = 6;
	public static final int BlackmanFilter = 7;
	public static final int GaussianFilter = 8;
	public static final int QuadraticFilter = 9;
	public static final int CubicFilter = 10;
	public static final int CatromFilter = 11;
	public static final int MitchellFilter = 12;
	public static final int JincFilter = 13;
	public static final int SincFilter = 14;
	public static final int SincFastFilter = 15;
	public static final int KaiserFilter = 16;
	public static final int WelchFilter = 17;
	public static final int ParzenFilter = 18;
	public static final int BohmanFilter = 19;
	public static final int BartlettFilter = 20;
	public static final int LagrangeFilter = 21;
	public static final int LanczosFilter = 22;
	public static final int LanczosSharpFilter = 23;
	public static final int Lanczos2Filter = 24;
	public static final int Lanczos2SharpFilter = 25;
	public static final int RobidouxFilter = 26;
	public static final int RobidouxSharpFilter = 27;
	public static final int CosineFilter = 28;
	public static final int SplineFilter = 29;
	public static final int LanczosRadiusFilter = 30;
	public static final int SentinelFilter = 31;		/* a count of all the filters, not a real filter */
}


