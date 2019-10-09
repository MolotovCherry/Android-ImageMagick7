package magick;

public interface CompressionType {
	/*
		Important! Constant values should correspond to:
		http://git.imagemagick.org/repos/ImageMagick/blob/master/MagickCore/compress.h
	*/
	public final static int UndefinedCompression = 0;
	public final static int B44ACompression = 1;
	public final static int B44Compression = 2;
	public final static int BZipCompression = 3;
	public final static int DXT1Compression = 4;
	public final static int DXT3Compression = 5;
	public final static int DXT5Compression = 6;
	public final static int FaxCompression = 7;
	public final static int Group4Compression = 8;
	public final static int JBIG1Compression = 9;			/* ISO/IEC std 11544 / ITU-T rec T.82 */
	public final static int JBIG2Compression = 10;			/* ISO/IEC std 14492 / ITU-T rec T.88 */
	public final static int JPEG2000Compression = 11;		/* ISO/IEC std 15444-1 */
	public final static int JPEGCompression = 12;
	public final static int LosslessJPEGCompression = 13;
	public final static int LZMACompression = 14;			/* Lempel-Ziv-Markov chain algorithm */
	public final static int LZWCompression = 15;
	public final static int NoCompression = 16;
	public final static int PizCompression = 17;
	public final static int Pxr24Compression = 18;
	public final static int RLECompression = 19;
	public final static int ZipCompression = 20;
	public final static int ZipSCompression = 21;
}
