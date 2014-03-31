package com.vedidev.cocos2dx.infantium;

import com.easyndk.AndroidNDKHelper;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:40 PM
 */
public class InfantiumBridge {

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            String methodName = params.getString("method");
            if (methodName.equals("init")) {
                String apiUser = params.getString("apiUser");
                String apiKey = params.getString("apiKey");
                String contentAppUuid = params.getString("contentAppUuid");
                InfantiumManager.init(apiUser, apiKey, contentAppUuid);
            } else if (methodName.equals("createGameplay")) {
                String subContentUuid = params.getString("subContentUuid");
                InfantiumManager.createGameplay(subContentUuid);
            } else if (methodName.equals("startPlaying")) {
                InfantiumManager.startPlaying();
            } /*else if (methodName.equals("setSuccesses")) {
                int successes = params.getInt("successes");
                InfantiumManager.setSuccesses(successes);
            } else if (methodName.equals("setFailures")) {
                int failures = params.getInt("failures");
                InfantiumManager.setFailures(failures);
            }*/ else if (methodName.equals("sendGameRawData")) {
                InfantiumManager.sendGameRawData();
            } else if (methodName.equals("closeGameplay")) {
                InfantiumManager.closeGameplay();
            } else if (methodName.equals("setSubContentUUID")) {
                String subContentUuid = params.getString("subContentUuid");
                InfantiumManager.setSubContentUUID(subContentUuid);
            } else if (methodName.equals("returnToInfantiumApp")) {
                InfantiumManager.returnToInfantiumApp();
            } else if (methodName.equals("addElement")) {
                String ID = params.getString("ID");
                InfantiumManager.addElement(ID);
            } else if (methodName.equals("addPaintedElement")) {
                String ID = params.getString("ID");
                InfantiumManager.addPaintedElement(ID);
            } else if (methodName.equals("addPictureElement")) {
                String ID = params.getString("ID");
                InfantiumManager.addPictureElement(ID);
            } else if (methodName.equals("addShapeElement")) {
                String ID = params.getString("ID");
                InfantiumManager.addShapeElement(ID);
            } else if (methodName.equals("addNumberElement")) {
                String ID = params.getString("ID");
                Integer value = params.getInt("value");
                InfantiumManager.addNumberElement(ID, value);
            } else if (methodName.equals("addGoal")) {
                String ID = params.getString("ID");
                InfantiumManager.addGoal(ID);
            } else if (methodName.equals("addSelectionGoal")) {
                String ID = params.getString("ID");
                InfantiumManager.addSelectionGoal(ID);
            } else if (methodName.equals("addMatchingGoal")) {
                String ID = params.getString("ID");
                String matching_element = params.getString("matching_element");
                InfantiumManager.addMatchingGoal(ID, matching_element);
            } else if (methodName.equals("addTappingGoal")) {
                String ID = params.getString("ID");
                InfantiumManager.addTappingGoal(ID);
            } else if (methodName.equals("newBasicInteraction")) {
                String ID = params.getString("ID");
                String object_type = params.getString("object_type");
                String goal_type = params.getString("goal_type");
                InfantiumManager.newBasicInteraction(ID, object_type, goal_type);
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
