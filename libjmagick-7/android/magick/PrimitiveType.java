package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/draw.h
 * @author Eric Yeo
 */
public interface PrimitiveType {

    public final static int UndefinedPrimitive = 0;
    public final static int AlphaPrimitive = 1;
    public final static int ArcPrimitive = 2;
    public final static int BezierPrimitive = 3;
    public final static int CirclePrimitive = 4;
    public final static int ColorPrimitive = 5;
    public final static int EllipsePrimitive = 6;
    public final static int ImagePrimitive = 7;
    public final static int LinePrimitive = 8;
    public final static int PathPrimitive = 9;
    public final static int PointPrimitive = 10;
    public final static int PolygonPrimitive = 11;
    public final static int PolylinePrimitive = 12;
    public final static int RectanglePrimitive = 13;
    public final static int RoundRectanglePrimitive = 14;
    public final static int TextPrimitive = 15;

}
