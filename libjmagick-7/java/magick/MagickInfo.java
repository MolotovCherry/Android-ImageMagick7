package magick;

/**
 * Encapsulation of the MagickInfo structure.
 *
 * @author Susan Dorr
 */
public class MagickInfo extends Magick {

    // Internal handle. Used as pointer to MagickInfo
    // structure in memory. We use long (64-bits) for
    // portibility.
    private long magickInfoHandle = 0;

    /**
     * Constructor.
     *
     * @param name the name
     * @throws MagickException on error
     */
    public MagickInfo(String name)
	throws MagickException
    {
	init(name);
    }

    /**
     * Automated destructor.
     */

    public void finalize()
    {
	destroyMagickInfo(); 
    }

    /**
     * Initialise the MagickInfo structure.
     *
     * @param name the name
     * @throws MagickException on error
     */
    public native void init(String name)
	throws MagickException;

    /**
     * Deallocate the MagickInfo structure.
     */
    private native void destroyMagickInfo();


    /**
     * Return the description  attribute of the handle.
     *
     * @return the description
     * @throws MagickException on error
     */
    public native String getDescription()
	throws MagickException;
}
