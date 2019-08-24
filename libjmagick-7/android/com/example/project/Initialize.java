package com.example.project;

import android.content.Context;
import android.system.ErrnoException;
import android.system.Os;

import java.io.File;

import magick.Magick;

class AppInitializer {
    static void initialize(Context context, String assetFolderName) {
        String magickConfigDir = context.getFilesDir().getAbsolutePath() + "/" + assetFolderName + "/";
        String magickCacheDir = context.getCacheDir().getPath();


        // copy over our ImageMagick-7 assets
       copyAsset(context, magickConfigDir, assetFolderName);

        // initialize Magick
        // ICU data dir is right beneath the same parent as the asset folder
        Magick.initialize(magickConfigDir, magickCacheDir, magickConfigDir);
    }

    static void copyAssets(Context context, String[] assetFolderNames) {
        AssetsHelper.checkExistsOrCopyFileOrDir(context, assetFolderNames);
    }

    static void copyAsset(Context context, String assetFolderName) {
        AssetsHelper.checkExistsOrCopyFileOrDir(context, assetFolderName);
    }

    static void setExecutableBit(String executableFilePath) {
        File execFile = new File(executableFilePath);
        execFile.setExecutable(true);
    }

    static void createSymbolicLink(String source, String link) throws ErrnoException {
        File linkFile = new File(link);
        if (linkFile.exists()) {
            linkFile.delete();
        }
        Os.symlink(source, link);
    }
}
