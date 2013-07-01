package com.vedidev.cocos2dx.nativeview;

import android.view.View;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:38 PM
 */
public interface NativeViewFactory {
    NativeViewProtocol createNativeView(Cocos2dxActivity activity, String viewKey, String viewData,
                                        float x, float y, float w, float h, Runnable onDismiss);
}
