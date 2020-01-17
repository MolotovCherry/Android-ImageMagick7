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

        /* CODE FOR SETTING UP BINARY USAGE
           Obviously you will need to check whether you already set this up or not
           You don't want to run this every time you start your app
           You can use Android SharedPrefs to keep track of it
            
            
            String[] files = {
                    "usr", "tmp"
            };

            // check for and copy over assets
            AppInitializer.copyAssets(this, files);

            // make sure executable bit is set
            String arch = Build.SUPPORTED_ABIS[0];
            String binDir = getFilesDir().getAbsolutePath() + "/usr/bin/" + arch + "/";
            String magickPath = binDir + "magick";

            AppInitializer.setExecutableBit(magickPath);


            // create magick symlinks. Used for different functions in magick
            // check imagemagick docs for more info
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
                
                }
            }
                
            // get some uri file stream from an intent, send it to AsyncTask for further processing
            Intent intent = getIntent();
            Uri uri = intent.getParcelableExtra("EXTRA_STREAM");
            INTENT_ACTION = intent.getAction();

            ProcessImageTask processTask = new ProcessImageTask(this);
            processTask.execute(uri);
            */
              
        // FOLLOWING CODE EXAMPLE BELOW IS FOR JMAGICK ONLY. IF YOU DON'T USE JMAGICK, 
        // USE THE BINARY CODE ABOVE ONLY
        // initialize app
        // I didn't make these an absolute path, but you NEED TO
        // getFilesDir().getAbsolutePath()
        AppInitializer.initialize("usr/ImageMagick-7", "tmp", "usr/icu");

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
        
    /// END JMAGICK SECTION
    }
    
    
    /* AsyncTask example code used for executing the binary
       If you don't run the binary on a separate thread, your UI will freeze
       Adapt it to your needs
    
        private static class ProcessImageTask extends AsyncTask<Uri, String, String> {
        final String TOAST_LONG  = "tl-";
        final String TOAST_SHORT = "ts-";
        final String ERROR       = "e-";
        final String INFO        = "i-";
        final String SUCCESS     = "s-";

        String INTENT_ACTION = null;
        String packageName = BuildConfig.APPLICATION_ID;

        private WeakReference<Context> mContext;
        private WeakReference<ShareActivity> mActivity;


        // only retain a weak reference to the activity
        ProcessImageTask(Context context) {
            mContext = new WeakReference<>(context);
            mActivity = new WeakReference<>((ShareActivity) context);
            ShareActivity aRef = mActivity.get();

            INTENT_ACTION = aRef.INTENT_ACTION;
        }

        protected String getFileName(Uri uri) {
            String result = null;
            Context ref = mContext.get();
            if (uri.getScheme().equals("content")) {
                Cursor cursor = ref.getContentResolver().query(uri, null, null, null, null);
                try {
                    if (cursor != null && cursor.moveToFirst()) {
                        result = cursor.getString(cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));
                    }
                } finally {
                    cursor.close();
                }
            }
            if (result == null) {
                result = uri.getPath();
                String sep = File.separator;
                int cut = result.lastIndexOf(sep);
                if (cut != -1) {
                    result = result.substring(cut + 1);
                }
            }

            // Remove the extension.
            int extensionIndex = result.lastIndexOf(".");
            if (extensionIndex != -1) {
                result = result.substring(0, extensionIndex);
            }

            return result;
        }


        @Override
        protected String doInBackground(Uri... uris) {
            Context ref = mContext.get();
            ShareActivity aRef = mActivity.get();

            Uri uri = uris[0];
            String filePath = uri.getPath();
            String fileName = getFileName(uri);
            String cacheDir = ref.getExternalCacheDir().getPath();
            String outputFile = cacheDir + "/" + fileName + ".gif";

            publishProgress("i-ts-Processing image");


            String arch = Build.SUPPORTED_ABIS[0];
            String usrDir = ref.getFilesDir().getPath() + "/usr";
            String tmpDir = ref.getFilesDir().getPath() + "/tmp";
            String binDir = usrDir + "/bin/" + arch;
            String libDir = usrDir + "/lib/" + arch;


            try {
                String cmd = null;

                if (INTENT_ACTION.equals(packageName + ".ACTION_SEND_WECHAT") ||
                        INTENT_ACTION.equals(packageName + ".ACTION_SEND_APP")) {

                    // magick configuration options
                    SharedPreferences options = aRef.retrieveExternalPreferences();
                    int border = options.getInt("border", aRef.BORDER);
                    int octagon = options.getInt("octagon", aRef.OCTAGON);
                    int fuzz = options.getInt("fuzz", aRef.FUZZ);
                    String blur = options.getString("blur", aRef.BLUR);

                    Map valuesMap = new HashMap<String, String>();
                    valuesMap.put("binDir", binDir);
                    valuesMap.put("filePath", filePath);
                    valuesMap.put("fuzz", Integer.toString(fuzz));
                    valuesMap.put("border", Integer.toString(border));
                    valuesMap.put("octagon", Integer.toString(octagon));
                    valuesMap.put("blur", blur);
                    valuesMap.put("outputFile", outputFile);

                    String origCmd = aRef.MAGICKCMD.replaceAll("\n", "");
                    String cmdO = options.getString("magickcmd", origCmd);
                    String cleanCmd = cmdO.replaceAll("\n", "");

                    StringSubstitutor sub = new StringSubstitutor(valuesMap);
                    cmd = sub.replace(cleanCmd);
                } else if (INTENT_ACTION.equals(packageName + ".ACTION_SEND_WECHAT_NO_MAGICK") ||
                        INTENT_ACTION.equals(packageName + ".ACTION_SEND_APP_NO_MAGICK")) {

                    SharedPreferences options = aRef.retrieveExternalPreferences();
                    Map valuesMap = new HashMap<String, String>();
                    valuesMap.put("binDir", binDir);
                    valuesMap.put("filePath", filePath);
                    valuesMap.put("outputFile", outputFile);

                    String origCmd = aRef.CONVERTCMD;
                    String cmdO = options.getString("convertcmd", origCmd);
                    StringSubstitutor sub = new StringSubstitutor(valuesMap);

                    // simple conversion to gif
                    cmd = sub.replace(cmdO);
                }

                ArrayList<String> env = new ArrayList<>();
                env.add("TMPDIR=" + tmpDir);
                env.add("MAGICK_HOME=" + usrDir);
                env.add("ICU_DATA_DIR_PREFIX=" + usrDir);
                env.add("LD_LIBRARY_PATH=" + ref.getApplicationInfo().nativeLibraryDir);
                for (Map.Entry<String, String> entry : System.getenv().entrySet()) {
                    env.add(entry.getKey() + "=" + entry.getValue());
                }

                String[] ENV = env.toArray(new String[0]);

                Process proc = Runtime.getRuntime().exec(cmd, ENV);

                int exitcode = proc.waitFor();
                if (exitcode != 0) {
                    String enc = "UTF-8";
                    String output = IOUtils.toString(proc.getInputStream(), enc);
                    String erroutput = IOUtils.toString(proc.getErrorStream(), enc);

                    String msg = "e-tl-Exit-code: " + exitcode + "\n\n" +
                            "Stdout: " + output + "\n\n" +
                            "Stderr: " + erroutput;
                    publishProgress(msg);
                    return null;
                }


                if (BuildConfig.DEBUG) {
                    String enc = "UTF-8";
                    String output = IOUtils.toString(proc.getInputStream(), enc);
                    String erroutput = IOUtils.toString(proc.getErrorStream(), enc);

                    Log.d("TAG", "Stdout: " + output);
                    Log.d("TAG", "Stderr: " + erroutput);
                    Log.d("TAG", "errcode: " + exitcode);
                }

                publishProgress("s-ts-Finished processing");
                return outputFile;
            } catch (IOException e) {
                Log.d("TAG", e.toString());
                publishProgress("e-tl-Failed to process image");
                return null;
            } catch (InterruptedException e) {
                Log.d("TAG", e.toString());
                publishProgress("e-tl-Processing interrupted");
                return null;
            }
        }

        @Override
        protected void onProgressUpdate(String... strings) {
            Context con = mContext.get();
            String fullMsg = strings[0];
            CharSequence msg = fullMsg.substring(5);

            String TYPE = fullMsg.substring(0, 2);
            String toastLength = fullMsg.substring(2, 5);
            int TOAST_LENGTH = Toast.LENGTH_SHORT;

            switch (toastLength) {
                case TOAST_SHORT:
                    TOAST_LENGTH = Toast.LENGTH_SHORT;
                    break;
                case TOAST_LONG:
                    TOAST_LENGTH = Toast.LENGTH_LONG;
                    break;
            }

            switch (TYPE) {
                case ERROR:
                    Toasty.error(con, msg, TOAST_LENGTH).show();
                    break;
                case INFO:
                    Toasty.info(con, msg, TOAST_LENGTH).show();
                    break;
                case SUCCESS:
                    Toasty.success(con, msg, TOAST_LENGTH).show();
                    break;
            }
        }

        @Override
        protected void onPostExecute(String path) {
            if (path != null) {
                Context con = mContext.get();
                File file = new File(path);

                Uri uri = FileProvider.getUriForFile(con,
                        BuildConfig.APPLICATION_ID + ".provider", file);

                if (INTENT_ACTION.equals(packageName + ".ACTION_SEND_WECHAT") ||
                    INTENT_ACTION.equals(packageName + ".ACTION_SEND_WECHAT_NO_MAGICK")) {

                    Intent shareIntent = new Intent();
                    shareIntent.setAction(Intent.ACTION_SEND);
                    shareIntent.putExtra(Intent.EXTRA_STREAM, uri);
                    shareIntent.setType("image/gif");
                    shareIntent.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION | Intent.FLAG_ACTIVITY_CLEAR_TASK);

                    shareIntent.setClassName("com.tencent.mm",
                            "com.tencent.mm.ui.tools.ShareImgUI");

                    con.startActivity(shareIntent);

                } else if (INTENT_ACTION.equals(packageName + ".ACTION_SEND_APP") ||
                           INTENT_ACTION.equals(packageName + ".ACTION_SEND_APP_NO_MAGICK")) {

                    Intent shareIntent = new Intent();
                    shareIntent.setAction(Intent.ACTION_SEND);
                    shareIntent.putExtra(Intent.EXTRA_STREAM, uri);
                    shareIntent.setType("image/gif");
                    shareIntent.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION | Intent.FLAG_ACTIVITY_CLEAR_TASK);

                    con.startActivity(Intent.createChooser(shareIntent, con.getResources().getText(R.string.share_image)));
                }
            }
        }
    
    */
}
