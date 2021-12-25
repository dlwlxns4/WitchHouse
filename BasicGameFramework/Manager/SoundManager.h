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
	~SoundManager() = default;

	void Init();
	void Update();

	void StopSound(wstring sound);
	void startSound(wstring sound);

	void fadeUpSound(wstring sound);

	unordered_map<wstring, CSound*> soundMap;
	list<CSound*> playList;
};