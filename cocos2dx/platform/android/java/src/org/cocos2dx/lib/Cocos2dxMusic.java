/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import java.io.FileInputStream;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.util.Log;

public class Cocos2dxMusic {

    public class MediaPlayerContainer {
        String mCurrentPath = null;
        boolean mPaused = false;
        float mLeftVolume = 0.5f;
        float mRightVolume = 0.5f;
        MediaPlayer mMediaPlayer = null;
    }
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = Cocos2dxMusic.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;
	private MediaPlayerContainer mMediaPlayerContainer[];

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxMusic(final Context pContext) {
		this.mContext = pContext;

		this.initData();
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	public void preloadSound(final String pPath, int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        String currentPath = mediaPlayerContainer.mCurrentPath;
        if ((currentPath == null) || (!currentPath.equals(pPath))) {
			// preload new background music

            releaseChannel(channelNum);
            createChannel(pPath, channelNum);
		}
	}

    public void playSound(final String pPath, final boolean isLoop, int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        MediaPlayer mediaPlayer = mediaPlayerContainer.mMediaPlayer;
        if (mediaPlayerContainer.mCurrentPath == null) {
			// it is the first time to play background music or end() was called
            mediaPlayer = createChannel(pPath, channelNum);
		} else {
			if (!mediaPlayerContainer.mCurrentPath.equals(pPath)) {
				// play new background music

				// release old resource and create a new one
                releaseChannel(channelNum);
                mediaPlayer = createChannel(pPath, channelNum);
			}
		}

		if (mediaPlayer == null) {
			Log.e(Cocos2dxMusic.TAG, "playSound: background media player is null");
		} else {
			// if the music is playing or paused, stop it
            mediaPlayer.stop();

            mediaPlayer.setLooping(isLoop);

			try {
                mediaPlayer.prepare();
                mediaPlayer.seekTo(0);
                mediaPlayer.start();

                mediaPlayerContainer.mPaused = false;
			} catch (final Exception e) {
				Log.e(Cocos2dxMusic.TAG, "playSound: error state");
			}
		}
	}

	public void stopSound(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
		if (mediaPlayerContainer.mMediaPlayer != null) {
            mediaPlayerContainer.mMediaPlayer.stop();

			// should set the state, if not, the following sequence will be error
			// play -> pause -> stop -> resume
            mediaPlayerContainer.mPaused = false;
		}
	}

	public void pauseSound(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        if (mediaPlayerContainer.mMediaPlayer != null) {
            mediaPlayerContainer.mMediaPlayer.pause();
            mediaPlayerContainer.mPaused = true;
		}
	}

	public void resumeSound(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        if (mediaPlayerContainer.mMediaPlayer != null && mediaPlayerContainer.mPaused) {
            mediaPlayerContainer.mMediaPlayer.start();
            mediaPlayerContainer.mPaused = false;
		}
	}

	public void rewindSound(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        if (mediaPlayerContainer.mMediaPlayer != null) {
            mediaPlayerContainer.mMediaPlayer.stop();

			try {
                mediaPlayerContainer.mMediaPlayer.prepare();
                mediaPlayerContainer.mMediaPlayer.seekTo(0);
                mediaPlayerContainer.mMediaPlayer.start();

                mediaPlayerContainer.mPaused = false;
			} catch (final Exception e) {
				Log.e(Cocos2dxMusic.TAG, "rewindSound: error state");
			}
		}
	}

	public boolean isSoundPlaying(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);

		boolean ret;
		if (mediaPlayerContainer.mMediaPlayer == null) {
			ret = false;
		} else {
			ret = mediaPlayerContainer.mMediaPlayer.isPlaying();
		}

		return ret;
	}

	public void end() {
        releaseChannel(0);
        releaseChannel(1);

        this.initData();
	}

	public float getSoundVolume(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        if (mediaPlayerContainer.mMediaPlayer != null) {
			return (mediaPlayerContainer.mLeftVolume + mediaPlayerContainer.mRightVolume) / 2;
		} else {
			return 0.0f;
		}
	}

	public void setSoundVolume(float pVolume, int channelNum) {
		if (pVolume < 0.0f) {
			pVolume = 0.0f;
		}

		if (pVolume > 1.0f) {
			pVolume = 1.0f;
		}

        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        mediaPlayerContainer.mLeftVolume = mediaPlayerContainer.mRightVolume = pVolume;
		if (mediaPlayerContainer.mMediaPlayer != null) {
            mediaPlayerContainer.mMediaPlayer.setVolume(mediaPlayerContainer.mLeftVolume, mediaPlayerContainer.mRightVolume);
		}
	}

    public float getSoundDuration(final String pPath, final int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        String currentPath = mediaPlayerContainer.mCurrentPath;
        if (mediaPlayerContainer.mMediaPlayer != null || (currentPath == null) || (!currentPath.equals(pPath))) {
            releaseChannel(channelNum);
            createChannel(pPath, channelNum);
        }
        if (mediaPlayerContainer.mMediaPlayer != null) {
            return mediaPlayerContainer.mMediaPlayer.getDuration() / 1000f;
        } else {
            Log.e(Cocos2dxMusic.TAG, "getSoundDuration: media player is null");
            return 0f;
        }
    }

    private void initData() {
        mMediaPlayerContainer = new MediaPlayerContainer[2];
        mMediaPlayerContainer[0] = new MediaPlayerContainer();
        mMediaPlayerContainer[1] = new MediaPlayerContainer();
	}

    private MediaPlayerContainer getMediaPlayerContrainer(int channelNum) {
        if (channelNum < 2) {
            return mMediaPlayerContainer[channelNum];
        } else {
            Log.e(TAG, "wrong channelNum");
            return mMediaPlayerContainer[0];
        }

    }

    private MediaPlayer createChannel(String pPath, int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        // record the path
        mediaPlayerContainer.mCurrentPath = pPath;
        mediaPlayerContainer.mMediaPlayer = this.createMediaplayer(mediaPlayerContainer);
        return mediaPlayerContainer.mMediaPlayer;
    }

    private void releaseChannel(int channelNum) {
        MediaPlayerContainer mediaPlayerContainer = getMediaPlayerContrainer(channelNum);
        // release old resource and create a new one
        if (mediaPlayerContainer.mMediaPlayer != null) {
            mediaPlayerContainer.mMediaPlayer.release();
        }
    }

    /**
	 * create mediaplayer for music
	 * 
	 *
     * @return
	 */
	private MediaPlayer createMediaplayer(final MediaPlayerContainer mediaPlayerContainer) {
		MediaPlayer mediaPlayer = new MediaPlayer();

		try {
			if (mediaPlayerContainer.mCurrentPath.startsWith("/")) {
				final FileInputStream fis = new FileInputStream(mediaPlayerContainer.mCurrentPath);
				mediaPlayer.setDataSource(fis.getFD());
				fis.close();
			} else {
				final AssetFileDescriptor assetFileDescritor = this.mContext.getAssets().openFd(mediaPlayerContainer.mCurrentPath);
				mediaPlayer.setDataSource(assetFileDescritor.getFileDescriptor(), assetFileDescritor.getStartOffset(), assetFileDescritor.getLength());
			}

			mediaPlayer.prepare();

			mediaPlayer.setVolume(mediaPlayerContainer.mLeftVolume, mediaPlayerContainer.mRightVolume);
		} catch (final Exception e) {
			mediaPlayer = null;
			Log.e(Cocos2dxMusic.TAG, "error: " + e.getMessage(), e);
		}

		return mediaPlayer;
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
