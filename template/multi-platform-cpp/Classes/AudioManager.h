//
// Created by vedi on 11/5/12.
//


#ifndef __AudioManager_H_
#define __AudioManager_H_

#include <string>

#include "vedidev/vedidev.h"

class AudioManager {
public:
    V_SHARED_DCL(AudioManager);

    bool getMute();
    void setMute(bool bMute);

    void stopAllSounds();
    void pauseAll();
    void resumeAll();

private:
    AudioManager();

    std::string m_sResourcePrefix;

    bool m_bMute;
    unsigned int m_uCurrentSpeechId;

    void preloadEffect(const char *pEffect);
    void unloadEffect(const char *pEffect);
    void playEffect(const char *pEffect);

    bool resolveResourcePath(std::string &sResourceName);
};

#endif //__AudioManager_H_
