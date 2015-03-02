package com.vedidev.cocos2dx.nativeview.webview;

import android.app.Dialog;
import android.content.DialogInterface;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.*;
import android.webkit.*;
import android.webkit.WebView;
import com.vedidev.cocos2dx.nativeview.NativeViewBridge;
import com.vedidev.cocos2dx.nativeview.NativeViewFactory;
import com.vedidev.cocos2dx.nativeview.NativeViewProtocol;
import com.vedidev.cocos2dx.nativeview.R;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;

/**
 * @author vedi
 *         date 7/2/13
 *         time 12:37 AM
 */
public class WebViewFactory implements NativeViewFactory {
    @Override
    public NativeViewProtocol createNativeView(final Cocos2dxActivity activity, final String viewKey, String viewData,
                                 float x, float y, float w, float h, final Runnable onDismiss) {

        return new WebViewProtocol(activity, viewKey, viewData, x, y, w, h, onDismiss);
    }
}
