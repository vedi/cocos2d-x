package com.vedidev.cocos2dx.nativeview;

import android.app.Dialog;
import android.util.Log;
import android.view.View;
import com.vedidev.cocos2dx.nativeview.webview.WebViewFactory;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.Map;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:44 PM
 */
public class NativeViewManager {

    public static final String WEB_VIEW_KEY = "WEB_VIEW_KEY";

    private static final String TAG = "NativeViewManager";


    private static Map<String, NativeViewFactory> nativeViewFactoryMap = new HashMap<String, NativeViewFactory>();

    private static WeakReference<Cocos2dxActivity> activityRef = new WeakReference<Cocos2dxActivity>(null);
    private static Map<String, WeakReference<NativeViewProtocol>> nativeViews =
            new HashMap<String, WeakReference<NativeViewProtocol>>();

    public static void init() {
    }

    public static void addFactory(String viewKey, NativeViewFactory nativeViewFactory) {
        nativeViewFactoryMap.put(viewKey, nativeViewFactory);
    }

    public static void setCocos2dxActivity(Cocos2dxActivity activity) {
        activityRef = new WeakReference<Cocos2dxActivity>(activity);
    }

    public static void createAndShowNative(final String viewKey, final String viewData,
                                           final float x, final float y, final float w, final float h) {
        final Cocos2dxActivity activity = activityRef.get();
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {

                NativeViewFactory nativeViewFactory = nativeViewFactoryMap.get(viewKey);

                if (nativeViewFactory != null) {
                    NativeViewProtocol nativeViewProtocol = nativeViewFactory.createNativeView(activity,
                            viewKey, viewData, x, y, w, h,

                            new Runnable() {
                                @Override
                                public void run() {
                                    nativeViews.remove(viewKey);
                                }
                            });
                    nativeViews.put(viewKey, new WeakReference<NativeViewProtocol>(nativeViewProtocol));
                } else {
                    Log.e(TAG, String.format("Cannot find factory for key: %s", viewKey));
                }
            }
        });
    }

    public static void nativeSendMessage(String viewKey, String messageData) {
        WeakReference<NativeViewProtocol> viewRef = nativeViews.get(viewKey);

        if (viewRef == null) {
            Log.e(TAG, String.format("There is no view with key: %s", viewKey));
            return;
        }

        NativeViewProtocol nativeViewProtocol = viewRef.get();
        if (nativeViewProtocol == null) {
            Log.e(TAG, String.format("Wrong reference for view with key: %s", viewKey));
            return;
        }

        nativeViewProtocol.sendMessageToView(messageData);
    }

    public static void closeNative(String viewKey) {
        WeakReference<NativeViewProtocol> viewRef = nativeViews.get(viewKey);

        if (viewRef == null) {
            Log.e(TAG, String.format("There is no view with key: %s", viewKey));
            return;
        }

        NativeViewProtocol nativeViewProtocol = viewRef.get();
        if (nativeViewProtocol == null) {
            Log.e(TAG, String.format("Wrong reference for view with key: %s", viewKey));
            return;
        }

        nativeViewProtocol.close();
    }

}
