package magick;

/**
 * Used in MagickImage.createImage to specify the size
 * of component.
 *
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/pixel.h
 *
 * @author Eric Yeo
 */
public interface StorageType {

    public final static int UndefinedPixel = 0;
    public final static int CharPixel = 1;
    public final static int DoublePixel = 2;
    public final static int FloatPixel = 3;
    public final static int LongPixel = 4;
    public final static int LongLongPixel = 5;
    public final static int QuantumPixel = 6;
    public final static int ShortPixel = 7;

}
