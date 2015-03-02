package com.vedidev.cocos2dx.flurry;

import android.content.Context;
import com.flurry.android.FlurryAgent;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * @author vedi
 *         date 6/2/13
 *         time 2:04 AM
 */
public class FlurryBridge {

    private static Context context;

    public static void setContext(Context context) {
        FlurryBridge.context = context;
    }

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("setUserId")) {
                String userId = params.getString("userId");
                FlurryAgent.setUserId(userId);
            }
            else if (methodName.equals("setAppVersion")) {
                String appVersion = params.getString("appVersion");
                FlurryAgent.setVersionName(appVersion);
            }
            else if (methodName.equals("init")) {
                String apiKey = params.getString("apiKey");
                FlurryAgent.onStartSession(context, apiKey);
                retParams.put("return", true);
            }
            else if (methodName.equals("logEvent")) {
                String eventId = params.getString("eventId");
                JSONObject paramMap = params.getJSONObject("paramMap");
                FlurryAgent.logEvent(eventId, convertToMap(paramMap));
            }
            else if (methodName.equals("logTimedEventBegin")) {
                String eventId = params.getString("eventId");
                JSONObject paramMap = params.getJSONObject("paramMap");
                FlurryAgent.logEvent(eventId, convertToMap(paramMap), true);
            }
            else if (methodName.equals("logTimedEventEnd")) {
                String eventId = params.getString("eventId");
                JSONObject paramMap = params.getJSONObject("paramMap");
                FlurryAgent.endTimedEvent(eventId, convertToMap(paramMap));
            }
            else {
                throw new UnsupportedOperationException();
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        }

        return retParams;
    }

    private static Map<String, String> convertToMap(JSONObject paramMap) throws JSONException {
        if (paramMap == null) {
            return null;
        }

        Map<String, String> mapResult = new HashMap<String, String>();

        Iterator<?> keys = paramMap.keys();

        while (keys.hasNext()) {
            String key = (String)keys.next();
            mapResult.put(key, paramMap.getString(key));
        }
        return mapResult;
    }
}
