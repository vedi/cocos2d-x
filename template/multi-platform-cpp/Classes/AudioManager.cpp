//
// Created by vedi on 11/5/12.
//

#include "AudioManager.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define RESOURCE_FOLDER "sounds"

USING_NS_CC;

#define SHARED_ENGINE SimpleAudioEngine::sharedEngine()

using namespace CocosDenshion;

V_SHARED_IMPL(AudioManager);

AudioManager::AudioManager() {
    m_bMute = false;
}

void AudioManager::setMute(bool bMute) {

    if (!m_bMute) {
        SHARED_ENGINE->stopAllEffects();
        SHARED_ENGINE->stopBackgroundMusic(true);
        m_bMute = bMute;
    } else {
        m_bMute = bMute;
    }
}

void AudioManager::resumeAll() {
    if (!m_bMute) {
        SHARED_ENGINE->resumeBackgroundMusic();
        SHARED_ENGINE->resumeAllEffects();
    }
}

void AudioManager::stopAllSounds() {
    SHARED_ENGINE->stopAllEffects();
}

void AudioManager::preloadEffect(char const *pEffect) {
    std::string sPath = pEffect;  
    if (resolveResourcePath(sPath)) {
        SHARED_ENGINE->preloadEffect(sPath.c_str());
    } else {
        CCLog("The resource is not exists: %s", pEffect);
    }
}

void AudioManager::unloadEffect(char const *pEffect) {
    std::string sPath = pEffect;
    if (resolveResourcePath(sPath)) {
        SHARED_ENGINE->unloadEffect(sPath.c_str());
    } else {
        CCLog("The resource is not exists: %s", pEffect);
    }
}


void AudioManager::playEffect(char const *pEffect) {
    if (!m_bMute) {
        std::string sPath = pEffect;
        if (resolveResourcePath(sPath)) {
            SHARED_ENGINE->playEffect(sPath.c_str());
        } else {
            CCLog("The resource is not exists: %s", pEffect);
        }
    }
}


bool AudioManager::resolveResourcePath(std::string & sResourceName) {
    bool exists = false;
    std::string sPath;
    std::string fullPath;
    if (!m_sResourcePrefix.empty()) {
        sPath = std::string(RESOURCE_FOLDER).append(m_sResourcePrefix.c_str()).append("/").append(sResourceName);
        fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(sPath.c_str());
        exists = sPath.compare(fullPath.c_str()) != 0;
    }

    if (!exists) {
        sPath = std::string(RESOURCE_FOLDER).append("/").append(sResourceName);
        fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(sPath.c_str());
        exists = sPath.compare(fullPath.c_str()) != 0;
    }

    sResourceName.assign(fullPath);

    return exists;
}

void AudioManager::pauseAll() {
    if (!m_bMute) {
        if (SHARED_ENGINE->isBackgroundMusicPlaying()) {
            SHARED_ENGINE->pauseBackgroundMusic();
        }
        SHARED_ENGINE->pauseAllEffects();
    }
}

bool AudioManager::getMute() {
    return m_bMute;
}

#undef SHARED_ENGINE


