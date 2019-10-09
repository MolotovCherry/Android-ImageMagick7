package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/draw.h
 */
public interface PaintMethod {

    public final int UndefinedMethod = 0;
    public final int PointMethod = 1;
    public final int ReplaceMethod = 2;
    public final int FloodfillMethod = 3;
    public final int FillToBorderMethod = 4;
    public final int ResetMethod = 5;

}
