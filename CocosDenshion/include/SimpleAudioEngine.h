/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Steve Oldmeadow

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

#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include <stddef.h>
#include "Export.h"
#include <typeinfo>
#include <ctype.h>
#include <string.h>

namespace CocosDenshion {

class TypeInfo
{
public:
    virtual long getClassTypeInfo() = 0;
};

static inline unsigned int getHashCodeByString(const char *key)
{
	unsigned int len = strlen(key);
	const char *end=key+len;
	unsigned int hash;

	for (hash = 0; key < end; key++)
	{
		hash *= 16777619;
		hash ^= (unsigned int) (unsigned char) toupper(*key);
	}
	return (hash);
}

/**
@class          SimpleAudioEngine
@brief          offer a VERY simple interface to play background music & sound effect
*/

class EXPORT_DLL SimpleAudioEngine : public TypeInfo
{
public:
    SimpleAudioEngine();
    /**
     *  @js NA
     *  @lua NA
     */
    ~SimpleAudioEngine();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual long getClassTypeInfo() {
        return getHashCodeByString(typeid(CocosDenshion::SimpleAudioEngine).name());
    }

    /**
    @brief Get the shared Engine object,it will new one when first time be called
    @js getInstance
    */
    static SimpleAudioEngine* sharedEngine();

    /**
    @brief Release the shared Engine object
    @warning It must be called before the application exit, or a memroy leak will be casued.
    @lua NA
    */
    static void end();

    /**
     @brief Preload background music
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     @js preloadMusic
     */
    void preloadBackgroundMusic(const char* pszFilePath) {
        this->preloadSound(pszFilePath, 0);
    }
    
    /**
    @brief Play background music
    @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
    @param bLoop Whether the background music loop or not
    @js playMusic
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop) {
        this->playSound(pszFilePath, bLoop, 0);
    };

    /**
     @js playMusic
     */
    void playBackgroundMusic(const char* pszFilePath) {
    	this->playSound(pszFilePath, false, 0);
    }

    /**
    @brief Stop playing background music
    @param bReleaseData If release the background music data or not.As default value is false
    @js stopMusic
    */
    void stopBackgroundMusic(bool bReleaseData) {
        this->stopSound(bReleaseData, 0);
    };

    /**
     @js stopMusic
     */
    void stopBackgroundMusic() {
    	this->stopSound(0);
    }

    /**
    @brief Pause playing background music
    @js pauseMusic
    */
    void pauseBackgroundMusic() {
        this->pauseSound(0);
    }

    /**
    @brief Resume playing background music
    @js resumeMusic
    */
    void resumeBackgroundMusic() {
        this->resumeSound(0);
    }

    /**
    @brief Rewind playing background music
    @js rewindMusic
    */
    void rewindBackgroundMusic() {
        this->rewindSound(0);
    }

    /**
     *  @js willPlayMusic
     */
    bool willPlayBackgroundMusic() {
        return this->willPlaySound();
    }

    /**
    @brief Whether the background music is playing
    @return If is playing return true,or return false
    @js isMusicPlaying
    */
    bool isBackgroundMusicPlaying() {
        return this->isSoundPlaying(0);
    }

    // properties
    /**
    @brief The volume of the background music max value is 1.0,the min value is 0.0
    @js getMusicVolume
    */
    float getBackgroundMusicVolume() {
        return this->getSoundVolume(0);
    }

    /**
    @brief set the volume of background music
    @param volume must be in 0.0~1.0
    @js setMusicVolume
    */
    void setBackgroundMusicVolume(float volume) {
        this->setSoundVolume(volume, 0);
    }


    /**
     @brief Preload sound at channelNum
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     @param channelNum The channelNum number
     */
    void preloadSound(char const *pszFilePath, unsigned int channelNum);

    /**
     @brief Play sound at channelNum
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     @param bLoop Whether the background music loop or not
     @param channelNum The channelNum number
    */
    void playSound(char const *pszFilePath, bool bLoop, unsigned int channelNum);
    void playSound(char const *pszFilePath, unsigned int channelNum) {
        this->playSound(pszFilePath, false, channelNum);
    }

    /**
    @brief Stop playing sound
    @param bReleaseData If release the background music data or not.As default value is false
     @param channelNum The channelNum number
    */
    void stopSound(bool bReleaseData, unsigned int channelNum);
    void stopSound(unsigned int channelNum) {
        this->stopSound(false, 0);
    }

    /**
    @brief Pause playing sound
     @param channelNum The channelNum number
    */
    void pauseSound(unsigned int channelNum);

    /**
    @brief Resume playing sound
     @param channelNum The channelNum number
    */
    void resumeSound(unsigned int channelNum);

    /**
    @brief Rewind playing sound
     @param channelNum The channelNum number
    */
    void rewindSound(unsigned int channelNum);

    bool willPlaySound();

    /**
    @brief Whether the sound is playing
     @param channelNum The channelNum number
    @return If is playing return true,or return false
    */
    bool isSoundPlaying(unsigned int channelNum);

    // properties
    /**
    @brief The volume of the sound max value is 1.0,the min value is 0.0
    */
    float getSoundVolume(unsigned int channelNum);

    /**
    @brief set the volume of sound
    @param volume must be in 0.0~1.0
     @param channelNum The channelNum number
    */
    void setSoundVolume(float volume, unsigned int channelNum);

    /**
     @brief Preload sound at channelNum
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     @param channelNum The channelNum number
     */
    float getSoundDuration(char const *pszFilePath, unsigned int channelNum);

    /**
    @brief The volume of the effects max value is 1.0,the min value is 0.0
    */
    float getEffectsVolume();

    /**
    @brief set the volume of sound effecs
    @param volume must be in 0.0~1.0
    */
    void setEffectsVolume(float volume);

    // for sound effects
    /**
    @brief Play sound effect
    @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
    @bLoop Whether to loop the effect playing, default value is false
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    unsigned int playEffect(const char* pszFilePath) {
    	return this->playEffect(pszFilePath, false);
    }

    /**
    @brief Pause playing sound effect
    @param nSoundId The return value of function playEffect
    */
    void pauseEffect(unsigned int nSoundId);

    /**
    @brief Pause all playing sound effect
    @param nSoundId The return value of function playEffect
    */
    void pauseAllEffects();

    /**
    @brief Resume playing sound effect
    @param nSoundId The return value of function playEffect
    */
    void resumeEffect(unsigned int nSoundId);

    /**
    @brief Resume all playing sound effect
    @param nSoundId The return value of function playEffect
    */
    void resumeAllEffects();

    /**
    @brief Stop playing sound effect
    @param nSoundId The return value of function playEffect
    */
    void stopEffect(unsigned int nSoundId);

    /**
    @brief Stop all playing sound effects
    */
    void stopAllEffects();

    /**
    @brief          preload a compressed audio file
    @details        the compressed audio will be decode to wave, then write into an 
    internal buffer in SimpleaudioEngine
    */
    void preloadEffect(const char* pszFilePath);

    /**
    @brief          unload the preloaded effect from internal buffer
    @param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
    */
    void unloadEffect(const char* pszFilePath);
};

} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_

