package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 * Important! Constant values should correspond to:
 * http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/quantum.h
 * @author Eric Yeo
 */
public interface QuantumTypes {

    public static final int UndefinedQuantum = 0;
    public static final int AlphaQuantum = 1;
    public static final int BGRAQuantum = 2;
    public static final int BGROQuantum = 3;
    public static final int BGRQuantum = 4;
    public static final int BlackQuantum = 5;
    public static final int BlueQuantum = 6;
    public static final int CbYCrAQuantum = 7;
    public static final int CbYCrQuantum = 8;
    public static final int CbYCrYQuantum = 9;
    public static final int CMYKAQuantum = 10;
    public static final int CMYKOQuantum = 11;
    public static final int CMYKQuantum = 12;
    public static final int CyanQuantum = 13;
    public static final int GrayAlphaQuantum = 14;
    public static final int GrayQuantum = 15;
    public static final int GreenQuantum = 16;
    public static final int IndexAlphaQuantum = 17;
    public static final int IndexQuantum = 18;
    public static final int MagentaQuantum = 19;
    public static final int OpacityQuantum = 20;
    public static final int RedQuantum = 21;
    public static final int RGBAQuantum = 22;
    public static final int RGBOQuantum = 23;
    public static final int RGBPadQuantum = 24;
    public static final int RGBQuantum = 25;
    public static final int YellowQuantum = 26;
}
