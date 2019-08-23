package magick;

import fakeawt.Point;

/**
 * Encapsulation of the TypeMetric structure.
 * MagickCore/draw.h
 */
public class TypeMetric extends Magick {

	public Point pixels_per_em;

	public double
	    ascent,
	    descent,
	    width,
	    height,
	    max_advance,
	    underline_position,
	    underline_thickness;

	public SegmentInfo
	    bounds;

	public Point
		origin;
	
	public TypeMetric(double pixels_per_emX, double pixels_per_emY,
		
		double ascent, double descent,
		double width, double height, double max_advance,
		double underline_position, double underline_thickness, 
		double boundsX1, double boundsY1, double boundsX2, double boundsY2,
		
		double originX, double originY)
	{	
		this.pixels_per_em = new Point((int)pixels_per_emX,(int)pixels_per_emY);
		this.ascent=ascent;	this.descent=descent;
		this.width=width; this.height=height; this.max_advance=max_advance;
		this.underline_position=underline_position; this.underline_thickness=underline_thickness;
		this.bounds=new SegmentInfo(boundsX1,boundsY1,boundsX2,boundsY2);
		this.origin=new Point((int)originX,(int)originY); 
	}
	
	public TypeMetric() {
	}
	
	public String toString() {
		SegmentInfo segmentInfo=this.bounds;
		return "typeMetrics: pixels_per_em .x="+this.pixels_per_em.x+" .y="+this.pixels_per_em.x+
			" ascent="+this.ascent+" descent="+this.descent+" "+
			" width="+this.width+" height="+this.height+" max_advance="+this.max_advance+
			" underline_position="+this.underline_position+" underline_thickness="+this.underline_thickness+
			" bounds x1="+segmentInfo.x1+" y1="+segmentInfo.y1+" x2="+segmentInfo.x2+" y2="+segmentInfo.y2+
			" origin .x="+this.origin.x+" .y="+this.origin.y;

	}
}
