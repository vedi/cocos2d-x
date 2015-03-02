package com.vedidev.cocos2dx.hasApp;

import com.easyndk.AndroidNDKHelper;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:40 PM
 */
public class HasAppBridge {

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("init")) {
                HasAppManager.init();
            } else if (methodName.equals("hasApp")) {
                String appId = params.getString("appId");
                HasAppManager.hasApp(appId);
            } else if (methodName.equals("openApp")) {
                String appId = params.getString("appId");
                HasAppManager.openApp(appId);
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
