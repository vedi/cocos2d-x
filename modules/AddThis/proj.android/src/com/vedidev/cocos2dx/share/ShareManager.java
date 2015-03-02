package com.vedidev.cocos2dx.share;

import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.Uri;
import android.os.Environment;
import android.util.Log;
import com.addthis.core.AddThis;
import com.addthis.core.Config;
import com.addthis.error.ATDatabaseException;
import com.addthis.error.ATSharerException;
import com.addthis.models.ATShareItem;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.*;
import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:44 PM
 */
public class ShareManager {

    private static final String ASSETS_PATH = "assets/";
    private static final String TAG = "ShareManager";

    private static WeakReference<Context> CONTEXT_WEAK_REFERENCE = new WeakReference<Context>(null);

    public static void init(JSONObject initParams) {
        try {
            JSONObject facebookObj = initParams.has("facebook") ? initParams.getJSONObject("facebook") : null;
            if (facebookObj != null) {
                if (facebookObj.has("appId")) {
                    Config.configObject().setShouldUseFacebookConnect(true);
                    Config.configObject().setFacebookAppId(facebookObj.getString("appId"));
                }
            }
            JSONObject addThisObj = initParams.has("addThis") ? initParams.getJSONObject("facebook") : null;
            if (addThisObj != null) {
                if (addThisObj.has("publisherId")) {
                    Config.configObject().setAddThisPubId(addThisObj.getString("publisherId"));
                }
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        }

    }

    public static void setContext(Context context) {
        CONTEXT_WEAK_REFERENCE = new WeakReference<Context>(context);
    }

    public static void shareText(String text, String serviceName) {
        if (serviceName != null) {
            try {
                AddThis.shareItem(getContext(), serviceName, "", "", text);
            } catch (ATDatabaseException e) {
                throw new IllegalArgumentException(e);
            } catch (ATSharerException e) {
                throw new IllegalArgumentException(e);
            }
        } else {
            AddThis.presentAddThisMenu(getContext(), "", text, (Bitmap) null);
        }

//        Intent intent = createIntent();
//
//        intent.setType("text/plain");
//        addText(text, intent);
//
//        startIntent(intent);
    }

    public static void shareUrl(String urlStr, String title, String serviceName) {
        if (serviceName != null) {
            try {
                AddThis.shareItem(getContext(), serviceName, urlStr, title, "");
            } catch (ATDatabaseException e) {
                throw new IllegalArgumentException(e);
            } catch (ATSharerException e) {
                throw new IllegalArgumentException(e);
            }
        } else {
            AddThis.presentAddThisMenu(getContext(), urlStr, title, "");
        }
//        Intent intent = createIntent();
//
//        intent.setType("text/url");
//
//        addTitle(title, intent);
//        addUrl(urlStr, intent);
//
//        startIntent(intent);
    }

    public static void shareImage(String imagePath, String title, String serviceName) {
        if (serviceName != null) {
            try {
                AddThis.shareItem(getContext(), serviceName, "", copyImage(imagePath), title, "");
            } catch (ATDatabaseException e) {
                throw new IllegalArgumentException(e);
            } catch (ATSharerException e) {
                throw new IllegalArgumentException(e);
            }
        } else {
            AddThis.presentAddThisMenu(getContext(), title, "", copyImage(imagePath));
        }
//
//        Intent intent = createIntent();
//
//        intent.setType("image/png");
//
//        addTitle(title, intent);
//        addImage(imagePath, intent);
//
//        startIntent(intent);
    }

    public static void share(String title, String text, String urlStr, String imagePath, String serviceName) {
        if (serviceName != null) {
            try {
                AddThis.shareItem(getContext(), serviceName, urlStr, copyImage(imagePath), title, text);
            } catch (ATDatabaseException e) {
                throw new IllegalArgumentException(e);
            } catch (ATSharerException e) {
                throw new IllegalArgumentException(e);
            }
        } else {
            AddThis.presentAddThisMenu(getContext(), urlStr, title, text, copyImage(imagePath));
        }

//        Intent intent = createIntent();
//
//        addTitle(title, intent);
//
//        if (imagePath != null) {
//            intent.setType("image/*");
//            addImage(imagePath, intent);
//            addUrl(urlStr, intent);
//            addText(text, intent);
//        } else if (urlStr != null) {
//            intent.setType("text/url");
//            addUrl(urlStr, intent);
//            addText(text, intent);
//        } else if (text != null) {
//            intent.setType("text/plain");
//            addText(text, intent);
//        } else {
//            throw new IllegalArgumentException(TAG + ":Cannot create sharing without any item defined");
//        }
//
//        startIntent(intent);
    }

    private static Context getContext() {
        Context context = CONTEXT_WEAK_REFERENCE.get();
        if (context != null) {
            return context;
        } else {
            throw new IllegalStateException();
        }
    }

    private static void startIntent(Intent sendIntent) {
        getContext().startActivity(Intent.createChooser(sendIntent, "Sharing"));
    }

    private static void addTitle(String title, Intent share) {
        share.putExtra(Intent.EXTRA_SUBJECT, title);
    }

    private static void addText(String text, Intent sendIntent) {
        sendIntent.putExtra(Intent.EXTRA_TEXT, text);
    }

    private static void addUrl(String urlStr, Intent intent) {
        addText(urlStr, intent);
    }

    private static void addImage(String imagePath, Intent intent) {
        try {
            String outFilePath = Environment.getExternalStorageDirectory().getAbsolutePath() +
                    "/" + Cocos2dxHelper.getCocos2dxPackageName() + "/";
            File outDir = new File(outFilePath);
            outDir.mkdirs();
            File outFile = new File(outDir, "tmp.jpg");
            FileOutputStream outFs = new FileOutputStream(outFile);

            InputStream in;
            if (imagePath.charAt(0) == '/') {
                // absolute path
                in = new FileInputStream(imagePath);
            } else {
                // remove prefix: "assets/"
                if (imagePath.startsWith(ASSETS_PATH)) {
                    imagePath = imagePath.substring(ASSETS_PATH.length());
                }
                AssetManager assetManager = getContext().getAssets();
                in = assetManager.open(imagePath);
            }

            copyFile(outFs, in);


            in.close();
            outFs.close();
            // Share
            intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(outFile));
        } catch (FileNotFoundException e) {
            throw new IllegalStateException(e);
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    private static Bitmap copyImage(String imagePath) {
        try {
//            String outFilePath = Environment.getExternalStorageDirectory().getAbsolutePath() +
//                    "/" + Cocos2dxHelper.getCocos2dxPackageName() + "/";
//            File outDir = new File(outFilePath);
//            outDir.mkdirs();
//            File outFile = new File(outDir, "tmp.jpg");
//            FileOutputStream outFs = new FileOutputStream(outFile);

            InputStream in;
            if (imagePath.charAt(0) == '/') {
                // absolute path
                in = new FileInputStream(imagePath);
            } else {
                // remove prefix: "assets/"
                if (imagePath.startsWith(ASSETS_PATH)) {
                    imagePath = imagePath.substring(ASSETS_PATH.length());
                }
                AssetManager assetManager = getContext().getAssets();
                in = assetManager.open(imagePath);
            }

            Bitmap originalBitmap = BitmapFactory.decodeStream(in);
//            copyFile(outFs, in);


            in.close();
//            outFs.close();

//            Log.d(TAG, "File name is " + outFile.getAbsolutePath());

//            Bitmap originalBitmap = BitmapFactory.decodeFile(outFile.getAbsolutePath());

//            // CREATE A MATRIX FOR THE MANIPULATION
//            Matrix matrix = new Matrix();
//            // RESIZE THE BIT MAP
//            matrix.postScale(0.1f, 0.1f);
//
            // "RECREATE" THE NEW BITMAP
            return Bitmap.createScaledBitmap(originalBitmap,
                    originalBitmap.getWidth() / 10, originalBitmap.getHeight() / 10, true);
        } catch (FileNotFoundException e) {
            throw new IllegalStateException(e);
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    private static void copyFile(FileOutputStream fOut, InputStream in) throws IOException {
        // Transfer bytes from in to out
        byte[] buf = new byte[1024];
        int len;
        while ((len = in.read(buf)) > 0) {
            fOut.write(buf, 0, len);
        }
    }

    private static Intent createIntent() {
        return new Intent(Intent.ACTION_SEND);
    }

}
