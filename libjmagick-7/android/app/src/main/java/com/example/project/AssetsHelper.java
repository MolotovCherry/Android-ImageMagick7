package com.example.project;


import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

import org.apache.commons.io.IOUtils;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

class AssetsHelper {
    static final private String TAG = "AssetsHelper";

    static void checkExistsOrCopyFileOrDir(Context context, String[] assetsToCopy) {
        // copy multiple assets
        for (String asset : assetsToCopy) {
            checkExistsOrCopyFileOrDir(context, asset);
        }
    }

    // check if pathToCheck exists (file or folder), if not, copy over the path in assetToCopy
    static void checkExistsOrCopyFileOrDir(Context context, String assetToCopy) {
        String assetDir = context.getFilesDir().getAbsolutePath() + "/";
        File path = new File(assetDir + assetToCopy);

        if (path.exists() && (path.isDirectory() || path.isFile())) {
            Log.d(TAG, "asset exists in destination, ignoring..: " + assetDir);
            return;
        }

        Log.d(TAG, "copying over asset: " + assetToCopy);
        // path doesn't exist, copy the asset over
        copyFileOrDir(context, assetToCopy);
    }

    static private void copyFileOrDir(Context context, String path) {
        AssetManager assetManager = context.getAssets();
        String[] assets;
        try {
            assets = assetManager.list(path);

            if (assets.length == 0) {
                copyFile(context, path);
            } else {
                String fullPath = context.getFilesDir().getAbsolutePath() + "/" + path;
                File dir = new File(fullPath);
                if (!dir.exists()) {
                    dir.mkdir();
                }
                for (int i = 0; i < assets.length; ++i) {
                    copyFileOrDir(context,path + "/" + assets[i]);
                }
            }
        } catch (IOException ex) {
            Log.e(TAG, "I/O Exception", ex);
        }
    }

    static private void copyFile(Context context, String filename) {
        AssetManager assetManager = context.getAssets();

        InputStream in;
        OutputStream out;
        try {
            in = assetManager.open(filename);
            String newFileName = context.getFilesDir().getAbsolutePath() + "/" + filename;
            out = new FileOutputStream(newFileName);

            IOUtils.copy(in, out);

            in.close();
            out.flush();
            out.close();
        } catch (Exception e) {
            Log.e(TAG, "Exception", e);
        }
    }
}
