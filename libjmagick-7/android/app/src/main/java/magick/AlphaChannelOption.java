package magick;

public interface AlphaChannelOption {
	/*
		Important! Constant values should correspond to:
		http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/channel.h
	*/

    public static final int UndefinedAlphaChannel = 0;
    public static final int ActivateAlphaChannel = 1;
    public static final int AssociateAlphaChannel = 2;
    public static final int BackgroundAlphaChannel = 3;
    public static final int CopyAlphaChannel = 4;
    public static final int DeactivateAlphaChannel = 5;
    public static final int DiscreteAlphaChannel = 6;
    public static final int DisassociateAlphaChannel = 7;
    public static final int ExtractAlphaChannel = 8;
    public static final int OffAlphaChannel = 9;
    public static final int OnAlphaChannel = 10;
    public static final int OpaqueAlphaChannel = 11;
    public static final int RemoveAlphaChannel = 12;
    public static final int SetAlphaChannel = 13;
    public static final int ShapeAlphaChannel = 14;
    public static final int TransparentAlphaChannel = 15;
	
}
