package com.example.project;


import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.util.Log;
import android.view.Display;
import android.widget.Toast;

import java.nio.channels.Channel;

import fakeawt.*;
import magick.*;


import es.dmoral.toasty.Toasty;


public class MainActivity extends AppCompatActivity {
    final public static String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

         String[] files = {
                    "usr", "tmp"
            };

            // check for and copy assets
            AppInitializer.copyAssets(this, files);

            // make sure executable bit is set
            String arch = Build.SUPPORTED_ABIS[0];
            String binDir = getFilesDir().getAbsolutePath() + "/usr/bin/" + arch + "/";
            String magickPath = binDir + "magick";

            AppInitializer.setExecutableBit(magickPath);

            /* For using the binary:::
            
            String[] symlinks = {
                "animate", "compare", "composite",
                "conjure", "convert", "display",
                "identify", "import", "magick-script",
                "mogrify", "montage", "stream"
            };

            try {
                for (String symlink : symlinks) {
                    AppInitializer.createSymbolicLink(magickPath, binDir + symlink);
                }
            } catch (ErrnoException e) {
                CharSequence msg = "Failed to create symlinks";
                Toasty.error(this, msg, Toast.LENGTH_LONG).show();

                // cleanup
                try {
                    for (String file : files) {
                        File f = new File(getFilesDir().getAbsolutePath() + "/" + file);
                        if (f.isDirectory()) {
                            FileUtils.deleteDirectory(f);
                        } else {
                            f.delete();
                        }
                    }
                } catch (IOException a) {
                    CharSequence msgs = "Failed to delete a file or folder on reset";
                    Toasty.error(this, msgs, Toast.LENGTH_LONG).show();
                }*/
                
        // initialize app
        // I didn't make these an absolute path, but you NEED TO
        // getFilesDir().getAbsolutePath()
        AppInitializer.initialize(this, "usr/ImageMagick-7", "usr/icu");

        int border = 15;
        int kernelArgs = 4;
        double fuzz = 0.03; // 3%
        String blur = "2x20";

        try {
            /*
             1st section of commands:
             \( $f +repage -bordercolor white -border 1x1 \
             -fuzz $fuzz% -fill transparent -floodfill +0+0 white -shave 1x1 \
             -bordercolor transparent -border ${border}x${border} \) \
            */

            //
            // $f +repage -bordercolor white -border 1x1
            //
            // $f
            ImageInfo info = new ImageInfo("/some/path/file.png");
            MagickImage image = new MagickImage(info);
            // +repage
            image.resetImagePage("0x0+0+0");
            // -bordercolor white
            image.setBorderColor(PixelPacket.getColor("white"));
            // -border 1x1
            MagickImage borderImg = image.borderImage(new Rectangle(1, 1));


            //
            // -fuzz $fuzz% -fill transparent -floodfill +0+0 white -shave 1x1 \
            //
            // -fuzz $fuzz%
            borderImg.setColorFuzz(fuzz);
            // -fill transparent
            DrawInfo fill = new DrawInfo(new ImageInfo());
            fill.setFill(PixelPacket.getColor("transparent"));
            // -floodfill +0+0 white
            borderImg.colorFloodfillImage(fill, PixelPacket.getColor("white"), 0, 0, PaintMethod.FloodfillMethod);
            // -shave 1x1
            // shave method is missing .. need alternate implementation
            // basically, I'll just do a crop for the original image dimensions (thereby undoing the border addition)
            int origWidth = (int) image.getDimension().getWidth();
            int origHeight = (int) image.getDimension().getHeight();
            MagickImage shave = borderImg.cropImage(new Rectangle(origWidth, origHeight));

            //
            // -bordercolor transparent -border ${border}x${border}
            //
            // -bordercolor transparent
            shave.setBorderColor(PixelPacket.getColor("transparent"));
            // -border ${border}x${border}
            MagickImage borderImgBig = shave.borderImage(new Rectangle(border, border));


            /*
             Second section
             \( -clone 0 -fill white -colorize 100% \) \
            */
            MagickImage colorizeImg = borderImgBig.cloneImage(0, 0, true);
            // -fill white -colorize 100%
            //MagickImage img = shave.colorizeImage("100", PixelPacket.getColor("white"));
            //img.setFileName("/some/path/file.png");
            //img.writeImage(new ImageInfo());



            /*
             Third section
             \( -clone 0 -alpha extract -write mpr:alpha -morphology edgeout octagon:$octagon -write mpr:edge \
                mpr:alpha -fill transparent -floodfill +0+0 black \
                -compose over -composite \
                -fill white -floodfill +0+0 transparent -alpha off -negate \
                -fill transparent -floodfill +0+0 black -write mpr:chunk \
                mpr:edge -compose dst_over -composite \) \
            */
            MagickImage alpha = borderImgBig.cloneImage(0, 0, true);
            shave.setImageAlphaChannel(AlphaChannelOption.OffAlphaChannel);
            shave.setImageAlphaChannel(AlphaChannelOption.ExtractAlphaChannel);

            shave.setFileName("/some/path/file.png"); //give new location
            shave.writeImage(new ImageInfo());

            borderImgBig.setFileName("/some/path/file.png"); //give new location
            borderImgBig.writeImage(new ImageInfo());
            MagickImage morph = shave.morphologyImage(
                    MorphologyMethod.EdgeOutMorphology,
                    KernelType.OctagonKernel, kernelArgs
            );
            morph.setFileName("/some/path/file.png"); //give new location
            morph.writeImage(new ImageInfo());

            //borderImgBig.setFileName("/some/path/file.png"); //give new location
            //borderImgBig.writeImage(info);
           // morph.setFileName("/some/path/file.png"); //give new location
            //morph.writeImage(info);

            CharSequence error = "Image conversion success";
            int duration = Toast.LENGTH_LONG;
            Toasty.success(this, error, duration, true).show();


        } catch (magick.MagickException name) {
            CharSequence error = "Image processing failed";
            int duration = Toast.LENGTH_LONG;


            Toasty.error(this, error, duration, true).show();
            Log.e(TAG, "exception", name);
        }

        Log.v("onCreate","message success");
    }
}
