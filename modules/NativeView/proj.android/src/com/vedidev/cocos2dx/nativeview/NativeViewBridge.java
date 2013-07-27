package com.vedidev.cocos2dx.nativeview;

import com.easyndk.AndroidNDKHelper;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:40 PM
 */
public class NativeViewBridge {

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("init")) {
                NativeViewManager.init();
            } else if (methodName.equals("createAndShowNative")) {
                String viewKey = params.getString("viewKey");
                String viewData = params.getString("viewData");
                float x = (float) params.getDouble("x");
                float y = (float) params.getDouble("y");
                float w = (float) params.getDouble("w");
                float h = (float) params.getDouble("h");
                NativeViewManager.createAndShowNative(viewKey, viewData, x, y, w, h);
            } else if (methodName.equals("sendMessage")) {
                String viewKey = params.getString("viewKey");
                String messageData = params.getString("messageData");
                NativeViewManager.nativeSendMessage(viewKey, messageData);
            } else if (methodName.equals("closeNative")) {
                String viewKey = params.getString("viewKey");
                NativeViewManager.closeNative(viewKey);
            } else {
                throw new UnsupportedOperationException();
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        }

        return retParams;
    }

    public static void dispatchNDKCallback(String key, JSONObject parameters) {
        AndroidNDKHelper.sendMessageWithParameters(key, parameters);
    }
}
