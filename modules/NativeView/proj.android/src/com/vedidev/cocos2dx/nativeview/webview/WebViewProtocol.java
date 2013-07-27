package com.vedidev.cocos2dx.nativeview.webview;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.*;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import com.vedidev.cocos2dx.nativeview.NativeViewBridge;
import com.vedidev.cocos2dx.nativeview.NativeViewProtocol;
import com.vedidev.cocos2dx.nativeview.R;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.lang.ref.WeakReference;
import java.net.URLDecoder;

public class WebViewProtocol implements NativeViewProtocol {

    private static final String TAG = "WebViewProtocol";

    protected final WeakReference<Activity> activityRef;
    protected final WeakReference<Dialog> dialogRef;
    protected final WeakReference<WebView> webViewRef;

    public WebViewProtocol(final Cocos2dxActivity activity, final String viewKey, String viewData,
                           float x, float y, float w, float h, final Runnable onDismiss) {

        final Dialog dialog = new Dialog(activity, android.R.style.Theme_Translucent_NoTitleBar) {
            @Override
            public void onBackPressed() {
                activity.getGLSurfaceView().onKeyDown(KeyEvent.KEYCODE_BACK, null);
            }
        };

        dialog.setContentView(R.layout.web_view);
        dialog.setCancelable(false);


        Window window = dialog.getWindow();

        window.setFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL,
                WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL);
        window.addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        window.clearFlags(WindowManager.LayoutParams.FLAG_DIM_BEHIND);

        // setup positions
        WindowManager.LayoutParams params = window.getAttributes();
        params.gravity = Gravity.LEFT | Gravity.BOTTOM;
        params.width = (int) w;
        params.height = (int) h;

        // calculate status bar height
        DisplayMetrics metrics = new DisplayMetrics();
        activity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
        switch (metrics.densityDpi) {
            case DisplayMetrics.DENSITY_HIGH:
                params.height -= 48;
                break;
            case DisplayMetrics.DENSITY_MEDIUM:
                params.height -= 32;
                break;
            case DisplayMetrics.DENSITY_LOW:
            default:
                params.height -= 24;
        }

        params.x = (int) (x - params.width / 2);
        params.y = (int) (y - params.height / 2);

        window.setAttributes(params);

        WebView webView = (WebView) dialog.findViewById(R.id.webView);
//                    webView.getSettings().setLoadWithOverviewMode(true);
//                    webView.getSettings().setUseWideViewPort(true);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(android.webkit.WebView view, String url) {
                if (url.startsWith("js-call:")) {
                    final String urlComponents[] = url.split(":");
                    activity.runOnGLThread(new Runnable() {
                        @Override
                        public void run() {
                            try {
                                String normalizedData = URLDecoder.decode(urlComponents[1], "UTF-8");
                                Log.v("jsCallBack", "call from JS in Android:  " + normalizedData);
                                JSONObject jsonObject = new JSONObject(normalizedData);
                                NativeViewBridge.dispatchNDKCallback(viewKey, jsonObject);
                            } catch (JSONException e) {
                                throw new IllegalArgumentException(e);
                            } catch (UnsupportedEncodingException e) {
                                throw new IllegalArgumentException(e);
                            }
                        }
                    });
                } else {
                    // Load the page via the webview
                    view.loadUrl(url);
                }
                return true;
            }
        });
        webView.loadUrl(viewData);

        dialog.show();
        dialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
            @Override
            public void onDismiss(DialogInterface dialogInterface) {
                if (onDismiss != null) {
                    onDismiss.run();
                }
            }
        });

        this.activityRef = new WeakReference<Activity>(activity);
        this.dialogRef = new WeakReference<Dialog>(dialog);
        this.webViewRef = new WeakReference<WebView>(webView);
    }

    @Override
    public void sendMessageToView(String messageData) {
    }

    @Override
    public void close() {
        Dialog dialog = dialogRef.get();
        if (dialog != null) {
            dialog.dismiss();
        } else {
            Log.e(TAG, "Wrong reference");
        }
    }
}
