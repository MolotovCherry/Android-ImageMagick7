package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/blob.h
 * @author Eric Yeo
 */
public interface MapMode {

    public final int ReadMode = 0;
    public final int WriteMode = 1;
    public final int IOMode = 2;

}
