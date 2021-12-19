#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <vector>

using namespace std;

class TalkManager : public Singleton<TalkManager>
{
public:
	TalkManager() = default;
	~TalkManager() = default;
	void Init();

	//--------------------Talk
	void SaveTalkData(int referenceId);
	vector<wstring> GetVecTalkData();
	vector<wstring> GetTalkData(int referenceId);


	//--------------------ItemTalk
	void SaveItemTalkData(int referenceId);
	vector<wstring> GetVecItemTalkData();
	vector<wstring> GetItemTalkData(int referenceId);


	//---
	bool GetIsItem();
private:
	unordered_map<int, vector<wstring>> talkData = {};
	unordered_map<int, vector<wstring>> itemTalkData = {};
	vector<wstring> vecTalkData = {};
	bool isItem = false;
};