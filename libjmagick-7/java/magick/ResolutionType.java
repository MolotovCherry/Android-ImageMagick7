package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 *
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/image.h
 */
public interface ResolutionType {

    public final static int UndefinedResolution = 0;
    public final static int PixelsPerInchResolution = 1;
    public final static int PixelsPerCentimeterResolution = 2;

}
