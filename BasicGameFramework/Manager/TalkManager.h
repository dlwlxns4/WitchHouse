#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <vector>

using namespace std;

class TalkManager : public Singleton<TalkManager>
{
private:
	unordered_map<int, vector<wstring>> talkData = {};
	vector<wstring> vecTalkData = {};

public:
	void Init();
	void SaveTalkData(int referenceId);
	vector<wstring> GetVecTalkData();
	vector<wstring> GetTalkData(int referenceId);
};