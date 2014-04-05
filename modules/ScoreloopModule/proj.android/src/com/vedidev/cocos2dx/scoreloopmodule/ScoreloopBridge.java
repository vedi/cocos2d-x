package com.vedidev.cocos2dx.scoreloopmodule;


import com.easyndk.AndroidNDKHelper;
import org.json.JSONException;
import org.json.JSONObject;

public class ScoreloopBridge {

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("submitScore")) {
                Double scoreResult = params.getDouble("scoreResult");
                ScoreloopManager.submitScore(scoreResult);
            } else if (methodName.equals("showLeaderboard")) {
                ScoreloopManager.showLeaderboard();
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
