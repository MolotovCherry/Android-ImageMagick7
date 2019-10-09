package magick;

/**
 * Corresponds to the ImageMagick ImageInfo structure.
 *
 * @author Eric Yeo
 */
public class ImageInfo extends Magick {

    /**
     * Internal ImageMagick ImageInfo handle.
     * We use long (64-bits) for portability.
     */
    private long imageInfoHandle = 0;

    /**
     * Constructor.
     * @throws MagickException if an error occurs
     */
    public ImageInfo()
	throws MagickException
    {
	init();
    }

    /**
     * Constructor.
     *
     * @param fileName initial value of the file_name attribute
     * @throws MagickException if an error occurs
     */
    public ImageInfo(String fileName)
	throws MagickException
    {
	init();
	setFileName(fileName);
    }

    /**
     * To release memory on cleanup.
     */
    protected void finalize()
    {
	destroyImageInfo();
    }

    /**
     * Initialises the internal native handle.
     * @throws MagickException if an error occurs
     */
    public native void init()
	throws MagickException;

    /**
     * Set the file name attribute of the handle.
     *
     * @param fileName the new file name
     * @throws MagickException if an error occurs
     */
    public native void setFileName(String fileName)
	throws MagickException;

		/**
		 * Associates a value with an image option.
		 * Example: <pre>
		 * ImageInfo info = new ImageInfo(...)
		 * info.setImageOption("quantum:polarity", "min-is-white");
		 * </pre>
		 * This then ensures that our tiffs come out in a way that works with
		 * Microsofts Tiff Viewer.
		 *
		 * @param option the image option
		 * @param value the image option value
		 * @since JMagick 6.4.3 (2008-08-05)
		 * @throws MagickException if an error occurs
		 */
		public native void setImageOption(String option, String value)
	throws MagickException;

		/**
		 * Return the file name attribute of the handle.
		 *
		 * @return the file name attribute value
		 * @throws MagickException if an error occurs
		 */
		public native String getFileName()
	throws MagickException;

    /**
     * Set the affirm attribute.
     *
     * @param affirm new value of affirm
     * @throws MagickException if an error occurs
     */
    public native void setAffirm(boolean affirm)
	throws MagickException;

    /**
     * Get the affirm attribute.
     *
     * @return the affirm attribute value
     * @throws MagickException if an error occurs
     */
    public native boolean getAffirm()
	throws MagickException;

    /**
     * Set the subimage attribute.
     *
     * @param value new value of subimage
     * @throws MagickException if an error occurs
     */
    public native void setSubimage(int value)
	throws MagickException;

    /**
     * Get the subimage attribute.
     *
     * @return the subimage attribute value
     * @throws MagickException if an error occurs
     */
    public native int getSubimage()
	throws MagickException;

    /**
     * Set the subrange attribute.
     *
     * @param value the new value of subrange
     * @throws MagickException if an error occurs
     */
    public native void setSubrange(int value)
	throws MagickException;

    /**
     * Get the subrange attribute.
     *
     * @return the subrange attribute value
     * @throws MagickException if an error occurs
     */
    public native int getSubrange()
	throws MagickException;

    /**
     * Set the server_name attribute.
     *
     * @param name the new value of server_name
     * @throws MagickException if an error occurs
     */
    public native void setServerName(String name)
	throws MagickException;

    /**
     * Get the server_name attribute.
     *
     * @return the server_name attribute value
     * @throws MagickException if an error occurs
     */
    public native String getServerName()
	throws MagickException;

    /**
     * Set the font attribute.
     *
     * @param font the new value of font
     * @throws MagickException if an error occurs
     */
    public native void setFont(String font)
	throws MagickException;

    /**
     * Get the font attribute.
     *
     * @return the font attribute value
     * @throws MagickException if an error occurs
     */
    public native String getFont()
	throws MagickException;

    /**
     * Set the size attribute.
     *
     * @param size the new value of size
     * @throws MagickException if an error occurs
     */
    public native void setSize(String size)
	throws MagickException;

    /**
     * Get the size attribute.
     *
     * @return the size attribute value
     * @throws MagickException if an error occurs
     */
    public native String getSize()
	throws MagickException;

    /**
     * Set the tile attribute.
     *
     * @param tile the new value of tile
     * @throws MagickException if an error occurs
     */
    public native void setTile(String tile)
	throws MagickException;

    /**
     * Get the tile attribute.
     *
     * @return the tile attribute value
     * @throws MagickException if an error occurs
     */
    public native String getTile()
	throws MagickException;

    /**
     * Set the density attribute.
     *
     * @param density the new value of density
     * @throws MagickException if an error occurs
     */
    public native void setDensity(String density)
	throws MagickException;

    /**
     * Get the density attribute.
     *
     * @return the density attribute value
     * @throws MagickException if an error occurs
     */
    public native String getDensity()
	throws MagickException;

