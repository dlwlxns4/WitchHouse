#include "SoundManager.h"
#include "../Util/CSound.h"

void SoundManager::Init()
{
	CSound::Init();
	CSound* title = new CSound("Audio/BGM/Lost_Chair.wav", true);
	soundMap[L"Title"] = title;
	playList.push_back(title);
	title->play();

	CSound* wind = new CSound("Audio/BGM/Wind2.wav", true);
	soundMap[L"Wind"] = wind;
	playList.push_back(wind);
	wind->SetVolume(0.01f);

	CSound* house = new CSound("Audio/BGM/WareHouse.ogg", true);
	soundMap[L"House"] = house;
	playList.push_back(house);
	house->SetVolume(0.01f);

	
}

void SoundManager::Update()
{
	for (auto sound : playList)
	{
		sound->Update();
	}
}

void SoundManager::StopSound(wstring sound)
{
	soundMap[sound]->pause();
}

void SoundManager::startSound(wstring sound)
{
	soundMap[sound]->play();
}


void SoundManager::fadeUpSound(wstring sound)
{
	soundMap[sound]->volumeFadeUp();
}