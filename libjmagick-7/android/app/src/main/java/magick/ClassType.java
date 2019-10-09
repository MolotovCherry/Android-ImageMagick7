package magick;

public interface ClassType {
	/*
          Important! Constant values should correspond to:
          http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/magick-type.h
	*/

	public final static int UndefinedClass = 0;
	/** DirectClass for true color images */
	public final static int DirectClass = 1;
	/** PseudoClass for colormapped images. */
	public final static int PseudoClass = 2;

}