    /**
     * Set the page attribute.
     *
     * @param page the new value of page
     * @throws MagickException if an error occurs
     */
    public native void setPage(String page)
	throws MagickException;

    /**
     * Get the page attribute.
     *
     * @return the page attribute value
     * @throws MagickException if an error occurs
     */
    public native String getPage()
	throws MagickException;

    /**
     * Set the texture attribute.
     *
     * @param texture the new value of texture
     * @throws MagickException if an error occurs
     */
    public native void setTexture(String texture)
	throws MagickException;

    /**
     * Get the texture attribute.
     *
     * @return the texture attribute value
     * @throws MagickException if an error occurs
     */
    public native String getTexture()
	throws MagickException;

    /**
     * Set the view attribute.
     *
     * @param view the new value of view
     * @throws MagickException if an error occurs
     */
    public native void setView(String view)
	throws MagickException;

    /**
     * Get the view attribute.
     *
     * @return the view attribute value
     * @throws MagickException if an error occurs
     */
    public native String getView()
	throws MagickException;

    /**
     * Set the adjoin attribute.
     *
     * @param value the new value of adjoin
     * @throws MagickException if an error occurs
     */
    public native void setAdjoin(int value)
	throws MagickException;

    /**
     * Get the adjoin attribute.
     *
     * @return the adjoin attribute value
     * @throws MagickException if an error occurs
     */
    public native int getAdjoin()
	throws MagickException;

    /**
     * Set the colorspace attribute.
     *
     * @param value the new value of colorspace
     * @throws MagickException if an error occurs
     */
    public native void setColorspace(int value)
	throws MagickException;

    /**
     * Get the colorspace attribute.
     *
     * @return the colorspace attribute value
     * @throws MagickException if an error occurs
     */
    public native int getColorspace()
	throws MagickException;

    /**
     * Set the compression attribute.
     *
     * @param value the new value of compression
     * @throws MagickException if an error occurs
     */
    public native void setCompression(int value)
	throws MagickException;

    /**
     * Get the compression attribute.
     *
     * @return the compression attribute value
     * @throws MagickException if an error occurs
     */
    public native int getCompression()
	throws MagickException;

    /**
     * Set the dither attribute.
     *
     * @param value the new value of dither
     * @throws MagickException if an error occurs
     */
    public native void setDither(int value)
	throws MagickException;

    /**
     * Get the dither attribute.
     *
     * @return the dither attribute value
     * @throws MagickException if an error occurs
     */
    public native int getDither()
	throws MagickException;

		/**
		 * Set the antialias attribute.
		 *
		 * @param value the new value of antialias
		 * @throws MagickException if an error occurs
		 */
		public native void setAntialias(int value)
	throws MagickException;

		/**
		 * Get the antialias attribute.
		 *
		 * @return the antialias attribute value
		 * @throws MagickException if an error occurs
		 */
		public native int getAntialias()
	throws MagickException;

		/**
		 * Set the interlace attribute.
		 *
		 * @param value the new value of interlace
		 * @throws MagickException if an error occurs
		 */
		public native void setInterlace(int value)
	throws MagickException;

    /**
     * Get the interlace attribute.
     *
     * @return the interlace attribute value
     * @throws MagickException if an error occurs
     */
    public native int getInterlace()
	throws MagickException;

    /**
     * Set the monochrome attribute.
     *
     * @param value the new value of monochrome
     * @throws MagickException if an error occurs
     */
    public native void setMonochrome(int value)
	throws MagickException;

    /**
     * Get the monochrone attribute.
     *
     * @return the monochrone attribute value
     * @throws MagickException if an error occurs
     */
    public native int getMonochrome()
	throws MagickException;

    /**
     * Set the fuzz attribute.
     *
     * @param value the new value of fuzz
     * @throws MagickException if an error occurs
     */
    public native void setFuzz(double value)
            throws MagickException;

    /**
     * Get the fuzz attribute.
     *
     * @return the fuzz attribute value
     * @throws MagickException if an error occurs
     */
    public native double getFuzz()
            throws MagickException;

    /**
     * Set the pointsize attribute.
     *
     * @param value the new value of pointsize
     * @throws MagickException if an error occurs
     */
    public native void setPointSize(int value)
	throws MagickException;

    /**
     * Get the pointsize attribute.
     *
     * @return the pointsize attribute value
     * @throws MagickException if an error occurs
     */
    public native int getPointSize()
	throws MagickException;

    /**
     * Set the quality attribute.
     *
     * @param value the new value of quality
     * @throws MagickException if an error occurs
     */
    public native void setQuality(int value)
	throws MagickException;

    /**
     * Get the quality attribute.
     *
     * @return the quality attribute value
     * @throws MagickException if an error occurs
     */
    public native int getQuality()
	throws MagickException;

