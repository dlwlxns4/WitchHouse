#include "CSound.h"

FMOD_SYSTEM* CSound::g_sound_system;

CSound::CSound(const char* path, bool loop) {

	if (loop) {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}

	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;
}

CSound::~CSound() {
	FMOD_Sound_Release(m_sound);
}


void CSound::Init() {

	FMOD_System_Create(&g_sound_system);
	FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, nullptr);

}

void CSound::Release() {

	FMOD_System_Close(g_sound_system);
	FMOD_System_Release(g_sound_system);

}


bool CSound::play() {

	if (isPlay == false)
	{
		isPlay = true;
		FMOD_System_PlaySound(g_sound_system, m_sound, nullptr, false, &m_channel);
		return true;
	}
	return false;
}

void CSound::InfPlay()
{
	FMOD_System_PlaySound(g_sound_system, m_sound, nullptr, false, &m_channel);
}


void CSound::pause() {
	FMOD_Channel_SetPaused(m_channel, true);

}

void CSound::resume() {
	isPlay = true;
	FMOD_Channel_SetPaused(m_channel, false);

}

void CSound::stop() {
	isPlay = false;
	FMOD_Channel_Stop(m_channel);

}

void CSound::volumeUp() {
	if (m_volume < SOUND_MAX) {
		m_volume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

}

void CSound::volumeDown() {
	if (m_volume > SOUND_MIN) {
		m_volume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

}

void CSound::volumeFadeUp()
{
	isVolumeUp = true;
}

void CSound::SetVolume(float volume)
{
	this->m_volume = volume;
}


void CSound::Update() {
	FMOD_Channel_IsPlaying(m_channel, &m_bool);

	if (m_bool) {

		FMOD_System_Update(g_sound_system);
	}

	if (isVolumeUp)
	{
		volumeUp();
		if (m_volume >= 1.0f)
		{
			isVolumeUp = false;
		}
	}

}
