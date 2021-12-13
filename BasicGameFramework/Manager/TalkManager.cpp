#include "TalkManager.h"

#define EXCEPTION "NoData"

void TalkManager::Init()
{
	talkData.emplace(10, vector<wstring>{L"뺵빽한 나무이다.뺵빽한 나무이다.뺵빽한 나무이다.뺵빽한 나무이다.빽한 나무이다.빽한 나무이다.빽한 나무이다."});

}

void TalkManager::SaveTalkData(int referenceId)
{
	vecTalkData = GetTalkData(referenceId);
}

vector<wstring> TalkManager::GetVecTalkData()
{
	return vecTalkData;
}

vector<wstring> TalkManager::GetTalkData(int referenceId)
{
	auto data = talkData.find(referenceId);
	if (data != talkData.end())
	{
		return (data->second);
	}
	vector<wstring> a;
	return a;
}
