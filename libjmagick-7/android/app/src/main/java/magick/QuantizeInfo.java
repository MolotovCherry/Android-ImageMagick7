package magick;

/**
 * Encapsulation of the QuantizedInfo structure.
 *
 * @author Eric Yeo
 *
 */
public class QuantizeInfo extends Magick {

    // Internal handle. Used as pointer to QuantizedInfo
    // structure in memory. We use long (64-bits) for
    // portibility.
    private long quantizeInfoHandle = 0;

    /**
     * Constructor.
     *
     * @throws MagickException on error
     */
    public QuantizeInfo()
	throws MagickException
    {
	init();
    }

    /**
     * Automated destructor.
     */
    protected void finalize()
    {
	destroyQuantizeInfo();
    }

    /**
     * Initialise the QuantizeInfo structure.
     *
     * @throws MagickException on error
     */
    public native void init()
	throws MagickException;

    /**
     * Deallocate the QuantizeInfo structure.
     */
    private native void destroyQuantizeInfo();


    /**
     * Set the value of number_colors field in the QuantizeInfo structure.
     *
     * @param value new value of number_colors
     *
     * @throws MagickException on error
     */
    public native void setNumberColors(int value)
	throws MagickException;


    /**
     * Return the value of number_colors field in the QuantizInfo structure.
     *
     * @return current value of number_colors field
     *
     * @throws MagickException on error
     */
    public native int getNumberColors()
	throws MagickException;


    /**
     * Set the value of tree_depth field in the QuantizeInfo structure.
     *
     * @param value new value of tree_depth
     *
     * @throws MagickException on error
     */
    public native void setTreeDepth(int value)
	throws MagickException;


    /**
     * Return the value of tree_depth field in the QuantizInfo structure.
     *
     * @return current value of tree_depth field
     *
     * @throws MagickException on error
     */
    public native int getTreeDepth()
	throws MagickException;


    /**
     * Set the value of dither field in the QuantizeInfo structure.
     *
     * @param value new value of dither
     *
     * @throws MagickException on error
     */
    public native void setDither(int value)
	throws MagickException;


    /**
     * Return the value of dither field in the QuantizInfo structure.
     *
     * @return current value of dither field
     *
     * @throws MagickException on error
     */
    public native int getDither()
	throws MagickException;


    /**
     * Set the value of colorspace field in the QuantizeInfo structure.
     *
     * @param value new value of colorspace
     * @see ColorspaceType
     *
     * @throws MagickException on error
     */
    public native void setColorspace(int value)
	throws MagickException;


    /**
     * Return the value of color_space field in the QuantizInfo structure.
     *
     * @return current value of color_space field
     *
     * @throws MagickException on error
     */
    public native int getColorspace()
	throws MagickException;


    /**
     * Set the value of measure_error field in the QuantizeInfo structure.
     *
     * @param value new value of measure_error
     *
     * @throws MagickException on error
     */
    public native void setMeasureError(int value)
	throws MagickException;


    /**
     * Return the value of measure_error field in the QuantizInfo structure.
     *
     * @return current value of measure_error field
     *
     * @throws MagickException on error
     */
    public native int getMeasureError()
	throws MagickException;

}
