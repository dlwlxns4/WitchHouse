#include "SoundManager.h"
#include "../Util/CSound.h"

SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::Init()
{
	CSound::Init();
	CSound* title = new CSound("Audio/BGM/Lost_Chair.wav", true);
	soundMap[L"Title"] = title;
	playList.push_back(title);

	CSound* Chaser = new CSound("Audio/BGM/loop_65.ogg", true);
	soundMap[L"Chaser"] = Chaser;
	playList.push_back(Chaser);

	CSound* wind = new CSound("Audio/BGM/Wind2.wav", true);
	soundMap[L"Wind"] = wind;
	playList.push_back(wind);
	wind->SetVolume(0.01f);

	CSound* house = new CSound("Audio/BGM/WareHouse.ogg", true);
	soundMap[L"House"] = house;
	playList.push_back(house);
	house->SetVolume(0.01f);

	CSound* cursor = new CSound("Audio/BGS/cursor+.ogg", false);
	soundMap[L"Cursor"] = cursor;
	playList.push_back(cursor);

	CSound* click = new CSound("Audio/BGS/cursor02.ogg", false);
	soundMap[L"Click"] = click;
	playList.push_back(click);

	CSound* save = new CSound("Audio/BGS/save+.ogg", false);
	soundMap[L"Save"] = save;
	playList.push_back(save);

	CSound* item = new CSound("Audio/BGS/item04.ogg", false);
	soundMap[L"Item"] = item;
	playList.push_back(item);

	CSound* forest = new CSound("Audio/BGS/ashioto_kusa.ogg", false);
	soundMap[L"Forest"] = forest;
	playList.push_back(forest);

	CSound* kishimi = new CSound("Audio/BGS/kishimi.ogg", false);
	soundMap[L"Kisimi"] = kishimi;
	playList.push_back(kishimi);

	CSound* door = new CSound("Audio/BGS/open1+xxx.ogg", false);
	soundMap[L"Door"] = door;
	playList.push_back(door);

	CSound* otosu = new CSound("Audio/BGS/otosu.ogg", false);
	soundMap[L"Otosu"] = otosu;
	playList.push_back(otosu);
	otosu->SetVolume(0.5f);

	CSound* press = new CSound("Audio/BGS/ti8.ogg", false);
	soundMap[L"Press"] = press;
	playList.push_back(press);

	CSound* bearFoot = new CSound("Audio/BGS/ti4.ogg", false);
	soundMap[L"BearFoot"] = bearFoot;
	playList.push_back(bearFoot);

	CSound* kinzoku = new CSound("Audio/BGS/kinzoku.ogg", false);
	soundMap[L"Kinzoku"] = kinzoku;
	playList.push_back(kinzoku);

	CSound* teddy = new CSound("Audio/BGS/door1_a.ogg", false);
	soundMap[L"Teddy"] = teddy;
	playList.push_back(teddy);

	CSound* pressTeddy = new CSound("Audio/BGS/ti6.ogg", false);
	soundMap[L"PressTeddy"] = pressTeddy;
	playList.push_back(pressTeddy);
}


void SoundManager::Update()
{
	for (auto sound : playList)
	{
		sound->Update();
	}
}

void SoundManager::Release()
{
	for (auto it = soundMap.begin(); it != soundMap.end(); ++it)
	{
		delete it->second;
	}
	playList.clear();
	soundMap.clear();
	CSound::Release();
}

void SoundManager::StopSound(wstring sound)
{
	soundMap[sound]->stop();
}

bool SoundManager::startSound(wstring sound)
{
	return soundMap[sound]->play();
}

void SoundManager::startInfSound(wstring sound)
{
	soundMap[sound]->InfPlay();
}

void SoundManager::fadeUpSound(wstring sound)
{
	soundMap[sound]->volumeFadeUp();
}