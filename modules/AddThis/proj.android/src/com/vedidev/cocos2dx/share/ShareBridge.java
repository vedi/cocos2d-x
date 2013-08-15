package com.vedidev.cocos2dx.share;

import com.easyndk.AndroidNDKHelper;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:40 PM
 */
public class ShareBridge {

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("init")) {
                JSONObject initParams = params.getJSONObject("initParams");
                ShareManager.init(initParams);
            } else if (methodName.equals("setFacebookKeys")) {
                String key = params.getString("key");
                String secret = params.getString("secret");
                // TODO: Implement
            } else if (methodName.equals("shareText")) {
                String text = params.getString("text");
                String serviceName = params.getString("serviceName");
                ShareManager.shareText(text, serviceName);
            } else if (methodName.equals("shareUrl")) {
                String urlStr = params.getString("urlStr");
                String title = params.getString("title");
                String serviceName = params.getString("serviceName");
                ShareManager.shareUrl(urlStr, title, serviceName);
            } else if (methodName.equals("shareImage")) {
                String imagePath = params.getString("imagePath");
                String title = params.getString("title");
                String serviceName = params.getString("serviceName");
                ShareManager.shareImage(imagePath, title, serviceName);
            } else if (methodName.equals("share")) {
                String text = params.has("text") ? params.getString("text") : null;
                String urlStr = params.has("urlStr") ? params.getString("urlStr") : null;
                String imagePath = params.has("imagePath") ? params.getString("imagePath") : null;
                String title = params.has("title") ? params.getString("title") : null;
                String serviceName = params.getString("serviceName");
                ShareManager.share(title, text, urlStr, imagePath, serviceName);
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
