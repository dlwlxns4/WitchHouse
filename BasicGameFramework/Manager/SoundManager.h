#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <list>

using namespace std;

class CSound;
class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager() = default;
	~SoundManager();

	void Init();
	void Update();
	void Release();

	void StopSound(wstring sound);
	bool startSound(wstring sound);

	void startInfSound(wstring sound);

	void fadeUpSound(wstring sound);

	unordered_map<wstring, CSound*> soundMap;
	list<CSound*> playList;
};