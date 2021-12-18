#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <vector>

using namespace std;

class TalkManager : public Singleton<TalkManager>
{
private:
	unordered_map<int, vector<wstring>> talkData = {};

	unordered_map<int, vector<wstring>> itemTalkData = {};
	vector<wstring> vecTalkData = {};


public:
	TalkManager() = default;
	~TalkManager() = default;
	void Init();

	//--------------------Talk
	void SaveTalkData(int referenceId);
	vector<wstring> GetVecTalkData();
	vector<wstring> GetTalkData(int referenceId);


	//--------------------ItemTalk
};