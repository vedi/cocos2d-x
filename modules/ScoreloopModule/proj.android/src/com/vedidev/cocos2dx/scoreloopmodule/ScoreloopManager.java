package com.vedidev.cocos2dx.scoreloopmodule;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;

import com.scoreloop.client.android.core.controller.RequestController;
import com.scoreloop.client.android.core.controller.RequestControllerObserver;
import com.scoreloop.client.android.core.controller.ScoreController;
import com.scoreloop.client.android.core.model.Score;
import com.vedidev.cocos2dx.scoreloopmodule.SubmitScore;

public class ScoreloopManager {
	
	private static Activity activity;
	
    public static void setContext(Activity activity) {
		ScoreloopManager.activity = activity;
	}
    
    public static void showLeaderboard()
    {
    	activity.startActivity(new Intent(activity, LeaderboardActivity.class));
    }
    
    public static void submitScore(Double scoreResult)
    {
    	// this is where you should input your game's score
    	
    	final Score score = new Score((double)scoreResult, null);

		// set up an observer for our request
		RequestControllerObserver observer = new RequestControllerObserver() {

			@Override
			public void requestControllerDidFail(RequestController controller, Exception exception) {
				// something went wrong... possibly no internet connection
				//activity.dismissDialog(DIALOG_PROGRESS);
				//activity.showDialog(DIALOG_FAILED);
			}

			// this method is called when the request succeeds
			@Override
			public void requestControllerDidReceiveResponse(RequestController controller) {
				// remove the progress dialog
				//activity.dismissDialog(DIALOG_PROGRESS);
				// show the success dialog
				//activity.showDialog(DIALOG_SUBMITTED);
				// alternatively, you may want to return to the main screen
				// or start another round of the game at this point
			}
		};

		// with the observer, we can create a ScoreController to submit the score
		final ScoreController scoreController = new ScoreController(observer);

		// show a progress dialog while we are submitting
		SubmitScore scoreLoopUpdater = new SubmitScore(scoreController, score);
		Handler mainHandler = new Handler(activity.getMainLooper());
		mainHandler.post(scoreLoopUpdater);
    }
}
