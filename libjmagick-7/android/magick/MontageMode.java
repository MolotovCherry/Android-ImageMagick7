package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/montage.h
 * @author Eric Yeo
 */
public interface MontageMode {

    public final int UndefinedMode = 0;
    public final int FrameMode = 1;
    public final int UnframeMode = 2;
    public final int ConcatenateMode = 3;

}
