package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/geometry.h
 *
 * @author Eric Yeo
 */
public interface GravityType {

    public static final int UndefinedGravity = 0;
    public static final int ForgetGravity = 0;
    public static final int NorthWestGravity = 1;
    public static final int NorthGravity = 2;
    public static final int NorthEastGravity = 3;
    public static final int WestGravity = 4;
    public static final int CenterGravity = 5;
    public static final int EastGravity = 6;
    public static final int SouthWestGravity = 7;
    public static final int SouthGravity = 8;
    public static final int SouthEastGravity = 9;
}
