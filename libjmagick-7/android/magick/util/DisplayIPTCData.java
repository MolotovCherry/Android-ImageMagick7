package magick.util;

import java.io.UnsupportedEncodingException;

class DisplayIPTCData {
  public static final int TITLE_ID = 0x0205;
  public static final int KEYWORDS_ID = 0x0219;
  public static final int CREATOR_ID = 0x0250;
  public static final int CREATOR_JOB_TITLE_ID = 0x0255;
  public static final int HEADLINE_ID = 0x0269;
  public static final int DESCRIPTION_WRITE_ID = 0x027a;

  /**
   * Translates IPTC id to name.
   *
   * @param    id        IPTC id to translate
   *
   * @return    IPTC name associated with given id<br/>
   *            null if id unrecognized
   */

  public static String idToName( int id )
  {
    switch ( id )
    {
    case TITLE_ID:
        return "Title";

    case KEYWORDS_ID:
        return "Keywords";

    case CREATOR_ID:
        return "Creator";

    case CREATOR_JOB_TITLE_ID:
        return "Creator's Job Title";

    case HEADLINE_ID:
        return "Headline";

    case DESCRIPTION_WRITE_ID:
        return "Description Writer";

    default:
        return null;
    }
  }

  /**
   * Parses IPTC metadata.
   * I wrote a simple method to parse the data available from MagickImage.getIptcProfile()
   * @author Terence Bandoian
   * @param    data    IPTC metadata
   */
  public void parse( byte[] data )
  {
    int index;
    int length;
    int id;
    String name;
    String value;
    int valueLength;

    index = 0;
    length = data.length;

    while ( index < length )
    {
      if (( length - index >= 1 ) && ( data[ index ] == 0x1c ))
      {
          index++;
      }
      else
      {
          break;
      }

      if ( length - index >= 2 )
      {
          id = (int)data[ index++ ] * 256 + data[ index++ ];
      }
      else
      {
          break;
      }

      name = idToName( id );

      if ( length - index >= 2 )
      {
          valueLength = (int)data[ index++ ] * 256 + data[ index++ ];
      }
      else
      {
          break;
      }

      if ( length - index >= valueLength )
      {
        try
        {
            value = new String( data, index, valueLength, "UTF-8" );
        }
        catch ( UnsupportedEncodingException uee )
        {
            value = "Always supported.";
        }

        index += valueLength;
      }
      else
      {
          break;
      }
    }
  }
}
