package com.vedidev.cocos2dx.infantium;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.sax.Element;
import android.util.Log;
import android.view.Display;
//import com.infantium.android.sdk.Infantium_SDK;
import com.infantium.android.sdk.InfantiumSDK;
import com.infantium.android.sdk.elements.*;
import com.infantium.android.sdk.goals.*;

import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;
import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * @author vedi
 *         date 7/1/13
 *         time 11:44 PM
 */
public class InfantiumManager {

    private static final String TAG = "Infantium";

    private static WeakReference<Activity> ACTIVITY_WEAK_REFERENCE = new WeakReference<Activity>(null);
    private static InfantiumSDK infantium = null;
    private static InfantiumHandler infantiumHandler;

    public static void initModule(Activity activity) {
        ACTIVITY_WEAK_REFERENCE = new WeakReference<Activity>(activity);
        //infantium = Infantium_SDK.getInfantium_SDK(activity.getBaseContext());
        infantium = InfantiumSDK.getInfantiumSDK(activity.getBaseContext());
        infantiumHandler = new InfantiumHandler();
    }

    public static void init(String apiUser, String apiKey, String contentAppUuid) {
        Activity activity = ACTIVITY_WEAK_REFERENCE.get();
        if (activity == null) {
            throw new IllegalStateException("Module Infantium is not initialized");
        }
        //  infantium
        Display display = activity.getWindowManager().getDefaultDisplay();

        int width = display.getWidth();
        int height = display.getHeight();

        infantium.setDeveloperCredentials(apiUser, apiKey);
        infantium.setDeviceInfo(width, height);
        infantium.setDeveloperHandler(infantiumHandler);
        infantium.setContentAppUUID(contentAppUuid);
        infantium.getPlayerUUIDFromApp();
    }

    public static void createGameplay(String subContentUuid) {
        if (infantiumHandler.isReady()) {
            infantium.createGameplay(subContentUuid);
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }

    public static void startPlaying() {
        if (infantiumHandler.isReady()) {
            infantium.startPlaying();
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }
/*
    public static void setSuccesses(int successes) {
        if (infantiumHandler.isReady()) {
            infantium.setSuccesses(successes);
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }

    public static void setFailures(int failures) {
        if (infantiumHandler.isReady()) {
            infantium.setFailures(failures);
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }
*/
    public static void sendGameRawData() {
        if (infantiumHandler.isReady()) {
            infantium.sendGameRawData();
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }

    public static void closeGameplay() {
        if (infantiumHandler.isReady()) {
            infantium.closeGameplay();
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }

    public static void setSubContentUUID(String subContentUuid) {
        if (infantiumHandler.isReady()) {
            infantium.setSubContentUUID(subContentUuid);
        } else {
            Log.w(TAG, "Infantium is not ready. The call is refused");
        }
    }

    public static void returnToInfantiumApp() {
        infantium.returnToInfantiumApp(ACTIVITY_WEAK_REFERENCE.get());
    }

    public static void onPause() {
        infantium.onPauseInfantium();
    }

    public static void onResume() {
        infantium.onResumeInfantium();
    }
    
    public static void addElement(String ID){
    	com.infantium.android.sdk.elements.Element element = new com.infantium.android.sdk.elements.Element(ID, null);
    	infantium.addElement(element);
    }
    
    public static void addPaintedElement(String ID){
    	PaintedElement element = new PaintedElement(ID);
    	infantium.addElement(element);
    }
    
    public static void addPictureElement(String ID){
    	PictureElement element = new PictureElement(ID);
    	infantium.addElement(element);
    }
    
    public static void addShapeElement(String ID){
    	
    	ShapeElement element = new ShapeElement(ID);
    	infantium.addElement(element);
    }
    
    public static void addNumberElement(String ID, Integer value){
    	NumberElement element = new NumberElement(ID, value);
    	infantium.addElement(element);
    }
    
    public static void addGoal(String ID)
    {
    	Goal goal = new Goal(ID, null);
    	infantium.addGoal(goal);
    }
    
    public static void addSelectionGoal(String ID)
    {
    	SelectionGoal goal = new SelectionGoal(ID);
    	infantium.addGoal(goal);
    }
    
    public static void addMatchingGoal(String ID, String matching_element)
    {
    	MatchingGoal goal = new MatchingGoal(ID, matching_element);
    	infantium.addGoal(goal);
    }
    
    public static void addTappingGoal(String ID)
    {
    	TappingGoal goal = new TappingGoal(ID);
    	infantium.addGoal(goal);
    }
    
    public static void newBasicInteraction(String ID, String object_type, String goal_type)
    {
    	infantium.newBasicInteraction(ID, object_type, goal_type);
    }
}
