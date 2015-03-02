package com.vedidev.parse_cocos2dx;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.util.Log;

import com.parse.Parse;
import com.parse.ParseInstallation;
import com.parse.ParseObject;
import com.parse.PushService;

public class ParseBridge
{
	private static Activity activity;

    public static void setActivity(Activity activity) {
    	ParseBridge.activity = activity;
    }
    
    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("setKeys")) {
                String applicationID = params.getString("applicationID");
                String clientKey = params.getString("clientKey");
                Parse.initialize(activity.getBaseContext(), applicationID, clientKey);
            }
            else if (methodName.equals("initParsePush")) {
                boolean notificationsOn = params.getBoolean("notificationsOn");
                PushService.setDefaultPushCallback(activity.getBaseContext(), notificationsOn ? activity.getClass() : null);
                ParseInstallation.getCurrentInstallation().saveInBackground();
            }
            else if (methodName.equals("sendParseObject")) {
            	String objectName = params.getString("objectName");
            	ParseObject testObject = new ParseObject(objectName);
            	testObject.saveInBackground();
            }
            else {
                throw new UnsupportedOperationException();
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        }

        return retParams;
    }
    
    public static void dispatchNDKCallback(JSONObject params) {
        Log.v("Parse Android", "dispatchNDKCallback: Illegal state: unexpected callback call");
    }
}