	/** Set the verbose attribute.
	 * This makes writeImage print out information about the written image on standard output, like:
	 * <pre>
	 * TIFF Directory at offset 0x0
					 Image Width: 102 Image Length: 68
					 Resolution: 72, 72 pixels/inch
					 Bits/Sample: 8
					 Compression Scheme: None
					 Photometric Interpretation: RGB color
					 FillOrder: msb-to-lsb
					 Document Name: "test/output/black_and_White_In_RGBRGB.tif"
					 Orientation: row 0 top, col 0 lhs
					 Samples/Pixel: 3
					 Rows/Strip: 26
					 Planar Configuration: single image plane
					 ICC Profile: <present>, 560 bytes
					 Software: ImageMagick 6.2.6 10/06/06 Q8 http://www.imagemagick.org
	 * </pre>
				 * <p>
				 * Note: The verbose setting is primarily for use with the utility programs.
				 * it is equivalent to the -verbose option for ImageMagick command line tool.
				 * The delegates subsystem does
				 * observe verbose, which is why setting verbose to true causes some
				 * output when loading a PDF or PS file.
				 * </p>
	 * @param value the new verbosity value
	 * @see MagickImage#writeImage(ImageInfo)
	 * @throws MagickException if an error occurs
	 */
	public native void setVerbose(int value) throws MagickException;

    /**
     * Get the verbose attribute.
     *
     * @return verbosity
     * @throws MagickException if an error occurs
     * @see #setVerbose(int)
     */
	public native int getVerbose() throws MagickException;

    /**
     * Set the preview_type attribute.
     *
     * @param value new value of the preview_type attribute
     * @throws MagickException if an error occurs
     */
    public native void setPreviewType(int value)
	throws MagickException;

    /**
     * Get the preview_type attribute.
     *
     * @return the preview_type attribute value
     * @throws MagickException if an error occurs
     */
    public native int getPreviewType()
	throws MagickException;

		/**
		 * Set the ping attribute.
		 * Used to get information about an image without having to read the image into memory.
		 * Afterwards you can use readImage to get the width, height, file size in bytes, and the file format of the image, without loading the pixels.
		 * @param value new value of the ping attribute
		 * @throws MagickException if an error occurs
		 */
		public native void setPing(boolean value)
	throws MagickException;

		/**
		 * Get the ping attribute.
		 *
		 * @return the ping attribute value
		 * @throws MagickException if an error occurs
		 * @see #setPing(boolean)
		 */
		public native boolean getPing()
	throws MagickException;

    /**
     * Clean up the memory allocated for the handle
     */
    private native void destroyImageInfo();

		/**
		 * Set the magick attribute of the handle.
		 *
		 * @author: Abdulbaset Gaddah &lt;agaddah@yahoo.com&gt;
		 * @param magick new value of the magick attribute
		 * @throws MagickException if an error occurs
		 */
		public native void setMagick(String magick)
	throws MagickException;

    /**
     * Return the magick attribute of the handle.
     *
     * @author Abdulbaset Gaddah &lt;agaddah@yahoo.com&gt;
     * @return the magick attribute value
     * @throws MagickException if an error occurs
     */
    public native String getMagick()
	throws MagickException;

		/**
		 * Set the units attribute of the ImageInfo.
		 *
		 * @param resolutionType the resolution type as defined in ResolutionType
		 * @see ResolutionType
		 * @throws MagickException if an error occurs
		 */
		public native void setUnits(int resolutionType)
				throws MagickException;

    /**
     * Get the units attribute of the ImageInfo.
     *
     * @return A integer representing the resolution type as defined
     *         in ResolutionType
     * @see ResolutionType
     * @exception MagickException on error
     * @throws MagickException if an error occurs
     */
    public native int getUnits()
        throws MagickException;



    /**
     * Set the border colour..
     * @param color the border colour
     * @see magick.MagickImage#borderImage
     * @throws MagickException if an error occurs
     */
    public native void setBorderColor(PixelPacket color)
        throws MagickException;


    /**
     * Get the current border colour..
     * @return the current border colour
     * @see magick.MagickImage#borderImage
     * @throws MagickException if an error occurs
     */
    public native PixelPacket getBorderColor()
        throws MagickException;

    /**
     * Return the depth of the image.
     *
     * @return the depth of the image.
     * @throws MagickException if an error occurs
     */
    public native int getDepth()
        throws MagickException;

    /**
     * Set the depth of the image.
     * 
     * @param depth the depth of the image
     * @throws MagickException if an error occurs
     */
    public native void setDepth(int depth)
          throws MagickException;

		
		public String toString() {
			try {
				return "Depth:"+this.getDepth()+" view:"+this.getView()+" monochrome:"+this.getMonochrome()+" size:"+this.getSize();
			} catch (MagickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return "ImageInfo get error";
			}
		}
}
