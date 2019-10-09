package com.example.project;

import android.content.Context;
import android.util.Log;

import java.io.File;

import magick.Magick;


public class AndroidMagick 
{
	private static final String LOGTAG = "AndroidMagick.java";


	public static void setCacheDir(Context context)
	{
		int k;
		File dir, maxDir = null;
		long space, maxSpace = -1;
		String path;
		
		Log.d(LOGTAG, "setCacheDir()");

		File[] dirs = context.getExternalCacheDirs();
		
		for(k = 0; k < dirs.length; ++k){
			dir = dirs[k];
			space = dir.getFreeSpace();
			
			// testing:
			path = dir.getAbsolutePath();
			if(path != null)
				Log.d(LOGTAG, "- #" + k + " cache path: " + path);
			else
				Log.d(LOGTAG, "- cache path null");
			//
			
			if(space > maxSpace){
				maxSpace = space;
				maxDir = dir;
			}
		}
		
		if(maxDir != null){
			path = maxDir.getAbsolutePath();
			if(path != null){
				Log.d(LOGTAG, "- best cache path: " + path);
		    	Magick.setCacheDir(path);
			}
			else
				Log.d(LOGTAG, "- best cache path null");
		}
		else
			Log.d(LOGTAG, "- best cache dir null");
	}
}
