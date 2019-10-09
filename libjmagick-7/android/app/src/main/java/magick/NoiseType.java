package magick;

/**
 * Corresponds to ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/fx.h
 */
public interface NoiseType {

    public final static int UndefinedNoise = 0;
    public final static int UniformNoise = 1;
    public final static int GaussianNoise = 2;
    public final static int MultiplicativeGaussianNoise = 3;
    public final static int ImpulseNoise = 4;
    public final static int LaplacianNoise = 5;
    public final static int PoissonNoise = 6;
    public final static int RandomNoise = 7;

}
