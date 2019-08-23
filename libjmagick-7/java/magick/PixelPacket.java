package magick;



public class PixelPacket extends Magick {

    private int red, green, blue, opacity;

    /**
     * Constructor
     *
     * @param red the red channel value
     * @param green the green channel value
     * @param blue the blue channel value
     * @param opacity the opacity/alpha channel value
     */
    public PixelPacket(int red, int green, int blue, int opacity)
    {
	this.red = red;
	this.green = green;
	this.blue = blue;
	this.opacity = opacity;
    }

    /**
     * Set the red channel value.
     *
     * @param red the new red channel value
     */
    public void setRed(int red)
    {
	this.red = red;
    }

    /**
     * Set the green channel value.
     *
     * @param green the new green channel value
     */
    public void setGreen(int green)
    {
	this.green = green;
    }

    /**
     * Set the blue channel value.
     *
     * @param blue the new blue channel value
     */
    public void setBlue(int blue)
    {
	this.blue = blue;
    }

    /**
     * Set the opacity/alpha channel value.
     *
     * @param opacity the new opacity/alpha channel value
     */
    public void setOpacity(int opacity)
    {
	this.opacity = opacity;
    }

    /**
     * Get the red channel value.
     *
     * @return the red channel value
     */
    public int getRed()
    {
	return red;
    }

    /**
     * Get the green channel value.
     *
     * @return the green channel value
     */
    public int getGreen()
    {
	return green;
    }

    /**
     * Get the blue channel value.
     *
     * @return the blue channel value
     */
    public int getBlue()
    {
	return blue;
    }

    /**
     * Get the opacity/alpha channel value.
     *
     * @return the opacity/alpha channel value
     */
    public int getOpacity()
    {
	return opacity;
    }

    /**
     * looks up a RGB values for a color given in the target string.
     *
     * @param target Specifies the color to lookup in the X color database
     * @return a PixelPacket that represents the target
     * @throws MagickException on error
     */
    public static native PixelPacket queryColorDatabase(String target)
	throws MagickException;
    

    /**
     * Converts a web (i.e. css-compliant) color string to a pixel packet.
     *
     * @param target Specifies the color string to convert
     * @return a PixelPacket that represents the target
     * @throws MagickException on error
     */
    public static native PixelPacket getColor(String target)
	throws MagickException;

    /**
     * Display the object as a String
     */
    @Override
    public String toString() {
        return "PixelPacket("+getRed()+","+getGreen()+","+getBlue()+","+getOpacity()+")";
    }
}
