package com.vedidev.cocos2dx.scoreloopmodule;

import java.lang.Runnable;

import com.scoreloop.client.android.core.controller.ScoreController;
import com.scoreloop.client.android.core.model.Score;

public class SubmitScore implements Runnable {
	  private Score score;
	  private ScoreController scoreController;
	  public SubmitScore (ScoreController scoreController, Score _score) {
		  this.score = _score;
		  this.scoreController = scoreController;
	  }

	  public void run() {
		  scoreController.submitScore(score);
	  }
}