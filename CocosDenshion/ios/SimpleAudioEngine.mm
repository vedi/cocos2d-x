/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine_objc.h"
#include "cocos2d.h"
USING_NS_CC;

static void static_end()
{
    [SimpleAudioEngine  end];
}

static void static_preloadSound(const char *pszFilePath, unsigned int channelNum)
{
    [[SimpleAudioEngine sharedEngine] preloadSound:[NSString stringWithUTF8String:pszFilePath] atChannelNum: channelNum];
}

static void static_playSound(char const *pszFilePath, bool bLoop, unsigned int channelNum) {
    [[SimpleAudioEngine sharedEngine] playSound:[NSString stringWithUTF8String:pszFilePath] loop:bLoop atChannelNum: channelNum];
}

static void static_stopSound(unsigned int channelNum) {
    [[SimpleAudioEngine sharedEngine] stopSound: channelNum];
}

static void static_pauseSound(unsigned int channelNum)
{
    [[SimpleAudioEngine sharedEngine] pauseSound: channelNum];
}

static void static_resumeSound(unsigned int channelNum)
{
    [[SimpleAudioEngine sharedEngine] resumeSound: channelNum];
} 

static void static_rewindSound(unsigned int channelNum)
{
    [[SimpleAudioEngine sharedEngine] rewindSound: channelNum];
}

static bool static_willPlaySound()
{
    return [[SimpleAudioEngine sharedEngine] willPlaySound];
}

static bool static_isSoundPlaying(unsigned int channelNum)
{
    return [[SimpleAudioEngine sharedEngine] isSoundPlaying: channelNum];
}

static float static_getSoundVolume(unsigned int channelNum)
{
    return [[SimpleAudioEngine sharedEngine] getSoundVolume: channelNum];
}

static void static_setSoundVolume(float volume, unsigned int channelNum)
{
    volume = MAX( MIN(volume, 1.0), 0 );
    [[SimpleAudioEngine sharedEngine] setSoundVolume:volume atChannelNum: channelNum];
}

static float static_getSoundDuration(char const *pszFilePath, unsigned int channelNum) {
    return [[SimpleAudioEngine sharedEngine] getSoundDuration:[NSString stringWithUTF8String:pszFilePath] atChannelNum: channelNum];
}

static float static_getEffectsVolume()
{
    return [[SimpleAudioEngine sharedEngine] effectsVolume];
}
     
static void static_setEffectsVolume(float volume)
{
    volume = MAX( MIN(volume, 1.0), 0 );
    [SimpleAudioEngine sharedEngine].effectsVolume = volume;
}
     
static unsigned int static_playEffect(const char* pszFilePath, bool bLoop)
{
    return [[SimpleAudioEngine sharedEngine] playEffect:[NSString stringWithUTF8String: pszFilePath] loop:bLoop]; 
}
     
static void static_stopEffect(int nSoundId)
{
    [[SimpleAudioEngine sharedEngine] stopEffect: nSoundId];
}
     
static void static_preloadEffect(const char* pszFilePath)
{
    [[SimpleAudioEngine sharedEngine] preloadEffect: [NSString stringWithUTF8String: pszFilePath]];
}
     
static void static_unloadEffect(const char* pszFilePath)
{
    [[SimpleAudioEngine sharedEngine] unloadEffect: [NSString stringWithUTF8String: pszFilePath]];
}

static void static_pauseEffect(unsigned int uSoundId)
{
    [[SimpleAudioEngine sharedEngine] pauseEffect: uSoundId];
}

static void static_pauseAllEffects()
{
    [[SimpleAudioEngine sharedEngine] pauseAllEffects];
}

static void static_resumeEffect(unsigned int uSoundId)
{
    [[SimpleAudioEngine sharedEngine] resumeEffect: uSoundId];
}

static void static_resumeAllEffects()
{
    [[SimpleAudioEngine sharedEngine] resumeAllEffects];
}

static void static_stopAllEffects()
{
    [[SimpleAudioEngine sharedEngine] stopAllEffects];
}

namespace CocosDenshion {

static SimpleAudioEngine *s_pEngine;

SimpleAudioEngine::SimpleAudioEngine()
{

}

SimpleAudioEngine::~SimpleAudioEngine()
{

}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    if (! s_pEngine)
    {
        s_pEngine = new SimpleAudioEngine();
    }
    
    return s_pEngine;
}

void SimpleAudioEngine::end()
{
    if (s_pEngine)
    {
        delete s_pEngine;
        s_pEngine = NULL;
    }
    
    static_end();
}

void SimpleAudioEngine::preloadSound(const char* pszFilePath, unsigned int channelNum) {
    // Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    static_preloadSound(fullPath.c_str(), channelNum);
}

void SimpleAudioEngine::playSound(const char* pszFilePath, bool bLoop, unsigned int channelNum) {
    // Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    static_playSound(fullPath.c_str(), bLoop, channelNum);
}

void SimpleAudioEngine::stopSound(bool bReleaseData, unsigned int channelNum) {
    static_stopSound(channelNum);
}

void SimpleAudioEngine::pauseSound(unsigned int channelNum) {
    static_pauseSound(channelNum);
}

void SimpleAudioEngine::resumeSound(unsigned int channelNum) {
    static_resumeSound(channelNum);
} 

void SimpleAudioEngine::rewindSound(unsigned int channelNum) {
    static_rewindSound(channelNum);
}

bool SimpleAudioEngine::willPlaySound() {
    return static_willPlaySound();
}

bool SimpleAudioEngine::isSoundPlaying(unsigned int channelNum) {
    return static_isSoundPlaying(channelNum);
}

float SimpleAudioEngine::getSoundVolume(unsigned int channelNum) {
    return static_getSoundVolume(channelNum);
}

void SimpleAudioEngine::setSoundVolume(float volume, unsigned int channelNum) {
    static_setSoundVolume(volume, channelNum);
}

float SimpleAudioEngine::getSoundDuration(char const *pszFilePath, unsigned int channelNum) {
    return static_getSoundDuration(pszFilePath, channelNum);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return static_getEffectsVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    static_setEffectsVolume(volume);
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    // Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    return static_playEffect(fullPath.c_str(), bLoop);
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    static_stopEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    // Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    static_preloadEffect(fullPath.c_str());
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    // Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    static_unloadEffect(fullPath.c_str());
}

void SimpleAudioEngine::pauseEffect(unsigned int uSoundId)
{
    static_pauseEffect(uSoundId);
}

void SimpleAudioEngine::resumeEffect(unsigned int uSoundId)
{
    static_resumeEffect(uSoundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    static_pauseAllEffects();
}

void SimpleAudioEngine::resumeAllEffects()
{
    static_resumeAllEffects();
}

void SimpleAudioEngine::stopAllEffects()
{
    static_stopAllEffects();
}

} // endof namespace CocosDenshion {
