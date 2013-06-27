#ifndef __SIMPLE_AUDIO_ENGINE_JNI__
#define __SIMPLE_AUDIO_ENGINE_JNI__

#include <jni.h>

extern "C"
{
    extern void preloadSoundJNI(const char *path, unsigned int channelNum);
    extern void playSoundJNI(const char *path, bool isLoop, unsigned int channelNum);
    extern void stopSoundJNI(unsigned int channelNum);
    extern void pauseSoundJNI(unsigned int channelNum);
    extern void resumeSoundJNI(unsigned int channelNum);
    extern void rewindSoundJNI(unsigned int channelNum);
    extern bool isSoundPlayingJNI(unsigned int channelNum);
    extern float getSoundVolumeJNI(unsigned int channelNum);
    extern void setSoundVolumeJNI(float volume, unsigned int channelNum);
    extern unsigned int playEffectJNI(const char* path, bool bLoop);
    extern void stopEffectJNI(unsigned int nSoundId);
    extern void endJNI();
    extern float getEffectsVolumeJNI();
    extern void setEffectsVolumeJNI(float volume);
    extern void preloadEffectJNI(const char *path);
    extern void unloadEffectJNI(const char* path);
    extern void pauseEffectJNI(unsigned int nSoundId);
    extern void pauseAllEffectsJNI();
    extern void resumeEffectJNI(unsigned int nSoundId);
    extern void resumeAllEffectsJNI();
    extern void stopAllEffectsJNI();
}

#endif // __SIMPLE_AUDIO_ENGINE_JNI__