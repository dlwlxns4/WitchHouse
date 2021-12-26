#pragma once
#ifndef _CSOUND_H_
#define _CSOUND_H_

#include <fmod.h>

#define SOUND_MAX 0.9f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.005f

using namespace std;

class CSound {
private:
    static FMOD_SYSTEM* g_sound_system;
    
    FMOD_SOUND* m_sound;
    FMOD_CHANNEL* m_channel;

    float m_volume;
    FMOD_BOOL m_bool;

    bool isVolumeUp = false;
    bool isPlay = false;
public:
    CSound(const char* path, bool loop);
    ~CSound();

    static void Init();
    static void
        Release();

    bool play();
    void InfPlay();
    void pause();
    void resume();
    void stop();
    void volumeUp();
    void volumeDown();
    void volumeFadeUp();
    void SetVolume(float volume);

    void Update();
};

#endif
