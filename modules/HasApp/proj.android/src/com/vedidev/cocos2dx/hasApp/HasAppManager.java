package com.vedidev.cocos2dx.hasApp;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.util.Log;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:44 PM
 */
public class HasAppManager {

    private static final String TAG = "HasAppManager";

    private static WeakReference<Context> CONTEXT_WEAK_REFERENCE = new WeakReference<Context>(null);

    public static void init() {

    }

    public static void setContext(Context context) {
        CONTEXT_WEAK_REFERENCE = new WeakReference<Context>(context);
    }

    public static void hasApp(String appId) {
        Context context = CONTEXT_WEAK_REFERENCE.get();
        if (context == null) {
            throw new IllegalStateException("context == null");
        }
        PackageManager pm = context.getPackageManager();
        JSONObject resultParams = new JSONObject();
        try {
            resultParams.put("method", "hasApp");
            resultParams.put("appId", appId);
            try {
                pm.getPackageInfo(appId, PackageManager.GET_META_DATA);
                resultParams.put("result", true);
            } catch (PackageManager.NameNotFoundException e) {
                resultParams.put("result", false);
            }
        } catch (JSONException e) {
            Log.w(TAG, "JSONException", e);
            try {
                resultParams.put("error", e.getLocalizedMessage());
            } catch (JSONException e1) {
                Log.e(TAG, "JSONException", e1);
            }
        }
        HasAppBridge.dispatchNDKCallback("HasApp_callback", resultParams);
    }

    public static void openApp(String appId) {
        Context context = CONTEXT_WEAK_REFERENCE.get();
        if (context == null) {
            throw new IllegalStateException("context == null");
        }
        PackageManager pm = context.getPackageManager();
        JSONObject resultParams = new JSONObject();
        try {
            try {
                Intent intent = pm.getLaunchIntentForPackage(appId);
                if (intent == null) {
                    throw new IllegalArgumentException("Cannot get launcher for app: " + appId);
                }
                intent.addCategory(Intent.CATEGORY_LAUNCHER);
                context.startActivity(intent);
            } catch (Exception e) {
                resultParams.put("method", "openApp");
                resultParams.put("error", e.getLocalizedMessage());
            }
        } catch (JSONException e) {
            Log.w(TAG, "JSONException", e);
            try {
                resultParams.put("error", e.getLocalizedMessage());
            } catch (JSONException e1) {
                Log.e(TAG, "JSONException", e1);
            }
        }
        if (resultParams.has("error")) {
            HasAppBridge.dispatchNDKCallback("HasApp_callback", resultParams);
        }
    }
}
