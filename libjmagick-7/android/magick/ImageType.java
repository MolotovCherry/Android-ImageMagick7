package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/image.h
 * @see MagickImage#getImageType()
 * @author Eric Yeo
 */
public interface ImageType {

	public static final int UndefinedType = 0;
	public static final int BilevelType = 1;
	public static final int GrayscaleType = 2;
	public static final int GrayscaleAlphaType = 3;
	public static final int PaletteType = 4;
	public static final int PaletteAlphaType = 5;
	public static final int TrueColorType = 6;
	public static final int TrueColorAlphaType = 7;
	public static final int ColorSeparationType = 8;
	public static final int ColorSeparationAlphaType = 9;
	public static final int OptimizeType = 10;
	public static final int PaletteBilevelAlphaType = 11;
}
