package magick;

public interface ColorspaceType {
	/*
		Important! Constant values should correspond to:
		http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/colorspace.h
	*/
	public final static int UndefinedColorspace = 0;
	public final static int CMYColorspace = 1;			/* negated linear RGB colorspace */
	public final static int CMYKColorspace = 2;			/* CMY with Black separation */
	public final static int GRAYColorspace = 3;			/* Single Channel greyscale (linear) image */
	public final static int HCLColorspace = 4;
	public final static int HCLpColorspace = 5;
	public final static int HSBColorspace = 6;
	public final static int HSIColorspace = 7;
	public final static int HSLColorspace = 8;
	public final static int HSVColorspace = 9;			/* alias for HSB */
	public final static int HWBColorspace = 10;
	public final static int LabColorspace = 11;
	public final static int LCHColorspace = 12;			/* alias for LCHuv */
	public final static int LCHabColorspace = 13;		/* Cylindrical (Polar) Lab */
	public final static int LCHuvColorspace = 14;		/* Cylindrical (Polar) Luv */
	public final static int LogColorspace = 15;
	public final static int LMSColorspace = 16;
	public final static int LuvColorspace = 17;
	public final static int OHTAColorspace = 18;
	public final static int Rec601YCbCrColorspace = 19;
	public final static int Rec709YCbCrColorspace = 20;
	public final static int RGBColorspace = 21;			/* Linear RGB colorspace */
	public final static int scRGBColorspace = 22;		/* ??? */
	public final static int sRGBColorspace = 23;		/* Default: non-linear sRGB colorspace */
	public final static int TransparentColorspace = 24;
	public final static int xyYColorspace = 25;
	public final static int XYZColorspace = 26;			/* IEEE Color Reference colorspace */
	public final static int YCbCrColorspace = 27;
	public final static int YCCColorspace = 28;
	public final static int YDbDrColorspace = 29;
	public final static int YIQColorspace = 30;
	public final static int YPbPrColorspace = 31;
	public final static int YUVColorspace = 32;
}
