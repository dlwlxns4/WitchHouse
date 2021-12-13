#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <vector>

using namespace std;

class TalkManager : public Singleton<TalkManager>
{
private:
	unordered_map<int, vector<string>> talkData = {};

public:
	void Init();
	string GetTalkData(int referenceId);
};