package magick;

public interface CompositeOperator {
	/*
		Important! Constant values should correspond to:
		http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/composite.h
	*/
	public static final int UndefinedCompositeOp = 0;
	public static final int AlphaCompositeOp = 1;
	public static final int AtopCompositeOp = 2;
	public static final int BlendCompositeOp = 3;
	public static final int BlurCompositeOp = 4;
	public static final int BumpmapCompositeOp = 5;
	public static final int ChangeMaskCompositeOp = 6;
	public static final int ClearCompositeOp = 7;
	public static final int ColorBurnCompositeOp = 8;
	public static final int ColorDodgeCompositeOp = 9;
	public static final int ColorizeCompositeOp = 10;
	public static final int CopyBlackCompositeOp = 11;
	public static final int CopyBlueCompositeOp = 12;
	public static final int CopyCompositeOp = 13;
	public static final int CopyCyanCompositeOp = 14;
	public static final int CopyGreenCompositeOp = 15;
	public static final int CopyMagentaCompositeOp = 16;
	public static final int CopyAlphaCompositeOp = 17;
	public static final int CopyRedCompositeOp = 18;
	public static final int CopyYellowCompositeOp = 19;
	public static final int DarkenCompositeOp = 20;
	public static final int DarkenIntensityCompositeOp = 21;
	public static final int DifferenceCompositeOp = 22;
	public static final int DisplaceCompositeOp = 23;
	public static final int DissolveCompositeOp = 24;
	public static final int DistortCompositeOp = 25;
	public static final int DivideDstCompositeOp = 26;
	public static final int DivideSrcCompositeOp = 27;
	public static final int DstAtopCompositeOp = 28;
	public static final int DstCompositeOp = 29;
	public static final int DstInCompositeOp = 30;
	public static final int DstOutCompositeOp = 31;
	public static final int DstOverCompositeOp = 32;
	public static final int ExclusionCompositeOp = 33;
	public static final int HardLightCompositeOp = 34;
	public static final int HardMixCompositeOp = 35;
	public static final int HueCompositeOp = 36;
	public static final int InCompositeOp = 37;
	public static final int IntensityCompositeOp = 38;
	public static final int LightenCompositeOp = 39;
	public static final int LightenIntensityCompositeOp = 40;
	public static final int LinearBurnCompositeOp = 41;
	public static final int LinearDodgeCompositeOp = 42;
	public static final int LinearLightCompositeOp = 43;
	public static final int LuminizeCompositeOp = 44;
	public static final int MathematicsCompositeOp = 45;
	public static final int MinusDstCompositeOp = 46;
	public static final int MinusSrcCompositeOp = 47;
	public static final int ModulateCompositeOp = 48;
	public static final int ModulusAddCompositeOp = 49;
	public static final int ModulusSubtractCompositeOp = 50;
	public static final int MultiplyCompositeOp = 51;
	public static final int NoCompositeOp = 52;
	public static final int OutCompositeOp = 53;
	public static final int OverCompositeOp = 54;
	public static final int OverlayCompositeOp = 55;
	public static final int PegtopLightCompositeOp = 56;
	public static final int PinLightCompositeOp = 57;
	public static final int PlusCompositeOp = 58;
	public static final int ReplaceCompositeOp = 59;
	public static final int SaturateCompositeOp = 60;
	public static final int ScreenCompositeOp = 61;
	public static final int SoftLightCompositeOp = 62;
	public static final int SrcAtopCompositeOp = 63;
	public static final int SrcCompositeOp = 64;
	public static final int SrcInCompositeOp = 65;
	public static final int SrcOutCompositeOp = 66;
	public static final int SrcOverCompositeOp = 67;
	public static final int ThresholdCompositeOp = 68;
	public static final int VividLightCompositeOp = 69;
	public static final int XorCompositeOp = 70;
}
