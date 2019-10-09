package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/image.h
 *
 * @author Eric Yeo
 */
public interface InterlaceType {

    public static final int UndefinedInterlace = 0;
    public static final int NoInterlace = 1;
    public static final int LineInterlace = 2;
    public static final int PlaneInterlace = 3;
    public static final int PartitionInterlace = 4;
    public static final int GIFInterlace = 5;
    public static final int JPEGInterlace = 6;
    public static final int PNGInterlace = 7;
}
